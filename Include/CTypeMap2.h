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
	// Storage is the inherited std::map, and only that.
	//
	// This class used to own a second map (data_map) as well: AddData and
	// friends used it, while find/insert/erase used the inherited one. The
	// world list rendered blank because size() reported the empty inherited
	// map, and shadowing size/begin/end onto data_map then left find() and
	// end() looking at DIFFERENT containers - which is what made
	// MHelicopterManager::RemoveHelicopter dereference an end node and kill
	// the client whenever a slayer left view.
	//-----------------------------------------------------

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
	auto iData = this->begin();

	while (iData != this->end())
	{
		DataType* pData = (*iData).second;

		delete pData;

		iData++;
	}

	this->clear();
}

//----------------------------------------------------------------------
// Add Data
//----------------------------------------------------------------------
template <class DataType>
bool
CTypeMap2<DataType>::AddData(unsigned int id, DataType* pData)
{
	auto iData = this->find(id);

	if (iData != this->end())
	{
		// �̹� �ִ� ���
		// pData�� �ܺο��� ��������Ѵ�.
		return false;
	}

	//------------------------------------------------------
	// ���� ��� --> �߰�
	//------------------------------------------------------
	this->insert({ id, pData });

	return true;
}

//----------------------------------------------------------------------
// Get Data
//----------------------------------------------------------------------
template <class DataType>
DataType*
CTypeMap2<DataType>::GetData(unsigned int id)
{
	auto iData = this->find(id);

	if (iData == this->end())
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
	auto iData = this->find(id);

	if (iData == this->end())
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
	auto iData = this->find(id);

	if (iData == this->end())
	{
		// ���� ��� 
		return false;
	}

	// ������ ������� �Ѵ�.
	delete (*iData).second;

	this->erase(iData);

	return true;
}

#endif

