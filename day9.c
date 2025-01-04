#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define sizee 96000
#define digits 5

static char disk[sizee][digits];
static char disk2[sizee][digits];

char* itos(int n) {
    char *string = malloc(5 * sizeof(char));
    strcpy(string, "");
    char num[100] = "";
    int num_length = (int)floor(log10(n == 0? 1 : n)) + 1;
    do {
        num[0] = (char)(n % 10 + '0');
        strcat(string, num);
        n /= 10;
    } while (n != 0);
    string[num_length] = '\0';
    strrev(string);

    return string;
}

int valid_gap(int size, int index) {
    int counter = 0;
    for (int i = 0; i < index + 1; i++) {
        if (strcmp(disk2[i], ".") == 0) {
            counter++;
        }
        else if (counter != 0) {
            if (counter >= size)
                return i - counter;
            // printf("%d\n", counter);
            counter = 0;
        }

    }
    return -1;
}

unsigned long long int checksum(int size) {
    unsigned long long int sum = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(disk[i], ".") == 0)
            return sum;
        unsigned long long int rez = i * atoll(disk[i]);
        sum += rez;
    }
    return sum;
}

unsigned long long int checksum2(int size) {
    unsigned long long int sum = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(disk2[i], ".") != 0) {
            unsigned long long int rez = i * atoll(disk2[i]);
            sum += rez;
        }
    }
    return sum;
}


int main() {
    FILE *fptr = fopen("D:\\CLionProjects\\advent of code 2024\\input.txt", "r");
    static char line[20000];
    int index = 0, disk_index = 0;
    while (fgets(line, 30000, fptr)) {}
    fclose(fptr);

    for (int i = 0; i < 20000; i++) {
        if (i & 1)
            for (int j = 0; j < line[i] - '0'; j++)
                strcpy(disk[index++], ".");
        else {
            char* ceva = itos(disk_index);
            for (int j = 0; j < line[i] - '0'; j++) {
                strcpy(disk[index++], ceva);
            }
            free(ceva);
            disk_index++;
        }
    }
    for (int i = 0; i < index; i++) {
        strcpy(disk2[i], disk[i]);
        // printf("%s", disk2[i]);
    }

    // part 1
    int disk_index_copy = index;
    for (int i = 0; i < index; i++) {
        if (strcmp(disk[i], ".") == 0) {
            while (strcmp(disk[disk_index_copy - 1], ".") == 0)
                disk_index_copy--;

            if (i > disk_index_copy - 2)
                break;

            strcpy(disk[i], disk[disk_index_copy - 1]);
            strcpy(disk[disk_index_copy-- - 1], ".");
        }
    }

    // part 2
    int prev_count = 1;
    int prev_index[10000][3], k = 0;
    int disk_index_copy2 = index - 2;
    while (strcmp(disk2[disk_index_copy2], ".") == 0) {
        disk_index_copy2--;
    }
    int prev = atoi(disk2[disk_index_copy2]);

    for (int i = 0; disk_index_copy2 >= 0; i++) {
        if (strcmp(disk2[disk_index_copy2], ".") != 0 && atoi(disk2[disk_index_copy2]) == prev) {
            prev_count++;
            prev = atoi(disk2[disk_index_copy2--]);
        }
        else {
            prev_index[k][0] = prev_count;
            prev_index[k][1] = prev;
            prev_index[k++][2] = disk_index_copy2 + 1;
            prev_count = 1;
            if (strcmp(disk2[disk_index_copy2], ".") != 0)
                prev = atoi(disk2[disk_index_copy2--]);
            else {
                while (strcmp(disk2[disk_index_copy2], ".") == 0)
                    disk_index_copy2--;
                prev = atoi(disk2[disk_index_copy2--]);
            }
        }
    }
    prev_index[k][0] = prev_count;
    prev_index[k++][1] = prev;

    for (int i = 0; i < k; i++) {
        int rez = valid_gap(prev_index[i][0], prev_index[i][2]);
        if (rez != -1) {
            for (int j = rez; j < prev_index[i][0] + rez; j++) {
                strcpy(disk2[j], itos(prev_index[i][1]));
                strcpy(disk2[prev_index[i][2] - rez + j], ".");
            }
        }
    }

    unsigned long long sum = checksum(index), sum2 = checksum2(index);
    printf("%lld\n%lld", sum, sum2);
}