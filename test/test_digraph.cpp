/*
 * =====================================================================================
 *
 *       Filename:  test_digraph.cpp
 *
 *    Description:  test for directed graph
 *
 *        Version:  1.0
 *        Created:  08/07/2014 09:43:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */
#include "graph.h"
#include "digraph.h"
#include <fstream>
using namespace std;

void print(deque<int> &d){
	for(unsigned i=0; i<d.size() - 1; ++i){
		cout << d[i] << "->";
	}
	if( d.size() - 1 >= 0 ){
		cout << d[d.size()-1] ;
	}
	cout << endl;
}

void make_Digraph(Digraph &dg){
	dg.addEdge(4, 2);
	dg.addEdge(2, 3);
	dg.addEdge(3, 2);
	dg.addEdge(6, 0);
	dg.addEdge(0, 1);
	dg.addEdge(2, 0);
	dg.addEdge(11, 12);
	dg.addEdge(12, 9);
	dg.addEdge(9, 10);
	dg.addEdge(9, 11);
	dg.addEdge(8, 9);
	dg.addEdge(10, 12);
	dg.addEdge(11, 4);
	dg.addEdge(4, 3);
	dg.addEdge(3, 5);
	dg.addEdge(7, 8);
	dg.addEdge(8, 7);
	dg.addEdge(5, 4);
	dg.addEdge(0, 5);
	dg.addEdge(6, 4);
	dg.addEdge(6, 9);
	dg.addEdge(7, 6);
}
void test_graph(){
	ifstream ifs("tinyG.txt", std::ifstream::in);
	Graph tiny(ifs);
	cout << tiny;
	CC cc(tiny);

	cout << " 3, 7 are connected?  " << cc.connected(3,7) <<endl;
	cout << "no. of connected component: " << cc.count() << endl;
	cout << "size of 8 = " << cc.size(8) <<endl;
	cout << "size of 9 = " << cc.size(9) << endl;
	cout << "size of 3 = " << cc.size(3) << endl;
}
void test_print(){
	Digraph dg(13);
	make_Digraph(dg);
	cout << dg;
	ifstream ifs("tinyDG.txt", std::ifstream::in);
	Digraph g2(ifs);
	cout << g2;
}

void test_dfs(){
	ifstream ifs("tinyDG.txt", std::ifstream::in);
	Digraph dg(ifs);
	cout << dg;

	DirectedDFS dfs(dg,0);
	cout << "is 5 reachable from 0 ???   " << dfs.reachable(5) << endl;
	cout << "is 6 reachable from 0 ???   " << dfs.reachable(6) << endl;
	cout << "is 4 reachable from 0 ???   " << dfs.reachable(4) << endl;
	cout << "is 12 reachable from 0 ???   " << dfs.reachable(12) << endl;


}


void test_path(){
	ifstream ifs("tinyDG.txt", std::ifstream::in);
	Digraph dg(ifs);
	cout << dg;

	DirectedDFS dfs(dg,0);
	cout << "is 5 reachable from 0 ???   " << dfs.reachable(5) << endl;
	cout << "is 6 reachable from 0 ???   " << dfs.reachable(6) << endl;
	cout << "is 4 reachable from 0 ???   " << dfs.reachable(4) << endl;
	cout << "is 12 reachable from 0 ???   " << dfs.reachable(12) << endl;
	deque<int> path = dfs.pathTo(2);
	for(unsigned int i=0; i<path.size(); ++i){
		cout << path[i] << "->";
	}
	cout << endl;
}

void test_cyc(const Digraph &dg){
	DirectedCycle cyc(dg);
	cout << "has a cycle ?  " << cyc.hasCycle() << endl;
	if( cyc.hasCycle() ){
		deque<int> c = cyc.cycle();
		print(c);
	}
}
void test_bfspath(const Digraph &dg){
	vector<int> sources;
	sources.push_back(0);
	sources.push_back(6);
	BFSDirectedPaths bfs(dg, sources);
	cout<<"has path to 3 " << bfs.reachable(3) << endl;
	deque<int> path = bfs.pathTo(4);
	print(path);
}

void test_dfs_order(const Digraph &dg){
	DFSOrder dfsOrder(dg);
	deque<int> call = dfsOrder.invokeOrder();
	deque<int> pre = dfsOrder.preOrder();
	deque<int> reverse = dfsOrder.reverseOrder();

	print(call);
	print(pre);
	print(reverse);

}

void test_topological(const Digraph &dg){
	TopologicalSort top(dg);
	deque<int> ts = top.topologicalOrder();
	print(ts);
}

void test_SCC(const Digraph &dg){
	SCC scc(dg);
	//cout << "# of SCC is " << scc.components() << endl;
	cout << "is 0 and 4 strongly connected " << scc.stronglyConnected(0,4) << endl;
	vector<deque<int> > comp = scc.components() ;
	cout << "# of SCC is " << scc.numOfComponents() << endl;
	for(unsigned i=0; i<comp.size(); ++i){
		print(comp[i]);
	}
}
void test(){
	ifstream ifs("tinyDG.txt", std::ifstream::in);
	Digraph dg(ifs);
	cout << dg;
	test_SCC(dg);
	//test_cyc(dg);
	//test_bfspath(dg);
	//test_topological(dg);
}
