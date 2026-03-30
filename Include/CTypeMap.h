//----------------------------------------------------------------------
// CTypeMap.h
//----------------------------------------------------------------------
// DataType은 pointer type이어야 한다.
//----------------------------------------------------------------------

#ifndef __CTYPEMAP_H__
#define	__CTYPEMAP_H__

#pragma warning(disable:4786)

#include <map>
#include "vfstream.h"

//----------------------------------------------------------------------
// CTypeMap (id, DataType*)의 map
//----------------------------------------------------------------------
template <class DataType>
class CTypeMap : public std::map<unsigned int, DataType*> {
	public :
		using TYPE_MAP = std::map<unsigned int, DataType*>;

	public :
		CTypeMap();
		virtual ~CTypeMap();

		//-----------------------------------------------------
		// Release
		//-----------------------------------------------------
		virtual void		Release();

		//-----------------------------------------------------
		// Item Info
		//-----------------------------------------------------
		virtual bool		AddData( unsigned int id, DataType* pData );
		virtual DataType*	GetData( unsigned int id );
		virtual bool		RemoveData( unsigned int id );

		//-----------------------------------------------------
		// File I/O
		//-----------------------------------------------------
		virtual void		SaveToFile(std::ofstream& file);
		virtual void		LoadFromFile(ivfstream& file);

	protected :
		TYPE_MAP data_map;
};



//----------------------------------------------------------------------
//
// CTypeMap
//
//----------------------------------------------------------------------
template <class DataType>
CTypeMap<DataType>::CTypeMap()
{
}

template <class DataType>		
CTypeMap<DataType>::~CTypeMap()
{
	Release();
}

//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
template <class DataType>
void
CTypeMap<DataType>::Release()
{
	auto iData = data_map.begin();

	while (iData != data_map.end())
	{
		DataType*	pData	= (*iData).second;		

		delete pData;

		iData ++;
	}

	data_map.clear();
}

//----------------------------------------------------------------------
// Add Data
//----------------------------------------------------------------------
template <class DataType>
bool				
CTypeMap<DataType>::AddData( unsigned int id, DataType* pData )
{
	auto iData = data_map.find( id );

	if (iData != data_map.end())
	{
		// 이미 있는 경우
		// pData는 외부에서 지워줘야한다.
		return false;
	}

	//------------------------------------------------------
	// 없는 경우 --> 추가
	//------------------------------------------------------
	data_map.insert({ id, pData });

	return true;
}

//----------------------------------------------------------------------
// Get Data
//----------------------------------------------------------------------
template <class DataType>
DataType*	
CTypeMap<DataType>::GetData( unsigned int id )
{
	auto iData = data_map.find( id );

	if (iData == data_map.end())
	{
		// 없는 경우 
		return NULL;
	}

	// 있는 경우
	return (*iData).second;
}

//----------------------------------------------------------------------
// Remove NPC Info
//----------------------------------------------------------------------
template <class DataType>
bool				
CTypeMap<DataType>::RemoveData( unsigned int id )
{
	auto iData = data_map.find( id );

	if (iData == data_map.end())
	{
		// 없는 경우 
		return false;
	}

	// 있으면 지워줘야 한다.
	delete (*iData).second;

	data_map.erase( iData );

	return true;
}

//----------------------------------------------------------------------
// Save To File
//----------------------------------------------------------------------
template <class DataType>
void		
CTypeMap<DataType>::SaveToFile(std::ofstream& file)
{
	auto iData = data_map.begin();

	//-----------------------------------------------------
	// 개수 저장
	//-----------------------------------------------------
	int infoSize = data_map.size();
	file.write((const char*)&infoSize, 4);

	//-----------------------------------------------------
	// 각 info 저장
	//-----------------------------------------------------
	while (iData != data_map.end())
	{
		unsigned int	id		= (*iData).first;
		DataType*		pData	= (*iData).second;		

		file.write((const char*)&id, 4);	// id 저장
		pData->SaveToFile( file );			// NPC info 저장

		iData ++;
	}
}
		
//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
template <class DataType>
void		
CTypeMap<DataType>::LoadFromFile(ivfstream& file)
{
	//-----------------------------------------------------
	// 기존에 있던것 제거
	//-----------------------------------------------------
	Release();

	//-----------------------------------------------------
	// size 
	//-----------------------------------------------------
	int infoSize;
	file.read((char*)&infoSize, 4);

	//-----------------------------------------------------
	// 각 info
	//-----------------------------------------------------
	unsigned int id;
	for (int i = 0; i < infoSize; i++)
	{
		file.read((char*)&id, 4);
		DataType* pData = new DataType;

		pData->LoadFromFile(file);

		//-----------------------------------------------------
		// map에 추가한다.
		//-----------------------------------------------------
		if (!AddData(id, pData))
		{
			delete pData;
		}
	}
}



#endif

