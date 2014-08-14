/*
 * =====================================================================================
 *
 *       Filename:  test_morris.cpp
 *
 *    Description:  test morris 
 *
 *        Version:  1.0
 *        Created:  08/11/2014 11:36:38 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#include "morris.h"
#include "rbtree.h"
#include <string>
#include <iostream>
using namespace std;
void test_rec(Node *root){
	rec_in(root);
}

void test_pre(Node *root){
	morris_pre(root);
}

void test_rb(){
	RBTree<int, string> map;	
	map[3] = "three";
	map[4] = "four";
	cout << map ;
}


void test_in(Node *root){
	morris_in(root);
}
void test(int argc, char **argv){
	Node *root = new Node(6);
	root->left = new Node(4);
	root->right = new Node(8);
	root->left->left = new Node(3);
	root->left->right = new Node(5);
	root->right->left = new Node(7);
	root->right->right = new Node(9);
	test_rec(root);
	test_pre(root);
	test_in(root);
	test_rb();
}
