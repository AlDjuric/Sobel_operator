#include "sample_buffer.h"

// Sample buffer supplies input to FIR-filter (used for verification/validation)
hls_avalon_slave_component component void sample_buffer(
	hls_avalon_slave_memory_argument(SAMPLE_SIZE * sizeof(float)) float* sample_buffer,
	ihc::stream_out<f_19_5_t>& sample_out)
{
	for(int i = 0; i < SAMPLE_SIZE; ++i)
	{
		sample_out.write(sample_buffer[i]);
	}
}