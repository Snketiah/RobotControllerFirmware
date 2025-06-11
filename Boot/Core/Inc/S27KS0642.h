/*
 * S27KS0642.h
 *
 *  Created on: Apr 21, 2025
 *      Author: stevenketiah
 */

#ifndef INC_S27KS0642_H_
#define INC_S27KS0642_H_

#include "SSROBOT_HAL.h"
#include "stm32h7rsxx_hal.h"


#define S27KS0642_TIMEOUT 0x10000

/*   Register Address   */
#define S27KS0642_ID0 0x000
#define S27KS0642_ID1 0x001
#define S27KS0642_CR0 0x800
#define S27KS0642_CR1 0x801


/* ===================================================================== */
/*  S27KS0642  —  CONFIGURATION-REGISTER-0 (CR0, addr 0x0100)            */
/* ===================================================================== */

// Deep power-down enable --> Bit[15]
#define S27KS0642_NORMAL_OPERATION       0b1
#define S27KS0642_DEEP_POWER_DOWN        0b0

// Drive strength --> bits[14:12]
#define S27KS0642_34_OHMS				 0b000  // 34Ω (default)
#define S27KS0642_115_OHMS               0b001  // 115Ω
#define S27KS0642_67_OHMS                0b010  // 67Ω
#define S27KS0642_46_OHMS                0b011  // 46Ω
#define S27KS0642_27_OHMS                0b101  // 27Ω
#define S27KS0642_22_OHMS                0b110  // 22Ω
#define S27KS0642_19_OHMS                0b111  // 19Ω

// RESERVED --> Bits[11:8]
#define S27KS0642_CR0_RESERVED           0xF    // All reserved bits should be 1

// Initial Latency --> Bits[7:4]
#define S27KS0642_5_CLOCK_LATENCY        0b0000 // 5 Clock latency @ 133 MHz
#define S27KS0642_6_CLOCK_LATENCY        0b0001 // 6 Clock latency @ 166 MHz
#define S27KS0642_7_CLOCK_LATENCY        0b0010 // 7 Clock latency @ 200/166 MHz (default)
#define S27KS0642_3_CLOCK_LATENCY        0b1110 // 3 Clock latency @ 85 MHz
#define S27KS0642_4_CLOCK_LATENCY        0b1111 // 4 Clock latency @ 104 MHz

// Fixed Latency Enable --> Bit[3]
#define S27KS0642_VARIABLE_LATENCY       0b0    // Variable latency
#define S27KS0642_FIXED_LATENCY          0b1    // Fixed latency (default)

// Hybrid burst enable --> Bit[2]
#define S27KS0642_HYBRID_BURST_ENABLE    0b0    // Wrapped burst sequence to follow hybrid burst sequencing
#define S27KS0642_LEGACY_WRAPPED_BURST   0b1    // Wrapped burst sequence in legacy wrapped burst manner (default)

// Burst length --> Bits[1:0]
#define S27KS0642_128_BYTES              0b00   // 128 bytes (64 clocks)
#define S27KS0642_64_BYTES               0b01   // 64 bytes (32 clocks)
#define S27KS0642_16_BYTES               0b10   // 16 bytes (8 clocks)
#define S27KS0642_32_BYTES               0b11   // 32 bytes (16 clocks) (default)



/* ===================================================================== */
/*  S27KS0642  —  CONFIGURATION-REGISTER-1 					             */
/* ===================================================================== */
// Reserved high bits --> Bits[15:8]
// Reserved high bits --> Bits[15:8]
#define S27KS0642_CR1_RESERVED_HIGH      0xFF   // These bits should always be set to FFh

// Reserved bit --> Bit[7]
#define S27KS0642_CR1_RESERVED_BIT7      0b1    // Reserved (default)

// Master clock type --> Bit[6]
#define S27KS0642_SINGLE_ENDED_CK        0b1    // Single-ended - CK (default)
#define S27KS0642_DIFFERENTIAL_CK        0b0    // Differential - CK#, CK

// Hybrid sleep --> Bit[5]
#define S27KS0642_ENTER_HYBRID_SLEEP     0b1    // Causes the device to enter Hybrid sleep state
#define S27KS0642_NORMAL_OPERATION_CR1   0b0    // Normal operation (default)

// Partial array refresh --> Bits[4:2]
#define S27KS0642_FULL_ARRAY             0b000  // Full array (default)
#define S27KS0642_BOTTOM_HALF_ARRAY      0b001  // Bottom 1/2 array
#define S27KS0642_BOTTOM_QUARTER_ARRAY   0b010  // Bottom 1/4 array
#define S27KS0642_BOTTOM_EIGHTH_ARRAY    0b011  // Bottom 1/8 array
#define S27KS0642_NO_REFRESH             0b100  // None
#define S27KS0642_TOP_HALF_ARRAY         0b101  // Top 1/2 array
#define S27KS0642_TOP_QUARTER_ARRAY      0b110  // Top 1/4 array
#define S27KS0642_TOP_EIGHTH_ARRAY       0b111  // Top 1/8 array

// Distributed refresh interval (read-only) --> Bits[1:0]
#define S27KS0642_REFRESH_1US            0b10   // 1 μs tCSM (Industrial plus temperature range devices)
#define S27KS0642_REFRESH_4US            0b01   // 4 μs tCSM (Industrial temperature range devices)







typedef struct {
	XSPI_HandleTypeDef* xspi_hnd;

}S27KS0642;




SSROBOT_Status S27KS0642_init(S27KS0642 *hnd);

SSROBOT_Status S27KS0642_register_write(XSPI_HandleTypeDef *hnd, uint32_t address, uint16_t data);

SSROBOT_Status S27KS0642_register_read(XSPI_HandleTypeDef *hnd, uint32_t address, uint16_t* data);




#endif /* INC_S27KS0642_H_ */
