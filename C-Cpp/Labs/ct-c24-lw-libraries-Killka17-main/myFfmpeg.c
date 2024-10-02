#include "myFfmpeg.h"

#include "myFftw.h"
#include "return_codes.h"

int audio_file_constructor(AudioFile *file)
{
	file->pFormatContext = avformat_alloc_context();
	file->codecContext = NULL;
	file->frame = av_frame_alloc();
	file->packet = av_packet_alloc();
	if (!file->frame || !file->packet || !file->pFormatContext)
	{
		fprintf(stderr, "Failed to allocate memory\n");
		return (ERROR_NOTENOUGH_MEMORY);
	}
	return SUCCESS;
}

int abstract_read(AudioFile *file, char **string)
{
	if (!file->pFormatContext)
	{
		fprintf(stderr, "ERROR could not allocate memory for Format Context");
		return ERROR_NOTENOUGH_MEMORY;
	}

	if (avformat_open_input(&file->pFormatContext, *string, NULL, NULL) != 0)
	{
		fprintf(stderr, "ERROR could not open file");
		return ERROR_CANNOT_OPEN_FILE;
	}

	if (avformat_find_stream_info(file->pFormatContext, NULL) < 0)
	{
		fprintf(stderr, "ERROR could not get the stream info");
		return ERROR_DATA_INVALID;
	}

	int audio_stream_idx = av_find_best_stream(file->pFormatContext, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
	if (audio_stream_idx < 0)
	{
		fprintf(stderr, "ERROR could not find audio stream in the file");
		return ERROR_FORMAT_INVALID;
	}

	file->codec = avcodec_find_decoder(file->pFormatContext->streams[audio_stream_idx]->codecpar->codec_id);
	if (!file->codec)
	{
		fprintf(stderr, "Failed to find codec");
		return ERROR_UNSUPPORTED;
	}

	file->codecContext = avcodec_alloc_context3(file->codec);
	if (!file->codecContext)
	{
		fprintf(stderr, "Failed to allocate codec context");
		return ERROR_NOTENOUGH_MEMORY;
	}

	if (avcodec_parameters_to_context(file->codecContext, file->pFormatContext->streams[audio_stream_idx]->codecpar) < 0)
	{
		fprintf(stderr, "Failed to copy codec parameters to codec context");
		return ERROR_DATA_INVALID;
	}

	if (avcodec_open2(file->codecContext, file->codec, NULL) < 0)
	{
		fprintf(stderr, "Failed to open codec");
		return ERROR_CANNOT_OPEN_FILE;
	}
	file->bestStreamIndex = audio_stream_idx;
	return SUCCESS;
}

int read_one_file(char **pString)
{
	AudioFile file;
	CHECK_RESULT(audio_file_constructor(&file));
	CHECK_RESULT(abstract_read(&file, &pString[1]));
	if (file.codecContext->ch_layout.nb_channels != 2)
	{
		fprintf(stderr, "Invalid chanels count");
		return (ERROR_FORMAT_INVALID);
	}
	DataArr arr1;
	DataArr arr2;
	CHECK_RESULT(arr_constructor(&arr1));
	CHECK_RESULT(arr_constructor(&arr2));
	CHECK_RESULT(take_samples(&arr1, &file, file.bestStreamIndex, 0));
	CHECK_RESULT(take_samples(&arr2, &file, file.bestStreamIndex, 1));
	int result;
	CHECK_RESULT(cross_correlation(&arr1, &arr2, &result));
	printf("delta: %i samples\nsample rate: %i Hz\ndelta time: %i ms\n",
		   result,
		   file.codecContext->sample_rate,
		   (result * 1000) / file.codecContext->sample_rate);
	av_frame_unref(file.frame);
	return SUCCESS;
}

int read_two_files(char **pString)
{
	AudioFile file1;
	AudioFile file2;
	CHECK_RESULT(audio_file_constructor(&file1));
	CHECK_RESULT(audio_file_constructor(&file2));
	CHECK_RESULT(abstract_read(&file1, &pString[1]));
	CHECK_RESULT(abstract_read(&file2, &pString[2]));
	if (file1.codecContext->sample_rate != file2.codecContext->sample_rate)
		return ERROR_UNSUPPORTED;
	DataArr arr1;
	DataArr arr2;
	CHECK_RESULT(arr_constructor(&arr1));
	CHECK_RESULT(arr_constructor(&arr2));
	CHECK_RESULT(take_samples(&arr1, &file1, file1.bestStreamIndex, 0));
	CHECK_RESULT(take_samples(&arr2, &file2, file2.bestStreamIndex, 0));
	int result;
	CHECK_RESULT(cross_correlation(&arr1, &arr2, &result));
	printf("delta: %i samples\nsample rate: %i Hz\ndelta time: %i ms\n",
		   result,
		   file1.codecContext->sample_rate,
		   (result * 1000) / file1.codecContext->sample_rate);
	av_frame_unref(file1.frame);
	av_frame_unref(file2.frame);
	return SUCCESS;
}

int take_samples(DataArr *pDouble, AudioFile *ptr, int ind, int dataNum)
{
	int counter = 0;
	while (av_read_frame(ptr->pFormatContext, ptr->packet) == 0)
	{
		if (ptr->packet->stream_index == ind)
		{
			int ret = avcodec_send_packet(ptr->codecContext, ptr->packet);
			if (ret < 0)
			{
				fprintf(stderr, "Error sending a packet for decoding\n");
				return (ERROR_DATA_INVALID);
			}

			ret = avcodec_receive_frame(ptr->codecContext, ptr->frame);
			while (ret != AVERROR(EAGAIN) && ret != AVERROR_EOF)
			{
				if (ret < 0)
				{
					fprintf(stderr, "Error during decoding\n");
					return (ERROR_DATA_INVALID);
				}
				int count_samples = ptr->frame->nb_samples;

				for (int i = 0; i < count_samples; i++, counter++)
				{
					CHECK_RESULT(push(pDouble, counter, ptr->frame->data[dataNum][i]));
				}
				ret = avcodec_receive_frame(ptr->codecContext, ptr->frame);
			}
		}
		av_packet_unref(ptr->packet);
	}
	return SUCCESS;
}

int push(DataArr *arr1, int counter, double value)
{
	if (counter >= arr1->size)
	{
		int newSize = arr1->size * 2;
		double *new_array = malloc(sizeof(double) * newSize);
		if (!new_array)
		{
			fprintf(stderr, "ERROR: Memory allocation failed when resizing array\n");
			return (ERROR_NOTENOUGH_MEMORY);
		}
		for (int i = 0; i < arr1->size; ++i)
		{
			new_array[i] = arr1->arr[i];
		}
		for (int i = arr1->size; i < newSize; ++i)
		{
			new_array[i] = 0;
		}
		free(arr1->arr);
		arr1->arr = new_array;
		arr1->size = newSize;
	}
	arr1->arr[counter] = value;
	return SUCCESS;
}

int arr_constructor(DataArr *ptr)
{
	ptr->arr = malloc(sizeof(double) * 2);
	if (!ptr->arr)
	{
		fprintf(stderr, "ERROR: Memory allocation failed during array construction\n");
		return (ERROR_NOTENOUGH_MEMORY);
	}
	ptr->size = 2;
	for (int i = 0; i < 2; ++i)
	{
		ptr->arr[i] = 0.0;
	}
	return SUCCESS;
}
