#ifndef KERNELS_H
#define KERNELS_H

enum
{
	KRN_AVG = 0,
	KRN_SHARP,
	NUM_KRN_TYPE,

	KRN_SOBEL_X,
	KRN_SOBEL_Y,
};

class Kernel
{
	double* data;
	size_t	size;
public:
	Kernel(int t);
	double conv(double* src);
	size_t getSize();
	~Kernel();
};

#endif