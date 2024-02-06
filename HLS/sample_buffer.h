#ifndef SAMPLE_BUFFER_H
#define SAMPLE_BUFFER_H

#include "config.h"

hls_avalon_slave_component component void sample_buffer(
	hls_avalon_slave_memory_argument(SAMPLE_SIZE * sizeof(float)) float* sample_buffer,
	ihc::stream_out<f_19_5_t>& sample_out);

#endif // SAMPLE_BUFFER_H