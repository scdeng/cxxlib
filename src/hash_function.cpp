/*
 * =====================================================================================
 *
 *       Filename:  hash_function.cpp
 *
 *    Description:  hash function for bytes
 *
 *        Version:  1.0
 *        Created:  08/13/2014 11:23:57 AM
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
#include "hash_function.h"

inline size_t unaligned_load(const char *p){
	size_t result;
	memcpy(&result, p, sizeof(result) );
	return result;
}

inline size_t load_bytes(const char *p, int n){
	size_t result = 0;
	--n;
	do
	  	result = (result << 8) + static_cast<unsigned char>(p[n]);
	while(--n >= 0);
	return result;
}

inline size_t shift_mix(size_t x){
	return x ^ (x >> 47 );
}

#if __SIZEOF_SIZE_T__ == 4
// Implementation of Murmur hash for 32-bit size_t.
size_t _Hash_bytes(const void* ptr, size_t len, 
			size_t seed = static_cast<size_t>(0xc70f6907UL) )
{
	//copy from gcc
	//size_t seed = static_cast<size_t>(0xc70f6907UL);

	const size_t m = 0x5bd1e995;
	size_t hash = seed ^ len;
	const char* buf = static_cast<const char*>(ptr);

	// Mix 4 bytes at a time into the hash.
	while(len >= 4)
	{
		size_t k = unaligned_load(buf);
		k *= m;
		k ^= k >> 24;
		k *= m;
		hash *= m;
		hash ^= k;
		buf += 4;
		len -= 4;
	}

	// Handle the last few bytes of the input array.
	switch(len)
	{
		case 3:
			hash ^= static_cast<unsigned char>(buf[2]) << 16;
		case 2:
			hash ^= static_cast<unsigned char>(buf[1]) << 8;
		case 1:
			hash ^= static_cast<unsigned char>(buf[0]);
			hash *= m;
	};

	// Do a few final mixes of the hash.
	hash ^= hash >> 13;
	hash *= m;
	hash ^= hash >> 15;
	return hash;
}

// Implementation of FNV hash for 32-bit size_t.
size_t _Fnv_hash_bytes(const void* ptr, size_t len,
			size_t hash = static_cast<size_t>(216613626UL))
{
	const char* cptr = static_cast<const char*>(ptr);
	for (; len; --len)
	{
		hash ^= static_cast<size_t>(*cptr++);
		hash *= static_cast<size_t>(16777619UL);
	}
	return hash;
}

#elif __SIZEOF_SIZE_T__ == 8

// Implementation of Murmur hash for 64-bit size_t.
size_t _Hash_bytes(const void* ptr, size_t len, 
			size_t seed = static_cast<size_t>(0xc70f6907UL))
{

	static const size_t mul = (0xc6a4a793UL << 32UL) + 0x5bd1e995UL;
	const char* const buf = static_cast<const char*>(ptr);

	// Remove the bytes not divisible by the sizeof(size_t).  This
	// allows the main loop to process the data as 64-bit integers.
	const int len_aligned = len & ~0x7;
	const char* const end = buf + len_aligned;
	size_t hash = seed ^ (len * mul);
	for (const char* p = buf; p != end; p += 8)
	{
		const size_t data = shift_mix(unaligned_load(p) * mul) * mul;
		hash ^= data;
		hash *= mul;
	}
	if ((len & 0x7) != 0)
	{
		const size_t data = load_bytes(end, len & 0x7);
		hash ^= data;
		hash *= mul;
	}
	hash = shift_mix(hash) * mul;
	hash = shift_mix(hash);
	return hash;
}

// Implementation of FNV hash for 64-bit size_t.
size_t _Fnv_hash_bytes(const void* ptr, size_t len,
			size_t hash = static_cast<size_t>(216613626UL))
{
	const char* cptr = static_cast<const char*>(ptr);
	for (; len; --len)
	{
		hash ^= static_cast<size_t>(*cptr++);
		hash *= static_cast<size_t>(1099511628211ULL);
	}
	return hash;
}

#else

// Dummy hash implementation for unusual sizeof(size_t).
size_t _Hash_bytes(const void* ptr, size_t len, 
			size_t seed = static_cast<size_t>(0xc70f6907UL))
{
	size_t hash = seed;
	const char* cptr = reinterpret_cast<const char*>(ptr);
	for (; clength; --clength)
	  	hash = (hash * 131) + *cptr++;
	return hash;
}

size_t _Fnv_hash_bytes(const void* ptr, size_t len, 
			size_t seed = static_cast<size_t>(216613626UL))
{ 
	return _Hash_bytes(ptr, len, seed);
}

#endif /* __SIZEOF_SIZE_T__ */




/*	@brief hash a string to a size_t
 */
size_t hashcode(string str){
	return _Hash_bytes( str.c_str(), str.length() );
}

/*	@brief hash array of char into size_t
 */
inline size_t hashcode(char *p, size_t n){
	return _Hash_bytes( p, n );
}

/*	@brief hash array of char into size_t
 */
inline size_t hashcode(char const *p, size_t n){
	return _Hash_bytes( p, n );
}

inline size_t hashcode(int n){
	return static_cast<size_t>(n);
}

inline size_t hashcode(char c){
	return static_cast<size_t>(c);
}

inline size_t hashcode(unsigned char c){
	return static_cast<size_t>(c);
}

inline size_t hashcode(unsigned int n){
	return static_cast<size_t>(n);
}

inline size_t hashcode(long n){
	return static_cast<size_t>(n);
}

inline size_t hashcode(unsigned long n){
	return static_cast<size_t>(n);
}

/*	@brief function object
 */
template <class T> size_t hashcode(const T &t ){
	return _Hash_bytes( &t, sizeof(t) );
}
