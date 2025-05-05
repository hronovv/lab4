#include "interpolationsort.h"


void InterpolationSorter(int* arr, int size) {
    int min = arr[0];
    int max = arr[0];

    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        } else if (arr[i] > max) {
            max = arr[i];
        }
    }

    if (min != max) {
        std::vector<std::vector<int>> bucket(size);
        int interpolation;


        for (int i = 0; i < size; i++) {
            interpolation = static_cast<int>(
                ((double)(arr[i] - min) / (max - min)) * (size - 1));
            bucket[interpolation].push_back(arr[i]);
        }

        int start = 0;
        for (int i = 0; i < size; i++) {
            if (bucket[i].size() > 1) {
                InterpolationSorter(bucket[i].data(), bucket[i].size());
            }
            for (size_t j = 0; j < bucket[i].size(); j++) {
                arr[start++] = bucket[i][j];
            }
        }
    }
}
