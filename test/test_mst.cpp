/*
 * =====================================================================================
 *
 *       Filename:  test_mst.cpp
 *
 *    Description:  minimum spanning tree test
 *
 *        Version:  1.0
 *        Created:  08/10/2014 10:50:24 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#include "mst.h"
void test_Array(){
	Array<int> arr;
	arr.push_back(3);
	arr.push_back(9);
	arr.push_back(6);
	arr.pop_back();
	cout << arr;
}

void test_MinPQ(){
	MinPQ<WeightEdge> pq;
	WeightEdge e1(0, 1, 4.3);
	pq.insert(e1);
	WeightEdge e2(0, 1, 3.4);
	pq.insert(e2);
	WeightEdge e3(3, 4, 2.4);
	pq.insert(e3);
	WeightEdge e4(5, 6, 0.9);
	pq.insert(e4);
	WeightEdge e5(2, 3, 1.4);
	pq.insert(e5);
	cout << pq;
	pq.removeMin();
	cout << pq;
	WeightEdge e6(1, 2, 0.2);
	pq.insert(e6);
	cout << pq;

}

void test_lazyPrim(EdgeWeightGraph &G){
	LazyPrim mst(G);
//	deque<WeightEdge> edges = mst.MST();
//	for(unsigned i=0; i<edges.size(); ++i){
//		cout << edges[i];
//	}
	cout << "minimum weight is: " << mst.weight() << endl;
}
void test_prim(EdgeWeightGraph &G){
	PrimMST mst(G);
//	vector<WeightEdge> edges = mst.MST();
//	for( size_t i=0; i<edges.size(); ++i){
//		cout << edges[i];
//	}
	cout <<"minimum weight is: " << mst.weight() << endl;
}

void test_kruskal(EdgeWeightGraph &G){
	KruskalMST mst(G);
//	vector<WeightEdge> edges = mst.MST();
//	for( size_t i=0; i<edges.size(); ++i){
//		cout << edges[i];
//	}
	cout <<"weight of MST is: " << mst.weight() << endl;
}

void test(){
	ifstream ifs("largeEWG.txt", std::ifstream::in);
	EdgeWeightGraph G(ifs);
	//test_lazyPrim(G);
	//test_prim(G);
	test_kruskal(G);
}
