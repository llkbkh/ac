#ifndef POOL_H
#define POOL_H

#include <ntifs.h>
#include "common.h"

#define REPORT_INVALID_PROCESS_BUFFER_SIZE 4000	// we want to make sure this allocation fits on a page

#define PAGE_BASE_SIZE 0x1000
#define POOL_TAG_SIZE 0x004

#define PML4_ENTRY_COUNT 512
#define PDPT_ENTRY_COUNT 512
#define PD_ENTRY_COUNT 512
#define PT_ENTRY_COUNT 512

#define LARGE_PAGE_2MB_ENTRIES 512
#define LARGE_PAGE_1GB_ENTRIES 0x40000

#define PROCESS_OBJECT_ALLOCATION_MARGIN 0x90

/* SIZE_2 = first alloc + 0x10 */
#define WIN_PROCESS_ALLOCATION_SIZE 0xcf0
#define WIN_PROCESS_ALLOCATION_SIZE_2 0xd00

#define CHUNK_SIZE 16

typedef struct _INVALID_PROCESS_ALLOCATION_REPORT
{
	INT report_code;
	CHAR process[ REPORT_INVALID_PROCESS_BUFFER_SIZE ];

}INVALID_PROCESS_ALLOCATION_REPORT, *PINVALID_PROCESS_ALLOCATION_REPORT;

NTSTATUS FindUnlinkedProcesses(
	_In_ PIRP Irp
);

VOID GetPsActiveProcessHead(
	_In_ PUINT64 Address
);

PKDDEBUGGER_DATA64 GetGlobalDebuggerData();

#endif