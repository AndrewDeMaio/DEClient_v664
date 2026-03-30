/*-----------------------------------------------------------------------------

	tree.h

	범용 Tree class.

	19991001. KJTINC
	19991004.

-----------------------------------------------------------------------------*/

#ifndef __TREE__
#define __TREE__

#include <limits.h>
#include <fstream>
#include <list>
#include "vfstream.h"
#include "typedef.h" // bool -> bool로 고칠 예정

typedef unsigned long LIST_LEVEL;
typedef unsigned long NODE_NUM;		// node number
typedef unsigned long UNIQUE_ID;	// double word exec id

#define EMPTY_UNIQUE_ID					ULONG_MAX // NO ZERO

/*-----------------------------------------------------------------------------
  Node

  `unique_id 는 app에서 구별하는 유일한 code이다. app마다 요구하는 node의 속성이
   있을테지만, 그것을 일반화하기 위해 unique_id 하나만 둔다. 이 unique_id로
	node의 특성을 부여하는 것은 app의 몫이다.
-----------------------------------------------------------------------------*/
struct S_NODE
{
	UNIQUE_ID				unique_id;	// if double-click, send signal to app
	char *					sz_title;	// title of a node
	bool						packed;		// do not show sub list
	std::list<S_NODE *>	list;
	std::list<S_NODE *> *parent_list; // node를 포함하는 list의 pointer

	// node table에서의 좌표
	LIST_LEVEL				level;
	NODE_NUM					node;

	// file load시에 필요한 좌표.
	LIST_LEVEL				save_level;
	NODE_NUM					save_node;
};

typedef std::list<S_NODE *> TREE_LIST;

/*-----------------------------------------------------------------------------
  Node table
-----------------------------------------------------------------------------*/
struct S_LEVEL
{
	S_NODE **	pp_node;
	NODE_NUM		count;	// 가지고 있는 node 수
};

/*-----------------------------------------------------------------------------
  Class Tree
-----------------------------------------------------------------------------*/
class C_TREE
{
private:
	bool LoadTree(ivfstream &file);
	void SaveTree(std::ofstream &file, TREE_LIST *p_list);

protected:
	//
	// Node table
	//
	TREE_LIST *	m_p_root; // the root 
	S_LEVEL *	m_p_level;
	LIST_LEVEL	m_level_count;

	S_NODE *		InsertNode(TREE_LIST *p_list, char *sz_title, UNIQUE_ID unique_id, 
		                    LIST_LEVEL level, NODE_NUM node);
	void			AddNodeToTable(LIST_LEVEL level, S_NODE *p_node);
	void			DeleteNodeFromTable(LIST_LEVEL level, NODE_NUM node);
	void			EraseNode(S_NODE *p_node);

public:
	bool Load(char *sz_full_filename);
	bool Save(char *sz_full_filename);
	void			TogglePackStateOfNode(LIST_LEVEL m, NODE_NUM n);
	void			InsertNode(LIST_LEVEL level, NODE_NUM node, char *sz_title, UNIQUE_ID unique_id);
	LIST_LEVEL	GetLevelCountFromTable() const;
	S_NODE *		GetNodeFromTable(LIST_LEVEL m, NODE_NUM n);
	NODE_NUM		GetNodeCountFromTable(LIST_LEVEL m);
	NODE_NUM		GetNodeCountFromTable();
	void			EraseNode(LIST_LEVEL m, NODE_NUM n);
	void			EraseTree();
	void			PrintTree();
	void			PrintTree(TREE_LIST *p_list);

	C_TREE();
	~C_TREE();
};

#endif