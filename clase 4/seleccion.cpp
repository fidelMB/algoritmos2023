void ordSeleccion(int a[], int n){
    int indiceMenor, i, j;
    int aux;

    for(i = 0; i<n-1;i++){
        indiceMenor = i;
        for(j = i+1;j<n;j++){
            if(a[j]<a[indiceMenor]){
                indiceMenor=j;
            }
        }
        if(i != indiceMenor){
            aux = a[i];
            a[i] = a[indiceMenor];
            a[indiceMenor] = aux;
        }
    }
}