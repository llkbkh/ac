#ifndef MODULES_H
#define MODULES_H

#include <ntifs.h>
#include <intrin.h>
#include "common.h"

#define MODULE_REPORT_DRIVER_NAME_BUFFER_SIZE 128

#define REASON_NO_BACKING_MODULE 1
#define REASON_INVALID_IOCTL_DISPATCH 2

typedef struct _WHITELISTED_REGIONS
{
	UINT64 base;
	UINT64 end;

}WHITELISTED_REGIONS, * PWHITELISTED_REGIONS;

typedef struct _NMI_POOLS
{
	PVOID thread_data_pool;
	PVOID stack_frames;
	PVOID nmi_context;

}NMI_POOLS, * PNMI_POOLS;

typedef struct NMI_CALLBACK_FAILURE
{
	INT report_code;
	INT were_nmis_disabled;
	UINT64 kthread_address;
	UINT64 invalid_rip;

}NMI_CALLBACK_FAILURE, * PNMI_CALLBACK_FAILURE;

typedef struct _NMI_CONTEXT
{
	INT nmi_callbacks_run;

}NMI_CONTEXT, * PNMI_CONTEXT;

typedef struct _NMI_CALLBACK_DATA
{
	UINT64		kthread_address;
	UINT64		kprocess_address;
	UINT64		start_address;
	UINT64		stack_limit;
	UINT64		stack_base;
	uintptr_t	stack_frames_offset;
	INT			num_frames_captured;
	UINT64		cr3;

}NMI_CALLBACK_DATA, * PNMI_CALLBACK_DATA;

typedef struct _MODULE_VALIDATION_FAILURE_HEADER
{
	INT module_count;

}MODULE_VALIDATION_FAILURE_HEADER, *PMODULE_VALIDATION_FAILURE_HEADER;

typedef struct _MODULE_VALIDATION_FAILURE
{
	INT report_code;
	INT report_type;
	UINT64 driver_base_address;
	UINT64 driver_size;
	CHAR driver_name[ 128 ];

}MODULE_VALIDATION_FAILURE, *PMODULE_VALIDATION_FAILURE;

typedef struct _INVALID_DRIVER
{
	struct _INVALID_DRIVER* next;
	INT reason;
	PDRIVER_OBJECT driver;

}INVALID_DRIVER, * PINVALID_DRIVER;

typedef struct _INVALID_DRIVERS_HEAD
{
	PINVALID_DRIVER first_entry;
	INT count;		//keeps track of the number of drivers in the list

}INVALID_DRIVERS_HEAD, * PINVALID_DRIVERS_HEAD;

/* system modules information */

typedef struct _SYSTEM_MODULES
{
	PVOID address;
	INT module_count;

}SYSTEM_MODULES, * PSYSTEM_MODULES;

NTSTATUS GetSystemModuleInformation(
	_Out_ PSYSTEM_MODULES ModuleInformation
);

NTSTATUS HandleValidateDriversIOCTL(
	_In_ PIRP Irp
);

PRTL_MODULE_EXTENDED_INFO FindSystemModuleByName(
	_In_ LPCSTR ModuleName,
	_In_ PSYSTEM_MODULES SystemModules
);

NTSTATUS HandleNmiIOCTL(
	_In_ PIRP Irp
);

#endif
