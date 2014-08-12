/*
 * =====================================================================================
 *
 *       Filename:  test_stat.cpp
 *
 *    Description:  test frequency
 *
 *        Version:  1.0
 *        Created:  08/12/2014 01:04:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#include "../src/rbtree.h"
#include <fstream>
#include <map>
#include "../src/priority_queue.h"
#include <iostream>
using namespace std;


void freqTopN(size_t n = 100){
	map<string, int> freq;
	//ifstream ifs("~/snooker/data/alg4/alg4-data/leipzig1M.txt", std::ifstream::in);
	//ifstream ifs("/home/gtx780/snooker/data/alg4/algs4-data/tale.txt", std::ifstream::in);
	ifstream ifs("/home/gtx780/snooker/data/alg4/algs4-data/leipzig1M.txt", std::ifstream::in);
	string str;
	int count = 0;
	while(ifs>>str){
		++freq[str];
		++count;
	}
	
	multimap<int,string> top;
	MinPQ<int> pq;
	for(map<string,int>::iterator it = freq.begin(); it != freq.end(); ++it){
		if( pq.size() < n ){
			//top[(it->second)] = it->first;
			top.insert( pair<int, string>(it->second, it->first) );
			pq.insert(it->second);
		}else{
			if( it->second > pq.min() ){
				top.erase( top.find(pq.removeMin()) );
				pq.insert(it->second);
				top.insert( pair<int, string>(it->second, it->first) );
				//top[it->second] = it->first;
			}
		}
	}
	//output top n freq and it's corresponding string(key word)
	for(multimap<int,string>::iterator it = top.begin(); it != top.end(); ++it){
		cout << it->first << "=>" << it->second << endl;
	}
	cout << "# of words: " << count<<endl;;	
}
