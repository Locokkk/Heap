#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef int HPDataType;
typedef struct Heap
{
	HPDataType* _a;
	int _size;
	int _capacity;
}Heap;

void HeapInit(Heap *hp, HPDataType *a, int n)
{
	hp->_a = (HPDataType*)malloc(sizeof(HPDataType)*n);
	memcpy(hp->_a, a, sizeof(HPDataType) * n);
	hp->_capacity = n;
	hp->_size = n;
 for (size_t i = (hp->_size - 2) / 2;i >= 0;--i)//建堆
	{
		AdjustDown(hp, i,n);
	}
}

void HeapDestory(Heap *hp)
{
	assert(hp);
	if (hp->_a)
	{
		free(hp->_a);
	}
	hp->_a =NULL;
	hp->_capacity = hp->_size = 0;
	
}

void swap(HPDataType *p1, HPDataType *p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}
void AdjustDown(Heap *hp, size_t parent,int n)
{
	assert(hp);
	int child = parent * 2 + 1;//左孩子

	while (child < n&&parent<n)
	{
		if (hp->_a[child] > hp->_a[child + 1])//选出小的那个孩子 child+1<n :保证有右孩子 
		{
			child++;
		}
		if (hp->_a[parent] > hp->_a[child])//小堆
		{
			swap(&(hp->_a[child]), &(hp->_a[parent]));
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void AdjustUp(Heap *hp, size_t child)
{
	size_t parent = (child - 1) / 2;
	while (child > 0)
	{
		if (hp->_a[child] < hp->_a[parent])
		{
			swap(&(hp->_a[child]), &(hp->_a[parent]));
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}

}

void HeapPush(Heap *hp, HPDataType x)
{
	assert(hp);
	if (hp->_size == hp->_capacity)
	{
		size_t newcapacity = (hp->_capacity == 0 ? 2 : hp->_capacity * 2);
		hp->_a = (HPDataType*)realloc(hp->_a, sizeof(HPDataType)*newcapacity);
		assert(hp->_a);
		hp->_capacity = newcapacity;
	}
	hp->_a[hp->_size] = x;
	++hp->_size;
	AdjustUp(hp, hp->_size-1);//传位置上去
}

void HeapPop(Heap *hp)
{
	assert(hp);
	swap(hp->_a[0], hp->_a[hp->_size - 1]);
	--hp->_size;
	AdjustDown(hp, 0,hp->_size-1);//传位置上去
}

HPDataType HeapTop(Heap *hp)
{
	assert(hp);
	return hp->_a[0];
}

int HeapSize(Heap *hp)
{
	assert(hp);
	return hp->_size;
}

int HeapEmpty(Heap *hp)
{
	assert(hp);
	return hp->_size == 0;
}

void Print(Heap *hp)
{
	assert(hp);
	for (int i = 0;i < hp->_size;i++)
	{
		printf("%d ", hp->_a[i]);
	}
	
}
