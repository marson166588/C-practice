#include <stdio.h>

void insert_sort(int numbers[], int len)
{
    int i, j, tmp, k;
    for (i = 1; i < len; i++) {
        for (k = 0; k < len; k++) {
            printf("%d ", numbers[k]);
        }

        tmp = numbers[i];
        j = i - 1;
        while (j >= 0 && numbers[j] > tmp) {
            numbers[j + 1] = numbers[j];
            j--;
        }
        numbers[j + 1] = tmp;
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int len = 10;
    int numbers[] = {12, 3, 67, 89, 4, 18, 90, 58, 22, 34};
    insert_sort(numbers, len);

    int i;
    for (i = 0; i < len; i++) {
        printf("%d ", numbers[i]);
    }
    return 0;
}
