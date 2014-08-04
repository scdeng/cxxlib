/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  driver program
 *
 *        Version:  1.0
 *        Created:  08/02/2014 11:02:53 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "../src/queue.h"
#include "../src/array.h"
#include "../src/list.h"
#include "../src/stack.h"

using namespace std;
void test_list();
void test_array();
void test_list_iterator();
void test_array_iterator(int);
void test_queue();
void test_stack();
int main(int argc, char **argv){
	//test_list();
	//test_array();
	test_list_iterator();
	//int num = atoi(argv[1]);
	//test_array_iterator(12);
	test_stack();
	test_queue();
	return 0;
}

void test_stack(){
	cout << endl << endl << "===============================test stack==============================" <<endl;
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
