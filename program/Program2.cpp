#include<iostream>
#include<unistd.h>
using namespace std;

int main(int argc, char* argv[])
{   
    int T_process = atoi(argv[1]);
    char i = 'a';
    while(i<'a'+char(T_process))
    {
        cout<<i<<endl;
        sleep(1);
        i = char(i+1);
    }
    return 0;
}