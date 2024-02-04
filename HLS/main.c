#include "config.h"
#include "sobel_filter.h"

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

	int errors = 0;
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
