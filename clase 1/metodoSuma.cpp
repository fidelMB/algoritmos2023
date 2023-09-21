#include <iostream>
using namespace std;


template<typename T>
T sumar(T numero_1, T numero_2){
    return numero_1 + numero_2;
}

int main(){
    cout<<sumar(1,2);
    return 0;
}
