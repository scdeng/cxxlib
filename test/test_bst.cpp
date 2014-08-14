/*
 * =====================================================================================
 *
 *       Filename:  test_bst.cpp
 *
 *    Description:  test binary search tree
 *
 *        Version:  1.0
 *        Created:  08/05/2014 12:55:46 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */
#include "tree.h"
#include <iostream>
#include <string>
using namespace std;
void print_help(){
	cout << endl;
	cout << "======================================" <<endl;
	cout << "add for insert(key, value)..." << endl;
	cout << "del for remove(key)..."<<endl;
	//cout << "print for print tree..." << endl;
	cout << "rmax for remove max..." << endl;
	cout << "rmin for remove min..." << endl;
	cout << "max for print maximum key..." << endl;
	cout << "min for print minimum key..." << endl;
	cout << "h for print height..." << endl;
	cout << "keys for print all keys..." << endl;
	cout << "rank for rank of key..." << endl;
	cout << "select for select kth key..." << endl;
	cout << "q for quit..." << endl;
}
void make_bst(BSTree<int, string> &bst){
	bst.insert(20, "tweenty");
	bst.insert(15, "fifteen");
	bst.insert(18, "eighteen");
	bst.insert(30, "thirty");
	bst.insert(25, "tweenty-five");
	bst.insert(35, "thirty-five");
	bst.insert(32, "thirty-two");
}


void test_bst(){
	BSTree<int, string> bst;
	cout << bst.empty() <<endl;	
	make_bst(bst);
	//bst.inorder();

	string op;
	int key;
	string value;
	unsigned k;

	while(true){
		cout << "input operator... " ;
		print_help();
		cin>> op;
		if (op == "add"){
			cout << "input key... " ;
			cin >> key;
			cout << "input value... ";
			cin >> value;
			bst.insert(key,value);
		}else if (op == "del"){
			cout << "input key... " ;
			cin >> key;
			bst.remove(key);
		}else if (op == "print"){
			//bst.inorder();
		}else if (op == "rmax"){
			bst.removeMax();
		}else if (op == "rmin"){
			bst.removeMin();
		}else if( op == "q"){
			break;
		}else if(op == "max"){
			cout << "max is " << bst.max() << endl;
		}else if(op == "min"){
			cout << "min is " << bst.min() << endl;
		}else if(op == "h"){
			cout << "height is " << bst.height() << endl;
		}else if(op == "keys"){
			cout << bst.keys() << endl;
		}else if( op == "rank" ){
			cout << "input key... " ;
			cin >> key;
			cout << "rank of " << key << " is " << bst.rank(key) << endl;
		}else if ( op == "select" ){
			cout << "input k... " ;
			cin >> k;
			cout << "k th keys is " << bst.select(k) << endl;
		}
		else{
			print_help();
		}
	}
}


