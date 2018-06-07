/**
 * Tree data structure template
 *
 * Tree is a frequently used data structure but it is not available in the C++ standard.
 * Our implementation consists of (sorted) array of children, indexed by edge.
 * In other words, each tree node is a map from edge -> child.
 * We use generic type for tree edge and each node also stores some associated data.
 * That way, we can make a tree whose edges are labelled by integers, characters, etc.
 * depending on the application.
 *
 * The key interface of tree consists of:
 *  - GetChild
 *  - CreateChild
 *  - RemoveChild
 *  - Insert(path) : Insert a path into the tree, creating intermediate nodes
 *  - Traverse(path) : Traverse the tree following a path
 *  - DFS : Visit the tree in depth first search manner
 *
 * Applications of trees are numerous in LawTeX and DevMax:
 *  - Virtual file system
 *  - Missing package look-up
 *  - Code suggestion in text editor
 */

#ifndef _LVITACPP_DATA_STRUCTURE_LT_TREE
#define _LVITACPP_DATA_STRUCTURE_LT_TREE

#include "LTSortedArray.h"

/// Forward declaration to define default function parameters to create node and compare
template <typename _EdgeType, typename _DataType>
class LTTree;

template <typename _EdgeType, typename _DataType>
inline LTTree<_EdgeType, _DataType> *default_create_node(LTTree<_EdgeType, _DataType> * parent, _EdgeType e);

template <typename _EdgeType, typename _DataType>
inline int default_compare_edge_tree(_EdgeType e, LTTree<_EdgeType, _DataType> *child);

///
/// Tree data structure
/// _EdgeType: type of edge label (for example, char for a tree labeled by characters)
/// _DataType: type of data stored in each tree node
/// The key method of this data structure is to Traverse the tree along a path, Insert a path
/// to the tree, and Depth First Search.
/// 
template <typename _EdgeType, typename _DataType>
class LTTree : public LTSortedArray<LTTree<_EdgeType, _DataType>*, _EdgeType>
{
public:
	LTTree(_EdgeType e) : LTSortedArray<LTTree<_EdgeType, _DataType>*, _EdgeType>(0)
	{
		edge = e;
	}

	// Return the subtree by following the edge e; create new subtree with edge e if there is none
	// Function to create a new node if the sub-tree doesn't exist, this is to allow for easy extension of this class for instance, tree with parent
	LTTree<_EdgeType, _DataType> *CreateChild(
		_EdgeType e,
		int(*compare_edge)(_EdgeType e, LTTree<_EdgeType, _DataType> *child) = default_compare_edge_tree,
		LTTree<_EdgeType, _DataType> *(*create_node)(LTTree<_EdgeType, _DataType> *parent, _EdgeType e) = default_create_node
	)
	{
		int c = -1;
		int p = ((LTSortedArray<LTTree<_EdgeType, _DataType>*,_EdgeType>*)this)->Insert(e, compare_edge, c);
		if (c != 0 || this->elements[p] == nullptr)
		{
			// For some reason, it could happen that c == 0 & elements[p] == nullptr
			this->elements[p] = create_node(this, e);
		}

		//assert(this->elements[p] != nullptr);
		return this->elements[p];
	}

	// Return the subtree by following the edge e; nullptr if there is no such sub-tree
	LTTree<_EdgeType, _DataType> *GetChild(
		_EdgeType e,
		int (*compare_edge)(_EdgeType e, LTTree<_EdgeType, _DataType> *child) = default_compare_edge_tree
	)
	{
		int c = -1;
		int p = this->Find(e, compare_edge, c);

		return (c == 0 ? this->elements[p] : nullptr);
	}

	// Return the subtree by following the edge e; nullptr if there is no such sub-tree
	bool RemoveChild(
		_EdgeType e,
		int (*compare_edge)(_EdgeType e, LTTree<_EdgeType, _DataType> *child) = default_compare_edge_tree
	)
	{
		// TODO Implement
		return false;
	}

