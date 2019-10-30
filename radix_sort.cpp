/*基数排序*/
#include <iostream>
using namespace std;

int main(void)
{
    int d = 1000;
    int i = 0;
    int j = 0;
    int k = 0;
    j = d%100/10;
    k = d/100;
    i = d%100%10;
    cout<<"d = "<<d<<endl;
    cout<<"个位数 = "<<i<<endl;
    cout<<"十位数 = "<<j<<endl;
    cout<<"百位数 = "<<k<<endl;
    return 0;
}