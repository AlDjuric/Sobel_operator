#ifndef SOBEL_FILTER_H
#define SOBEL_FILTER_H

#include "config.h"

hls_avalon_slave_component component void
	sobel_filter(float image[HEIGHT][WIDTH], float result[(HEIGHT - 2) * (WIDTH - 2)]);
#endif