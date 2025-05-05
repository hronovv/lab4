#include "median.h"


double calculateMedian(std::vector<int>& group) {
    quickSort(group, 0, group.size() - 1);
    int size = group.size();
    if (size % 2 == 1) {
        return group[size / 2];
    } else {
        return (group[(size / 2) - 1] + group[size / 2]) / kMedianNumber;
    }
}
