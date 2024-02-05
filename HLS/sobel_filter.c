#include "sobel_filter.h"

// It still uses a lot of ALUTs , RAMs FFs and DSP.
// At least, we got it down to under 60% on most of the stuff from the 120+%
// fix: shift registers are used in this function.

// Initialize the buffer with the first two rows of the image
void initialize_buffer(float buffer[3][WIDTH], const float image[HEIGHT][WIDTH])
{
#pragma unroll
	for(int i = 0; i < 2; ++i)
	{
#pragma unroll
		for(int j = 0; j < WIDTH; ++j)
		{
			buffer[i][j] = image[i][j];
		}
	}
}

// Load a new row into the buffer
void load_new_row(float buffer[3][WIDTH], const float image[HEIGHT][WIDTH], int row)
{
#pragma unroll
	for(int j = 0; j < WIDTH; ++j)
	{
		buffer[2][j] = image[row][j];
	}
}

// Shift the buffer up by one row
void shift_buffer(float buffer[3][WIDTH])
{
#pragma unroll
	for(int j = 0; j < WIDTH; ++j)
	{
		buffer[0][j] = buffer[1][j];
		buffer[1][j] = buffer[2][j];
	}
}

// Compute the sum of the products of the kernel and the buffer
float compute_kernel_sum(float buffer[3][WIDTH], int x, const float kernel[3][3])
{
	float sum = 0;
#pragma unroll
	for(int ki = -1; ki <= 1; ++ki)
	{
#pragma unroll
		for(int kj = -1; kj <= 1; ++kj)
		{
			float pixel = buffer[ki + 1][x + kj];
			sum += pixel * kernel[ki + 1][kj + 1];
		}
	}
	return sum;
}

// Sobel filter implementation
hls_avalon_slave_component component void
	sobel_filter(float image[HEIGHT][WIDTH], float result[(HEIGHT - 2) * (WIDTH - 2)])
{
	// Temporary fixed-point image buffer
	float f_image[HEIGHT][WIDTH];

// Convert input image from float to fixed-point
#pragma unroll
	for(int i = 0; i < HEIGHT; ++i)
	{
#pragma unroll
		for(int j = 0; j < WIDTH; ++j)
		{
			f_image[i][j] = image[i][j]; // Assuming implicit conversion is available
		}
	}

	// Buffer for the sliding window technique
	float buffer[3][WIDTH];

	// Initialize buffer with the first two rows of the fixed-point image
	initialize_buffer(buffer, f_image);

	/**
	 * This code here takes a lot of resources,  the multiplication and the square root
	 * are the main culprits but gx_sum and gy_sum should be able to be optimized
	 * to use less resources.
	 */

	// Process each pixel with the Sobel operator
	for(int i = 1; i < HEIGHT - 1; ++i)
	{
		// Load a new row into the buffer
		load_new_row(buffer, f_image, i + 1);

		for(int j = 1; j < WIDTH - 1; ++j)
		{
			float gx_sum = compute_kernel_sum(buffer, j, Gx);
			float gy_sum = compute_kernel_sum(buffer, j, Gy);

			result[(i - 1) * (WIDTH - 2) + (j - 1)] =
				sqrt(gx_sum * gx_sum + gy_sum * gy_sum);
		}

		// Shift the buffer up by one row for the next iteration
		shift_buffer(buffer);
	}
}
