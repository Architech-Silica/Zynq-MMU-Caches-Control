#include "include/mmu_control.h"


int adjust_mmu_mode(unsigned int start_of_1MB_address_region, unsigned int features)
{
	unsigned int mmu_attributes = 0;

	/* Declare the part of the page table value that gets written to the MMU Table, which is always fixed. */
	/* NS = b0, Bit 18 = b0, TEX(2) = b1, Bit 9 = b0, Domain = b1111, Bits(1:0) = b10 ... 0x41e2 */
	/* Fiddle with this at your own risk.  If you're not sure of what you're doing, it won't end well!! */
	const unsigned int fixed_values = 0x41e2;

	// Calculate the value that will be written to the MMU Page Table
	mmu_attributes = fixed_values + features;

	// Write the value to the TLB
	Xil_SetTlbAttributes(start_of_1MB_address_region, mmu_attributes);

	return (0);
}

