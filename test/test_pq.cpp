/*
 * =====================================================================================
 *
 *       Filename:  test_pq.cpp
 *
 *    Description:  test priority queue
 *
 *        Version:  1.0
 *        Created:  08/09/2014 01:59:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;
void test_array(){
	Array<int> arr;
	arr.push_back(3);
	arr.push_back(5);
	cout << arr;
	for(Array<int>::iterator it = arr.begin(); it != arr.end(); ++it){
		cout << *it << endl;
	}

	cout << "assignment operator"<<endl;
	Array<int> arr2 = arr;
	arr2.push_back(7);
	cout << arr2;
	arr2.clear();
	cout<< "copy constructor" << endl;
	Array<int> arr3(arr2);
	cout << arr3;
	arr3.push_back(1);
	cout << arr3;
	cout<<"=========================================="<<endl<<endl;
	arr.clear();
	for(int i=0; i<1e6; ++i){
		arr.push_back(i);
		//cout << "size is: " << arr.size() <<
		//	"\tcapacity is: " << arr.capacity() << endl;
	}
	cout <<"it works"<<endl;
}

void test_insert( MinPQ<char> &pq){
	cout<< "is empty    " << pq.empty() << endl;
	cout << "size is: " << pq.size()<< endl;
	pq.insert( 'D' );
	pq.insert( 'B' );
	pq.insert( 'C' );
	pq.insert( 'M' );
	pq.insert( 'A' );
		
//	char ch;
//	while( true ){
//		cin >> ch;
//		if( ch == 'q' ) break;
//		pq.insert(ch);
//		cout << pq;
//	}
	cout << pq;
	cout << "it works" <<endl;
}

void test_delMin(MinPQ<char> &pq){
	char min = pq.removeMin();
	cout <<"min is: " << min << endl;
	cout << pq;
}
void test_IndexPQ(IndexMinPQ<double> &pq){
	pq.insert(0, 4.7);
	pq.insert(4, 1.3);
	pq.insert(3, 0.8);
	cout << pq;
	cout <<"=================================="<<endl<<endl;
	pq.changeKey(3, 0.5);
	cout << pq;

	cout <<"==============================="<<endl<<endl;
	pq.insert(6, 1.4);
	cout << pq;
//	cout<<pq;
//	cout << "minimum key is: " << pq.min() <<endl;
//	cout << "index of minimum key is: " << pq.removeMin() <<endl;
//	cout<<pq;
	cout <<"==============================="<<endl<<endl;
	pq.remove(0);
	cout << pq;
}
void test(){
	//test_array();
	//MinPQ<char> pq;
	//test_insert(pq);
	//test_delMin(pq);
	IndexMinPQ<double> pq(9);
	test_IndexPQ(pq);
}
