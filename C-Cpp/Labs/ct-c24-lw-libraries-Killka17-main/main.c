#include "myFfmpeg.h"
#include "return_codes.h"

#include <stdio.h>

int readData(int argc, char **pString);

int main(int argc, char **argv)
{
	av_log_set_level(AV_LOG_QUIET);
	return readData(argc, argv);
}

int readData(int argc, char **pString)
{
	switch (argc)
	{
	case 2:
	{
		CHECK_RESULT(read_one_file(pString));
		return SUCCESS;
	}
	case 3:
	{
		CHECK_RESULT(read_two_files(pString));
		return SUCCESS;
	}
	default:
	{
		fprintf(stderr, "failed to read files");
		return ERROR_FORMAT_INVALID;
	}
	}
}
