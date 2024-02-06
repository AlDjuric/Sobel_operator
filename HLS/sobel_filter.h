#ifndef SOBEL_FILTER_H
#define SOBEL_FILTER_H

#include "config.h"

hls_always_run_component component void
	sobel_filter(ihc::stream_in<f_19_5_t>& image, ihc::stream_out<f_19_5_t>& result);

#endif