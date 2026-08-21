//////////////////////////////////////////////////////////////////////////////
/// \file LeakMemoryDumper.cpp
/// \author sonee
/// \date 2004.12.30
//////////////////////////////////////////////////////////////////////////////

#include "Client_PCH.h"
#include "LeakMemoryDumper.h"

#ifdef _DEBUG

typedef struct {
	DWORD_PTR	address;
	DWORD	size;
	char	file[64];
	DWORD	line;
} ALLOC_INFO;      

typedef std::list<ALLOC_INFO*> AllocList;      
AllocList allocList;      

void AddTrack(DWORD_PTR addr,  DWORD asize,  const char *fname, DWORD lnum)
{
	ALLOC_INFO *info;	      
//	if(!allocList) 
//	{
//		allocList = new (AllocList);
//	}	      
	info = new (ALLOC_INFO);
	info->address = addr;
	strncpy(info->file, fname, 63);
	info->line = lnum;
	info->size = asize;
	allocList.insert(allocList.begin(), info);
}
  
void RemoveTrack(DWORD_PTR addr)
{
	AllocList::iterator i;	      
	
	for(i = allocList.begin(); i != allocList.end(); i++)
	{
		if((*i)->address == addr)
		{
			allocList.remove((*i));
			break;
		}
	}
}

void DumpUnfreed()
{
	AllocList::iterator i;
	DWORD totalSize = 0;
	char buf[1024];	      

	for(i = allocList.begin(); i != allocList.end(); i++) 
	{
		sprintf(buf, "%-50s:\t\tLINE %u,\t\tADDRESS %p\t%u unfreed\n",
			(*i)->file, (*i)->line, (void*)(*i)->address, (*i)->size);
		OutputDebugString(buf);
		totalSize += (*i)->size;
	}
	sprintf(buf, "-----------------------------------------------------------\n");
	OutputDebugString(buf);
	sprintf(buf, "Total Unfreed: %u bytes\n", totalSize);
	OutputDebugString(buf);
}

#endif