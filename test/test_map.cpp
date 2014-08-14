/*
 * =====================================================================================
 *
 *       Filename:  test_map.cpp
 *
 *    Description:  test map
 *
 *        Version:  1.0
 *        Created:  08/09/2014 01:04:26 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */
#include "map.h"
#include <string>
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
	vector<int> keys = rb.getAllKeys();
	for(unsigned i=0; i<keys.size(); ++i){
		cout << i << " th key is:  " << keys[i] << endl;
	}
}
void fun(unsigned un){
	cout << "unsigned is " << un << endl;
}
void test_operator( Map<int,string> &map ){
	cout << "is empty   " << map.empty()<<endl;
	map[1] = "one";	
	cout << map;
	cout << "is contain 1 ????     " << map.isContain(1) << endl;

	map.insert(2,"two");
	map.insert(3,"three");
	map.insert(4,"four");
	cout << map;
	map.erase(3);
	cout << map;
	int n = -3;
	fun(n);
}

void test(){
	Map<int,string> map;
	test_operator(map);
	RBTree<int,string> rb;
	create_rbt(rb);
}
