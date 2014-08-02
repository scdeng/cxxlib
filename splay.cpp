/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  test driver of splay tree
 *
 *        Version:  1.0
 *        Created:  07/31/2014 06:28:11 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */
#include "splay_tree.h"
#include <iostream>
using namespace std;

void insertSeq(splay_tree<int> &st, int arr[], int n){
	while(n-- > 0){
		st.insert(arr[n]);
	}
}

int main(){
	splay_tree<int> st;
	int arr[10] = {3, 4, 6, 8, 2, 5, 9, 7, 10, 1};
	insertSeq(st, arr, 10);
	
	node<int> *p = st.find(4);

	cout << p->key <<endl;
	
	cout << "it works" <<endl;
	return 0;

}
