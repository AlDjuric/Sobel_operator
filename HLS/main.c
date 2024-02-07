#include "config.h"
#include "sobel_filter.h"
#include "sample_buffer.h"
#include "result_buffer.h"
// Helper function to calculate square root using sqrt_fixed and convert the result
// Sobel filter implementation
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
	f_19_5_t sample_output[SAMPLE_SIZE];
	f_19_5_t sobel_output[SAMPLE_SIZE];
	float results[SAMPLE_SIZE];
	float results_tb[SAMPLE_SIZE];

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

	// Streams
	// in
	ihc::stream_in<f_19_5_t> sobel_in;
	ihc::stream_in<f_19_5_t> result_in;
	// out
	ihc::stream_out<f_19_5_t> sample_out;
	ihc::stream_out<f_19_5_t> sobel_out;
	ihc::stream_out<f_19_5_t> result_out;

	// sample_buffer
	sample_buffer(image_data, sample_out);
	for(int i = 0; i < SAMPLE_SIZE; ++i)
	{
		sample_output[i] = sample_out.read(); // Populate the output array
	}

	// Sobel filter
	for(int i = 0; i < SAMPLE_SIZE; ++i)
	{
		sobel_in.write(sample_output[i]); // Populate the input stream
	}

	for(int i = 0; i < SAMPLE_SIZE; ++i)
	{
		ihc_hls_enqueue_noret(
			&sobel_filter, sobel_in, sobel_out); // Call the sobel_filter
	}
	ihc_hls_component_run_all(sobel_filter);     // Wait for the sobel_filter to finish

	for(int i = 0; i < SAMPLE_SIZE; ++i)
	{
		sobel_output[i] = sobel_out.read(); // read the output array
	}

	// Sobel end

	// result_buffer
	for(int i = 0; i < SAMPLE_SIZE; ++i)
	{
		result_in.write(sobel_output[i]); // Populate the input stream
	}
	ihc_hls_enqueue_noret(&result_buffer, results, result_in); // Call the result_buffer
	ihc_hls_component_run_all(result_buffer); // Wait for the result_buffer to finish

	// call verify function
	sobel_filter_tb(image_data, results_tb);

	int errors      = 0;
	float tolerance = 0.001; // Adjust the tolerance value as needed

	for(int i = 0; i < (HEIGHT - 2) * (WIDTH - 2); ++i)
	{
		float expected = expected_result[i];
		float result   = results_tb[i]; // Use results_tb for the reference

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