#include<iostream>
#include<cstdlib>
#include<string>
using namespace std;

int main(int argc,char* argv[])
{
    if(argc >= 2) {
        double sum=0;
        int N = argc-1;
        double av;
        for(int i = 1; i < argc ;i++)
        {
            sum += atof(argv[i]);
        }
        av = sum/N;
        cout<<"---------------------------------\n";
        cout<<"Average of "<<N<<" numbers = "<< av; 
        cout<<"\n---------------------------------";
    }
    else {cout<<"Please input numbers to find average.";}
}
