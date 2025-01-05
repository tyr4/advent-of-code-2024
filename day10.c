#include <stdio.h>

#define size 42

int a[size + 2][size + 2];
int overlap[size + 2][size + 2], overlap2[size + 2][size + 2];

// mode table
// 1 - up
// 2 - down
// 3 - left
// 4 - right

int trailhead(int i, int j, int prev, int mode) {
    if (a[i][j] - prev != 1)
        return 0;
    if (a[i][j] - prev == 1 && a[i][j] == 9) {
        // part 1
        overlap[i][j] = 1;

        // part 2
        overlap2[i][j] += 1;
        return 1;
    }

    if (prev == -1) {
        trailhead(i - 1, j, a[i][j], 1);
        trailhead(i + 1, j, a[i][j], 2);
        trailhead(i, j - 1, a[i][j], 3);
        trailhead(i, j + 1, a[i][j], 4);
    }
    else if (mode == 1) {
        trailhead(i - 1, j, a[i][j], 1);
        trailhead(i, j - 1, a[i][j], 3);
        trailhead(i, j + 1, a[i][j], 4);
    }
    else if (mode == 2) {
        trailhead(i + 1, j, a[i][j], 2);
        trailhead(i, j - 1, a[i][j], 3);
        trailhead(i, j + 1, a[i][j], 4);
    }
    else if (mode == 3) {
        trailhead(i - 1, j, a[i][j], 1);
        trailhead(i + 1, j, a[i][j], 2);
        trailhead(i, j - 1, a[i][j], 3);
    }
    else if (mode == 4) {
        trailhead(i - 1, j, a[i][j], 1);
        trailhead(i + 1, j, a[i][j], 2);
        trailhead(i, j + 1, a[i][j], 4);
    }
}

void reset_overlap() {
    for (int i = 0; i < size + 2; i++) {
        for (int j = 0; j < size + 2; j++) {
            overlap[i][j] = 0;
            overlap2[i][j] = 0;
        }
    }
}

int overlap_sum(int mode) {
    int sum = 0;
    for (int i = 0; i < size + 2; i++) {
        for (int j = 0; j < size + 2; j++) {
            if (overlap[i][j] != 0) {
                sum += mode == 1? 1 : overlap2[i][j];
            }
        }
    }
    return sum;
}

int main() {
    FILE *fptr = fopen("E:\\CL Ion projects\\advent of code 2024\\input.txt", "r");
    int i = 1, j = 1, sum = 0, sum2 = 0;
    char line[size + 2];
    while (fgets(line, size + 2, fptr)) {
        for (int k = 0; k < size; k++) {
            a[i][j++] = line[k] - '0';
        }
        i++;
        j = 1;
    }
    fclose(fptr);

    // surround the matrix with 0's
    for (i = 0; i < size + 2; i++) {
        a[0][i] = 0;
        a[size + 1][i] = 0;
        a[i][0] = 0;
        a[i][size + 1] = 0;
    }

    for (i = 1; i < size + 1; i++) {
        for (j = 1; j < size + 1; j++) {
            if (a[i][j] == 0) {
                reset_overlap();
                trailhead(i, j, -1, 1);
                sum += overlap_sum(1);
                sum2 += overlap_sum(2);
            }
        }
    }
    printf("%d\n%d", sum, sum2);
}