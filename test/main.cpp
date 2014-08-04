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

#include "../src/array.h"
#include "../src/list.h"
#include <stdlib.h>

using namespace std;
void test_list();
void test_array();
void test_list_iterator();
void test_array_iterator(int);

int main(int argc, char **argv){
	//test_list();
	//test_array();
	test_list_iterator();
	//int num = atoi(argv[1]);
	//test_array_iterator(12);
	return 0;
}

void test_array(){
	//array<int>  ai(4, 3);
	//cout << ai[1] <<endl;
	//ai[2] = 5;
	Array<double> ai;
	for(unsigned i=0; i<8; i++){
		ai.push_back(i*1.5);
	}
		
	ai.insert(2,0.47);
	cout << ai;
	cout<< "size = " << ai.size() <<endl;
	cout<< "capacity = " << ai.capacity() <<endl;
	ai.erase(0);
	cout << ai;
	cout<< "size = " << ai.size() <<endl;
	cout<< "capacity = " << ai.capacity() <<endl;
	
	cout << ai.pop_back() <<endl;
	cout << ai;
	cout<< "size = " << ai.size() <<endl;
	cout<< "capacity = " << ai.capacity() <<endl;
}


void test_list(){
	
	List<int> li;
	for(int i=0; i<3; i++){
		cout << "check Linked list is " << assert_list(li) <<endl;
		li.push_front(i);
	}
	cout << li.size()<<endl;;
	cout<<li;
	
	li.push_back(100);
	cout << "check Linked list is " << assert_list(li) <<endl;
	
	cout << li.size()<<endl;;
	cout << li;

	li.push_front(100);
	cout << "check Linked list is " << assert_list(li) <<endl;
	li.push_front(47);
	cout << "check Linked list is " << assert_list(li) <<endl;
	cout << li.size()<<endl;;
	cout << li;
	
	List<int> bob = li;
	cout << "check Linked list is " << assert_list(li) <<endl;
	cout << bob.size() <<endl;
	cout << bob;



	li.clear();
	cout << "check Linked list is " << assert_list(li) <<endl;
	cout << "li's size = " << li.size() <<endl;;
	cout << li;

	cout << "bob's size = " << bob.size() <<endl;
	cout << bob;
	
	List<int> cesear(bob);

	cout << "check Linked list is " << assert_list(li) <<endl;
	cout << "cesear's size = " << cesear.size() <<endl;
	cout << cesear;

	while(  !cesear.empty() ){

		cout << "front is " << cesear.front() <<endl;
		cout << "check cesear is " << assert_list(li) <<endl;
		cout << cesear.size() <<endl;
		cout << cesear;
		cesear.pop_front();
	}



}

void test_list_iterator(){
	List<int> li;

	cout << "check Linked list is " << assert_list(li) <<endl;


	for(int i=0; i<6; i++){
		li.push_front(i);
		cout << "check Linked list is " << assert_list(li) <<endl;
	}
	List<int>::iterator iter;
	for(iter = li.begin(); iter != li.end(); ++iter){
		cout << "from iterator...\t"  <<  *iter <<endl;
	}

	iter = li.begin();

	li.insert(iter, 12);
	cout << "li size is " << li.size() <<endl;
	cout <<li ;

	iter = li.begin();
	iter = li.remove(iter);
	
	cout << li.size() << "\t" << assert_list(li) << endl;
	cout << li;

	cout << "=======================test insert======================" <<endl;
	
	li.insert(iter, 2, 120);
	cout << "check Linked list is " << assert_list(li) <<endl;
	cout << li.size() <<endl;
	cout << li ;
	cout << "==========================================================" <<endl;
	
	cout << endl << endl;
	cout << "=======================java style iterator===========================" <<endl;
	
	List<int>::iterator it3 = li.begin();
	while(it3.hasNext()){
		cout << "java style iterator>>> " << it3.next() <<endl;
	}

	cout << "==========================================================" <<endl;
	
	List<int>::iterator it2 = li.end(), it1 = li.begin();
	--it2; --it2;
	it1++;
	cout << endl << endl;
	cout << *it1 << endl << *it2 <<endl <<endl;
	li.remove(it1, it2);	
	cout << "=======================test remove=====================" <<endl;
	cout << "check Linked list is " << assert_list(li) <<endl;
	cout << li.size() <<endl;
	cout << li ;
	cout << "==========================================================" <<endl;
	
	List<int>::iterator it4 = li.begin();
	it4++;
	*it4 = 1293;
	cout << endl << endl << li;
	
	
	cout << endl << endl << "==============iterator erase==========" <<endl;
	List<int>::iterator it6 = li.begin();
	List<int>::iterator it7 = li.end();
	++it6;
	--it7;
	cout << "*it4 = " << *it6 <<endl;
	cout << "*it5 = " << *it7 <<endl;
	li.swap(it6,it7);
	cout << "li size = " << li.size() <<endl;
	cout << li;
	cout << "================================================" <<endl;

}



void test_array_iterator(int num){
	Array<double> ai;
	for(unsigned i=0; i<8; i++){
		ai.push_back(i*1.5);
	}
	cout <<endl<<endl;
	cout << "==============iterate through=================" <<endl;
	for(Array<double>::iterator it = ai.begin(); it !=  ai.end(); ++it){
		cout << "from iterator....\t" << *it <<endl;
	}
	cout << "=============end iterate through==============" <<endl;
	cout << ai <<endl;
	
	Array<double>::iterator it1 = ai.end();
	ai.insert(it1,120.5);
	ai.insert(ai.size(), 214);
	cout << endl << endl << "================iterator insert==============" <<endl;
	cout << "ai size = " << ai.size() <<endl;
	cout << ai; 
	cout << "================end iterator insert==========" <<endl;
	

	cout << endl << endl << "==============iterator erase==========" <<endl;
	//Array<double>::iterator it2 = ai.end();
	cout << "ai size = " << ai.size() <<endl;
	cout << ai;
	cout << "================================================" <<endl;



	cout << endl << endl << "==============iterator erase==========" <<endl;
	Array<double>::iterator it4 = ai.begin();
	Array<double>::iterator it5 = ai.end();
	++it4;
	--it5;
	cout << "*it4 = " << *it4 <<endl;
	cout << "*it5 = " << *it5 <<endl;
	ai.swap(it4,it5);
	cout << "ai size = " << ai.size() <<endl;
	cout << ai;
	cout << "================================================" <<endl;

}
