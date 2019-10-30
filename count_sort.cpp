/*计数排序*/
#include <iostream>
using namespace std;

int find_max(int * A,int l);
void count_sort(int * A,int A_l,int * B,int max);
void display(int * A);

int main(void)
{
    int Test[10] = {5,9,1,0,2,4,3,7,11,6};
    int global_max;
    int l = sizeof(Test)/sizeof(int);
    display(Test);
    global_max = find_max(Test,l);
    
    int B[l];
    
    count_sort(Test,l,B,global_max);
    cout<<endl;
    display(B);
    return 0;
}

int find_max(int * A,int l)
{
    int max = A[0];
    for(int i=0;i<l;i++)
    {
        if(A[i] > max)
        {
            max = A[i];
        }
    }
    return max;
}

void count_sort(int * A,int A_l,int * B,int max)
{
    int C[max+1];
    for(int i=0;i<=max;i++)
    {
        C[i] = 0;
    }
    for(int j=0;j<A_l;j++)
    {
        C[A[j]] = C[A[j]] + 1;
    }
    for(int i=1;i<=max;i++)
    {
        C[i] = C[i] + C[i-1];
    }
    for(int j=A_l-1;j>=0;j--)
    {
        B[C[A[j]]-1] = A[j];
        //这里细节，B数组的下标应该为C[A[j]]减一，因为B数组的下标是从0开始排列的
        //但是C数组的对应项是指小于等于i的元素数量
        C[A[j]] = C[A[j]] - 1;
    }
}

void display(int * A)
{
    for(int i=0;i<10;i++)
    {
        cout<<A[i]<<" ";
    }
}