#include <stdio.h>

void number_sort(int numbers[], int size)
{
    int i, j, tmp;
    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            if (numbers[i] > numbers[j]) {
                tmp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = tmp;
            }
        }
    }
}

int binary_search(int target, int numbers[], int size)
{
    int mid, start = 0, end = size - 1;

    while (start <= end) {
        mid = (start + end) / 2;
        if (target > numbers[mid]) {
            start = mid + 1;
        } else if (target < numbers[mid]) {
            end = mid - 1;
        } else {
            return mid;
        }
    }

    return -1;
}

int main(int argc, char *argv[])
{
    int len = 6;
    int numbers[] = {10, 3, 5, 7, 2, 9};
    number_sort(numbers, len);
    for (int i = 0; i < len; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // find
    printf("target: 9, pos: %d\n", binary_search(9, numbers, len));
    printf("target: 2, pos: %d\n", binary_search(2, numbers, len));
    // not found
    printf("target: 8, pos: %d\n", binary_search(8, numbers, len));

    return 0;
}
