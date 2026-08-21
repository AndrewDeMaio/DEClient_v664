//////////////////////////////////////////////////////////////////////
//
// Filename    : WhisperTypes.h
// Description : Wire type shared by the CRWhisper packet and the client's
//               WhisperManager. It lives here, with the protocol, so that
//               Packet\ never has to include a UI header.
//
//////////////////////////////////////////////////////////////////////

#ifndef __WHISPER_TYPES_H__
#define __WHISPER_TYPES_H__

#include <windows.h>
#include <string>

struct WHISPER_MESSAGE
{
	std::string msg;
	DWORD color;
};

#endif