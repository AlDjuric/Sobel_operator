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

// includes
#include "HLS/hls.h"
#include "HLS/ac_fixed.h"
#include "HLS/ac_fixed_math.h"
#include "HLS/Math.h"

#include "stdio.h"

// defines
#define HEIGHT 5
#define WIDTH  5

// typedefs
typedef ac_fixed<8, 4, false> fixed_8_4_f;

// constants
const float tolerance = 1e-5; // Tolerance level

#endif