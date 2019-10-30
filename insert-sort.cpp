#include <iostream>
using namespace std;

void insertsort(int * A,int length);

int main()
{
    int A[10] = {3,1,2,7,5,4,6,0,9,8};
    insertsort(A,10);
    for(int i=0;i<10;i++)
    {
        cout<<A[i]<<" ";
    }
    return 0;
}

void insertsort(int * A,int length)
{
    int key = 0;
    for(int j=1;j<length;j++)
    {
        key = A[j];
        int i = j-1;
        //key codes of insert-sort
        while(i>=0 && A[i]>key)
        {
            A[i+1] = A[i];
            i--;
        }
        A[i+1] = key;
    }
}