void burbuja(int a[], int n){
    bool interruptor = true;
    for(int pasada = 0;pasada<n-1 && interruptor; pasada++){
        interruptor = false;
        for(int j = 0; j<n-1-pasada;j++){
            if(a[j+1]<a[j]){
                int tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
                interruptor = true;
            }

        }
    }
}