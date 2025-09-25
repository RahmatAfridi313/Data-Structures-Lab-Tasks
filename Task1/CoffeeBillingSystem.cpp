#include<iostream>
using namespace std;


int main(){
    int equantity;
    int lquantity;
    int cquantity;

    float espressoPrice = 150;
    float *ePrice = &espressoPrice;

    float lattePrice = 200;
    float *lPrice = &lattePrice;

    float cappucinoPrice = 250;
    float *cPrice = &cappucinoPrice;

    cout<<"Enter the espresso quantity : ";
    cin>>equantity;
    cout<<"Enter the latte quantity : ";
    cin>>lquantity;
    cout<<"Enter the cuppuccino : ";
    cin>>cquantity;

    // creating pointers for quantities
    int *e = &equantity;
    int *l = &lquantity;
    int *c = &cquantity;

    // pointers for calculating total prices of single single items
    float eTotalPrice = *ePrice * *e; 
    float *eTotal = &eTotalPrice;

    float lTotalPrice = *lPrice * *l;
    float *lTotal = &lTotalPrice;

    float cTotalPrice = *cPrice * *c;
    float *cTotal = &cTotalPrice;

    // calculating sum as a whole 
    float TotalSum = *eTotal + *lTotal + *cTotal;
    float *tsum = &TotalSum;

    cout<<" -----Cafe Bill----"<<endl;
    cout<<"Espresso ("<<*e<<" X "<<*ePrice<<") = "<<*eTotal<<endl; 
    cout<<"Latte ("<<*l<<" X "<<*lPrice<<") = "<<*lTotal<<endl; 
    cout<<"Cappucino ("<<*c<<" X "<<*cPrice<<") = "<<*cTotal<<endl; 
    cout<<"----------------------------"<<endl;
    cout<<"The total = "<<*tsum<<endl;
    return 0;
}
