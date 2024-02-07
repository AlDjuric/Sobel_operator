# Sobel Filter Implementation in HLS

## Overview

This project presents an implementation of the Sobel filter using High-Level Synthesis (HLS). The Sobel filter is a popular edge detection algorithm used in image processing to highlight edges and contours within images. Our implementation focuses on achieving efficient processing suitable for real-time applications. Future updates will aim to enhance this project with real-time image processing capabilities.

---

## Developed and tested on

- DE-10 Lite board.
- Quartus 18.1 and Nios II.

---

## Features

- Sobel edge detection algorithm implemented in HLS.
- Efficient resource utilization.

---

## Planned Features

- **Real-Time Image Processing**: Future versions will aim to process images in real-time, allowing for dynamic edge detection in video streams or high-speed camera inputs.
- **Performance Optimization**: We plan to refine the algorithm and its implementation to ensure higher performance, focusing on faster processing times and reduced resource consumption on FPGA devices.
- **Support for Additional Edge Detection Algorithms**: Beyond the Sobel filter, future updates could include implementations of other edge detection algorithms like Canny, Prewitt, and Scharr, providing users with a suite of options for their specific needs.
- **Integration with Machine Learning Models**: Exploring the integration of the Sobel filter output with machine learning models for advanced image processing tasks, such as object detection and image classification.

---

## Requirements

- Intel Quartus HLS (current version runs on Quartus 18.1, you will need to install Visual studio 2010 for toolchain).
- A suitable FPGA board for deployment (optional for simulation purposes).
- Basic understanding of HLS and edge detection algorithms.

---

## Installation

To get started with the Sobel filter HLS implementation, clone this repository to your local machine using the following command:

```bash
git clone https://github.com/AlDjuric/Sobel_operator.git
```

Check out the examples folder of a simple implementation of the algorithm.

---
