#ifndef LAB2_MYFFMPEG_H
#define LAB2_MYFFMPEG_H

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

#define CHECK_RESULT(res)                                                                                              \
	if ((res) != SUCCESS)                                                                                              \
	return (res)

typedef struct
{
	AVFormatContext *pFormatContext;
	const AVCodec *codec;
	AVCodecContext *codecContext;
	AVPacket *packet;
	AVFrame *frame;
	int bestStreamIndex;
} AudioFile;

typedef struct
{
	double *arr;
	int size;
} DataArr;

int abstract_read(AudioFile *ptr, char **pstring);
int take_samples(DataArr *pDouble, AudioFile *ptr, int ind, int i);
int arr_constructor(DataArr *ptr);
int push(DataArr *array, int counter, double value);
int read_one_file(char **pString);
int read_two_files(char **pString);
int audio_file_constructor(AudioFile *file);

#endif
