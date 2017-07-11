// SortTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>

using namespace std;

//C++�����7�N�������㷨

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

//�x������
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

//��������
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

//��������
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

//��������
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

//�鲢����
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

//������
void HeapAjust(int *array, int toAjust, int size)
{
	int pos = toAjust;
	while ((pos * 2 + 1) < size)
	{
		int lChild = pos * 2 + 1;
		if (array[lChild] > array[pos])
		{
			pos = lChild;//���Ӵ�
		}

		int rChild = lChild + 1;
		if (rChild < size && array[rChild] > array[pos])
		{
			pos = rChild;//�Һ��Ӹ���
		}

		if (pos != toAjust) //���ڵ������һ������С
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

//������
void HeapSort(int* array, int size)
{
	int lastP = size / 2;
	//�����һ���к��ӵĽ�㿪ʼ����ʼ��
	for (int i = lastP - 1; i >= 0; i--)
	{
		HeapAjust(array, i, size);
	}

	int j = size;
	//���Ѷ�Ԫ�غ�������������һ��Ԫ�ؽ������ٵ�����
	while (j > 0)
	{
		Swap(array, 0, j - 1);
		j--;
		HeapAjust(array, 0, j);
	}
}

//������
void TreeSort(int* array, int size)
{
	int *parent = new int[size];//���Y�c���
	int *lChild = new int[size];//�������
	int *rChild = new int[size];//�Һ������

	//�����Y�c�����ӽY�cָ�˾��Þ�-1����ʾ�]�������ӽY�c
	for (int i = 0; i < size; i++)
	{
		lChild[i] = -1;
		rChild[i] = -1;
	}

	parent[0] = -1; //����һ��Ԫ��������Y�c���丸�Y�c�Þ�-1

	//�ĵ�2�����_ʼ�����
	for (int i = 1; i < size; i++)
	{
		int last = 0;
		while (true)
		{
			int compare = array[i] - array[last];
			if (compare > 0) //�Ȯ�ǰֵ���M�����Ә�
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
			else //�ȵ�ǰֵС������������
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

	//���������������v�Y��
	int* midRetrival = new int[size];
	TreeMidRetrival(array, midRetrival, 0, lChild, rChild);
	//���ź�������򔵽M�}�u��ԭ���
	for (int i = 0; i < size; i++)
	{
		array[i] = midRetrival[i];
	}
}

//�������
void TreeMidRetrival(int *array, int* temp, int pos, int* lChild, int* rChild)
{
	static int i = 0;
	if (pos != -1)
	{
		TreeMidRetrival(array, temp, lChild[pos], lChild, rChild);//��v���Ә�
		temp[i++] = array[pos];//���殔ǰֵ
		TreeMidRetrival(array, temp, rChild[pos], lChild, rChild);//��v���Ә�
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

