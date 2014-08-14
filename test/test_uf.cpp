/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  test file
 *
 *        Version:  1.0
 *        Created:  08/04/2014 06:46:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#include "../src/list.h"
#include "../src/array.h"
#include "../src/queue.h"
#include "../src/stack.h"
#include "../src/union_find.h"
#include <iostream>
#include <fstream>

using namespace std;

void test_stack(){
	cout << endl << endl << "===============test stack====================" <<endl;
	Stack<int> st;
	for(int i=0; i<5; ++i){
		st.push(i);
		cout << st;
	}
	st.top() = 9;
	cout << st;

	for(Stack<int>::iterator it = st.begin(); it != st.end(); ++it){
		cout << "from iterator... " << *it <<endl;
	}
}


void test_union_find(){
	UF uf(20);

	int u, v;
	while(true){
		cin >> u;
		cin >> v;
		if( u == -1 && v == -1){
			break;
		}
		uf.connect(u,v);
	}
	cout << "constructed" <<endl;
	while(true){
		cin >> u;
		cin >> v;
		if(u == -1 && v == -1){
			break;
		}
		cout << "is " << u << " and v connected?  " << uf.isConnected(u,v) <<endl;
	}

}


void test_UF(){
	ifstream ifs("tinyUF.txt", "r");
	
	int N;
	ifs >> N;

	UF uf(N);

	int u, v;
	while ( ifs>>u && ifs>>v){
		uf.connect(u,v);
	}
	
	cout << "constructed" <<endl;
	while(true){
		cin >> u;
		cin >> v;
		if(u == -1 && v == -1){
			break;
		}
		cout << "is " << u << " and v connected?  " << uf.isConnected(u,v) <<endl;
	}

}
