/*
 * =====================================================================================
 *
 *       Filename:  test_maxpq.cpp
 *
 *    Description:  test max pq
 *
 *        Version:  1.0
 *        Created:  08/12/2014 12:49:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#include "priority_queue.h"
#include <iostream>
using namespace std;

void test_pq(){
	IndexMaxPQ<char> pq(2e7);
	pq.insert(0, 'A');
	pq.insert(2, 'C');
	pq.insert(4, 'D');
	pq.insert(8, 'M');
	//cout << pq;
	int n;
	cout << "input a number" << endl;
	cin >> n;
}

void test(){
	test_pq();
}
