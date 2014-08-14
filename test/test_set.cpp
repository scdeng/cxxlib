/*
 * =====================================================================================
 *
 *       Filename:  test_set.cpp
 *
 *    Description:  set test 
 *
 *        Version:  1.0
 *        Created:  08/09/2014 10:39:02 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#include "set.h"
#include <iostream>
#include <string>
using namespace std;
void test_set(Set<int> &set){
	set.insert(4);
	set.insert(6);
	set.insert(40);
	set.insert(23);
	set.insert(12);
	cout << set;
	cout <<"0 th element is: " << set[0] << endl;
	cout <<" min is: " << set.min() << endl;
	cout <<" max is: " << set.max() << endl;
}
void test(){
	Set<int> set;
	test_set(set);
	cout << "size of bool is: " << sizeof(bool) << endl;
	cout<< "size of string is: " << sizeof(string) << endl;
}
