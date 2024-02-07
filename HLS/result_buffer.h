#ifndef RESULT_BUFFER_H
#define RESULT_BUFFER_H

#include "config.h"

hls_always_run_component component void result_buffer(
	hls_avalon_slave_memory_argument(SAMPLE_SIZE * sizeof(float)) float* result_buffer,
	ihc::stream_in<f_19_5_t>& result_in);

#endif // RESULT_BUFFER_H