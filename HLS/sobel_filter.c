#include "sobel_filter.h"

// Sobel filter
// The input sample is a 2D array of size HEIGHT x WIDTH
// The output result is a 1D array of size (HEIGHT - 2) * (WIDTH - 2)
// The result is the squared magnitude of the gradient
// The magnitude is calculated as the square root of the sum of the squares of the
// horizontal and vertical gradients The horizontal and vertical gradients are calculated
// using the Gx and Gy kernels The Gx and Gy kernels are 3x3 matrices

component void
	sobel_filter(float sample[HEIGHT][WIDTH], float result[(HEIGHT - 2) * (WIDTH - 2)])
{
	float Gx[3][3] = {
		{1, 0, -1},
        {2, 0, -2},
        {1, 0, -1}
    };
	float Gy[3][3] = {
		{ 1,  2,  1},
        { 0,  0,  0},
        {-1, -2, -1}
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
			// Store the squared magnitude instead of the actual magnitude
			result[(i - 1) * (WIDTH - 2) + (j - 1)] =
				sqrt(Gx_sum * Gx_sum + Gy_sum * Gy_sum);
		}
	}
}