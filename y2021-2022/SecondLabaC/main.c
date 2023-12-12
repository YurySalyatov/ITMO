#include "return_codes.h"
#include <stdio.h>
#include <stdlib.h>

#if defined(ZLIB)
	#include <zlib.h>
#elif defined(LIBDEFLATE)
	#include <libdeflate.h>
#elif defined(ISAL)
	#include <include/igzip_lib.h>
#else
	#error "You don't include any supported libs as zlib, isal or libdeflate, please chek"
#endif
int paeth_four_filtere(int a, int b, int c)
{
	int num = a + b - c;
	int nbuma = abs(num - a);
	int numb = abs(num - b);
	int numc = abs(num - c);
	if ((nbuma <= numb) && (nbuma <= numc))
	{
		return a;
	}
	else if (numb <= numc)
	{
		return b;
	}
	else
	{
		return c;
	}
}
unsigned char *unpackIDATs(unsigned char *IDATs, size_t *lenIDATs, unsigned int color, size_t height, size_t width, int *error)
{
	int col;
	if (color == 0)
	{
		col = 1;
	}
	else if (color == 2)
	{
		col = 3;
	}
	else
	{
		*error = ERROR_INVALID_DATA;
		fprintf(stderr, "Unsupported type of color\n");
		free(IDATs);
		return NULL;
	}
	unsigned long rawLen = (width + 1) * height * col + 100;
	unsigned char *rawIDAT = malloc(rawLen);
	if (rawIDAT == NULL)
	{
		*error = ERROR_MEMORY;
		fprintf(stderr, "Not enough memory\n");
		free(IDATs);
		return NULL;
	}
#ifdef ZLIB
	int er = uncompress(rawIDAT, &rawLen, IDATs, *lenIDATs);
	if (er != Z_OK)
	{
		*error = ERROR_INVALID_DATA;
		fprintf(stderr, "can't unpuck file data\n");
		free(rawIDAT);
		free(IDATs);
		return NULL;
	}
	if (rawLen != col * height * width + height)
	{
		fprintf(stderr, "Maybe your IDATs chunks unfollowing one by one\n");
		*error = ERROR_INVALID_DATA;
		return NULL;
	}
	// can't chek other libs with this condition
#endif
#ifdef ISAL
	struct inflate_state dcrt;
	isal_inflate_init(&dcrt);
	dcrt.next_out = rawIDAT;
	dcrt.avail_out = rawLen;
	dcrt.next_in = IDATs;
	dcrt.avail_in = lenIDATs;
	dcrt.crc_flag = IGZIP_ZLIB;
	isal_inflate(&dcrt);
#endif
#ifdef LIBDEFLATE
	&struct libdeflate_decompressor *dcpr = libdeflate_alloc_decompressor();
	size_t a = 0;
	libdeflate_zlib_decompress(dcpr, IDATs, (size_t)&rawLen, rawIDAT, (size_t)rawLen, &a);
	libdeflate_free_decompressor(dcpr);
#endif
	free(IDATs);
	unsigned char *finalIDATs = malloc(col * height * width);
	if (finalIDATs == NULL)
	{
		*error = ERROR_MEMORY;
		fprintf(stderr, "Not enough memory\n");
		free(rawIDAT);
		return NULL;
	}
	size_t index = 0;
	for (size_t i = 0; i < height; i++)
	{
		size_t ind_filt = i * (width * col + 1);
		for (int j = 1; j <= width * col; j++)
		{
			unsigned char ufilt = rawIDAT[ind_filt + j];
			unsigned char pred = (j - col - 1 < 0 ? 0 : finalIDATs[index - col]);
			unsigned char pred_str = (i == 0 ? 0 : finalIDATs[index - width * col]);
			int pred_str_pred = (((j - col - 1 < 0) || (i == 0)) ? 0 : finalIDATs[index - width * col - col]);
			if (rawIDAT[ind_filt] == 0)
			{
				// do nothing
			}
			else if (rawIDAT[ind_filt] == 1)
			{
				ufilt += pred;
			}
			else if (rawIDAT[ind_filt] == 2)
			{
				ufilt += pred_str;
			}
			else if (rawIDAT[ind_filt] == 3)
			{
				ufilt += (pred + pred_str) / 2;
			}
			else if (rawIDAT[ind_filt] == 4)
			{
				ufilt += paeth_four_filtere(pred, pred_str, pred_str_pred);
			}
			else
			{
				fprintf(stderr, "Unsupoted type of filter\n");
				free(rawIDAT);
				free(finalIDATs);
				*error = ERROR_INVALID_DATA;
				return NULL;
			}
			finalIDATs[index++] = ufilt % 256;
		}
	}
	free(rawIDAT);
	return finalIDATs;
}
int comper_char_array(const unsigned char *first, const unsigned char *second, const int n)
{
	for (int i = 0; i < n; i++)
	{
		if (first[i] != second[i])
		{
			return 0;
		}
	}
	return 1;
}
void chek_header(FILE *filein, int *error)
{
	unsigned char header[8];
	const unsigned char expected[] = { 137, 80, 78, 71, 13, 10, 26, 10 };
	if (fread(header, sizeof(*header), 8, filein) < 8)
	{
		fprintf(stderr, "It's too few bytes for png\n");
		*error = ERROR_INVALID_DATA;
		return;
	}
	if (!comper_char_array(&header[0], &expected[0], 8))
	{
		fprintf(stderr, "it's not a png file\n");
		*error = ERROR_INVALID_DATA;
	}
}
unsigned int parse_chunk_len(FILE *filein, int *error)
{
	unsigned char lengths[4];
	int test = fread(lengths, 1, 4, filein);
	if (test == 0)
	{
		return -1;
	}
	if (test < 4)
	{
		fprintf(stderr, "Too few bytes for new chunk length, please chek your file\n");
		*error = ERROR_INVALID_DATA;
		return -1;
	}
	unsigned int length = 0;
	for (int i = 0; i < 4; i++)
	{
		length *= 256;
		length += lengths[i];
	}
	return length;
}
void parse_chunk_name(FILE *filein, int *error, unsigned char *name)
{
	if (fread(name, 1, 4, filein) < 4)
	{
		fprintf(stderr, "Expecterd name for new chunk, but couldn't read, please chek your file\n");
		*error = ERROR_INVALID_DATA;
	}
}
void parse_chunk_data(FILE *filein, int *error, unsigned char *data, unsigned int length)
{
	if (fread(data, 1, length, filein) < length)
	{
		fprintf(stderr, "Expecterd data of new chunk, but couldn't read, please chek your file\n");
		*error = ERROR_INVALID_DATA;
	}
}
void parse_chunk_CRC(FILE *filein, int *error)
{
	unsigned char CRC[4];
	if (fread(CRC, 1, 4, filein) < 4)
	{
		fprintf(stderr, "Expecterd CRC of new chunk, but couldn't read, please chek your file\n");
		*error = ERROR_INVALID_DATA;
	}
	int crc = 0;
	for (int i = 0; i < 4; i++)
	{
		crc *= 256;
		crc += CRC[i];
	}
}
unsigned long read_from_arr(const unsigned char *buffer, int i, int sz)
{
	unsigned long res = 0;
	for (int j = i; j < i + sz; j++)
	{
		res = res * 256 + (unsigned long)buffer[j];
	}
	return res;
}
void print_in_file(unsigned char *IDATA, FILE *fileout, unsigned int width, unsigned int height, unsigned int color)
{
	int k, type;
	if (color == 0)
	{
		k = 1;
		type = 5;
	}
	else if (color == 2)
	{
		k = 3;
		type = 6;
	}
	fprintf(fileout, "P%d\n%d %d\n255\n", type, width, height);
	fwrite(IDATA, sizeof(unsigned char), width * height * k, fileout);
}
int main(int arg, char *args[])
{
	if (arg != 3)
	{
		fprintf(stderr, "Many or less arguments were given");
		return ERROR_INVALID_PARAMETER;
	}
	int error = 0;
	int *flag = &error;
	FILE *filein, *fileout;
	filein = fopen(args[1], "rb");
	if (filein == NULL)
	{
		fprintf(stderr, "Couldn't open input file %s", args[1]);
		return ERROR_FILE_EXISTS;
	}
	chek_header(filein, flag);
	if (error)
	{
		fclose(filein);
		fprintf(stderr, "It's not a png file\n");
		return error;
	}
	int bool = 0;
	unsigned int IHDR_len = parse_chunk_len(filein, flag);
	if (IHDR_len == -1)
	{
		fclose(filein);
		fprintf(stderr, "Nothing find after png header\n");
		return ERROR_INVALID_DATA;
	}
	unsigned char *IHDR_name = malloc(4);
	parse_chunk_name(filein, flag, IHDR_name);
	if (error)
	{
		fclose(filein);
		free(IHDR_name);
		fprintf(stderr, "Something wrong in your file\n");
		return error;
	}
	const unsigned char IHDR[4] = { 'I', 'H', 'D', 'R' };
	if (!comper_char_array(&IHDR[0], IHDR_name, 4))
	{
		fclose(filein);
		free(IHDR_name);
		fprintf(stderr, "First chunk is not IHDR\n");
		return ERROR_INVALID_DATA;
	}
	unsigned char *IHDR_data = malloc(IHDR_len);
	if (!IHDR_data)
	{
		free(IHDR_name);
		fclose(filein);
		fprintf(stderr, "Not enough memory");
		return ERROR_MEMORY;
	}
	parse_chunk_data(filein, flag, IHDR_data, IHDR_len);
	if (error)
	{
		free(IHDR_name);
		fclose(filein);
		free(IHDR_data);
		fprintf(stderr, "can't get IHDR data");
		return error;
	}
	parse_chunk_CRC(filein, flag);
	if (error)
	{
		free(IHDR_data);
		free(IHDR_name);
		fclose(filein);
		fprintf(stderr, "something in your file");
		return error;
	}
	const unsigned int width = read_from_arr(IHDR_data, 0, 4);
	const unsigned int height = read_from_arr(IHDR_data, 4, 4);
	const unsigned int bit_depth = read_from_arr(IHDR_data, 8, 1);
	const unsigned int color = read_from_arr(IHDR_data, 9, 1);
	free(IHDR_data);
	free(IHDR_name);
	const unsigned char IDAT[4] = { 'I', 'D', 'A', 'T' };
	const unsigned char IEND[4] = { 'I', 'E', 'N', 'D' };
	size_t lengthIDATs = 0;
	unsigned char *IDATA = malloc(lengthIDATs);
	int find_idata = 0;
	int end_iadata = 0;
	while (1)
	{
		unsigned int len = parse_chunk_len(filein, flag);
		if (error)
		{
			free(IDATA);
			fclose(filein);
			fprintf(stderr, "something wrong in your file\n");
			return error;
		}
		if (len == -1)
		{
			fclose(filein);
			free(IDATA);
			fprintf(stderr, "can't find any other chunk\n");
			return ERROR_INVALID_DATA;
		}
		unsigned char *name = malloc(4);
		parse_chunk_name(filein, flag, name);
		if (error)
		{
			fclose(filein);
			free(name);
			free(IDATA);
			fprintf(stderr, "something wrong in your file\n");
			return error;
		}
		if (comper_char_array(&IEND[0], name, 4))
		{
			if (!find_idata)
			{
				fprintf(stderr, "find IEND, but not find IDAT\n");
				fclose(filein);
				free(name);
				free(IDATA);
				return ERROR_INVALID_DATA;
			}
			parse_chunk_CRC(filein, flag);
			if (error)
			{
				fprintf(stderr, "something wrong in your file\n");
				fclose(filein);
				free(name);
				free(IDATA);
				return ERROR_INVALID_DATA;
			}
			parse_chunk_len(filein, flag);
			if (len > -1)
			{
				fprintf(stderr, "expected end of the file\n");
				fclose(filein);
				free(name);
				free(IDATA);
				return ERROR_INVALID_DATA;
			}
			break;
		}
		else if (comper_char_array(&IDAT[0], name, 4))
		{
			find_idata = 1;
			if (end_iadata)
			{
				fprintf(stderr, "IDAT are separated in your file\n");
				fclose(filein);
				free(name);
				free(IDATA);
				return ERROR_INVALID_DATA;
			}
			unsigned char *data = malloc(len);
			if (!data)
			{
				fprintf(stderr, "not enough memory\n");
				fclose(filein);
				free(name);
				free(IDATA);
				return ERROR_MEMORY;
			}
			parse_chunk_data(filein, flag, data, len);
			if (error)
			{
				fprintf(stderr, "something wrong in your file\n");
				fclose(filein);
				free(name);
				free(IDATA);
				free(data);
				return error;
			}
			unsigned char *p = realloc(IDATA, lengthIDATs + len);
			if (!p)
			{
				fprintf(stderr, "not enough memory\n");
				fclose(filein);
				free(name);
				free(IDATA);
				free(data);
				return ERROR_NOT_ENOUGH_MEMORY;
			}
			IDATA = p;
			for (unsigned int i = 0; i < len; i++)
			{
				IDATA[lengthIDATs + i] = data[i];
			}
			lengthIDATs += len;
			free(data);
			parse_chunk_CRC(filein, flag);
			if (error)
			{
				fprintf(stderr, "something wrong in your file\n");
				fclose(filein);
				free(name);
				free(IDATA);
				return error;
			}
		}
		else
		{
			if (find_idata)
			{
				end_iadata = 1;
			}
			unsigned char *data = malloc(len);
			if (!data)
			{
				fprintf(stderr, "not enough memory\n");
				fclose(filein);
				free(name);
				free(IDATA);
				return ERROR_MEMORY;
			}
			parse_chunk_data(filein, flag, data, len);
			if (error)
			{
				fprintf(stderr, "something wrong in your file\n");
				fclose(filein);
				free(name);
				free(IDATA);
				free(data);
				return error;
			}
			free(data);
			parse_chunk_CRC(filein, flag);
			if (error)
			{
				fprintf(stderr, "something wrong in your file\n");
				fclose(filein);
				free(name);
				free(IDATA);
				return error;
			}
		}
		free(name);
	}
	fclose(filein);
	size_t *len = &lengthIDATs;
	IDATA = unpackIDATs(IDATA, len, color, height, width, flag);
	if (error)
	{
		free(IDATA);
		fprintf(stderr, "something has gone wrong while unpacking data\n");
		return error;
	}
	fileout = fopen(args[2], "wb");
	if (fileout == NULL)
	{
		free(IDATA);
		fprintf(stderr, "Couldn't open output file\n");
		return ERROR_FILE_EXISTS;
	}
	print_in_file(IDATA, fileout, width, height, color);
	free(IDATA);
	fclose(fileout);
	return 0;
}