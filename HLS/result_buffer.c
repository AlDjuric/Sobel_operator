#include "result_buffer.h"

// Result buffer stores output from FIR-filter (used for verification/validation)
hls_always_run_component component void result_buffer(
	hls_avalon_slave_memory_argument(SAMPLE_SIZE * sizeof(float)) float* result_buffer,
	ihc::stream_in<f_19_5_t>& result_in)
{
	for(int i = 0; i < SAMPLE_SIZE; ++i)
	{
		result_buffer[i] = result_in.read().to_double();
		;
	}
}