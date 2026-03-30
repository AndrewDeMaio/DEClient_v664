#include <string>
#include "BasicS.h"
#include "directory.h"

/*-----------------------------------------------------------------------------
  GLOBALS
-----------------------------------------------------------------------------*/
C_DIRECTORY		gC_directory;

/*-----------------------------------------------------------------------------
- C_DIRECTORY
- program directory를 넣을 buffer를 할당하고, program directory를 설정한다.
-----------------------------------------------------------------------------*/
C_DIRECTORY::C_DIRECTORY()
{
	// alloc full path mem for program directory
	m_sz_program_directory = new char[MAX_PATH];
	CheckMemAlloc(m_sz_program_directory);

	DWORD count = GetCurrentDirectory(MAX_PATH, m_sz_program_directory);
	if (!count)
		_Error(FAILED_JOB);

	// alloc full path mem for mixed directory
	m_sz_mixed_directory = new char[MAX_PATH];
	CheckMemAlloc(m_sz_mixed_directory);
	memset(m_sz_mixed_directory, 0, MAX_PATH);
}

/*-----------------------------------------------------------------------------
- ~C_DIRECTORY
-
-----------------------------------------------------------------------------*/
C_DIRECTORY::~C_DIRECTORY()
{
	DeleteNewArray(m_sz_program_directory);
	DeleteNewArray(m_sz_mixed_directory);
}

/*-----------------------------------------------------------------------------
- GetMixedPathWidthProgramDir
- Program directory와 인자명을 결합한 경로명을 반환한다.

  `이 값은 바뀔 수 있으므로 저장하지 말것!
-----------------------------------------------------------------------------*/
char * C_DIRECTORY::GetMixedPathWidthProgramDir(const char *name) const
{
	static char temp[MAX_PATH];
	memset(temp, 0, MAX_PATH);

	assert(m_sz_program_directory);
	assert(m_sz_program_directory[0] != 0);

	strcpy_s(temp, sizeof(temp), m_sz_program_directory);
	strcat_s(temp, sizeof(temp) ,name);

	return temp;
}

/*-----------------------------------------------------------------------------
- GetProgramDirectory
-
-----------------------------------------------------------------------------*/
char * C_DIRECTORY::GetProgramDirectory() const
{
	return m_sz_program_directory;
}

/*-----------------------------------------------------------------------------
- GetMixedDirectory
- path와 filename을 mix한다.

  `이 값은 바뀔 수 있으므로 저장하지 말것!
-----------------------------------------------------------------------------*/
char * C_DIRECTORY::GetMixedDirectory(const char * path, const char * filename) const
{
	assert(path);
	assert(filename);

	memset(m_sz_mixed_directory, 0, MAX_PATH);
	strcat_s(m_sz_mixed_directory, MAX_PATH, path);
	//m_sz_mixed_directory[strlen(m_sz_mixed_directory)-2] = 0;
	strcat_s(m_sz_mixed_directory, MAX_PATH, filename);

	return m_sz_mixed_directory;
}

//-----------------------------------------------------------------------------
// ExistFile
//
// file이 존재하면 true를 반환한다.
//-----------------------------------------------------------------------------
bool C_DIRECTORY::ExistFile(const char * fullpath) const
{
	assert(fullpath);

	DWORD ret_sf;
	LPTSTR lp_file;
	char *sz_filename_buf = new char[MAX_PATH];
	CheckMemAlloc(sz_filename_buf);

	// attribute icon
	ret_sf = SearchPath(NULL, fullpath, NULL, MAX_PATH, sz_filename_buf, &lp_file);

	DeleteNewArray(sz_filename_buf);

	if (ret_sf)
		return true;
	else
		return false;
}