#include <stdio.h>

// Function to find the maximum sum of a subarray of size k
int maxSum(int arr[], int n, int k) {
    // Compute sum of the first window of size k
    int max_sum = 0;
    for (int i = 0; i < k; i++) {
        max_sum += arr[i];
        printf("111111111111 Adding arr[%d] = %d to max_sum: %d\n", i, arr[i], max_sum);
    }

    // Compute sums of remaining windows by removing the first element of the
    // previous window and adding the last element of the current window
    int window_sum = max_sum;
    printf("Initial max_sum after first window: %d\n", max_sum);
    for (int i = k; i < n; i++) {
        window_sum += arr[i] - arr[i - k];
        printf("Adding arr[%d] = %d and removing arr[%d] = %d from window_sum: %d\n", i, arr[i], i - k, arr[i - k], window_sum);
        if (window_sum > max_sum) {
            max_sum = window_sum;
            printf("Updated max_sum to: %d\n", max_sum);
        }
    }

    return max_sum;
}


int main() {
    int arr[] = {11, 12, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);  // Calculate the number of elements in the array
    int k = 3;

    // Printing the size of the array in bytes and the number of elements
    printf("Size of arr in bytes: %zu\n", sizeof(arr));
    printf("size of arr[0] in bytes: %zu\n", sizeof(arr[0]));
    printf("Number of elements in arr: %d\n", n);

    printf("Maximum sum of a subarray of size %d is %d\n", k, maxSum(arr, n, k));
    return 0;
}