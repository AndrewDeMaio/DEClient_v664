//////////////////////////////////////////////////////////////////////
// 
// SocketOutputStream.h 
// 
// by Reiot
// 
//////////////////////////////////////////////////////////////////////

#ifndef __SOCKET_OUTPUT_STREAM_H__
#define __SOCKET_OUTPUT_STREAM_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Socket.h"
#if __CONTENTS(__CRYPT)
#include "Crypt.h"
#endif
// constant definitions
const unsigned int DefaultSocketOutputBufferSize = 8192;

// forward declaration
class Packet;

//////////////////////////////////////////////////////////////////////
//
// class SocketOutputStream
//
//////////////////////////////////////////////////////////////////////

class SocketOutputStream {

//////////////////////////////////////////////////
// constructor/destructor
//////////////////////////////////////////////////
public :
	
	// constructor
	SocketOutputStream ( Socket * sock , uint BufferSize = DefaultSocketOutputBufferSize );
	
	// destructor
	virtual ~SocketOutputStream ();

	
//////////////////////////////////////////////////
// methods
//////////////////////////////////////////////////
public :
	
	// write data to stream (output buffer)
	// *CAUTION*
	// string 을 버퍼에 writing 할 때, 자동으로 size 를 앞에 붙일 수도 있다.
	// 그러나, string 의 크기를 BYTE/WORD 중 어느 것으로 할 건지는 의문이다.
	// 패킷의 크기는 작을 수록 좋다는 정책하에서 필요에 따라서 string size 값을
	// BYTE 또는 WORD 를 수동으로 사용하도록 한다.
	uint write ( const char * buf , uint len );
	uint write(const std::string& buf) { return write(buf.c_str(), static_cast<uint>(buf.size())); }
	void write ( const Packet * pPacket );
	
    uint write ( bool   buf ) { return write( (const char*)&buf, szbool   ); }
    uint write ( char   buf ) { return write( (const char*)&buf, szchar   ); }
    uint write ( uchar  buf ) { return write( (const char*)&buf, szuchar  ); }
    uint write ( short  buf ) { return write( (const char*)&buf, szshort  ); }
    uint write ( ushort buf ) { return write( (const char*)&buf, szushort ); }
    uint write ( int    buf ) { return write( (const char*)&buf, szint    ); }
    uint write ( uint   buf ) { return write( (const char*)&buf, szuint   ); }
    uint write ( long   buf ) { return write( (const char*)&buf, szlong   ); }
    uint write ( ulong  buf ) { return write( (const char*)&buf, szulong  ); }

// Deliberately NOT provided: uint write(size_t).
// It existed under #ifdef _WIN64 and silently wrote sizeof(size_t) bytes, which
// is how commit db7b6ba's size_t length prefixes compiled on x64 while emitting
// 8 bytes where DEServer reads 1. Without it, passing a size_t to write() is a
// compile error on both platforms, which is the behaviour we want.

	// flush stream (output buffer) to socket
	uint flush ();

	// resize buffer 
	void resize ( int size );

	// get buffer length
	int capacity () const { return m_BufferLen; }
 
    // get data length in buffer
    uint length () const;
    uint size () const { return length(); }
 
    // check if buffer is empty
    bool isEmpty () const { return m_Head == m_Tail; }

    // get debug string
    std::string toString () const
    {
        StringStream msg;
        msg << "SocketOutputStream(m_BufferLen:"<<m_BufferLen<<",m_Head:"<<m_Head<<",m_Tail:"<<m_Tail
<<")";
        return msg.toString();
    }
#if __CONTENTS(__CRYPT)
	bool CopyPacket(PACKETDATA* pData, uint len);
	bool Replace(PACKETDATA* pData, uint len);
	void EncryptHeader(PACKETDATA* pData) { m_pCryptManager->EncryptHeader(pData); }
#endif




//////////////////////////////////////////////////
// attributes
//////////////////////////////////////////////////
private :
	
	// socket
	Socket * m_Socket;
	
	// output buffer
	char * m_Buffer;
	
	// buffer length
	uint m_BufferLen;
	
	// buffer head/tail
	uint m_Head;
	uint m_Tail;
#if __CONTENTS(__CRYPT)
	uint m_RealMsgSize;
	KEY_TYPE m_Key;
	CCryptManager* m_pCryptManager;
#endif
};

#endif
