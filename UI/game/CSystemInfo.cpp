/********************************************************************
	created:	2003/10/17
	created:	17:10:2003   13:48
	filename: 	E:\designed\project\client\CSystemInfo.cpp
	file path:	E:\designed\project\client
	file base:	CSystemInfo
	file ext:	cpp
	author:		sonee
	
	purpose:	시스템 정보를 알아낸다.
				2003-10-17		CPU Clock 얻어오기
								MMX,SSE2 테크놀러지 Enable 여부
								Hyper Thread Enable 여부
*********************************************************************/
#include "Client_PCH.h"
#include <windows.h>
#include "CSystemInfo.h"

#pragma warning( disable : 4035 )		// disable 시켜버리자-_-;
#pragma warning( disable: 4800 )		//'int' : forcing value to bool 'true' or 'false' (performance warning)

inline unsigned __int64 theCycleCount(void)
{
	return __rdtsc();
}

static bool cpuid(unsigned long function, unsigned long& out_eax, unsigned long& out_ebx, unsigned long& out_ecx, unsigned long& out_edx)
{
#ifdef _LINUX
	asm("cpuid": "=a" (out_eax), "=b" (out_ebx), "=c" (out_ecx), "=d" (out_edx) : "a" (function));
	return true;
#else
	bool retval = true;
	int regs[4];
	unsigned long local_eax, local_ebx, local_ecx, local_edx;

	__cpuid(regs, function);
	
	out_eax = regs[0];
	out_ebx = regs[1];
	out_ecx = regs[2];
	out_edx = regs[3];

	return retval;
#endif
}

long CSystemInfo::GetCpuClock()
{
	unsigned __int64			start;
	unsigned __int64			overhead;

	start = theCycleCount();
	overhead = theCycleCount()-start;
	start = theCycleCount();
	Sleep(100);

	unsigned cpuspeed100 = (unsigned)( (theCycleCount()-start-overhead) / 1000 );
	return cpuspeed100 /100;
}

// --------------------------------------------------------------------------
bool CSystemInfo::CheckMMXTechnology()
{
	// All modern OS Windows XP and above support MMX Technology.
	int regs[4];
	__cpuid(regs, 1);
	return (regs[3] & (1 << 23)) != 0;
}


