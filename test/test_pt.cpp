/*
 * =====================================================================================
 *
 *       Filename:  test_pt.cpp
 *
 *    Description:  test pattern search
 *
 *        Version:  1.0
 *        Created:  08/11/2014 03:47:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */

#include "regex.h"
#include <iostream>
using namespace std;

void test_dfa(DFA & dfa){
	string txt("abcAAAABCA");
	cout << dfa.pattern()<<endl;
	cout << txt << endl;
	cout << dfa.search(txt)<<endl;
}
void test_nfa(NFA &nfa){
	string txt("abdadhacBD");
	cout << nfa.pattern() << endl;
	cout << txt << endl;
	cout << nfa.recoginize(txt) << endl;
	cout << nfa.epsilonTransition() << endl;
}

void test(int argc, char **argv){
	string pat = "AAABC";
	DFA dfa(pat);
	test_dfa(dfa);
	NFA nfa("((A*B|AC)D)");
	test_nfa(nfa);
}
