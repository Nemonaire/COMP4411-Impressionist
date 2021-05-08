#include "ultilities.h"

double conv2d(int size, const double* src, const double* kernel)
{
	double rst = 0.0f;
	for (int i = 0; i < size * size; ++i)
		rst += src[i] * kernel[i];
	return rst;
}

double rgb2g(uint8_t r, uint8_t g, uint8_t b)
{
	return 0.299 * r + 0.587 * g + 0.114 * b;
}

double rgb2g(const uint8_t* prgb)
{
	return rgb2g(prgb[0], prgb[1], prgb[2]);
}

void rgb3c(const void* rgb, int len, int size, void* r, void* g, void* b)
{
	const char* prgb = (char*)rgb;
	char* pr = (char*)r;
	char* pg = (char*)g;
	char* pb = (char*)b;
	for (int i = 0; i < len; ++i)
	{
		memcpy(pr + i * size, prgb + 3 * i * size, size);
		memcpy(pg + i * size, prgb + 3 * i * size + size, size);
		memcpy(pb + i * size, prgb + 3 * i * size + size + size, size);
	}
}

void ub2d(unsigned char* src, double* dst, size_t size)
{
	for (int i = 0; i < size; ++i)
		dst[i] = (double)src[i] / 255.0f;
}

