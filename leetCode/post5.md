# LeetCode



Key algorithms:
binary search
DFS
BFS
Sliding window


## Binary search algo
![alt text](image-58.png)



#include <stdio.h>
#include <stdlib.h>

// Define a hash map structure
typedef struct {
    int key;
    int value;
} HashMap;

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    // Initialize hash map
    HashMap* hashMap = (HashMap*)malloc(numsSize * sizeof(HashMap));
    int hashMapSize = 0;

    // Iterate through the array
    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        // Check if complement is already in the hash map
        for (int j = 0; j < hashMapSize; j++) {
            if (hashMap[j].key == complement) {
                int* result = (int*)malloc(2 * sizeof(int));
                result[0] = hashMap[j].value;
                result[1] = i;
                *returnSize = 2;
                free(hashMap);
                return result;
            }
        }
        // Add current element to the hash map
        hashMap[hashMapSize].key = nums[i];
        hashMap[hashMapSize].value = i;
        hashMapSize++;
    }

    *returnSize = 0;
    free(hashMap);
    return NULL;
}
// Helper function to print the result
void printResult(int* result, int returnSize) {
    if (result != NULL) {
        printf("[");
        for (int i = 0; i < returnSize; i++) {
            printf("%d", result[i]);
            if (i < returnSize - 1) {
                printf(",");
            }
        }
        printf("]\n");
        free(result);
    } else {
        printf("No solution found.\n");
    }
}