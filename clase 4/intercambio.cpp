#include <iostream>
using namespace std;

void ordIntercambio(int a[], int n){
    int i, j, aux;
    for(i = 0; i<= n-2; i++){
        for(j=i+1;j<=n-1;j++){
            if(a[i]>a[j]){
                aux = a[i];
                a[i] = a[j];
                a[j] = aux;
            }
        }
    }
}

