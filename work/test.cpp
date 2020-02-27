#include<iostream>

using namespace std;

int get()
{
    static int i=0;
    i++;
    return i;
}

int main()
{
    for(int i=0;i<100;i++)
        cout<<get()<<endl;
    return 0;
}
