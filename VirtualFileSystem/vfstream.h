//////////////////////////////////////////////////////////////////////////////
/// @file iovfs_base.h
/// @author chyaya
/// @date 2007.06.26
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include "VirtualFileSystem.h"
#include "IFileIO.h"

class IFileIO;

//////////////////////////////////////////////////////////////////////////////
/// @class iovfs_base
/// @brief I/O Package File Stream Base
///
///          
/// iostream     .
///  iostream    
///  /     iostream  
///  iostream       . 
//////////////////////////////////////////////////////////////////////////////
class iovfs_base
{
public:
	/// @brief  
	/// @sa Init()
	iovfs_base();

	/// @brief open 
	/// @param szName  
	/// @param nMode   
	/// @sa Init(), open()
	iovfs_base(LPCTSTR szName, int nMode);

	/// @brief 
	/// @sa Destory()
	virtual ~iovfs_base();

public:
	/// @brief  .
	void			Init();

	/// @brief  .
	void			Destory();

public:
	/// @brief  .
	/// @param szName  
	/// @param nMode   
	virtual void	open(LPCTSTR szName, int nMode);

	/// @brief  .
	void			close();

	/// @brief     .
	/// @return    true
	bool			is_open() const;

	/// @brief Get Count.      .
	/// @return    
	/// @sa ivfstream::read()
	int				gcount() const;

	/// @brief       .
	/// @return     true
	bool			is_virtualfile() const;

	/// @brief  VirtualFileSystem .
	/// @param filename VFS 
	/// @param flags  
	/// @warning        . (flags FS_READ)
	///          VFS             .
	/// @sa s_VFSystem
	static bool			start_vfs(LPCTSTR filename, int flags);

	/// @brief  VirtualFileSystem .
	/// @sa s_VFSystem
	static void			end_vfs();	

	/// @brief  VirtualFileSystem  .
	/// @return  VFS 
	/// @sa s_VFSystem
	static LPVFSYSTEM	get_vfs()	{ return &s_VFSystem;	}

protected:
	IFileIO*		m_pFileIO;			///<   
	static VFSYSTEM s_VFSystem;			///<  VirtualFileSystem
};


//////////////////////////////////////////////////////////////////////////////
/// @class ivfstream
/// @brief Virtual File System Input Stream
///
///        
//////////////////////////////////////////////////////////////////////////////
class ivfstream : public iovfs_base
{
public:
	/// @brief  
	ivfstream();

	/// @brief     
	/// @param szName  
	/// @param nMode   , ios_base::in  .
	/// @sa open()
	ivfstream(LPCTSTR szName, int nMode);

	/// @brief 
	~ivfstream();

public:
	/// @brief        .
	/// @param szName  
	/// @param nMode  , ios_base::in  .
	void			open(LPCTSTR szName, int nMode);

	/// \brief  .
	/// \param buf  
	/// \param len   (BYTE)
	void			read(char* buf, unsigned len);

	/// @brief  .
	/// @param off  
	/// @param dir  
	/// - ios_base::beg     (default)
	/// - ios_base::cur    
	/// - ios_base::end    
	void			seekg(long off, int dir = std::ios_base::beg);

	/// @brief    .
	/// @return   
	int				tellg();

	/// @brief   .
	/// @return   true
	bool			eof() const;

	/// @brief   .
	/// @param ch    
	void			get(char& ch);

	/// @brief   .
	/// @param psch    
	/// @param nCount  
	/// @param delim  
	bool			getline(char* psch, int nCount, char delim = '\n');
};


//////////////////////////////////////////////////////////////////////////////
/// @class ovfstream
/// @brief Virtual File System Output Stream
///
///        
//////////////////////////////////////////////////////////////////////////////
class ovfstream : public iovfs_base
{
public:
	/// @brief  
	ovfstream();

	/// @brief     
	/// @param szName  
	/// @param nMode   , ios_base::out  .
	/// @sa open()
	ovfstream(LPCTSTR szName, int nMode);

	/// @brief 
	~ovfstream();

public:
	/// @brief        .
	/// @param szName  
	/// @param nMode  , ios+_base::out  .
	void			open(LPCTSTR szName, int nMode);

	/// @brief   .
	/// @param src  
	/// @param len  
	void			write(const char* src, int len);
};


#ifndef _DEBUG
#define PACKAGEFILE_INLINE inline
#include "vfstream.inl"
#endif