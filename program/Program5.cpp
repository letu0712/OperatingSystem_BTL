#include<iostream>
#include<unistd.h>
using namespace std;

int main(int argc, char* argv[])
{   
    int T_process = atoi(argv[1]);
    for(int i=0; i<T_process; i++)
    {
        cout<<2*i<<endl;
        sleep(1);
    }
    return 0;
}