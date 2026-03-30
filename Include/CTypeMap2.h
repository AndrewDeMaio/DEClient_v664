//----------------------------------------------------------------------
// CTypeMap2.h
//----------------------------------------------------------------------
// DataType은 pointer type이어야 한다.
//
// fstream와 fstream의 충돌로 인해서..
// 임시로...
// fstream을 사용하지 않는 version이당. - -;
//----------------------------------------------------------------------

#ifndef __CTYPEMAP2_H__
#define	__CTYPEMAP2_H__

#pragma warning(disable:4786)

#include <map>

//----------------------------------------------------------------------
// CTypeMap2 (id, DataType*)의 map
//----------------------------------------------------------------------
template <class DataType>
class CTypeMap2 : public std::map<unsigned int, DataType*> {
public:
	using TYPE_MAP = std::map<unsigned int, DataType*>;

public:
	CTypeMap2();
	virtual ~CTypeMap2();

	//-----------------------------------------------------
	// Release
	//-----------------------------------------------------
	virtual void			Release();

	//-----------------------------------------------------
	// Item Info
	//-----------------------------------------------------
	virtual bool			AddData(unsigned int id, DataType* pData);
	virtual DataType*		GetData(unsigned int id);
	virtual const DataType* GetData(unsigned int id) const;
	virtual bool			RemoveData(unsigned int id);

protected:
	TYPE_MAP data_map;
};

//----------------------------------------------------------------------
//
// CTypeMap2
//
//----------------------------------------------------------------------
template <class DataType>
CTypeMap2<DataType>::CTypeMap2()
{
}

template <class DataType>
CTypeMap2<DataType>::~CTypeMap2()
{
	Release();
}

//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
template <class DataType>
void
CTypeMap2<DataType>::Release()
{
	auto iData = data_map.begin();

	while (iData != data_map.end())
	{
		DataType* pData = (*iData).second;

		delete pData;

		iData++;
	}

	data_map.clear();
}

//----------------------------------------------------------------------
// Add Data
//----------------------------------------------------------------------
template <class DataType>
bool
CTypeMap2<DataType>::AddData(unsigned int id, DataType* pData)
{
	auto iData = data_map.find(id);

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
CTypeMap2<DataType>::GetData(unsigned int id)
{
	auto iData = data_map.find(id);

	if (iData == data_map.end())
	{
		// 없는 경우 
		return nullptr;
	}

	// 있는 경우
	return (*iData).second;
}

//----------------------------------------------------------------------
// Get Data
//----------------------------------------------------------------------
template <class DataType>
const DataType*
CTypeMap2<DataType>::GetData(unsigned int id) const
{
	auto iData = data_map.find(id);

	if (iData == data_map.end())
	{
		// 없는 경우 
		return nullptr;
	}

	// 있는 경우
	return (*iData).second;
}

//----------------------------------------------------------------------
// Remove NPC Info
//----------------------------------------------------------------------
template <class DataType>
bool
CTypeMap2<DataType>::RemoveData(unsigned int id)
{
	auto iData = data_map.find(id);

	if (iData == data_map.end())
	{
		// 없는 경우 
		return false;
	}

	// 있으면 지워줘야 한다.
	delete (*iData).second;

	data_map.erase(iData);

	return true;
}

#endif

