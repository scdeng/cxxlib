/*
 * =====================================================================================
 *
 *       Filename:  test_rbt.cpp
 *
 *    Description:  red black tree test
 *
 *        Version:  1.0
 *        Created:  08/06/2014 10:03:03 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */
#include <iostream>
#include "rbtree.h"
using namespace std;
void create_rbt(RBTree<int, string> &rb){
	rb.insert(30, "thirty");
	rb.insert(2, "two");
	rb.insert(15, "fifteen");
	rb.insert(13, "thirteen");
	rb.insert(8, "eight");
	rb.insert(23, "tweenty-three");
	rb.insert(100, "a hundred");
	rb.insert(40, "forty");
}
void printBST(RBTree<char,int> &rb){
	cout << rb;
	cout << "height of tree is: " << rb.height() << endl;
}

void test_insert(){
	RBTree<char,int> rb;
	cout << "*************************************************" << endl;
	rb.insert('S', 0);
	//printBST(rb);	
	rb.insert('E', 0);
	//printBST(rb);
	rb.insert('A', 0);
	//printBST(rb);
	rb.insert('R', 0);
	//printBST(rb);
	rb.insert('C', 0);
	//printBST(rb);
	rb.insert('H', 0);
	//printBST(rb);
	rb.insert('X', 0);
	//printBST(rb);
	rb.insert('M', 0);
	//printBST(rb);
	rb.insert('P', 0);
	//printBST(rb);
	rb.insert('L', 0);
	printBST(rb);
	cout << "************************************************" << endl;
	cout << "min is " << rb.min()<<endl;
//	while( !rb.empty() ){
//		rb.removeMax();
//		cout << rb ;
//	}
	cout << "=====================================" <<endl;
	
	rb.remove('A');

	cout << rb;

	cout << endl;

}

void test_rbt(){
	RBTree<int, string> rb;
	create_rbt(rb);
	cout << rb;
	cout << "is empty? " << rb.empty()<<endl;
	cout << "height of rb is ? " << rb.height() <<endl;
	cout << "min key = " << rb.min() << endl;
	cout << "max key = " << rb.max() << endl;
	cout << "max key rank of 30 is " << rb.rank(30) << endl;
	cout << "4th key is " << rb.select(4) << endl;
	cout << "keys are: " << endl;
//	deque<int> keys = rb.keys(); 
//	for( deque<int>::iterator it = keys.begin(); it != keys.end(); ++it){
//		cout << *it << " ";
//	}
	
	rb.removeMin();

	cout << rb ;
	cout << "=====================================" <<endl;
	
	cout << endl;
}

void delete_rbt(){
	RBTree<unsigned, double> rb;
	double v;
	srand(time(NULL));
	for(unsigned i=0; i<1e4; ++i){
		v = rand() * 1001 * 0.001f;
		rb.insert(i,v);
	}
	cout<< "height is " << rb.height() << endl;
	cout<< "# of left rotation = " << NUM_OF_LEFT_ROTATION << endl;
	cout<< "# of right rotation = " << NUM_OF_RIGHT_ROTATION <<endl;
	unsigned n;
	while( cin >> n ){
		cout <<"key = " << n << "\tvalue = " <<  rb.get(n) << endl;
		if (n==1) break;
	}
	cout <<"size of BST is " << rb.size() << endl;

	cout <<"=====================ceiling floor======================" << endl;
	cout <<"floor of 4 is " << rb.floor(4) << endl;
	cout <<"floor of 9 is " << rb.floor(9) << endl;
	cout <<"ceiling of 4 is " << rb.ceiling(4) << endl;
	cout <<"ceiling of 9 is " << rb.ceiling(9) << endl;
	cout <<" is 2-3 tree ?  " << rb.isLeftLeaning23tree() << endl;
	cout <<"is size consistent ?  " << rb.isSizeConsistent() << endl;
	cout <<"Is balanced search tree ?  " << rb.isBalancedSearchTree() << endl;
	cout <<"is rank consistent ?  " << rb.isRankConsistent() << endl;

}

void test_rbtree(){
	delete_rbt();
	cout << "insertion " << NUM_OF_INSERTION << " times" <<endl;
	cout << "deletion " << NUM_OF_DELETION << " times" <<endl;
	int n;
	cin>>n;
}


void test_alg4(){
	RBTree<char, int> rbt;
	
	rbt.insert('S', 0);
	cout << "******************after insert S************************" << endl;
	printBST(rbt);
	cout << endl;

	rbt.insert('E', 1);
	cout << "******************after insert E************************" << endl;
	printBST(rbt);
	cout << endl;
	
	rbt.insert('A', 2);
	cout << "******************after insert A************************" << endl;
	printBST(rbt);
	cout << endl;
	
	rbt.insert('R', 3);
	cout << "******************after insert R************************" << endl;
	printBST(rbt);
	cout << endl;

	rbt.insert('C', 4);
	cout << "******************after insert C************************" << endl;
	printBST(rbt);
	cout << endl;
	
	rbt.insert('H', 5);
	cout << "******************after insert H************************" << endl;
	printBST(rbt);
	cout << endl;
	
	rbt.insert('X', 6);
	cout << "******************after insert X************************" << endl;
	printBST(rbt);
	cout << endl;
	
	rbt.insert('M', 7);
	cout << "******************after insert M************************" << endl;
	printBST(rbt);
	cout << endl;
	
	rbt.insert('P', 8);
	cout << "******************after insert P************************" << endl;
	printBST(rbt);
	cout << endl;
	
	rbt.insert('L', 9);
	cout << "******************after insert L************************" << endl;
	printBST(rbt);
	
	rbt.removeMax();
	cout << "******************after remove max**********************" << endl;
	printBST(rbt);

	rbt.removeMax();
	cout << "******************after remove max**********************" << endl;
	printBST(rbt);
	
	rbt.removeMin();
	cout << "******************after remove min**********************" << endl;
	printBST(rbt);

	rbt.removeMin();
	cout << "******************after remove min**********************" << endl;
	printBST(rbt);

}



void test(int argc, char **argv){
	test_alg4();
}
