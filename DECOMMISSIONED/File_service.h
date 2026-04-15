#ifndef __FILE_SERVICE__
#define __FILE_SERVICE__

#include <stdlib.h>
#include "typedef.h"
#include "listbox.h"


/*-----------------------------------------------------------------------------
  File service name
-----------------------------------------------------------------------------*/
typedef enum
{
	NO_FILE_SERVICE,
	SNAME_DIR_CHANGE,
	SNAME_FILE_OPEN,
	SNAME_FILE_SAVE,
	SNAME_FILE_DELETE,
	SNAME_FILE_COPY,
	SNAME_FILE_SELECT,

} E_FILE_SERVICE_NAME;

/*-----------------------------------------------------------------------------
  File service info

  `file을 double click하면 app로 전달된다.
-----------------------------------------------------------------------------*/
typedef struct
{
	char *					sz_file_name;
	char *					sz_full_file_name; // included path
	E_FILE_SERVICE_NAME	e_service_name;

} S_FILE_SERVICE_INFO;

/*-----------------------------------------------------------------------------
  File manager class
-----------------------------------------------------------------------------*/
class C_FILE_SERVICE
{
private:
	void ChangeDir(char *sz_cur_dirname, char *sz_pathname);
	bool GetParentDir(char *sz_name);

	void (*m_fp_FileServiceProc)(const S_FILE_SERVICE_INFO *);

	//
	// MixPath_FileName method에서 필요한 작업버퍼.
	// `이 버퍼는 정적으로 잡혀지고, 따라서 UI가 실행되는 동안 존재한다.
	// `이 버퍼의 포인터는 S_FILE_SERVICE_INFO의 sz_full_file_name으로 가리켜진다.
	//  따라서 app에 file service info를 보낼 때마다 이 값은 새로운 full path로 
	//  변경된다. 이 값을 저장하는 것은 app의 몫이다.
	//
	char m_sz_dir_buffer[_MAX_DIR];

public:
	char *	MixPath_FileName(const char *sz_path, const char *sz_file_name);
	void		SendFileServiceInfoToApp(S_FILE_SERVICE_INFO *S_serviceinfo);
	bool		SetFileServiceProcFp(void (*FileServiceProc)(const S_FILE_SERVICE_INFO *));
	void		RefreshFileList(S_DIALOG_POINTER *dp, char *sz_dirname);

	E_FILE_SERVICE_NAME FileService(S_LIST_ITEM *pS_item_unit, char *sz_pathname, 
												C_LISTBOX::EVENT_CATEGORY category);

	C_FILE_SERVICE();
	~C_FILE_SERVICE();
};

#endif