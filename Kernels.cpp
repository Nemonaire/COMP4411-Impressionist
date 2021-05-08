#include "Kernels.h"
#include "ultilities.h"
#include <string>

Kernel::Kernel(int t)
{
	switch (t)
	{
		case KRN_AVG:
		{
			double tmp[9] = {
				1.0 / 9,	1.0 / 9,	1.0 / 9,
				1.0 / 9,	1.0 / 9,	1.0 / 9,
				1.0 / 9,	1.0 / 9,	1.0 / 9,
			};
			data = new double[9];
			size = 3;
			memcpy(data, tmp, sizeof(tmp));
			break;
		}
		case KRN_SHARP:
		{
			double tmp[9] = {
				-1.0,	-1.0,	-1.0,
				-1.0,	9.0,	-1.0,
				-1.0,	-1.0,	-1.0,
			};
			data = new double[9];
			size = 3;
			memcpy(data, tmp, sizeof(tmp));
			break;
		}
		case KRN_SOBEL_X:
		{
			double tmp[9] = {
				1.0,	0.0,	-1.0,
				2.0,	0.0,	-2.0,
				1.0,	0.0,	-1.0,
			};
			data = new double[9];
			size = 3;
			memcpy(data, tmp, sizeof(tmp));
			break;
		}
		case KRN_SOBEL_Y:
		{
			double tmp[9] = {
				1.0,	2.0,	1.0,
				0.0,	0.0,	0.0,
				-1.0,	-2.0,	-1.0,
			};
			data = new double[9];
			size = 3;
			memcpy(data, tmp, sizeof(tmp));
			break;
		}
		default:
			break;
	}
}

Kernel::~Kernel()
{
	delete [] data;
}

double Kernel::conv(double* src)
{
	return conv2d(size, src, data);
}

size_t Kernel::getSize() { return size; }
