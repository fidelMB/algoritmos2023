#include <iostream>
#include <vector>
#include <string>

// Function to merge two subarrays
void merge(std::vector<std::string> &arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<std::string> leftArr(n1);
    std::vector<std::string> rightArr(n2);

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[middle + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Merge sort function
void mergeSort(std::vector<std::string> &arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}

int main() {
    std::vector<std::string> ips = {"192.168.1.2", "10.0.0.1", "172.16.0.1", "192.168.0.1", "10.1.1.1"};

    int n = ips.size();
    mergeSort(ips, 0, n - 1);

    std::cout << "Sorted IP Addresses:" << std::endl;
    for (const std::string &ip : ips) {
        std::cout << ip << std::endl;
    }

    return 0;
}
