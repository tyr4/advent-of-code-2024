#include <stdio.h>
#include <string.h>

// can prob optimize with a structure but cba
int a[100][100], order[1500][100], middle[1500], sizes[1500];

int valid(int printed[100], int size, int i) {
    for (int j = 1; order[i][j]; j++) {
        for (int k = 0; k < size; k++) {
            if (a[order[i][j]][printed[k]] == 123456) {
                return 0;
            }
        }
        printed[size++] = order[i][j];
    }
    return size;
}

int* swap(int printed[100], int size, int i) {
    int aux;
    for (int j = 0; order[i][j]; j++) {
        for (int k = 0; k < size; k++) {
            if (a[printed[j]][printed[k]] == 123456) {
                aux = printed[j];
                printed[j] = printed[k];
                printed[k] = aux;
            }
        }
    }
    return printed;
}

int main() {
    FILE *fptr = fopen("E:\\CL Ion projects\\advent of code 2024\\input.txt", "r");
    int size = -1, mode = 0;
    int order_i = 0, order_j = 0, sum = 0;

    char input[1500][100];
    while (fgets(input[++size], 1000, fptr)) {
        order_j = 0;
        if (input[size][0] == '\n')
            mode = 1;

        if (mode == 0) {
            int page = (input[size][0] - '0') * 10 + (input[size][1] - '0');
            int printed_before = (input[size][3] - '0') * 10 + (input[size][4] - '0');
            a[page][printed_before] = 123456;
        }

        // ReSharper disable once CppDFAConstantConditions
        else if (mode == 1 && input[size][0] != '\n') {
            for (int i = 0; i < strlen(input[size]); i++) {
                if ((i + 3) % 3 == 0)
                    order[order_i][order_j++] = (input[size][i] - '0') * 10 + (input[size][i + 1] - '0');
            }
            middle[order_i] = order[order_i][order_j / 2];
            sizes[order_i] = order_j;
            order_i++;
        }
    }

    // part 1

    for (int i = 0; i < order_i; i++) {
        int printed[100];
        size = 0;
        printed[size++] = order[i][0];
        if (!valid(printed, size, i))
            continue;
        sum += middle[i];
    }

    // part 2
    int sum2 = 0;
    for (int c = 0; c < order_i; c++) {
        int printed[100];
        for (int i = 0; i < sizes[c]; i++)
            printed[i] = order[c][i];

        *printed = *swap(printed, sizes[c], c);
        sum2 += printed[sizes[c] / 2];

        for (int i = 0; i < sizes[c]; i++)
            printf("%d ", printed[i]);

        printf("// %d\n", printed[sizes[c] / 2]);
    }

    printf("%d\n%d", sum, sum2 - sum);
    fclose(fptr);
}
