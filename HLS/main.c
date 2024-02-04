#include <stdio.h>  // for printf
#include <stdlib.h> // for abs
#include <math.h>   // for sqrt

#define HEIGHT 5
#define WIDTH  5

component void
	sobel_filter(float sample[HEIGHT][WIDTH], float result[(HEIGHT - 2) * (WIDTH - 2)])
{
	float Gx[3][3] = {
		{-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
	float Gy[3][3] = {
		{-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

	for(int i = 1; i < HEIGHT - 1; ++i)
	{
		for(int j = 1; j < WIDTH - 1; ++j)
		{
			float Gx_sum = 0;
			float Gy_sum = 0;
			for(int k = -1; k <= 1; ++k)
			{
				for(int l = -1; l <= 1; ++l)
				{
					Gx_sum += sample[i + k][j + l] * Gx[k + 1][l + 1];
					Gy_sum += sample[i + k][j + l] * Gy[k + 1][l + 1];
				}
			}
			result[(i - 1) * (WIDTH - 2) + (j - 1)] =
				sqrt(Gx_sum * Gx_sum + Gy_sum * Gy_sum);
		}
	}
}

int main()
{
	float image[HEIGHT][WIDTH] = {
		{100, 100, 100, 100, 100},
		{100,  50,  50,  50, 100},
		{100,  50,  50,  50, 100},
		{100,  50,  50,  50, 100},
		{100, 100, 100, 100, 100}
    };

	// Adjusting expected_result to a 1D array to match the output format
	float expected_result[(HEIGHT - 2) * (WIDTH - 2)] = {
		212.13203436, 200.00000000, 212.13203436, 200.00000000, 0.00000000,
		200.00000000, 212.13203436, 200.00000000, 212.13203436};

	float memory_tb[(HEIGHT - 2) * (WIDTH - 2)];

	sobel_filter(image, memory_tb);

	int errors      = 0;
	float tolerance = 1e-5; // tolerance for floating point comparison
	for(int i = 0; i < (HEIGHT - 2) * (WIDTH - 2); ++i)
	{
		float expected = expected_result[i];
		float result   = memory_tb[i];
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
