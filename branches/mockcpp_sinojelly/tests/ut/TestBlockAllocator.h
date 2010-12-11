/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2010>  <Darwin Yuan: darwin.yuan@gmail.com>
	                      <Chen Guodong: sinojelly@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/

#include <testngpp/testngpp.hpp>
#include <mockcpp/BlockAllocator.h>


USING_MOCKCPP_NS
USING_TESTNGPP_NS


FIXTURE(BlockAllocator)
{
	BlockAllocator allocator;
	TestBlockAllocator() : allocator(10, 3){}

	TEST(can alloc memory)
	{
		void* ptr = allocator.alloc(10);
		ASSERT_NE((void*)0, ptr);
		allocator.free(ptr);
	}

	TEST(should return null if the alloc size larger than block size)
	{    
		void* ptr = allocator.alloc(11);
		ASSERT_EQ((void*)0, ptr);
	}

	TEST(should get two different memory addresses in two invocations of alloc)
	{    
		void* ptr1 = allocator.alloc(10);
		void* ptr2 = allocator.alloc(10);
		ASSERT_NE(ptr1, ptr2);
		allocator.free(ptr1);
		allocator.free(ptr2);
	}

	TEST(should return null if the invocation number of alloc more than block number)
	{    
		void* ptr1 = allocator.alloc(10);
		void* ptr2 = allocator.alloc(10);
	    
		void* ptr3 = allocator.alloc(10);
		ASSERT_NE((void *)0, ptr3);

		void* ptr4 = allocator.alloc(10);    
		ASSERT_EQ((void*)0, ptr4);

		allocator.free(ptr1);
		allocator.free(ptr2);
		allocator.free(ptr3);
	}

	TEST(alloc all the blocks, then free one, and then alloc one, should get the one freed recently)
	{    
		void* ptr1 = allocator.alloc(10);
		void* ptr2 = allocator.alloc(10);
		void* ptr3 = allocator.alloc(10);

		allocator.free(ptr2);
	    
		void* ptr4 = allocator.alloc(10);    
		ASSERT_EQ(ptr2, ptr4);

		allocator.free(ptr1);
		allocator.free(ptr3);
		allocator.free(ptr4);
	}

	TEST(can free null)
	{  
		allocator.free(0);
	}

	TEST(should not free the block that not in the allocated blocks)
	{  
		void* ptr1 = allocator.alloc(10);
		void* ptr2 = allocator.alloc(10);
		void* ptr3 = allocator.alloc(10);

		allocator.free((void *)((char *)ptr1 + 4));

		void* ptr4 = allocator.alloc(10);    
		ASSERT_EQ((void*)0, ptr4);

		allocator.free(ptr1);
		allocator.free(ptr2);
		allocator.free(ptr3);
	}

	TEST(should not free the block that not in the allocator)
	{  
		char  ptr[1000];

		void* ptr1 = allocator.alloc(10);
		void* ptr2 = allocator.alloc(10);
		void* ptr3 = allocator.alloc(10);

		for(unsigned int i=0; i<1000; i++)
			allocator.free(&ptr[i]);

		void* ptr4 = allocator.alloc(10);    
		ASSERT_EQ((void*)0, ptr4);

		allocator.free(ptr1);
		allocator.free(ptr2);
		allocator.free(ptr3);
	}

	TEST(can free a block two times)
	{  
		void* ptr1 = allocator.alloc(10);
		void* ptr2 = allocator.alloc(10);
		void* ptr3 = allocator.alloc(10);

		allocator.free(ptr2);
		allocator.free(ptr2);

		void* ptr4 = allocator.alloc(10);    
		ASSERT_EQ(ptr2, ptr4);

		void* ptr5 = allocator.alloc(10);    
		ASSERT_EQ((void*)0, ptr5);

		allocator.free(ptr1);
		allocator.free(ptr3);
		allocator.free(ptr4);
	}

	TEST(can alloc a block that size smaller than allocator block size)
	{
		void* ptr1 = allocator.alloc(1);
		ASSERT_NE((void *)0, ptr1);

		allocator.free(ptr1);
	}

	TEST(can only alloc at most allocator block number of smaller blocks)
	{
		void* ptr1 = allocator.alloc(1);
		ASSERT_NE((void *)0, ptr1);
		void* ptr2 = allocator.alloc(1);
		ASSERT_NE((void *)0, ptr2);
		void* ptr3 = allocator.alloc(1);
		ASSERT_NE((void *)0, ptr3);

		void* ptr4 = allocator.alloc(10);    
		ASSERT_EQ((void*)0, ptr4);

		allocator.free(ptr1);
		allocator.free(ptr2);
		allocator.free(ptr3);    
	}

};
