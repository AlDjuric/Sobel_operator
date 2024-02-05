/**
 * @file config.h
 * @author Aleksandar Djuric
 * @brief Configuration file for the Sobel operator
 * @version 0.1
 * @date 2024-02-04
 *
 * @copyright Check the LICENSE file for details
 *
 */

#ifndef CONFIG_H_
#define CONFIG_H_
//**********************//
// includes
//**********************//
#include "HLS/hls.h"
#include "HLS/ac_fixed.h"
// #include "HLS/ac_fixed_math.h"
#include "HLS/Math.h"
#include "stdio.h"

//**********************//
// defines
//**********************//
#define HEIGHT 5
#define WIDTH  5

#define N      110

typedef ac_fixed<19, 5, true> f_19_5_t;
// Adjust the width and integer/fractional bits as needed

//**********************//
// constants
//**********************//
const float tolerance = 1e-5; // Tolerance level

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
//**********************//
#endif