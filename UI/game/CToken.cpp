//------------------------------------------------------------------------
// CToken.cpp
//------------------------------------------------------------------------
#include "Client_PCH.h"
#include "CToken.h"


//------------------------------------------------------------------------
//
// constructor/destructor
//
//------------------------------------------------------------------------
CToken::CToken(const char* str)
{
   m_pString = nullptr;
   m_pCurrent = nullptr;

   SetString(str);
}

CToken::~CToken()
{
   Release();
}


//------------------------------------------------------------------------
//
// member functions
//
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// 메모리 해제
//------------------------------------------------------------------------
void
CToken::Release()
{
   if (m_pString)
      delete [] m_pString;
}

//------------------------------------------------------------------------
// string을 다시 설정한다.
//------------------------------------------------------------------------
void
CToken::SetString(const char *str)
{
	Release();
	  
   if (str)
   {
	   m_nStringLenght	= strlen(str);

      // 메모리 잡기
      m_pString = new char [m_nStringLenght + 1];

      strcpy(m_pString, str);

      m_pCurrent = m_pString;
   }
}

//------------------------------------------------------------------------
// delimiter에 의해서 현재의 token string을 구한다.
//------------------------------------------------------------------------
const char*
CToken::GetToken(const char* delimiter)
{
	if (!m_pCurrent ||
		m_pCurrent > m_pString + m_nStringLenght - 1)
	{
		return nullptr;
	}
	
	SkipSpace();

	char* pTemp = m_pCurrent;
	
	// delimiter가 최초로 나타나는 pointer를 구한다.
	char* pFound = strpbrk(m_pCurrent, delimiter);
	
	// last token
	if (!pFound)
	{
		m_pCurrent = nullptr;
	}
	// else
	else
	{
		*pFound = '\0';
		
		m_pCurrent = pFound+1;
	}
	
	return pTemp;
}

//------------------------------------------------------------------------
// 현재 위치부터 끝까지의 string을 넘겨준다.
//------------------------------------------------------------------------
const char*
CToken::GetEnd()
{
   SkipSpace();

   char* pTemp = m_pCurrent;

   m_pCurrent = nullptr;

   return pTemp;
}

//------------------------------------------------------------------------
// 공백이 여러개 있을때 무시한다.
//------------------------------------------------------------------------
void
CToken::SkipSpace()
{
	while (m_pCurrent != nullptr && *m_pCurrent != '\0' && *m_pCurrent == ' ')
	{
		m_pCurrent += 1;
	}
}

