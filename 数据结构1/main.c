#include <stdio.h>
#include <stdlib.h>

#define leftchild(i)(2 * (i) + 1)
#define X1 10
#define X2 100
#define X3 1000
#define X4 10000
#define X5 100000
#define X6 1000000

void Swap(int *a,int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

void InsertionSort(int A[],int N){              //插入排序
    int j,p;
    int temp;
    for(p = 1;p < N;p++){
        temp = A[p];
        for(j = p;j > 0 && A[j - 1] > temp;j--)
        A[j] = A[j - 1];
        A[j] = temp;
    }
}

void perdown(int A[],int i,int n){            //堆排序
    int child;
    int temp;
    for(temp = A[i];leftchild(i) < n;i = child){
        child = leftchild(i);
        if(child != n - 1 && A[child + 1] > A[child])
            child++;
        if(temp < A[child])
            A[i] = A[child];
        else
            break;
    }
    A[i] = temp;
}
void Heapsort(int A[],int n){
    int i;
    for(i = n / 2;i >= 0;i--)
        perdown(A,i,n);
    for(i = n - 1;i > 0;i--){
        Swap(&A[0],&A[i]);
        perdown(A,0,i);
    }
}

void msort(int A[],int tempA[],int left,int right){          //合并排序
    int center;
    if(left < right){
        center = (left + right) / 2;
        msort(A,tempA,left,center);
        msort(A,tempA,center + 1,right);
        merge(A,tempA,left,center + 1,right);
    }
}
void mergesort(int A[],int n){
    int *tempA;
    tempA = malloc(n * sizeof(int));
    if(tempA != NULL){
        msort(A,tempA,0,n - 1);
        free(tempA);
    }
    else
        printf("No space!");
}
void merge(int A[],int tempA[],int lpos,int rpos,int rightend){
    int i,leftend,num,tempos;
    leftend = rpos - 1;
    tempos = lpos;
    num = rightend - lpos + 1;
    while(lpos <= leftend && rpos <= rightend)
        if(A[lpos] <= A[rpos])
            tempA[tempos++] = A[lpos++];
        else
            tempA[tempos++] = A[rpos++];
    while(lpos <= leftend)
        tempA[tempos++] = A[lpos++];
    while(rpos <= rightend)
        tempA[tempos++] = A[rpos++];
    for(i = 0;i < num;i++,rightend--)
        A[rightend] = tempA[rightend];
}

int Partition(int arr[],int low,int high)      //快速排序
{
    int base = arr[low];
    while(low < high)
    {
        while(low < high && arr[high] >= base)
        {
            high--;
        }
        Swap(&arr[low],&arr[high]);
        while(low < high && arr[low] <= base)
        {
            low++;
        }
        Swap(&arr[low],&arr[high]);
    }
    return low;
}
void Qsort(int arr[],int low,int high)
{
    if(low < high)
    {
        int base = Partition(arr,low,high);
        Qsort(arr,low,base - 1);
        Qsort(arr,base + 1,high);
    }
}

int GetMaxVal(int arr[], int len)               //桶排序
{
    int maxVal = arr[0]; //假设最大为arr[0]
    int i;
    for(i = 1; i < len; i++)  //遍历比较，找到大的就赋值给maxVal
    {
        if(arr[i] > maxVal)
            maxVal = arr[i];
    }
    return maxVal;  //返回最大值
}
void BucketSort(int arr[] , int len)
{
    int tmpArrLen = GetMaxVal(arr , len) + 1;
    int tmpArr[tmpArrLen];  //获得空桶大小
    int i, j;
    for( i = 0; i < tmpArrLen; i++)  //空桶初始化
        tmpArr[i] = 0;
    for(i = 0; i < len; i++)   //寻访序列，并且把项目一个一个放到对应的桶子去。
        tmpArr[ arr[i] ]++;
    for(i = 0, j = 0; i < tmpArrLen; i ++)
    {
        while( tmpArr[ i ] != 0) //对每个不是空的桶子进行排序。
        {
            arr[j ] = i;  //从不是空的桶子里把项目再放回原来的序列中。
            j++;
            tmpArr[i]--;
        }
    }
}

int main()
{
    double begintime,endtime;
	int i = 0;



	int a1[X1];
	for(i = 0;i < X1;i++){           //要计时的程序
		a1[i] = rand()%1000;
	}
    begintime = clock();	             //计时开始
    for(i = 1; i < 100000;i++)
        //InsertionSort(a1,X1);
        //Qsort(a1,0,X1 - 1);
        //Heapsort(a1,X1);
        //mergesort(a1,X1);
        BucketSort(a1,X1);
    endtime = clock();
	printf("\n\nRunning Time：%fms\n\n", (endtime-begintime)/100000);




	int a2[X2];
	for(i = 0;i < X2;i++){           //要计时的程序
		a2[i] = rand()%1000;
	}
    begintime = clock();	             //计时开始
    for(i = 1; i < 100000;i++)
        //InsertionSort(a2,X2);
        //Qsort(a2,0,X2 - 1);
        //Heapsort(a2,X2);
        //mergesort(a2,X2);
        BucketSort(a2,X2);
    endtime = clock();
	printf("\n\nRunning Time：%fms\n\n",(endtime-begintime)/100000);




	int a3[X3];
	for(i = 0;i < X3;i++){           //要计时的程序
		a3[i] = rand()%1000;
	}
    begintime = clock();	             //计时开始
    for(i = 1; i < 1000;i++)
        //InsertionSort(a3,X3);
        //Qsort(a3,0,X3 - 1);
        //Heapsort(a3,X3);
        //mergesort(a3,X3);
        BucketSort(a3,X3);
    endtime = clock();
	printf("\n\nRunning Time：%fms\n\n", (endtime-begintime)/1000);




	int a4[X4];
	for(i = 0;i < X4;i++){           //要计时的程序
		a4[i] = rand()%1000;
	}
    begintime = clock();	             //计时开始
    for(i = 0;i < 10;i++)
    //InsertionSort(a4,X4);
    //Qsort(a4,0,X4 - 1);
    //Heapsort(a4,X4);
    //mergesort(a4,X4);
    BucketSort(a4,X4);
    endtime = clock();
	printf("\n\nRunning Time：%fms\n\n", (endtime-begintime)/10);





	int a5[X5];
	for(i = 0;i < X5;i++){           //要计时的程序
		a5[i] = rand()%1000;
	}
    begintime = clock();	             //计时开始
    for(i = 0;i < 10;i++)
    //InsertionSort(a5,X5);
    //Qsort(a5,0,X5 - 1);
    //Heapsort(a5,X5);
    //mergesort(a5,X5);
    BucketSort(a5,X5);
    endtime = clock();
	printf("\n\nRunning Time：%fms\n\n", (endtime-begintime)/10);




/*	int a6[X6];
	for(i = 0;i < X6;i++){           //要计时的程序
		a6[i] = rand()%1000;
	}
    begintime = clock();	             //计时开始
    InsertionSort(a6,X6);
    //Qsort(a6,0,X6 - 1);
    //Heapsort(a6,X6);
    //mergesort(a6,X6);
    //BucketSort(a6,X6);
    endtime = clock();
	printf("\n\nRunning Time：%fms\n\n", endtime-begintime);*/

    return 0;
}
