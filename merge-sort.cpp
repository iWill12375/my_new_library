/*归并排序*/
#include <iostream>
using std::cout;
using std::cin;

void merge(int * A,int p,int q,int r);
void merge_sort(int * A,int p,int r);

int main(void)
{
    int Test[10] = {4,11,-2,7,78,0,1,2,3,9};
    merge_sort(Test,0,9);
    for(int i=0;i<10;i++)
    {
        cout<<Test[i]<<" ";
    }
    return 0;
}

void merge(int * A,int p,int q,int r)
{
    int n1 = q-p+1;
    int n2 = r-q;
    int T1[n1+1];
    int T2[n2+1];

    for(int i=0;i<n1;i++)
    {
        T1[i] = A[p+i];
    }
    for(int i=0;i<n2;i++)
    {
        T2[i] = A[q+i+1];
    }
    T1[n1] = INT32_MAX;
    T2[n2] = INT32_MAX;
    int i = 0;
    int j = 0;

    for(int k=p;k<=r;k++)
    {
        if(T1[i]<=T2[j])
        {
            A[k] = T1[i];
            i++;
        }
        else
        {
            A[k] = T2[j];
            j++;
        }
        
    }
}

void merge_sort(int * A,int p,int r)
{
    if(p<r)
    {
        int q = (p+r)/2;
        merge_sort(A,p,q);
        merge_sort(A,q+1,r);
        merge(A,p,q,r);
    }
}