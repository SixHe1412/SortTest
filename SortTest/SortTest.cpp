// SortTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>

using namespace std;

//C++經典的7種排序演算法

void SelectSort(int* array, int size);
void InsertSort(int* array, int size);
void BubbleSort(int* array, int size);
void MergeSort(int* array, int left, int right);
void Merge(int* array, int left, int mid, int right);
void HeapSort(int *array, int size);
void HeapAjust(int *array, int toAjust, int size);
void QuickSort(int *array, int left, int right);
void TreeSort(int *array, int size);
void TreeMidRetrival(int* array, int* temp, int pos, int* lChild, int* rChild);
void Swap(int* array, int x, int y);


void Swap(int* array, int x, int y)
{
	int temp = array[x];
	array[x] = array[y];
	array[y] = temp;
}

//選擇排序
void SelectSort(int* array, int size)
{
	int minIndex;
	for (int i = 0; i < size; i++)
	{
		minIndex = i;
		for (int j = i + 1; j < size; j++)
		{
			if (array[minIndex] > array[j])
			{
				minIndex = j;
			}
		}

		if (minIndex != i)
		{
			Swap(array, i, minIndex);
		}
	}
}

//氣泡排序
void BubbleSort(int* array, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 1; j < size - i; j++)
		{
			if (array[j] < array[j - 1])
			{
				Swap(array, j, j - 1);
			}
		}
	}
}

//插入排序
void InsertSort(int* array, int size)
{
	for (int i = 1; i < size; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (array[j] < array[j - 1])
			{
				Swap(array, j, j - 1);
			}
		}
	}
}

//快速排序
void QuickSort(int* array, int left, int right)
{
	if (left < right)
	{
		int i = left - 1, j = right + 1;
		int mid = array[(left + right) / 2];
		while (true)
		{
			while (array[++i] < mid);
			while (array[--j] > mid);
			if (i >= j)
			{
				break;
			}
			Swap(array, i, j);
		}
		QuickSort(array, left, i - 1);
		QuickSort(array, j + 1, right);
	}
}

void Merge(int* array, int left, int mid, int right)
{
	int* temp = new int[right - left + 1];
	int i = left, j = mid + 1, m = 0;
	while (i <= mid && j <= right)
	{
		if (array[i] < array[j])
		{
			temp[m++] = array[i++];
		}
		else
		{
			temp[m++] = array[j++];
		}
	}

	while (i <= mid)
	{
		temp[m++] = array[i++];
	}

	while (j <= right)
	{
		temp[m++] = array[j++];
	}

	for (int n = left, m = 0; n <= right; n++, m++)
	{
		array[n] = temp[m];
	}

	delete temp;
}

//归并排序
void MergeSort(int* array, int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		MergeSort(array, left, mid);
		MergeSort(array, mid + 1, right);
		Merge(array, left, mid, right);
	}
}

//调整堆
void HeapAjust(int *array, int toAjust, int size)
{
	int pos = toAjust;
	while ((pos * 2 + 1) < size)
	{
		int lChild = pos * 2 + 1;
		if (array[lChild] > array[pos])
		{
			pos = lChild;//左孩子大
		}

		int rChild = lChild + 1;
		if (rChild < size && array[rChild] > array[pos])
		{
			pos = rChild;//右孩子更大
		}

		if (pos != toAjust) //父节点比其中一个孩子小
		{
			Swap(array, toAjust, pos);
			toAjust = pos;
		}
		else
		{
			break;
		}
	}
}

//堆排序
void HeapSort(int* array, int size)
{
	int lastP = size / 2;
	//从最后一个有孩子的结点开始建初始堆
	for (int i = lastP - 1; i >= 0; i--)
	{
		HeapAjust(array, i, size);
	}

	int j = size;
	//将堆顶元素和无序区间的最后一个元素交换，再调整堆
	while (j > 0)
	{
		Swap(array, 0, j - 1);
		j--;
		HeapAjust(array, 0, j);
	}
}

//树排序
void TreeSort(int* array, int size)
{
	int *parent = new int[size];//父結點子針
	int *lChild = new int[size];//左孩子子針
	int *rChild = new int[size];//右孩子子針

	//將各結點左右子結點指標均置為-1，表示沒有左右子結點
	for (int i = 0; i < size; i++)
	{
		lChild[i] = -1;
		rChild[i] = -1;
	}

	parent[0] = -1; //將第一個元素作為根結點，其父結點置為-1

	//從第2個數開始構造樹
	for (int i = 1; i < size; i++)
	{
		int last = 0;
		while (true)
		{
			int compare = array[i] - array[last];
			if (compare > 0) //比當前值大，進入右子樹
			{
				if (rChild[last] == -1)
				{
					rChild[last] = i;
					parent[i] = last;
					break;
				}
				else
				{
					last = rChild[last];
				}
			}
			else //比当前值小，进入左子树
			{
				if (lChild[last] == -1)
				{
					lChild[last] = i;
					parent[i] = last;
					break;
				}
				else
				{
					last = lChild[last];
				}
			}
		}
	}

	//保存排序樹的中序遍歷結果
	int* midRetrival = new int[size];
	TreeMidRetrival(array, midRetrival, 0, lChild, rChild);
	//將排好序的中序數組複製到原陣列
	for (int i = 0; i < size; i++)
	{
		array[i] = midRetrival[i];
	}
}

//中序遍历
void TreeMidRetrival(int *array, int* temp, int pos, int* lChild, int* rChild)
{
	static int i = 0;
	if (pos != -1)
	{
		TreeMidRetrival(array, temp, lChild[pos], lChild, rChild);//遍歷左子樹
		temp[i++] = array[pos];//保存當前值
		TreeMidRetrival(array, temp, rChild[pos], lChild, rChild);//遍歷右子樹
	}
	else
	{
		return;
	}
}

int main()
{
	int i;
	int intdata[5] = { 5,3,1,2,4 };
	printf("before: ");
	for (i = 0; i<5; i++)
	{
		printf("%d\t", intdata[i]);
	}

	printf("\n");
	//SelectSort(intdata, 5);
	//InsertSort(intdata, 5);
	BubbleSort(intdata, 5);
	//MergeSort(intdata, 0, 4);
	//HeapSort(intdata, 5);
	//QuickSort(intdata, 0, 4);
	//TreeSort(intdata, 5);
	printf("after: ");

	for (i = 0; i<5; i++)
	{
		printf("%d\t", intdata[i]);
	}

	printf("\n");
	cout << "Hello world!" << endl;
	return 0;
}

