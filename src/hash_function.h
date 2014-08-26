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
#ifndef HASH_FUNCTION_H
#define HASH_FUNCTION_H
#include <iostream>
#include <cstring>
#include <string>
using namespace std;
#define __SIZEOF_SIZE_T 8

#if __SIZEOF_SIZE_T == 4

/*	@brief implementation of Murmur hash for 32-bit size_t
 */
size_t _Hash_bytes(const void* ptr, size_t len, 
			size_t seed /*= static_cast<size_t>(0xc70f6907UL)*/ );

/*	@brief implementation of FNV hash for 64-bit size_t
 */
size_t _Fnv_hash_bytes(const void *ptr, size_t len, 
			size_t seed /*= static_cast<size_t>(216613626UL)*/ );


#elif __SIZEOF_SIZE_T == 8 
/*	@brief implementation of Murmur hash for 32-bit size_t
 */
size_t _Hash_bytes(const void* ptr, size_t len, 
			size_t seed /*= static_cast<size_t>(0xc70f6907UL)*/ );

/*	@brief implementation of FNV hash for 64-bit size_t
 */
size_t _Fnv_hash_bytes(const void *ptr, size_t len, 
			size_t seed /*= static_cast<size_t>(216613626UL)*/ );

#else

/*	@brief implementation of Murmur hash for 32-bit size_t
 */
size_t _Hash_bytes(const void* ptr, size_t len, 
			size_t seed /*= static_cast<size_t>(0xc70f6907UL)*/ );

/*	@brief implementation of FNV hash for 64-bit size_t
 */
size_t _Fnv_hash_bytes(const void *ptr, size_t len, 
			size_t seed /*= static_cast<size_t>(216613626UL)*/ );

#endif

//==================another hash function=====================//

static unsigned long CRYPTOTABLE[0x500];

void prepareCryptoTable(){
	unsigned long seed = 0x00100001;
	unsigned long index1 = 0; 
	unsigned long index2 = 0;
	unsigned long i;
	for( index1 = 0; index1 < 0x100; ++index1 ){
		for( index2 = index1, i = 0; i<5; ++i, index2 += 0x100 ){
			unsigned long tmp1, tmp2;
			seed = (seed * 125 + 3) % 0x2AAAAB;
			tmp1 = (seed & 0xFFFF) << 0x10;

			seed = (seed * 125 + 3) % 0x2AAAAB;
			tmp2 = (seed & 0xFFFF);	
			CRYPTOTABLE[index2] = ( tmp1 | tmp2 );
		}
	}
}

unsigned long hashString( const char *lpszkeyName, unsigned long dwHashType){
	unsigned char *key = (unsigned char*)lpszkeyName;
	unsigned long seed1 = 0x7FED7FED;
	unsigned long seed2 = 0xEEEEEEEE;
	int ch;
	while( *key != 0 ){
		ch = *key++;
		seed1 = CRYPTOTABLE[ (dwHashType<<8) + ch ] ^ (seed1 + seed2);
		seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3;
	}
	return seed1;
}

//=====================================================//

#endif












