/*
 * =====================================================================================
 *
 *       Filename:  test_wg.cpp
 *
 *    Description:  edge weighted graph test
 *
 *        Version:  1.0
 *        Created:  08/10/2014 08:57:33 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */
#include "graph.h"
using namespace std;

void test_createEWG(EdgeWeightGraph &ewg){
	cout << ewg;		
}

void test(){
	ifstream is("tinyEWG.txt", std::ifstream::in);
	EdgeWeightGraph ewg(is);
	test_createEWG(ewg);
}

