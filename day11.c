#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define blinks 75

int index = 0, index2 = 0, half[2];
unsigned long long dict[10000][2], dict2[10000][2];

int search(unsigned long long n) {
    for (int i = 0; i < 10000; i++) {
        if (dict2[i][0] == n)
            return i;
    }
    return -1;
}

void split(unsigned long long n) {
    char string[15] = "";
    int left = 0, right = 0;
    for (int i = 0; n != 0; i++) {
        string[i] = n % 10 + '0';
        n /= 10;
    }
    strrev(string);

    for (int i = 0; i < strlen(string) / 2; i++) {
        left = left * 10 + (string[i] - '0');
        right = right * 10 + (string[i + strlen(string) / 2] - '0');
    }

    half[0] = left, half[1] = right;
}

int digits(unsigned long long n) {
    int i = 0;
    while (n != 0) {
        n = n / 10;
        i++;
    }
    return i;
}

int main() {
    FILE *fptr = fopen("D:\\CLionProjects\\advent of code 2024\\input.txt", "r");
    char line[100];
    unsigned long long sum = 0, sum2 = 0;

    // initialize dict
    for (int i = 0; i < 10000; i++) {
        dict[i][0] = dict2[i][0] = -1;
        dict[i][1] = dict2[i][1] = 0;
    }

    while (fgets(line, 100, fptr)) {
        char *p = strtok(line, " ");
        while (p) {
            dict[index][0] = atoll(p);
            dict[index++][1] = 1;
            p = strtok(NULL, " ");
        }
    }
    fclose(fptr);

    for (int blink = 0; blink < blinks; blink++) {
        for (int j = 0; j < 10000; j++) {
            dict2[j][0] = -1;
            dict2[j][1] = 0;
        }
        for (int i = 0; i < index; i++) {
            unsigned long long stone = dict[i][0], freq = dict[i][1];
            int rez = search(stone + 1);
            // rule #1
            if (stone == 0) {
                if (rez != -1) {
                    // dict2[rez][0] = 1;
                    dict2[rez][1] += freq;
                }
                else {
                    dict2[index2][0] = 1;
                    dict2[index2++][1] += freq;
                }
            }
            // rule #2
            else if (digits(stone) % 2 == 0) {
                split(stone);
                int left = search(half[0]);
                // add left stone
                if (left != -1) {
                    // dict2[left][0] = half[0];
                    dict2[left][1] += freq;
                }
                else {
                    dict2[index2][0] = half[0];
                    dict2[index2++][1] += freq;
                }
                int right = search(half[1]);
                // add right stone
                if (right != -1) {
                    // dict2[right][0] = half[1];
                    dict2[right][1] += freq;
                }
                else {
                    dict2[index2][0] = half[1];
                    dict2[index2++][1] += freq;
                }
            }
            // rule #3
            else {
                stone *= 2024;
                rez = search(stone);
                if (rez != -1) {
                    dict2[rez][1] += freq;
                }
                else {
                    dict2[index2][0] = stone;
                    dict2[index2++][1] += freq;
                }
            }
        }

        for (int i = 0; i < index2; i++) {
            dict[i][0] = dict2[i][0];
            dict[i][1] = dict2[i][1];
        }

        index = index2;
        index2 = 0;
        // part 1
        if (blink == 25 - 1) {
            for (int i = 0; i < index; i++)
                sum += dict[i][1];
        }
    }
    // part 2
    for (int i = 0; i < index; i++)
        sum2 += dict[i][1];
    printf("%llu\n%llu", sum, sum2);
}
