#ifndef _DEVICE_MEMORY_MAP_H_
#define _DEVICE_MEMORY_MAP_H_

#include <Library/ArmLib.h>

#define MAX_ARM_MEMORY_REGION_DESCRIPTOR_COUNT 64

/* Below flag is used for system memory */
#define SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES \
                EFI_RESOURCE_ATTRIBUTE_PRESENT |                 \
                EFI_RESOURCE_ATTRIBUTE_INITIALIZED |             \
                EFI_RESOURCE_ATTRIBUTE_TESTED |                  \
                EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |             \
                EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |       \
                EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE | \
                EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE |    \
                EFI_RESOURCE_ATTRIBUTE_EXECUTION_PROTECTABLE

typedef enum {
	NoHob,
	AddMem,
	AddDev,
	MaxMem
} DeviceMemoryAddHob;

typedef struct {
	EFI_PHYSICAL_ADDRESS				Address;
	UINT64								Length;
	EFI_RESOURCE_TYPE					ResourceType;
	EFI_RESOURCE_ATTRIBUTE_TYPE			ResourceAttribute;
	ARM_MEMORY_REGION_ATTRIBUTES		ArmAttributes;
	DeviceMemoryAddHob					HobOption;
	EFI_MEMORY_TYPE						MemoryType;
} ARM_MEMORY_REGION_DESCRIPTOR_EX, *PARM_MEMORY_REGION_DESCRIPTOR_EX;

/*
 *    Memory Map is as follows
 *
 * ------------------------------   <-- Start of DRAM
 * |                            |
 * |      Available DRAM        |
 * |____________________________|
 * |                            |
 * |   UEFI Mem, Stack and FB   |
 * |____________________________|
 * |                            |
 * |      Other carveouts       |
 * | (with dynamic allocation)  |
 * |____________________________|
 * |                            |
 * |    TZ carveout of size     |
 * | TRUSTZONE_CARVEOUT_SIZE_MB |
 * |____________________________|   <-- 0x100000000
 * |                            |
 * |      Available DRAM        |
 * |                            |
 * ------------------------------   <-- End of DRAM
 *
 */

static ARM_MEMORY_REGION_DESCRIPTOR_EX gDeviceMemoryDescriptorEx[] =
{
	/* Address, Length, ResourceType, Resource Attribute, ARM MMU Attribute, HobOption, EFI Memory Type */
	{
		// Registers regions
		0x00000000,
		0x41000000,
		EFI_RESOURCE_MEMORY_MAPPED_IO,
		EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
		ARM_MEMORY_REGION_ATTRIBUTE_DEVICE,
		AddDev,
		EfiMemoryMappedIO
	},
	{
		// HLOS memory 1 (hopefully)
		0x41000000,
		0x00110000,
		EFI_RESOURCE_SYSTEM_MEMORY,
		SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
		ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK,
		AddMem,
		EfiConventionalMemory
	},
	{
		// UEFI FD
		0x41110000,
		0x000E0000,
		EFI_RESOURCE_SYSTEM_MEMORY,
		SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
		ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK,
		AddMem,
		EfiBootServicesCode
	},
	{
		// HLOS memory 2
		0x411F0000,
		0x6E10000,
		EFI_RESOURCE_SYSTEM_MEMORY,
		SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
		ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK,
		AddMem,
		EfiConventionalMemory
	},
	{
		// Display Reserved
		0x48000000,
		0x1000000,
		EFI_RESOURCE_MEMORY_RESERVED,
		EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE,
		ARM_MEMORY_REGION_ATTRIBUTE_WRITE_THROUGH,
		AddMem,
		EfiMaxMemoryType
	},
	{
                // HLOS memory 3
                0x49000000,
                0x37000000,
                EFI_RESOURCE_SYSTEM_MEMORY,
                SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
                ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK,
                AddMem,
                EfiConventionalMemory
        },
	/* Terminator */
	{ 0 }
};

#endif
