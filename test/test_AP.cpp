/*
 * =====================================================================================
 *
 *       Filename:  test_AP.cpp
 *
 *    Description:  test for articulation point
 *
 *        Version:  1.0
 *        Created:  08/18/2014 07:14:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <fstream>
#include <iostream>
using namespace std;
void test_AP(const Graph &G, int v){
	ArticPoint ap(G);
	cout << G;
	cout << "vertex " << v << " is ap:  " << ap.isArticulationPoint(v) << endl;
}

void test(int argc, char **argv){
	if( argc != 2 ){
		cout << "usage: " <<argv[0] <<" vertex"<<endl;
		exit(1);
	}
	int v = atoi(argv[1]);

	ifstream ifs("../data/tinyG.txt", std::ifstream::in);
	Graph G(ifs);
	test_AP(G,v);
}
