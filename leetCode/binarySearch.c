#include <stdio.h>

// Binary Search function
int search(int* nums, int numsSize, int target) {
    printf("nums = %d, numsSize = %d, target = %d\n", *nums, numsSize, target);
    int l = 0;
    int r = numsSize - 1;
    printf("l = %d, r = %d\n", l, r);
    while (l <= r) {
        int mid = l + (r - l) / 2;
        
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] > target) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    
    return -1;
}

// Main function to test the binary search
int main() {
    int nums[] = {-1, 0, 3, 5, 9, 12};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int target;

    // Taking input from the user for the target
    printf("Enter the target number: ");
    scanf("%d", &target);

    int result = search(nums, numsSize, target);

    if (result != -1) {
        printf("Element found at index %d\n", result);
    } else {
        printf("Element not found\n");
    }

    return 0;
}
