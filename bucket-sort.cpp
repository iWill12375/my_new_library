/*bucket sort sources*/
#include <iostream>
#include <vector>
#include <algorithm>
using std::cout;
using std::cin;
using std::vector;

/*桶排序的主函数，参数两个，一个待排序数组，一个数组长度*/
void bucket_sort(int * A,int n);

int main(void)
{
    int test[10] = {6,1,0,9,4,5,3,2,7,8};
    
    return 0;
}

void bucket_sort(int * A,int n)
{
    vector<int> B[n];//声明的向量，当作桶，桶是用来装待排序数的，按等长区间分配元素
    int max = *std::max_element(A,A+n);
    //最大元素
    int min = *std::min_element(A,A+n);
    //最小元素

    int part = (max - min)/n + 1;
    //求得的等长区间的长度，向上取等，防止下面除数为零的异常出现

    for(int i=0;i<n;i++)
    {
        B[(A[i]-min)/part].push_back(A[i]);
        //按所属区间把待排序数组中的元素赋值给代表对应区间的向量
    }

    for(int i=0;i<n;i++)
    {
        sort(B[i].begin(),B[i].end());
        //给每个向量排序
    }

    int j = 0;

    //把每个有序向量从前到后串联起来赋值给待排序数组，排序结束
    for(int i=0;i<n;i++)
    {
        for(auto it:B[i])
        {
            if(j<n)
            {
                A[j] = it;
                j++;
            }
        }
    }
}