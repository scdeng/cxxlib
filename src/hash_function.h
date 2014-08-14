/*
 * =====================================================================================
 *
 *       Filename:  hash_function.h
 *
 *    Description:  hash function define
 *
 *        Version:  1.0
 *        Created:  08/13/2014 12:12:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deng Yong (dy), scdeng@163.com
 *        Company:  IIE,CAS
 *
 * =====================================================================================
 */
#include <iostream>
#include <cstring>
#include <string>
using namespace std;
#define __SIZEOF_SIZE_T 8

#if __SIZEOF_SIZE_T == 4

/*	@brief implementation of Murmur hash for 32-bit size_t
 */
size_t _Hash_bytes(const void* ptr, size_t len, 
			size_t seed = static_cast<size_t>(0xc70f6907UL) );

/*	@brief implementation of FNV hash for 64-bit size_t
 */
size_t _Fnv_hash_bytes(const void *ptr, size_t len, 
			size_t seed = static_cast<size_t>(216613626UL) );


#elif __SIZEOF_SIZE_T == 8 
/*	@brief implementation of Murmur hash for 32-bit size_t
 */
size_t _Hash_bytes(const void* ptr, size_t len, 
			size_t seed /* = static_cast<size_t>(0xc70f6907UL)*/ );

/*	@brief implementation of FNV hash for 64-bit size_t
 */
size_t _Fnv_hash_bytes(const void *ptr, size_t len, 
			size_t seed /* = static_cast<size_t>(216613626UL)*/ );

#else

/*	@brief implementation of Murmur hash for 32-bit size_t
 */
size_t _Hash_bytes(const void* ptr, size_t len, 
			size_t seed = static_cast<size_t>(0xc70f6907UL) );

/*	@brief implementation of FNV hash for 64-bit size_t
 */
size_t _Fnv_hash_bytes(const void *ptr, size_t len, 
			size_t seed = static_cast<size_t>(216613626UL) );

#endif

/*	@brief hash a string to a size_t
 */
size_t hashcode(string str);

/*	@brief hash array of char into size_t
 */
size_t hashcode(char *p, size_t n);

size_t hashcode(char const *p, size_t n);

size_t hashcode(int n);

size_t hashcode(char c);

size_t hashcode(unsigned char c);

size_t hashcode(unsigned int n);

size_t hashcode(long n);

size_t hashcode(unsigned long n);

/*	@brief function object
 */
template <class T> size_t hashcode(const T &t);

