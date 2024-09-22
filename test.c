#include <stdio.h>

void findLargestSmallest(int arr[], int start, int end, int *largest, int *smallest, int *largestIndex, int *smallestIndex) {
    *largest = arr[start];
    *smallest = arr[start];
    *largestIndex = start;
    *smallestIndex = start;

    for (int i = start; i <= end; i++) {
        if (arr[i] > *largest) {
            *largest = arr[i];
            *largestIndex = i;
        } else if (arr[i] < *smallest) {
            *smallest = arr[i];
            *smallestIndex = i;
        }
    }
}

void customSort(int arr[], int n) {
    int start = 0, end = n - 1;
    int largest, smallest, largestIndex, smallestIndex;

    while (start < end) {
        findLargestSmallest(arr, start, end, &largest, &smallest, &largestIndex, &smallestIndex);

        
        int temp = arr[start];
        arr[start] = smallest;
        arr[smallestIndex] = temp;

        
        if (largestIndex == start) {
            largestIndex = smallestIndex;
        }

        
        temp = arr[end];
        arr[end] = largest;
        arr[largestIndex] = temp;

        start++;
        end--;
    }
}

int main() {
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    int arr[n];

    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    customSort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}