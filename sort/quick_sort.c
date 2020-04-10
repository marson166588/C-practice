#include <stdio.h>

#define LENGTH(array) ( (sizeof(array) / sizeof(array[0])) )

void quick_sort(int numbers[], int left, int right)
{
    if (left < right) {
        int i = left, j = right;
        int ele = numbers[left];

        while (i < j) {
            while (i < j && numbers[j] > ele) {
                // 从右向左找小于ele的
                j--;
            }
            if (i < j) {
                numbers[i] = numbers[j];
                i++;
            }

            while (i < j && numbers[i] < ele) {
                // 从左向右找大于ele的
                i++;
            }
            if (i < j) {
                numbers[j] = numbers[i];
                j--;
            }
        }

        numbers[i] = ele;

        quick_sort(numbers, left, i - 1);
        quick_sort(numbers, i + 1, right);
    }
}

void split_quick_sort(int numbers[], int left, int right)
{
    if (left < right) {
        int i = left, j = left + 1;
        int ele = numbers[i];
        int tmp;

        for (; j <= right; j++) {
            if (numbers[j] < ele) {
                i++;
                tmp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = tmp;
            }
        }
        tmp = numbers[left];
        numbers[left] = numbers[i];
        numbers[i] = tmp;

        split_quick_sort(numbers, left, i - 1);
        split_quick_sort(numbers, i + 1, right);
    }

}

int main(int argc, char *argv[])
{
    int numbers[] = {20, 50, 10, 40, 90, 60, 100, 80, 70, 30};
    int len = LENGTH(numbers);
    int i;

    printf("sort befort:\n");
    for (i = 0; i < len; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    quick_sort(numbers, 0, len - 1);

    printf("sort after:\n");
    for (i = 0; i < len; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}
