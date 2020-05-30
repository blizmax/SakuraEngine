/*
 * @CopyRight: MIT License
 * Copyright (c) 2020 SaeruHikari
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THESOFTWARE.
 * 
 * 
 * @Description: 
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-05-30 17:07:10
 * @LastEditTime: 2020-05-30 17:33:09
 */ 

#include <iostream>
#include "HashMap.h"
#include <unordered_map>
#include <EASTL/unordered_map.h>
#include <time.h>
using namespace std;
struct FakeHash
{
	size_t operator()(const int& a) const
	{
		return a;
	}
};
uint64 value = 0;
//#define NON_COLLIDE

#ifdef NON_COLLIDE
using STDMap = std::unordered_map<int, int, FakeHash>;
using CustomHashMap = HashMap<int, int, FakeHash>;
using EASTLHashMap = eastl::unordered_map<int, int, FakeHash>;
#else
using STDMap = std::unordered_map<int, int>;
using CustomHashMap = HashMap<int, int>;
using EASTLHashMap = eastl::unordered_map<int, int>;
#endif

inline void* operator new[](size_t size, const char* pName, int flags, unsigned     debugFlags, const char* file, int line) 
{
    return malloc(size);
}  

inline void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line) 
{
    return malloc(size);
}  
#define N 2000

int main()
{


	clock_t start = 0;
	clock_t end = 0;

	alignas(STDMap) char c0[sizeof(STDMap)];
	alignas(CustomHashMap) char c1[sizeof(CustomHashMap)];
	alignas(EASTLHashMap) char c2[sizeof(EASTLHashMap)];

	STDMap* stdmapPtr = reinterpret_cast<STDMap*>(c0);
	CustomHashMap* hashMapPtr = reinterpret_cast<CustomHashMap*>(c1);
	EASTLHashMap* eastlPtr = reinterpret_cast<EASTLHashMap*>(c2);

	cout << "Testing Construct: ";
	start = clock();
	new (stdmapPtr)STDMap();
	stdmapPtr->reserve(N);
	end = clock();
	cout << "unordered_map construct time: " << end - start << endl;
	
	start = clock();
	new (hashMapPtr)CustomHashMap(N);
	end = clock();
	cout << "hashmap construct time: " << end - start << endl;

	start = clock();
	new (eastlPtr)EASTLHashMap(N);
	eastlPtr->reserve(N);
	end = clock();
	cout << "eastl construct time: " << end - start << endl;


	cout << "Testing Insert(Multiple capacity resize inside)" << endl;
	start = clock();
	for (uint i = 0; i < N; ++i)
		stdmapPtr->insert_or_assign(i, i);
	end = clock();
	cout << "unordered_map insert time: " << end - start << endl;

	start = clock();
	for (uint i = 0; i < N; ++i)
		hashMapPtr->Insert(i, i);
	end = clock();
	cout << "hashmap insert time: " << end - start << endl;
	
	start = clock();
	for (uint i = 0; i < N; ++i)
		eastlPtr->insert_or_assign(i, i);
	end = clock();
	cout << "eastl insert time: " << end - start << endl;


	cout << "Testing Search Time: " << endl;
	start = clock();
	for (uint i = 0; i < N; ++i)
		value = stdmapPtr->find(i)->second;
	end = clock();
	cout << "unordered_map time: " << end - start << endl;

	start = clock();
	for (uint i = 0; i < N; ++i)
		value = hashMapPtr->Find(i).Value();
	end = clock();
	cout << "hashmap time: " << end - start << endl;

	start = clock();
	for (uint i = 0; i < N; ++i)
		value = eastlPtr->find(i)->second;
	end = clock();
	cout << "eastl time: " << end - start << endl;
}
