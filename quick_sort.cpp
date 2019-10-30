/*快速排序*/
#include <iostream>
using namespace std;

int x;
int i;

void exchange(int * A, int x,int y);
void quicksort(int * A,int p,int r);
int partition(int * A,int p,int r);
void display(int * A);

int main(void)
{
    int Test[10] = {0,9,3,1,2,8,4,7,5,6};
    display(Test);
    quicksort(Test,0,9);
    cout<<endl;
    display(Test);
    return 0;
}
//快速排序--找到选定“标杆“元素的位置并返回
int partition(int * A,int p,int r)
{
    x = A[r];
    i = p-1;
    for(int j=p;j<r;j++)
    {
        if(A[j] <= x)
        {
            i++;
            exchange(A,i,j);
        }
    }
    exchange(A,i+1,r);
    return i+1;
}
//连续递归调用使得最基本情况为有序状态
void quicksort(int * A,int p,int r)
{
    if(p<r)
    {
        int q = partition(A,p,r);
        quicksort(A,p,q-1);
        quicksort(A,q+1,r);
    }
}

void exchange(int * A, int x,int y)
{
    int temp;
    temp = A[x];
    A[x] = A[y];
    A[y] = temp;
}

void display(int * A)
{
    for(int i=0;i<10;i++)
    {
        cout<<A[i]<<" ";
    }
}