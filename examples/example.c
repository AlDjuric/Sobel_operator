/**
 * @file example.c
 * @author Aleksandar Djuric
 * @date 7 Feb 2024
 * @brief File containing example of how to use the Sobel filter.
 *
 * For more information about the project and the author, please visit:
 * @see https://github.com/AlDjuric
 *
 */

#include <stdio.h>
#include <math.h>
#include <altera_avalon_timer_regs.h>
#include "sample_buffer_driver.h"

// Defines
#define SAMPLE_SIZE 25
#define HEIGHT      5
#define WIDTH       5

// Sobel operator kernels
//**********************//
static const float Gx[3][3] = {
	{-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};
static const float Gy[3][3] = {
	{-1, -2, -1},
    { 0,  0,  0},
    { 1,  2,  1}
};
// Global

// Sobel filter testbench function
void sobel_filter_tb(float* image, float* result)
{
	for(int i = 1; i < HEIGHT - 1; ++i)
	{
		for(int j = 1; j < WIDTH - 1; ++j)
		{
			float gx_sum = 0, gy_sum = 0;

			// Compute the gradient in X and Y direction
			for(int ki = -1; ki <= 1; ++ki)
			{
				for(int kj = -1; kj <= 1; ++kj)
				{
					float pixel = image[(i + ki) * WIDTH + (j + kj)];

					gx_sum += pixel * Gx[ki + 1][kj + 1];
					gy_sum += pixel * Gy[ki + 1][kj + 1];
				}
			}

			// Calculate the magnitude of gradients
			result[(i - 1) * (WIDTH - 2) + (j - 1)] =
				sqrt(gx_sum * gx_sum + gy_sum * gy_sum);
		}
	}
}

int main()
{
	float filter_result[SAMPLE_SIZE];
	float output_comp[SAMPLE_SIZE];

	// Sample buffer
	float image[HEIGHT][WIDTH] = {
		{100, 100, 100, 100, 100},
		{100,  50,  50,  50, 100},
		{100,  50,  50,  50, 100},
		{100,  50,  50,  50, 100},
		{100, 100, 100, 100, 100}
    };

	// Convert 2D array to 1D array
	float image_data[SAMPLE_SIZE];
	for(int i = 0; i < HEIGHT; ++i)
	{
		for(int j = 0; j < WIDTH; ++j)
		{
			image_data[i * WIDTH + j] = image[i][j];
		}
	}

	float expected_result[(HEIGHT - 2) * (WIDTH - 2)] = {
		212.13203436, 200.00000000, 212.13203436, 200.00000000, 0.00000000,
		200.00000000, 212.13203436, 200.00000000, 212.13203436};

	// Load samples in local memory (sample buffer)
	for(int i = 0; i < SAMPLE_SIZE; i++)
	{
		sample_memory_write((i << 2), *(alt_32*)(&image_data[i]));
	}

	// Disable interrupt and clear interrupt status register
	sample_disable_interrupt();
	sample_clear_done_status();

	// Call sample buffer
	while(sample_busy())
	{
	}
	sample_start();
	while(!(sample_done()))
	{
	}

	// Read Result from local memory (result buffer)
	for(int i = 0; i < SAMPLE_SIZE; i++)
	{
		*(alt_32*)(&output_comp[i]) = result_memory_read(i << 2);
	}

	/**
	 * @brief Margin of error
	 *
	 */
	// call verify function
	sobel_filter_tb(image_data, filter_result);

	//**************************************************//
	// Verify the results
	//**************************************************//

	int errors      = 0;
	float tolerance = 0.001; // Adjust the tolerance value as needed

	for(int i = 0; i < (HEIGHT - 2) * (WIDTH - 2); ++i)
	{
		float expected = expected_result[i];
		float result   = filter_result[i]; // Use results_tb for the reference

		if(fabs(result - expected) > tolerance)
		{
			printf("Index %d: Expected %f, got %f - FAIL\n", i, expected, result);
			errors++;
		}
		else
		{
			printf("Index %d: Expected %f, got %f - PASS\n", i, expected, result);
		}
	}

	if(errors == 0)
	{
		printf("Overall result: Sobel filter test PASSED.\n");
	}
	else
	{
		printf("Overall result: Sobel filter test FAILED with %d errors.\n", errors);
	}

	return 0;
}