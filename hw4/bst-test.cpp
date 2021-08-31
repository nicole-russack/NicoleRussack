#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{ 

	AVLTree<int, int> testTree;

	testTree.insert(std::make_pair(2, 8));
	testTree.insert(std::make_pair(1, -50));
	testTree.insert(std::make_pair(3, 0));
	testTree.insert(std::make_pair(10, 0));
	testTree.insert(std::make_pair(15, 0));


	std::cout << "Before any removals, tree is: " << std::endl;
	testTree.print();


	testTree.remove(-1);
	


	std::cout << "After removing -1 (which doesn't exist), tree is: " << std::endl;
	testTree.print();


    cout << "DO TESTS RIGHT NOW TO SEE ALL VALUS" << endl;    
	testTree.remove(2);

	std::cout << "After removing 2 (the root), tree is: " << std::endl;
	testTree.print();


	testTree.remove(10);
    std::cout << "After removing 10, tree is: " << std::endl;
	testTree.print();



    return 0;
}