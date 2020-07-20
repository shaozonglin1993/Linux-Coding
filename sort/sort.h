#include <assert.h>
#include <stdio.h>

void Swap(int *a,int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void Print(int *a, size_t size)
{
	int i = 0;
	for(i=0; i < size; i++)
	{
		printf("%d ",a[i]);
	}
}

//直接插入排序
void Insert_Sort(int *a, size_t size)
{
	assert(a);
	
	int i = 0;
	int j = 0;
	for(i = 1;i < size; i++)
	{
		if(a[i] < a[i-1]){
			int tmp = a[i];
			for(j = i -1;j >= 0 && tmp < a[j];j--)
			{
				a[j+1] = a[j];
			}
			a[j+1] = tmp;
		}
	}
}

void TestInsertSort()
{
	int a[10] = {0,2,4,6,8,1,3,5,7,9};
	Insert_Sort(a,10);
	Print(a,10);
	printf("\n");
}

//希尔排序
void Shell_Sort(int *a, size_t size)
{
	assert(a);

	int gap = size;
	while(gap > 1)
	{
		gap = (gap/4)+1;
		
		int i = gap;
		for(; i < size; i++)
		{
			int index = i;
			int tmp = a[index];
			int end = index - gap;

			while(end >= 0 && tmp < a[end])
			{
				a[end + gap] = a[end];
				end-=gap;
			}
			a[end + gap] = tmp;
		}
	}
}

void TestShellSort()
{
	int a[10] = {0,2,4,6,8,1,3,5,7,9};
	Shell_Sort(a,10);
	Print(a,10);
	printf("\n");
}

//冒泡排序

void BubbleSort(int *a, size_t size)
{
	assert(a);

	int i = 0;
	int j = 0;

	for(i = 0;i < size;i++)
	{
		for(j = 0;j < size-i-1;j++)
		{
			if(a[j+1] < a[j])
			{
				Swap(&a[j+1],&a[j]);
			}
		}	
	}
}

void TestBubbleSort()
{
	int a[10] = {1,3,5,7,9,2,4,8,6,0};
	BubbleSort(a,10);
	Print(a,10);
	printf("\n");
}

//快速排序

//方法一

int Partition1(int *a,int left,int right)
{
	assert(a);

	int begin = left;
	int end = right - 1;
	int key = a[right];

	while(begin < end)
	{
		while(a[begin] <= key && begin < end)
		{
			begin++;
		}
		while(a[end] >= key && begin < end)
		{
			end--;
		}
		if(begin < end)
		{
			Swap(&a[begin],&a[end]);
		}
	}
	if(a[begin] > a[right])
	{
		Swap(&a[begin],&a[right]);

	//	printf("begin = %d",begin);
		return begin;
	}
	else
	{
	//	printf("end = %d",right);
		return right;
	}
}

void QuickSort1(int *a, size_t left, size_t right)
{
	assert(a);
	if(right > left){
		int boundary = Partition1(a,left,right);
		QuickSort1(a,left,boundary-1);
		QuickSort1(a,boundary+1,right);
	}
}

void TestQuickSort1()
{
	//int a[10] = {0,2,4,8,6,1,5,9,7,3};
	int a[10]={0,1,2,3,6,4,5,7,8,9};
	QuickSort1(a,0,9);
	Print(a,10);
	printf("\n");
}

//方法二
int Partition2(int *a, size_t left, size_t right)
{
	assert(a);

	int cur = left;
	int prev = left - 1;
	int key = a[right];

	while(cur < right){
		if(a[cur] < key && (++prev) != cur){
			Swap(&a[prev],&a[cur]);
		}
		cur++;
	}
	Swap(&a[++prev],&a[right]);

	return prev;
}

void QuickSort2(int *a, size_t left, size_t right)
{
	assert(a);

	if(left < right){
		int boundary = Partition2(a,left,right);
		QuickSort2(a,left,boundary-1);
		QuickSort2(a,boundary+1,right);
	}
}

void TestQuickSort2()
{
	int a[10] = {0,1,3,5,7,9,6,8,2,4};
	QuickSort2(a,0,9);
	Print(a,10);
	printf("\n");
}

//方法三

int Partition3(int *a,size_t left, size_t right)
{
	assert(a);

	int begin = left;
	int end = right;
	int key = a[right];
	
	while(begin < end){
		while(begin < end && a[begin] <= key){
			begin++;
		}
		if(begin < end){
			a[end] = a[begin];
		}

		while(begin < end && a[end] >= key){
			end--;
		}
		if(end > begin){
			a[begin] = a[end];
		}
	}
	a[begin] = key;
	return begin;
}

void QuickSort3(int *a,size_t left,size_t right)
{
	assert(a);
	if(left < right){
		int boundary = Partition3(a,left,right);
		QuickSort3(a,left,boundary-1);
		QuickSort3(a,boundary+1,right);
	}
}

void TestQuickSort3()
{
	int a[10] = {0,2,4,6,8,9,7,6,3,0};
	QuickSort3(a,0,9);
	Print(a,10);
	printf("\n");
}

//非递归排序

//void QuickSort4(int *a,size_t left,size_t right)
//{
//	assert(a);
//
//	stack<int> s;
//	if(left < right){
//		int boundary = Partition3(a,left,right);
//		if(left < boundary - 1){
//			s.push(left);
//			s.push(boundary - 1);
//		}
//		if(boundary+1 < right){
//			s.push(boundary+1);
//			s.push(right);
//		}
//		while(!s.empty()){
//			int end = s.top();
//			s.pop();
//			int begin = s.top();
//			s.pop();
//			
//			boundary = partition3(a,begin,end);
//			if(begin < boundary-1){
//				s.push(begin);
//				s.push(boundary-1);
//			}
//			if(end > boundary+1){
//				s.push(boundary+1);
//				s.push(end);
//			}
//		}
//	}
//}
//
//void TestQuickSort4()
//{
//	int a[10] = {0,1,3,6,4,7,9,8,2,5};
//	QuickSort4(a,0,9);
//	Print(a,10);
//	printf("\n");
//}

//选择排序

void SelectSort(int *a,size_t size)
{
	assert(a);

	int i = 0;
	int j = 0;
	for(i = 0;i < size;i++){
		int min = i;
		for(j = i+1;j < size;j++){
			if(a[min] > a[j]){
				min = j;
			}
		}
		if(min != i){
			Swap(&a[min],&a[i]);
		}
	}
}

void TestSelectSort()
{
	int a[10] = {0,2,4,6,8,1,3,9,7,5};
	SelectSort(a,10);
	Print(a,10);
	printf("\n");
}

//归并排序

void MergeSection(int *a)
{

}



