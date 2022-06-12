#include "rbt.hpp"

int main(void)
{
	ft::RBT<int, int> tree;
	tree.insert(1, 1);
	tree.insert(5, 5);
	tree.insert(2, 2);
	tree.insert(3, 3);
	tree.insert(6, 6);
	tree.insert(7, 7);
	tree.insert(8, 8);
	tree.insert(9, 9);
	tree.insert(10, 10);
	tree.insert(11, 11);
	tree.insert(12, 12);
	tree.insert(13, 13);
	tree.insert(14, 14);
	tree.insert(15, 15);
	tree.insert(16, 16);
	tree.insert(17, 17);
	tree.insert(18, 18);
	tree.insert(19, 19);
	tree.insert(20, 20);
	tree.insert(21, 21);
	tree.insert(22, 22);
	tree.erase(11);
	tree.erase(22);
	tree.erase(20);
	tree.erase(16);
	tree.erase(17);
	tree.print();
}