	/// Insert node to the tree according to the specified path
	/// @param path
	///             An array of edges; originally, I use an 'edge generating function'
	/// @param depth
	///             The length of the `path`
	/// @param create_node
	///             Function to create a new node if the sub-tree doesn't exist, this is to allow for easy extension of this class for instance, tree with parent
	LTTree<_EdgeType, _DataType> *Insert(
		const _EdgeType *path,
		int depth,
		int(*compare_edge)(_EdgeType e, LTTree<_EdgeType, _DataType> *child) = default_compare_edge_tree,
		LTTree<_EdgeType, _DataType> *(*create_node)(LTTree<_EdgeType, _DataType> *parent, _EdgeType e) = default_create_node
	)
	{
		auto t = this;
		int i = 0;
		while (i < depth)
		{
			t = t->CreateChild(path[i], compare_edge, create_node);
			//assert(t != nullptr);
			i++;
		}

		return t;
	}

	/// Traverse the tree by path; return the farthest node we can reach
	/// @param path
	///             An array of edges; originally, I use an 'edge generating function'
	/// @param depth
	///             The length of the `path`
	/// @param compare
	///             Function to compare an edge and a node's edge for binary search
	LTTree<_EdgeType, _DataType> *Traverse(
		const _EdgeType *path,
		int &depth,
		int(*compare)(_EdgeType e, LTTree<_EdgeType, _DataType> *child) = default_compare_edge_tree
	)
	{
		auto t = this;
		int i = 0;
		while (depth > 0)
		{
			auto child = t->GetChild(path[i], compare);
			i++;
			if (child == nullptr)
				return t;
			else
			{
				t = child;
				depth--;
			}
		}

		return t;
	}

	/// Perform Depth First Search traversal, invoke <visit_node>
	/// function when visiting a node. This function should return
	/// <true> if we should not continue with the traversal and
	/// <false> otherwise. For example, the function could indicate
	/// if it found the search result (if this tree is meant for
	/// some kind of searching).
	/// This function return <true> if some invocation of <visit_node>
	/// returns <true>.
	/// @param visit_node
	///            Function to invoke on a visited node
	/// @param state
	///            Additional state function for visit_node
	template <typename _State>
	bool DFS(
		bool (*visit_node)(LTTree<_EdgeType, _DataType> *node, _State &state),
		void (*exit_node)(LTTree<_EdgeType, _DataType> *node, _State &state),
		_State &state
	)
	{
		bool done = visit_node(this, state);
		for(int i = 0; !done && i < this->Count(); i++)
		{
			done = this->elements[i]->DFS(visit_node, exit_node, state);
		}
		exit_node(this, state);
		return done;
	}

	/// Print the tree for debugging
	/// @param print_node
	///             Generic method to print the content of a node
	/// @param print_indentation
	///             Generic function to print the indentation, `level` will be passed to it
	/// @param level
	///             Indentation level for this node
	void Print(
		void (*print_node)(_EdgeType edge, _DataType data),
		void (*print_indentation)(int level),
		int level
	)
	{
		print_indentation(level);
		print_node(edge, data);
		for (int i = 0; i < this->Count(); i++)
		{
			this->elements[i]->Print(print_node, print_indentation, level + 1);
		}
	}

	_EdgeType edge;
	_DataType data;
};

template <typename _EdgeType, typename _DataType>
inline LTTree<_EdgeType, _DataType> *default_create_node(LTTree<_EdgeType, _DataType> * parent, _EdgeType e)
{
	//return new LTTree<_EdgeType, _DataType>(e);
	LTTree<_EdgeType, _DataType> *node = (LTTree<_EdgeType, _DataType> *)realloc(nullptr, sizeof(LTTree<_EdgeType, _DataType>));
	node->Init(0);
	node->edge = e;
	node->data = nullptr;
	return node;
}

template <typename _EdgeType, typename _DataType>
inline int default_compare_edge_tree(_EdgeType e, LTTree<_EdgeType, _DataType> *child)
{
	return e - child->edge;
}

#endif