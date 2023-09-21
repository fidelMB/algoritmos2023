#include <iostream>
using namespace std;


int secuencial(int nums[], int objetivo){
    for(int i = 0; i < sizeof(nums); i++){
        if(nums[i] == objetivo){
        return i;
        break;
        }
    }
    return -1;
}

int linearsearch(int arr[], int size, int key){
    if(size == 0){
        return -1;
    }
    if(arr[size-1] == key){
        return size - 1;
    }
    else{
        int ans = linearsearch(arr, size - 1, key);
        return ans;
    }
}



int main(){
    int lista[5] = {1,2,3,4,5};
    cout << secuencial(lista,3);

}