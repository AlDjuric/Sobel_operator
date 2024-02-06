#include "sobel_filter.h"

// Sobel filter implementation
hls_always_run_component component void
	sobel_filter(ihc::stream_in<f_19_5_t>& image, ihc::stream_out<f_19_5_t>& result)
{
	for(int i = 1; i < HEIGHT - 1; ++i)
	{
		for(int j = 1; j < WIDTH - 1; ++j)
		{
			f_19_5_t gx_sum = 0, gy_sum = 0;

			// Compute the gradient in X and Y direction
			for(int ki = -1; ki <= 1; ++ki)
			{
				for(int kj = -1; kj <= 1; ++kj)
				{
					f_19_5_t pixel = image.read();
					// Ensure consistent types
					gx_sum += pixel * static_cast<f_19_5_t>(Gx[ki + 1][kj + 1]);
					gy_sum += pixel * static_cast<f_19_5_t>(Gy[ki + 1][kj + 1]);
				}
			}

			// Calculate the magnitude of gradients

			result.write(sqrt_fixed<19, 5, true>(gx_sum * gx_sum + gy_sum * gy_sum));
		}
	}
}