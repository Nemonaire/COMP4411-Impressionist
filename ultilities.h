#ifndef ULTILITIES_H
#define ULTILITIES_H

#include <stdint.h>
#include <string>

double conv2d(int size, const double* src, const double* kernel);

double rgb2g(uint8_t r, uint8_t g, uint8_t b);
double rgb2g(const uint8_t* prgb);

void rgb3c(const void* rgb, int len, int size, void* r, void* g, void* b);
void ub2d(unsigned char* src, double* dst, size_t size);
#endif
