/**
 *Programa con 3 métodos de suma desde 1 hasta n
 *Fidel Morales Briones A01198630
 *13 de agosto de 2023
 */
#include <iostream>
#include <vector>
using namespace std;

/**
 * Método de ordenación por intercambio
 *
 * Con dos ciclos for, ... para ordenar el vector de números de manera ascendente.
 *
 * Entrada: un vector<double> con n números
 * Salida: nada
 * Complejidad tiempo: n^2
 * Complejidad espacio:
 */

template<typename T>
void ordenaPorIntercambio(vector<T>& arr){
    int i, j, aux, n = arr.size();
    for(i = 0; i <= n - 2; i++){
        for(j = i + 1; j <= n - 1; j++){
            if(arr[i] > arr[j]){
                aux = arr[i];
                arr[i] = arr[j];
                arr[j] = aux;
            }
        }
    }
}

/**
 * Suma desde 1 hasta n, método iterativo / título breve
 *
 * Con el uso de un ciclo for, se suma de manera iterativa desde 1 hasta el número n. / descrpción más detallada
 *
 * Entrada:
 * Salida:
 * Complejidad tiempo:
 * Complejidad espacio:
 */
template<typename T>
void ordenaPorBurbuja(vector<T>& arr){
    int n = arr.size();
    bool interruptor = true;
    for(int i = 0; i < n - 1 && interruptor; i++){
        interruptor = false;
        for(int j = 0; j < n - 1 - i; j++){
            if(arr[j + 1] < arr[j]){
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                interruptor = true;
            }
        }
    }
}

/**
 * Suma desde 1 hasta n, método iterativo / título breve
 *
 * Con el uso de un ciclo for, se suma de manera iterativa desde 1 hasta el número n. / descrpción más detallada
 *
 * Entrada:
 * Salida:
 * Complejidad tiempo:
 * Complejidad espacio:
 */
// Merge two subarrays L and M into arr
// Merge two sorted subarrays into a single sorted array
template<typename T>
void merge(vector<T>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;

    // Create temporary arrays
    vector<T> L(n1);
    vector<T> R(n2);

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge sort function
/**
 * Suma desde 1 hasta n, método iterativo / título breve
 *
 * Con el uso de un ciclo for, se suma de manera iterativa desde 1 hasta el número n. / descrpción más detallada
 *
 * Entrada:
 * Salida:
 * Complejidad tiempo:
 * Complejidad espacio:
 */
template<typename T>
void ordenaPorMerge(vector<T>& arr, int left, int right){
    if (left < right) {
        // Same as (left+right)/2, but avoids overflow for large left and right
        int mid = left + (right - left) / 2;

        // Recursively sort two halves
        ordenaPorMerge(arr, left, mid);
        ordenaPorMerge(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

/**
 * Suma desde 1 hasta n, método iterativo / título breve
 *
 * Con el uso de un ciclo for, se suma de manera iterativa desde 1 hasta el número n. / descrpción más detallada
 *
 * Entrada:
 * Salida:
 * Complejidad tiempo:
 * Complejidad espacio:
 */
template<typename T>
int busquedaSecuencial(vector<T>& arr, int objetivo){
    for(int i = 0; i < arr.size(); i++){
        if(arr[i] == objetivo){
        return i;
        break;
        }
    }
    return -1;
}

/**
 * Suma desde 1 hasta n, método iterativo / título breve
 *
 * Con el uso de un ciclo for, se suma de manera iterativa desde 1 hasta el número n. / descrpción más detallada
 *
 * Entrada:
 * Salida:
 * Complejidad tiempo:
 * Complejidad espacio:
 */
template<typename T>
int busquedaBinaria(vector<T>& arr, int objetivo)
{
    int l = 0, r = arr.size();
	while (l <= r) {
		int m = l + (r - l) / 2;
		// Check if x is present at mid
		if (arr[m] == objetivo)
			return m;
		// If x greater, ignore left half
		if (arr[m] < objetivo)
			l = m + 1;
		// If x is smaller, ignore right half
		else
			r = m - 1;
	}
	// If we reach here, then element was not present
	return -1;
}

int main(){
    vector<double> vector1 = {3.14, 0.987, 2.718, 4.56, 7.89, 6.543, 9.12, 5.678, 1.234, 8.765};
    vector<double> vector2 = {2.22, 9.87, 4.32, 1.11, 6.66, 5.55, 3.33, 8.88, 7.77, 0.99};
    vector<double> vector3 = {0.123, 4.567, 9.876, 3.456, 1.234, 7.890, 6.789, 5.678, 2.345, 8.901};
    vector<double> vector4 = {8.31, 6.72, 4.59, 0.87, 2.46, 3.99, 5.12, 1.23, 9.54, 7.68};


    /*ordenaPorIntercambio(vector1);
    ordenaPorBurbuja(vector1);
    */
    ordenaPorMerge(vector1, 0, vector1.size());

    for(int i = 0; i <= vector1.size(); i++){
        cout << vector1[i] << " ";
    }

    return 0;
}
