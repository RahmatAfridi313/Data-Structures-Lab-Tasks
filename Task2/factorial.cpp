#include<iostream>
using namespace std;

int generateCode(int n)
{
    int fact = 1;
    if(n<=0)
    {
        fact = 1;
    }
    else
    {
        for(int i=n; i>=1; i--)
        {
            fact = fact * i;
        }
    }
    return fact;   
}

int(*ptrfact)(int) = &generateCode;
int main()
{
    int num;
    cout<<"Enter the number for factorial : ";
    cin>>num;
    //int factoial = generateCode(num);

    int factoraiPtr = (*ptrfact)(num);
    cout<<factoraiPtr<<endl;

    return 0;
}
