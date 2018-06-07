#include <stdio.h>
#include "LTArray.h"
#include "LTSortedArray.h"
#include "LTTree.h"
#include "LTMap.h"

void print_node(char edge, const char *data)
{
	if (data == nullptr)
	{
		char buf[3] = {edge,'\n','\0'};
		PrintString(buf);
	}
	else
	{
		char buf[80];
		sprintf(buf, "%c [%s]\n", edge, data);
		PrintString(buf);
	}
}

void print_indentation(int level)
{
	for (int i = 0; i < level; i++)
		PrintString(" ");
}

int main(int argc, char **argv)
{
	LTTree<char, const char*> tree(0);
	tree.data = nullptr;
	auto node = tree.Insert("Hello", 5);
	node->data = "H";
	node = tree.Insert("World", 5);
	node->data = "W";
	// Note: can use lambda for print_node and print_indentation but I prefer extracting these functions due to potential additional Print() in the future.
	tree.Print(print_node, print_indentation, 0);

	LTMap<int, const char *> strmap;
	strmap.Put(0, "Hello");
	strmap.Put(1, "World");
	strmap.Put(2, "Lightech");
	for(int i = 0; i < 3; i++)
	{
		auto str = strmap.Lookup(i, nullptr);
		char buf[100];
		sprintf(buf, "%d -> %s\n", i, str);
		PrintString(buf);
	}

	return 0;
}