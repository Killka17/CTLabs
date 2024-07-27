#include <iostream>



void QuickSortHoare(int* array, const int start, const int end) {
    int pivot = (array[start] + array[end]) / 2;
    int left_cur = start, right_cur = end;

    while (left_cur <= right_cur) {

        while (array[left_cur] < pivot) left_cur++;

        while (array[right_cur] > pivot) right_cur--;

        if (left_cur <= right_cur) {
            std::swap(array[left_cur], array[right_cur]);
            left_cur++;
            right_cur--;
        }
    }

    if (left_cur < end)
        QuickSortHoare(array, left_cur, end);

    if (right_cur > start)
        QuickSortHoare(array, start, right_cur);

}


int main() {

    int n;
    std::cin >> n;

    int numbers[n];

    for (int i = 0; i < n; ++i) {

        std::cin >> numbers[i];

    }

    QuickSortHoare(numbers, 0, n - 1);

    for (int i = 0; i < n; ++i) {
        std::cout << numbers[i];

        if (i < n-1)
            std::cout << " ";

    }
}