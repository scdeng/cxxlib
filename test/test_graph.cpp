/*
 * =====================================================================================
 *
 *       Filename:  graph_test.cpp
 *
 *    Description:  test undirected graph
 *
 *        Version:  1.0
 *        Created:  08/05/2014 07:04:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#include "graph.h"
void make_graph(Graph &g){
	g.addEdge(0,5);	
	g.addEdge(4,3);	
	g.addEdge(0,1);	
	g.addEdge(9,12);	
	g.addEdge(6,4);	
	g.addEdge(5,4);	
	g.addEdge(0,2);	
	g.addEdge(11,12);	
	g.addEdge(9,10);	
	g.addEdge(0,6);	
	g.addEdge(7,8);	
	g.addEdge(9,11);	
	g.addEdge(5,3);	
}

void test_graph(){
	Graph g(13);
	make_graph(g);
//	cout << g;
//	DepthFirstPaths dfs(g,0);
//	cout << "connected to 0? " << dfs.connected(1) << endl;
//	deque<int> path = dfs.pathTo(3);
//	for(deque<int>::iterator it = path.begin(); it != path.end(); ++it){
//		cout << *it << "->" ;
//	}
//	cout<< " Yes, You did it"  <<endl;
//
//	cout << "=========================================" << endl;
//	ifstream ifs;
//	ifs.open("mediumG.txt", std::ifstream::in);
//	Graph g1(ifs);
//	cout <<g1;	
//	cout << "====================================================" << endl;
//	DepthFirstPaths dfs1(g1,0);
//	cout << dfs1;
//	vector<int> s;
//	s.push_back(0);
//	s.push_back(7);
//	BreadthFirstPaths bfs(tiny, s);
//
//
//	deque<int> path = bfs.pathTo(8);
//	for(deque<int>::iterator it = path.begin(); it != path.end(); ++it){
//		cout << *it << "->" ;
//	}
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
