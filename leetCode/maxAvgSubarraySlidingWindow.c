#include <stdio.h>

int maxAvgSub(int *nums, int numsSize, int k){
    // getting sum of first window of size k
    int max_sum = 0;
    for (int i = 0; i < k; i++){
        max_sum += nums[i];

    }
    printf("max sum %d\n", max_sum);


    int window_sum = max_sum;
    printf("Initial max_avg_sub after first window: %d\n", max_sum);
    for (int i = k; i < numsSize; i++){
        // sliding window
        window_sum += nums[i] - nums[i - k];
        // adding last element to current window
        if (window_sum > max_sum){
            max_sum = window_sum;
            printf("updated max_avg_sub: %d\n", max_sum);
        }
    }
    double max_avg_sub = (double) max_sum /k;

    return max_avg_sub;
}







int main() {
    int nums[] = {1,12,-5,-6,50,3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);  // Calculate the number of elements in the array
    int k = 4;

    // Printing the size of the array in bytes and the number of elements
    printf("Size of arr in bytes: %zu\n", sizeof(nums));
    printf("size of arr[0] in bytes: %zu\n", sizeof(nums[0]));
    printf("Number of elements in arr: %d\n", numsSize);

    printf("Maximum sum of a subarray of size %d is %d\n", k, maxAvgSub(nums, numsSize, k));
    return 0;
}