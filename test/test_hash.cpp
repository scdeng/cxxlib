/*
 * =====================================================================================
 *
 *       Filename:  test_hash.cpp
 *
 *    Description:  hash test case
 *
 *        Version:  1.0
 *        Created:  08/13/2014 12:10:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#include <stack>
#include "hash_function.h"
#include "hash_map.h"
#include <iostream>
#include <cstdlib>
using namespace std;

void test_hf(){
	stack<double> st;
	cout << sizeof(size_t) << endl;
	string str("hello");
	cout << "hash code of string: " << hashcode(str) << endl;	
	cout << "hash code of stack: " << hashcode(st) << endl;
	cout << "hash code of const char array: " << hashcode("helloworld")<< endl;
	cout << "hash code of int: " << hashcode(3) << endl;
	double d = 8.9;
	cout << "hash code of double: " << hashcode(d) << endl;
}

void test_hashmap(){
	HashMap<string, int> map;
	map.insert("abc", 1);
	map.insert("efg", 2);
	map.insert("hij", 3);
	map.insert("klm", 4);
	map.insert("nop", 5);
	cout << "what happens"<<endl;
	cout << map;
	cout << "contain klm: " << map.contain("klm")<<endl;
	map.remove("hij");
	//after remove
	cout << "after remove hij" << endl;
	cout << map;
	cout << "bucket_count is: " << map.bucket_count() << endl;
	cout << "bucket 1 has: " << map.bucket_size(1) << endl;
}
void test(int argc, char ** argv){
	test_hf();
	test_hashmap();
}
