//////////////////////////////////////////////////////////////////////////
//
//							atltypes.cpp
//
// atltypes.inl을 디버그 가능하게 빌드

#include "Client_PCH.h"
#include "atltypes.h"

#ifdef _DEBUG
#define ATLTYPES_INLINE
#include "atltypes.inl"
#endif