/*
 * mmu_control.h
 *
 *  Created on: 27 Jun 2014
 *      Author: GriffinR
 */

#ifndef MMU_CONTROL_H
#define MMU_CONTROL_H

// These values are derived from the L1 Page Table Entry Format
// This is documented in Figure 3-5 of the TRM.

#define NON_CACHEABLE 0x00  // TEX(1:0) = b00, C = b0, B = b0
#define WRITEBACK_WRITEALLOCATE  0x1004  // TEX(1:0) = b01, C = b0, B = b1
#define WRITETHROUGH_NO_WRITEALLOCATE 0x2008  // TEX(1:0) = b10, C = b1, B = b0
#define WRITEBACK_NO_WRITEALLOCATE 0x300C  // TEX(1:0) = b11, C = b1, B = b1
#define EXECUTE_NEVER 0x10  // XN = b1
#define SHAREABLE 0x10000  // S = b1
#define AP_PERMISSIONFAULT 0x00  // AP(2) = b0, AP(1:0) = b00
#define AP_PRIVIEGED_ACCESS_ONLY 0x400  // AP(2) = b0, AP(1:0) = b01
#define AP_NO_USERMODE_WRITE 0x800  // AP(2) = b0, AP(1:0) = b10
#define AP_FULL_ACCESS 0xC00  // AP(2) = b0, AP(1:0) = b11
#define AP_PRIVILEGED_READ_ONLY 0x8800  // AP(2) = b1, AP(1:0) = b10
#define NON_GLOBAL 0x20000  // nG = b1


// Function Prototypes
int adjust_mmu_mode(unsigned int start_of_1MB_address_region, unsigned int features);


#endif /* MMU_CONTROL_H */
