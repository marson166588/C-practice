#include <stdio.h>

#define LENGTH(array) ( (sizeof(array) / sizeof(array[1])) )

/**
 * 选择排序法
 */
void select_sort(int numbers[], int len)
{
    int i, j, k, min, tmp;

    for (i = 0; i < len; i++) {
        min = i;
        for (j = i + 1; j < len; j++) {
            if (numbers[j] < numbers[min]) {
                min = j;
            }
        }

        if (min != i) {
            tmp        = numbers[i];
            numbers[i] = numbers[min];
            numbers[min] = tmp;
        }

        for (k = 0; k < len; k++) {
            printf("%d ", numbers[k]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int numbers[] = {20, 50, 10, 40, 90, 60};
    int len = LENGTH(numbers);
    int i;

    printf("sort befort:\n");
    for (i = 0; i < len; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    printf("sorting\n");
    select_sort(numbers, len);

    printf("sort after:\n");
    for (i = 0; i < len; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}
