#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


unsigned long long int concat(unsigned long long x, int y) {
    return x * (long long)pow(10, floor(log10(y != 0? y : 1)) + 1) + y;
}

char* binary_permutation(int n) {
    char *result = malloc(35 * sizeof(char));
    int index = 0;

    while (n != 0) {
        result[index++] = n & 1? '*' : '+';
        n >>= 1;
    }
    for (int i = 0; i < 20; i++) {
        result[index++] = '+';
    }
    result[index] = '\0';
    strrev(result);

    return result;
}

unsigned long long int eval(unsigned long long result, int numbers[20], int size, char* multi) {
    unsigned long long int sum = numbers[0];
    strrev(multi);
    for (int i = 1; i < size; i++) {
        if (multi[i - 1] == '+')
            sum += numbers[i];

        else if (multi[i - 1] == '*')
            sum *= numbers[i];

        else sum = concat(sum, numbers[i]);
    }
    return sum == result? 1 : 0;
}

// for the concat operator
char* binary_permutation_part_2(char* multi, int size, int n) {
    char* result = malloc(35 * sizeof(char));
    strcpy(result, multi);
    int i = 0;
    while (n != 0) {
        if (n & 1 && i < size)
            result[i] = '|';
        n >>= 1;
        i++;
    }
    strrev(result);
    return result;
}

int main() {
    FILE *fptr = fopen("E:\\CL Ion projects\\advent of code 2024\\input.txt", "r");
    char line[100];
    int numbers[1000][20], i = 0, j = 0;
    unsigned long long int sum = 0, sum2 = 0;
    printf("please wait a bit :)\n");

    while (fgets(line, 1000, fptr)) {
        j = 0;
        int ok = 0;
        char *p = strtok(line + 1 + strlen(line) - strlen(strstr(line, ":")), " ");
        while (p) {
            if (strstr(p, "\n"))
                p[strlen(p) - 1] = '\0';

            numbers[i][j++] = atoi(p);
            p = strtok(NULL, " ");
        }
        line[strlen(line) - strlen(strstr(line, ":"))] = '\0';
        const unsigned long long result = atoll(line);

        // part 1
        for (int k = 0; k <= pow(2, j - 1); k++) {
            char *multi = binary_permutation(k);
            if (eval(result, numbers[i], j, multi)) {
                sum += result;
                sum2 += result;
                free(multi);
                break;
            }
            
            // part 2 - ultra mega slow
            for (int l = 0; l <= k; l++) {
                char *concat_multi = binary_permutation_part_2(multi, (int)strlen(multi), l);
                if (eval(result, numbers[i], j, concat_multi)) {
                    sum += result;
                    free(concat_multi);
                    ok = 1;
                    break;
                }
                free(concat_multi);
            }
            if (ok == 1) break;

            free(multi);
        }
        i++;
    }
    printf("%llu\n%llu", sum2, sum);
    fclose(fptr);
}
