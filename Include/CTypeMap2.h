//----------------------------------------------------------------------
// CTypeMap2.h
//----------------------------------------------------------------------
// DataType�� pointer type�̾�� �Ѵ�.
//
// fstream�� fstream�� �浹�� ���ؼ�..
// �ӽ÷�...
// fstream�� ������� �ʴ� version�̴�. - -;
//----------------------------------------------------------------------

#ifndef __CTYPEMAP2_H__
#define	__CTYPEMAP2_H__

#pragma warning(disable:4786)

#include <map>

//----------------------------------------------------------------------
// CTypeMap2 (id, DataType*)�� map
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

	//-----------------------------------------------------
	// Container access.
	//
	// This class derives from std::map AND owns data_map, but every
	// method above operates only on data_map -- so the inherited base
	// map is permanently empty. Callers using size()/begin()/end()
	// therefore saw an empty container no matter how much AddData()
	// had been called. That is what made the world list render blank:
	// UI_SetWorldList() reads g_pServerInformation->size().
	//
	// Shadow the base accessors so they report the data that is
	// actually stored. (Removing the inheritance would be cleaner but
	// is a wider change than this needs to be.)
	//-----------------------------------------------------
	typename TYPE_MAP::size_type size() const { return data_map.size(); }
	bool empty() const { return data_map.empty(); }

	typename TYPE_MAP::iterator begin() { return data_map.begin(); }
	typename TYPE_MAP::iterator end() { return data_map.end(); }
	typename TYPE_MAP::const_iterator begin() const { return data_map.begin(); }
	typename TYPE_MAP::const_iterator end() const { return data_map.end(); }

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
		// �̹� �ִ� ���
		// pData�� �ܺο��� ��������Ѵ�.
		return false;
	}

	//------------------------------------------------------
	// ���� ��� --> �߰�
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
		// ���� ��� 
		return nullptr;
	}

	// �ִ� ���
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
		// ���� ��� 
		return nullptr;
	}

	// �ִ� ���
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
		// ���� ��� 
		return false;
	}

	// ������ ������� �Ѵ�.
	delete (*iData).second;

	data_map.erase(iData);

	return true;
}

#endif

