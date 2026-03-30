//////////////////////////////////////////////////////////////////////////////
/// @file iovfs_base.h
/// @author chyaya
/// @date 2007.06.26
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include <WTypes.h>
#include "CNFS.h"

// Darkeden 
//#define SPECIALIZE_DARKEDEN

#define VFS_VERSION		1	///< VirtualFileSystem 
//# define SPECIALIZE_DARKEDEN
class IFileIO;

//////////////////////////////////////////////////////////////////////////////
/// @struct VirtualFileHeader
/// @brief Virtual File Header
///
///      
//////////////////////////////////////////////////////////////////////////////
struct VirtualFileHeader
{
	DWORD	FileSize;		///<   
	BYTE	Version;		///< VFS Version (   2 ? - _-;;)
	BYTE	IsCompressed;	///<   

	/// @brief  
	/// @sa Init()
	VirtualFileHeader()	{ Init(); }

	/// @brief    .
	void Init()
	{
		FileSize		= 0;
		Version			= VFS_VERSION;
		IsCompressed	= 0;
	}
};

/// struct VirtualFileHeader 
/// sizeof()  4   
///    .
#define VF_HEADER_SIZE		6


//////////////////////////////////////////////////////////////////////////////
/// @class VirtualFileSystem
/// @brief Virtual File System
///
///     
//////////////////////////////////////////////////////////////////////////////
class VirtualFileSystem
{
public:
	/// @brief  
	/// @sa Init()
	VirtualFileSystem();

	/// @brief start 
	/// @param filename  
	/// @param flags  
	/// @sa Start()
	/// @warning        . (flags FS_READ)\n
	///          VFS             .
	VirtualFileSystem(LPCTSTR filename, int flags = FS_READ);

	/// @brief 
	~VirtualFileSystem();

	/// @brief     
	enum { FILE_COPY_BUFFER_SIZE = 65536 };

public:
	/// @brief    .
	void		Init();

	/// @brief Virtual File System .
	/// @param filename  
	/// @param flags  
	/// @return  
	/// @warning        . (flags FS_READ)\n
	///          VFS             .
	bool		Start(LPCTSTR filename, int flags = FS_READ);

	/// @brief Virtual File System 
	void		End();

	/// @brief VFS   .
	/// @param srcname    
	/// @param compress    
	/// @warning (2007.06.26)       .
	///                   .
	/// @sa AddFileRename()
	void		AddFile(LPCTSTR srcname, bool compress = false);

	/// @brief VFS     .
	/// @param srcname    
	/// @param destname    
	/// @param compress    
	/// @warning (2007.06.26)       .
	///                   .
	/// @sa AddFile()
	void		AddFileRename(LPCTSTR srcname, LPCTSTR destname, bool compress = false);

#ifdef SPECIALIZE_DARKEDEN
	/// @brief VFS   . (TypePackFile  )
	/// @param srcname    
	/// @param compress    
	/// @warning (2007.06.26)   
	/// @sa AddTypePackFileRename(), AddFile(), AddFileRename()
	///
	/// TypePack  Type     
	///     . - _-;;
	///  
	void		AddTypePackFile(LPCTSTR srcname, bool compress = false);

	/// @brief VFS     . (TypePackFile  )
	/// @param srcname    
	/// @param destname    
	/// @param compress    
	/// @warning (2007.06.26)   
	/// @sa AddTypePackFile(), AddFile(), AddFileRename()
	///
	/// TypePack  Type     
	///     . - _-;;
	///  
	void		AddTypePackFileRename(LPCTSTR srcname, LPCTSTR destname, bool compress = false);
#endif // SPECIALIZE_DARKEDEN

	/// @brief VFS   .
	/// @param filename    
	///
	/// filename      
	///    .
	void		DeleteFile(LPCTSTR filename);

	/// @brief       
	/// @param filename   
	/// @return   true
	///
	///           .
	///           
	/// ,       true .
	///      .
	///       . - _-;;
	bool		IsFileExist(LPCTSTR filename) const;

	/// @brief       
	/// @param filename   
	/// @return   (BYTE)
	///
	///           
	///    ,      ,
	///       .
	///          . - _-;;
	int			GetFileSize(LPCTSTR filename);

	/// @brief      .
	/// @param srcname    
	/// @return  
	/// @sa CreateTempFileRename()
	///
	/// CreateTempFileRename()    
	/// make_temp_filepath()       .
	
	bool		CreateTempFile(LPCTSTR srcname);

	/// @brief      .
	/// @param srcname    
	/// @param destname    
	/// @return  
	/// @sa CreateTempFile()
	///
	///      .
	///     
	bool		CreateRealFile(LPCTSTR srcname, LPCTSTR destname);

	/// @brief NFS Wrapper   .
	/// @return CNFS 
	CNFS*		GetNFS()	{ return &m_NFS;	}

protected:
	/// @brief    .
	/// @param szFullPath    
	/// @return  
	///
	///      .
	bool		BuildFullPathDirectory(LPCTSTR szFullPath);
	
private:
	CNFS		m_NFS;	///< NFS Wrapper
};

typedef VirtualFileSystem	VFSYSTEM;
typedef VFSYSTEM*			LPVFSYSTEM;