#include <iostream>
using namespace std;

int main(){
    int a = 5, *p;
    p = new int; 
    *p = a;
    a = *p + 2;
    cout << a << " " << *p;

    delete p;
}