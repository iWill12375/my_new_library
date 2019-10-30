#include <iostream>
using namespace std;

#define Length 10  /*数组长度*/

int largest;
int l;
int r;
int Size = Length;

int left(int i);
int right(int i);
void exchange(int * A,int x,int y);
void max_heaplfy(int * A,int i);
void build_heap(int * A);
void heap_sort(int * A);
void display(int * A);

int main(void)
{
    int A[Length] = {0,4,5,1,3,6,9,7,8,10};
    display(A);
    heap_sort(A);
    cout<<endl;
    display(A);
    return 0;
}
//返回某个节点的左孩子节点
int left(int i)
{
    return 2*i+1;
}
//返回某个节点的右孩子节点
int right(int i)
{
    return 2*i+2;
}
//交换数组两个元素的位置
void exchange(int * A,int x,int y)
{
    int temp;
    temp = A[x];
    A[x] = A[y];
    A[y] = temp;
}
//假定左右子树均为最大堆的情况下，根据堆的性质调整
void max_heaplfy(int * A,int i)
{
    l = left(i);
    r = right(i);
    if(l<Size && A[l]>A[i])
        largest = l;
    else
        largest = i;
    if(r<Size && A[r]>A[largest])
        largest = r;
    if(largest != i)
    {
        exchange(A,i,largest);
        //使用递归调整不是最大堆的子树
        max_heaplfy(A,largest);
    }
}
//创建一个最大堆
void build_heap(int * A)
{
    //建堆的核心代码之一，因为叶子节点不用调整即是天然的最大堆，所以
    //从叶子节点的父节点开始调整堆，即从“下”往“上”可以得到一个最大堆
    for(int i=(Size-1)/2;i>=0;i--)//(Size-1)/2表示最后一个节点的父节点,从它开始进行逐个调整
        max_heaplfy(A,i);
}
//输出数组以显示
void display(int * A)
{
    for(int i=0;i<Length;i++)
    {
        cout<<A[i]<<" ";
    }
}
//使用堆排序，参数A表示待排序数组
void heap_sort(int * A)
{
    //建立堆结构（最大堆）
    build_heap(A);
    //堆排序的核心代码之一，取新建堆的堆顶，与数组末尾元素交换
    for(int i = Length-1;i>0;i--)
    {
        exchange(A,0,i);
        //每一次取出堆顶，即把其余元素看作另一个堆，尺寸减一
        Size--;
        //继续调整堆的性质，调整为最大堆
        max_heaplfy(A,0);
    }
}