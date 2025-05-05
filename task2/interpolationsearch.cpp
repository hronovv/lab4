#include "interpolationsearch.h"


int InterpolationSearch(int* arr, int size, int target) {
    int left = 0;
    int right = size - 1;
    while (left <= right && target >= arr[left] && target <= arr[right]) {
        int pos = left + (((target - arr[left]) * (right - left)) / (arr[right] - arr[left]));
        if (arr[pos] == target) {
            return pos;
        }
        if (arr[pos] < target) {
            left = pos + 1;
        } else {
            right = pos - 1;
        }
    }

    return -1;
}
