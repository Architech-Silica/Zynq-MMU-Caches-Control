#include "xil_types.h"  // This is required by "xil_mmu.h" but has a dependency which is broken in the BSP.
#include "xil_mmu.h"
#include "xparameters_ps.h"
#include "xil_io.h"
#include "xil_testmem.h"
#include "xscutimer.h"
#include "mmu_control.h"

//#define MEM_TEST_START_ADDRESS XPAR_DDR_MEM_BASEADDR
#define MEM_TEST_START_ADDRESS 0x10000000
#define MEM_TEST_END_ADDRESS 0x1FFFFFFF

#define MEMORY_TEST_PATTERN 0xA1B2C3D4


int main()
{
	init_platform();

	unsigned int status = 0;
	unsigned int timer_value = 0;
	unsigned int memory_region;
	unsigned int mem_test_WRITEBACK_WRITEALLOCATE_cycle_count = 0;
	unsigned int mem_test_WRITEBACK_NO_WRITEALLOCATE_cycle_count = 0;
	unsigned int mem_test_WRITETHROUGH_NO_WRITEALLOCATE_cycle_count = 0;
	unsigned int mem_test_NOT_CACHED_cycle_count = 0;
	float mem_test_WRITEBACK_WRITE_ALLOCATE_seconds_count = 0;
	float mem_test_WRITEBACK_NO_WRITE_ALLOCATE_seconds_count = 0;
	float mem_test_WRITETHROUGH_NO_WRITE_ALLOCATE_seconds_count = 0;
	float mem_test_NOT_CACHED_seconds_count = 0;

	const int initial_timer_value = 0xFFFFFFFF;
	const int number_of_cycles_in_1_second = XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ / 2;  //  SCU timer runs at half the CPU Frequency


	// Declare two structs.  One for the Timer instance, and
	// the other for the timer's config information
	XScuTimer my_Timer;
	XScuTimer_Config *Timer_Config;

	printf("=========================\n\r");
	printf("Cache Control Experiments\n\r");
	printf("=========================\n\r");

	printf("\n\r\n\r");
	printf("This application runs a series of memory tests, changing the caching mode in between each.\n\r");
	printf("The performance of each memory test is measured and reported using a timer\n\r");
	printf("\n\r\n\r");


	// -------------------------------------------------
	// ----------------- INITIAL SETUP -----------------
	// -------------------------------------------------
	// Look up the the config information for the timer
	Timer_Config = XScuTimer_LookupConfig(XPAR_PS7_SCUTIMER_0_DEVICE_ID);

	// Initialise the timer using the config information
	status = XScuTimer_CfgInitialize(&my_Timer, Timer_Config, Timer_Config->BaseAddr);



	// -------------------------------------------------
	// -------- CACHED, WRITEBACK_WRITEALLOCATE --------
	// -------------------------------------------------

	// Load the timer with a known value
	XScuTimer_LoadTimer(&my_Timer, initial_timer_value);

	printf("Adjusting the MMU settings... ");
	for (memory_region = 0; memory_region<256; memory_region++)
	{
		adjust_mmu_mode(MEM_TEST_START_ADDRESS+(memory_region*(1024*1024)), SHAREABLE + WRITEBACK_WRITEALLOCATE + AP_FULL_ACCESS);
	}
	printf("Done.\n\r\n\r");

	// Read the timer and display the value
	timer_value = XScuTimer_GetCounterValue(&my_Timer);
	printf("Timer counter before test = 0x%08X\n\r", timer_value);

	printf("    Running a memory test using CACHED, WRITEBACK_WRITEALLOCATE settings\n\r");
	XScuTimer_Start(&my_Timer);
	Xil_TestMem32(MEM_TEST_START_ADDRESS,48*1024*1024, MEMORY_TEST_PATTERN, XIL_TESTMEM_FIXEDPATTERN);

	// Start the timer running (it counts down)
	XScuTimer_Stop(&my_Timer);

	// Read the timer and display the value
	timer_value = XScuTimer_GetCounterValue(&my_Timer);
	printf("Timer counter after test =  0x%08X\n\r", timer_value);
	mem_test_WRITEBACK_WRITEALLOCATE_cycle_count = initial_timer_value-timer_value;
	printf("\n\r");

	// --------------------------------------------------
	// ------- CACHED, WRITEBACK_NO_WRITEALLOCATE -------
	// --------------------------------------------------

	// Load the timer with a known value
	XScuTimer_LoadTimer(&my_Timer, initial_timer_value);

	printf("Adjusting the MMU settings... ");
	for (memory_region = 0; memory_region<256; memory_region++)
	{
		adjust_mmu_mode(MEM_TEST_START_ADDRESS+(memory_region*(1024*1024)), SHAREABLE + WRITEBACK_NO_WRITEALLOCATE + AP_FULL_ACCESS);
	}
	printf("Done.\n\r\n\r");

	// Read the timer and display the value
	timer_value = XScuTimer_GetCounterValue(&my_Timer);
	printf("Timer counter before test = 0x%08X\n\r", timer_value);

	printf("    Running a memory test using CACHED, WRITEBACK_NO_WRITEALLOCATE MMU settings\n\r");
	XScuTimer_Start(&my_Timer);
	Xil_TestMem32(MEM_TEST_START_ADDRESS,48*1024*1024, MEMORY_TEST_PATTERN, XIL_TESTMEM_FIXEDPATTERN);

	// Start the timer running (it counts down)
	XScuTimer_Stop(&my_Timer);

	// Read the timer and display the value
	timer_value = XScuTimer_GetCounterValue(&my_Timer);
	printf("Timer counter after test =  0x%08X\n\r", timer_value);
	mem_test_WRITEBACK_NO_WRITEALLOCATE_cycle_count = initial_timer_value-timer_value;
	printf("\n\r");

	// --------------------------------------------------
	// ------ CACHED, WRITETHROUGH_NO_WRITEALLOCATE -----
	// --------------------------------------------------

	// Load the timer with a known value
	XScuTimer_LoadTimer(&my_Timer, initial_timer_value);

	printf("Adjusting the MMU settings... ");
	for (memory_region = 0; memory_region<256; memory_region++)
	{
		adjust_mmu_mode(MEM_TEST_START_ADDRESS+(memory_region*(1024*1024)), SHAREABLE + WRITETHROUGH_NO_WRITEALLOCATE + AP_FULL_ACCESS);
	}
	printf("Done.\n\r\n\r");

	// Read the timer and display the value
	timer_value = XScuTimer_GetCounterValue(&my_Timer);
	printf("Timer counter before test = 0x%08X\n\r", timer_value);

	printf("    Running a memory test using CACHED, WRITETHROUGH_NO_WRITEALLOCATE MMU settings\n\r");
	XScuTimer_Start(&my_Timer);
	Xil_TestMem32(MEM_TEST_START_ADDRESS,48*1024*1024, MEMORY_TEST_PATTERN, XIL_TESTMEM_FIXEDPATTERN);

	// Start the timer running (it counts down)
	XScuTimer_Stop(&my_Timer);
	printf("Done.  Status code was %d\n\r", status);

	// Read the timer and display the value
	timer_value = XScuTimer_GetCounterValue(&my_Timer);
	printf("Timer counter after test =  0x%08X\n\r", timer_value);
	mem_test_WRITETHROUGH_NO_WRITEALLOCATE_cycle_count = initial_timer_value-timer_value;
	printf("\n\r");

	// -------------------------------------------------
	// ------------------- NOT CACHED ------------------
	// -------------------------------------------------

	printf("Adjusting the MMU settings... ");
	for (memory_region = 0; memory_region<256; memory_region++)
	{
		adjust_mmu_mode(MEM_TEST_START_ADDRESS+(memory_region*(1024*1024)), SHAREABLE + NON_CACHEABLE + AP_FULL_ACCESS);
	}
	printf("Done.\n\r\n\r");


	// Load the timer with a known value
	XScuTimer_LoadTimer(&my_Timer, initial_timer_value);

	// Read the timer and display the value
	timer_value = XScuTimer_GetCounterValue(&my_Timer);
	printf("Timer counter before test = 0x%08X\n\r", timer_value);

	printf("    Running a memory test using NOT CACHED MMU settings\n\r");
	XScuTimer_Start(&my_Timer);
	Xil_TestMem32(MEM_TEST_START_ADDRESS,48*1024*1024, MEMORY_TEST_PATTERN, XIL_TESTMEM_FIXEDPATTERN);
	// Start the timer running (it counts down)
	XScuTimer_Stop(&my_Timer);

	// Read the timer and display the value
	timer_value = XScuTimer_GetCounterValue(&my_Timer);
	printf("Timer counter after test =  0x%08X\n\r", timer_value);
	mem_test_NOT_CACHED_cycle_count = initial_timer_value-timer_value;

	printf("\n\r\n\r");

	mem_test_WRITEBACK_WRITE_ALLOCATE_seconds_count = (float)mem_test_WRITEBACK_WRITEALLOCATE_cycle_count / (float)number_of_cycles_in_1_second;
	mem_test_WRITEBACK_NO_WRITE_ALLOCATE_seconds_count = (float)mem_test_WRITEBACK_NO_WRITEALLOCATE_cycle_count / (float)number_of_cycles_in_1_second;
	mem_test_WRITETHROUGH_NO_WRITE_ALLOCATE_seconds_count = (float)mem_test_WRITETHROUGH_NO_WRITEALLOCATE_cycle_count / (float)number_of_cycles_in_1_second;
	mem_test_NOT_CACHED_seconds_count = (float)mem_test_NOT_CACHED_cycle_count / (float)number_of_cycles_in_1_second;

	printf("=======\n\r");
	printf("Results\n\r");
	printf("=======\n\r");
	printf("\n\r");
	printf("Clock cycles elapsed (Write-Back, Write-Allocate memory test)       = %d\n\r", mem_test_WRITEBACK_WRITEALLOCATE_cycle_count);
	printf("Clock cycles elapsed (Write-Back, No Write-Allocate memory test)    = %d\n\r", mem_test_WRITEBACK_NO_WRITEALLOCATE_cycle_count);
	printf("Clock cycles elapsed (Write-Through, No Write-Allocate memory test) = %d\n\r", mem_test_WRITETHROUGH_NO_WRITEALLOCATE_cycle_count);
	printf("Clock cycles elapsed (Non-cached memory test)                       = %d\n\r", mem_test_NOT_CACHED_cycle_count);
	printf("\n\r");
	printf("Real Time elapsed (Write-Back, Write-Allocate memory test)          = %f seconds\n\r", mem_test_WRITEBACK_WRITE_ALLOCATE_seconds_count);
	printf("Real Time elapsed (Write-Back, No Write-Allocate memory test)       = %f seconds\n\r", mem_test_WRITEBACK_NO_WRITE_ALLOCATE_seconds_count);
	printf("Real Time elapsed (Write-Through, No Write-Allocate memory test)    = %f seconds\n\r", mem_test_WRITETHROUGH_NO_WRITE_ALLOCATE_seconds_count);
	printf("Real time elapsed (Non-cached memory test)                          = %f seconds\n\r", mem_test_NOT_CACHED_seconds_count);

	printf("\n\r\n\r");
	printf("## Finished ##\n\r");

	return 0;
}
