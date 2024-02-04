#ifndef SOBEL_FILTER_H
#define SOBEL_FILTER_H

#include "config.h"

component void
	sobel_filter(float sample[HEIGHT][WIDTH], float result[(HEIGHT - 2) * (WIDTH - 2)]);

#endif