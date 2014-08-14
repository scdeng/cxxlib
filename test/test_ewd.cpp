/*
 * =====================================================================================
 *
 *       Filename:  test_ewd.cpp
 *
 *    Description:  test EWD
 *
 *        Version:  1.0
 *        Created:  08/11/2014 01:06:53 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#include "digraph.h"
#include "shortest_path.h"
#include <fstream>
using namespace std;
typedef EdgeWeightedDigraph EWD;
typedef DirectedWeightedEdge Edge;

void printPath(const deque<Edge> &path ){
	int L = path.size();
	for(int i=0; i<L; ++i){
		cout << path[i] <<"  ";
	}
}

void test_out(EdgeWeightedDigraph &G){
	cout << G;
}
void test_sp(EdgeWeightedDigraph &G){
	DijkstraSP sp(G,0);
	for( int i=0; i<G.V(); ++i){
		cout <<"shortest path from s to " << i <<" is: "<< sp.weightTo(i) << endl;
	}
}

void test_nBF(EWD &G){
	NaiveBellmanFordSP sp(G,0);
	//cout<<"============naive bellman ford===========" << endl;
	for( int i=0; i<G.V(); ++i){
		cout <<"shortest path from s to " << i <<" is: "<< sp.weightTo(i) << endl;
	}
}
void test_bf(EWD &G){
	BellmanFordSP sp(G,0);
	//cout<<"============bellman ford===========" << endl;
	for( int i=0; i<G.V(); ++i){
		cout <<"shortest path from s to " << i <<" is: "<< sp.weightTo(i) << endl;
	}
}

void test_bfnc(EWD &G){
	BellmanFordSP sp(G,0);
	cout <<"has negative cycle:  " << sp.hasNegativeCycle() << endl;
	printPath( sp.negativeCycle() );
}
void test(){
	ifstream is("tinyEWD.txt", std::ifstream::in);
	EdgeWeightedDigraph G(is);
	test_out(G);
	//test_sp(G);
	//test_nBF(G);
	test_bf(G);
	//test_bfnc(G);
}
