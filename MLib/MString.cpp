//--------------------------------------------------------------------------
// MString.cpp
//--------------------------------------------------------------------------


/*	using namespace std ?? ???? ???? ???? ????? ???? --;;
#include <windows.h>
#include "MString.h"
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <stdio.h> 
#include <stdarg.h>
#include <mmsystem.h>
#include <iostream.h>
#include <fstream>
#include "DebugInfo.h"
*/

#include "MLib_PCH.h"
#include <stdarg.h>
#include <new>
#include "MString.h"

//#include "DebugInfo.h"
//#define	new			DEBUG_NEW
//#define	delete		DEBUG_DELETE

//--------------------------------------------------------------------------
// static
//--------------------------------------------------------------------------
char MString::s_pBuffer[MAX_BUFFER_LENGTH];

//--------------------------------------------------------------------------
//
// constructor / destructor
//
//--------------------------------------------------------------------------
MString::MString()
{
	m_Length = 0;
	m_pString = NULL;
}

MString::MString(const MString& str)
{
	m_Length = 0;
	m_pString = NULL;
	*this = str;
}

MString::MString(const char* str)
{
	m_Length = 0;
	m_pString = NULL;
	*this = str;
}

MString::~MString()
{
	if (m_pString!=NULL)
	{
		delete [] m_pString;		
	}		
}

//--------------------------------------------------------------------------
//
// member functions
//
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// Init( len )
//--------------------------------------------------------------------------
// size??? memory???
//--------------------------------------------------------------------------
void	
MString::Init(int len)
{
	Release();

	m_Length = 0;
	m_pString = new char [len + 1];
	m_pString[0] = NULL;
}

//--------------------------------------------------------------------------
// Relase
//--------------------------------------------------------------------------
// memory???? ????
//--------------------------------------------------------------------------
void	
MString::Release()
{
	if (m_pString!=NULL)
	{
		delete [] m_pString;
		m_pString = NULL;
		m_Length = 0;
	}
}

//--------------------------------------------------------------------------
// Assign operator =
//--------------------------------------------------------------------------
void	
MString::operator = (const char* str)
{
	if (m_pString!=NULL)
	{
		delete [] m_pString;
		m_pString = NULL;
	}

	if (str==NULL)
	{
		m_Length = 0;
	}
	else
	{
		m_Length = strlen(str);

		if (m_Length!=0)
		{
			m_pString = new char [m_Length + 1];
			strcpy( m_pString, str );
		}
	}
}

//--------------------------------------------------------------------------
// Assign operator =
//--------------------------------------------------------------------------
void
MString::operator = (const MString& str)
{
	//--------------------------------
	// ????? 0?? ???..
	//--------------------------------
	if (str.m_Length==0)
	{
		if (m_pString!=NULL)
		{
			delete [] m_pString;			
			m_pString	= NULL;
			m_Length	= 0;			
		}		
	}
	//--------------------------------
	// ????? 0 ????? ???...
	//--------------------------------
	else
	{
		if (m_pString!=NULL)
		{
			delete [] m_pString;
		}			
		
		m_Length = str.m_Length;
		m_pString = new char [m_Length + 1];
		
		strcpy(m_pString, str.m_pString);
	}
}

//--------------------------------------------------------------------------
// Format
//--------------------------------------------------------------------------
// ?????? ???????? string?? ?????.
//--------------------------------------------------------------------------
void
MString::Format(const char* format, ...)
{
	va_list		vl;

    va_start(vl, format);
    vsprintf(s_pBuffer, format, vl);
    va_end(vl);

	*this = s_pBuffer;
}

//--------------------------------------------------------------------------
// Save To File
//--------------------------------------------------------------------------
void		
MString::SaveToFile(std::ofstream& file)
{
	file.write((const char*)&m_Length, 4);

	// length?? 0?? ??? ?????..
	if (m_Length!=0)
	{
		file.write((const char*)m_pString, static_cast<int>(m_Length));
	}
}

//--------------------------------------------------------------------------
// Load From File
//--------------------------------------------------------------------------
void
MString::LoadFromFile(ivfstream& file)
{
	if (m_pString!=NULL)
	{
		delete [] m_pString;
		m_pString = NULL;
	}

	// --- diagnostic: capture offset before read ---
	int preOff = file.tellg();

	m_Length = 0;
	file.read((char*)&m_Length, 4);

	// Sanity-check the length.  Anything over 64 KB in .inf strings is almost
	// certainly a read that drifted off alignment due to a struct layout change.
	if (m_Length > 0x10000)
	{
		FILE* dbg = fopen("Log\\winmain_step.log", "a");
		if (dbg)
		{
			fprintf(dbg,
				"\n*** MString::LoadFromFile absurd length ***\n"
				"  preReadOffset=%d (0x%X)\n"
				"  m_Length=%u (0x%X)\n"
				"  postReadOffset=%d\n"
				"This means an earlier read drifted off-alignment.\n",
				preOff, preOff,
				(unsigned)m_Length, (unsigned)m_Length,
				(int)file.tellg());
			fflush(dbg);
			fclose(dbg);
		}
		// Force a controlled throw so the catch block in WinMain reports it.
		throw std::bad_alloc();
	}

	bool bNull = (m_Length != 0);

	if(bNull)
	{
		// len?? 0?? ??? ?????...
		m_pString = new char [m_Length + 1];

		if (m_Length != 0)
		{
			file.read((char*)m_pString, static_cast<int>(m_Length));
		}

		m_pString[m_Length] = '\0';
	}
	else
	{
		const char* nullString	= "<null string>";
		const int nullStringLen	= strlen(nullString);

		m_pString = new char [nullStringLen + 1];
		//m_Length = nullStringLen+1;

		strcpy(m_pString, nullString);
	}
}