/*
// --------------------------------------------------------------------------
bool CSystemInfo::CheckSSETechnology(void)
{
    BOOL retval = TRUE;
    DWORD RegEDX;

#ifdef CPUID
	_asm pushad;
#endif

	// Do we have support for the CPUID function?
    __try
	{
        _asm
		{
#ifdef CPUID
			xor edx, edx			// Clue the compiler that EDX is about to be used.
#endif
            mov eax, 1				// set up CPUID to return processor version and features
									//      0 = vendor string, 1 = version info, 2 = cache info
            CPUID					// code bytes = 0fh,  0a2h
            mov RegEDX, edx			// features returned in edx
		}
    } 
	__except(EXCEPTION_EXECUTE_HANDLER) 
	{ 
		retval = FALSE; 
	}

	// If CPUID not supported, then certainly no SSE extensions.
    if (retval)
	{
		// Do we have support for SSE in this processor?
		if ( RegEDX & 0x2000000L )		// bit 25 is set for SSE technology
		{
			// Make sure that SSE is supported by executing an inline SSE instruction

// BUGBUG, FIXME - Visual C Version 6.0 does not support SSE inline code YET (No macros from Intel either)
// Fix this if VC7 supports inline SSE instructinons like "xorps" as shown below.
#if 1
			__try
			{
				_asm
				{
					// Attempt execution of a SSE instruction to make sure OS supports SSE FPU context switches
					xorps xmm0, xmm0
					// This will work on Win2k+ (Including masking SSE FPU exception to "normalized" values)
					// This will work on Win98+ (But no "masking" of FPU exceptions provided)
				}
			} 
			__except(EXCEPTION_EXECUTE_HANDLER) 
#endif

			{ 
				retval = FALSE; 
			}
		}
		else
			retval = FALSE;
	}
#ifdef CPUID
	_asm popad;
#endif

    return retval;
}
bool CSystemInfo::CheckSSE2Technology()
{
    BOOL retval = TRUE;
    DWORD RegEDX;

#ifdef CPUID
	_asm pushad;
#endif

	// Do we have support for the CPUID function?
    __try
	{
        _asm
		{
#ifdef CPUID
			xor edx, edx			// Clue the compiler that EDX is about to be used.
#endif
            mov eax, 1				// set up CPUID to return processor version and features
									//      0 = vendor string, 1 = version info, 2 = cache info
            CPUID					// code bytes = 0fh,  0a2h
            mov RegEDX, edx			// features returned in edx
		}
    } 
	__except(EXCEPTION_EXECUTE_HANDLER) 
	{ 
		retval = FALSE; 
	}

	// If CPUID not supported, then certainly no SSE extensions.
    if (retval)
	{
		// Do we have support for SSE in this processor?
		if ( RegEDX & 0x04000000 )		// bit 26 is set for SSE2 technology
		{
			// Make sure that SSE is supported by executing an inline SSE instruction

			__try
			{
				_asm
				{
					// Attempt execution of a SSE2 instruction to make sure OS supports SSE FPU context switches
					xorpd xmm0, xmm0
				}
			} 
			__except(EXCEPTION_EXECUTE_HANDLER) 

			{ 
				retval = FALSE; 
			}
		}
		else
			retval = FALSE;
	}
#ifdef CPUID
	_asm popad;
#endif

    return retval;
}
*/

// --------------------------------------------------------------------------
bool CSystemInfo::Check3DNowTechnology()
{
	// AMD 3DNow! is obsolete technology, but we will check for it anyway.  99% of the time it will return false.
	int regs[4];

	// Get highest extended function
	__cpuid(regs, 0x80000000);
	if ((unsigned int)regs[0] <= 0x80000000)
		return false;

	// Get extended features
	__cpuid(regs, 0x80000001);

	// EDX bit 31 = 3DNow!
	return (regs[3] & (1u << 31)) != 0;
}

// Returns non-zero if Hyper-Threading Technology is supported on the processors and zero if not.  This does not mean that 
// Hyper-Threading Technology is necessarily enabled.
bool CSystemInfo::CheckHyperThreadTechnology()
{
	const unsigned int HT_BIT		 = 0x10000000;  // EDX[28] - Bit 28 set indicates Hyper-Threading Technology is supported in hardware.
	const unsigned int FAMILY_ID     = 0x0f00;      // EAX[11:8] - Bit 11 thru 8 contains family processor id
	const unsigned int EXT_FAMILY_ID = 0x0f00000;	// EAX[23:20] - Bit 23 thru 20 contains extended family  processor id
	const unsigned int PENTIUM4_ID   = 0x0f00;		// Pentium 4 family processor id

	unsigned long unused,
				  reg_eax = 0, 
				  reg_edx = 0,
				  vendor_id[3] = {0, 0, 0};

	// verify cpuid instruction is supported
	if( !cpuid(0,unused, vendor_id[0],vendor_id[2],vendor_id[1]) 
	 || !cpuid(1,reg_eax,unused,unused,reg_edx) )
	 return false;

	//  Check to see if this is a Pentium 4 or later processor
	if (((reg_eax & FAMILY_ID) ==  PENTIUM4_ID) || (reg_eax & EXT_FAMILY_ID))
		if (vendor_id[0] == 'uneG' && vendor_id[1] == 'Ieni' && vendor_id[2] == 'letn')
			return (reg_edx & HT_BIT) != 0;	// Genuine Intel Processor with Hyper-Threading Technology

	return false;  // This is not a genuine Intel processor.
}
