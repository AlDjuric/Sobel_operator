/**
 * @file sample_buffer_driver.h
 * @author Aleksandar Djuric
 * @date 7 Feb 2024
 * @brief  Sample buffer driver for the De-10 lite board
 * For more information about the project and the author, please visit:
 * @see https://github.com/AlDjuric
 *
 */

#ifndef SAMPLE_BUFFER_H_INCLUDED
#define SAMPLE_BUFFER_H_INCLUDED

#include "SAMPLE_BUFFER_csr.h"
#include "sobel_filter_csr.h"
//-----------------------------------------------------------------
// Read and write macros for the component

#define sample_read(offset) \
	IORD_32DIRECT(SAMPLE_BUFFER_SAMPLE_BUFFER_INTERNAL_INST_AVS_CRA_BASE, offset)
#define sample_write(offset, data) \
	IOWR_32DIRECT(SAMPLE_BUFFER_SAMPLE_BUFFER_INTERNAL_INST_AVS_CRA_BASE, offset, data)

//-----------------------------------------------------------------
// Read and write macros for component memory
//-----------------------------------------------------------------

#define result_memory_read(offset) \
	IORD_32DIRECT(RESULT_BUFFER_RESULT_BUFFER_INTERNAL_INST_BASE, offset)
#define sample_memory_write(offset, data) \
	IOWR_32DIRECT(SAMPLE_BUFFER_SAMPLE_BUFFER_INTERNAL_INST_AVS_CRA_BASE, offset, data)
//-----------------------------------------------------------------
// Component register macros
//-----------------------------------------------------------------

#define sample_enable_interrupt()               \
	sample_write(                               \
		SAMPLE_BUFFER_CSR_INTERRUPT_ENABLE_REG, \
		SAMPLE_BUFFER_CSR_INTERRUPT_ENABLE_MASK & 0x1)
#define sample_disable_interrupt()              \
	sample_write(                               \
		SAMPLE_BUFFER_CSR_INTERRUPT_ENABLE_REG, \
		SAMPLE_BUFFER_CSR_INTERRUPT_ENABLE_MASK & 0x0)
#define sample_clear_done_status()              \
	sample_write(                               \
		SAMPLE_BUFFER_CSR_INTERRUPT_STATUS_REG, \
		SAMPLE_BUFFER_CSR_INTERRUPT_STATUS_MASK & 0x1)

#define sample_start() \
	sample_write(SAMPLE_BUFFER_CSR_START_REG, SAMPLE_BUFFER_CSR_START_MASK & 0x1)
#define sample_busy() \
	sample_read(SAMPLE_BUFFER_CSR_BUSY_REG) & SAMPLE_BUFFER_CSR_BUSY_MASK
#define sample_done()                                     \
	sample_read(SAMPLE_BUFFER_CSR_INTERRUPT_STATUS_REG) & \
		SAMPLE_BUFFER_CSR_INTERRUPT_STATUS_MASK

//-----------------------------------------------------------------

#endif /* SAMPLE_BUFFER_H_INCLUDED */
