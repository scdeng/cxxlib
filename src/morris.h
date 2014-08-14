/*
 * =====================================================================================
 *
 *       Filename:  morris.h
 *
 *    Description:  morris traversal
 *
 *        Version:  1.0
 *        Created:  08/11/2014 11:25:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */
#include <iostream>
using namespace std;
struct Node{
	int data;
	Node *left;
	Node *right;
	Node(int n):data(n),left(NULL),right(NULL){}
};

void rec_in(Node *root){
	if( !root ){
		return ;
	}
	rec_in(root->left);
	cout << root->data << " ";
	rec_in(root->right);
}


void morris_in(Node *root){
	Node *cur = root;
	Node *pre;
	cout << endl;
	while( cur != NULL ){
		if( cur->left == NULL ){
			cout << cur->data << " ";
			cur = cur->right;
		}else{
			
			pre = cur->left;
			while( pre->right != NULL && pre->right != cur ){
				pre = pre->right;
			}
			//first time to get cur's previous node
			if( pre->right == NULL ){
				pre->right = cur;
				cur = cur->left;
			}else{
				//cur->left subtree has been traversed
				cout << cur->data << " ";
				pre->right = NULL;
				cur = cur->right;
			}
		}
	}
	cout << endl;
}




void morris_pre(Node *root){
	Node *cur = root;
	Node *pre;
	cout << endl;
	while( cur != NULL ){
		if( cur->left == NULL ){
			cout << cur->data << " ";
			cur = cur->right;
		}else{
			
			pre = cur->left;
			while( pre->right != NULL && pre->right != cur ){
				pre = pre->right;
			}
			//first time to get cur's previous node
			if( pre->right == NULL ){
				cout << cur->data << " ";
				pre->right = cur;
				cur = cur->left;
			}else{
				//cur->left subtree has been traversed
				pre->right = NULL;
				cur = cur->right;
			}
		}
	}
	cout << endl;
}
