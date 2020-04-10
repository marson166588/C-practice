#include <stdio.h>

#define LENGTH(array) ( (sizeof(array) / sizeof(array[0])) )

void bubble_sort(int numbers[], int len)
{
    int i, j, k, tmp;

    for (i = 0; i < len; i++) {
        for (j = 0; j < len - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                tmp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = tmp;
            }
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
    bubble_sort(numbers, len);

    printf("sort after:\n");
    for (i = 0; i < len; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}
