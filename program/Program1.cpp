#include<iostream>
#include<unistd.h>
using namespace std;

int main(int argc, char* argv[])
{   
    int T_process = atoi(argv[1]);
    int i=0;
    while(i<T_process)     //i< P[1].T_processing
    {
        cout<<i<<endl;
        sleep(1);
        i++;
    }
    cout<<"DONE";
    return 0;
}