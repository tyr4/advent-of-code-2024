#include <math.h>
#include <stdio.h>

char a[100][100], overlap[100][100], overlap2[100][100], a2[100][100]; // the last 2 are for part 2

void add_extra_antinodes(int i, int j, int x, int y, int size) {
    while (x != 0 && y != 0) {
        int distance_i = abs(x - i);
        int distance_j = abs(y - j);
        if (y > j) {
            if (x + distance_i < size && y + distance_j < size) {
                if (a2[x + distance_i][y + distance_j] == '.')
                    a2[x + distance_i][y + distance_j] = '#';
                else overlap2[x + distance_i][y + distance_j] = '#';
            }
            i = x;
            j = y;
            x += distance_i;
            y += distance_j;
        }
        else if (y < j) {
            if (x + distance_i < size && y - distance_j >= 0) {
                if (a2[x + distance_i][y - distance_j] == '.')
                    a2[x + distance_i][y - distance_j] = '#';
                else overlap2[x + distance_i][y - distance_j] = '#';
            }
            i = x;
            j = y;
            x += distance_i;
            y -= distance_j;
        }
        if (x > size || y > size || (x == i && y == j))
            break;
    }
}

void add_extra_antinodes2(int i, int j, int x, int y, int size) {
    if (x == i && y == j)
        return;

    while (x >= 0 && y >= 0) {
        if (x < 0 || y < 0 || i < 0 || j < 0)
            return;
        int distance_i = abs(x - i);
        int distance_j = abs(y - j);

        if (y > j) {

            if (i - distance_i >= 0 && j - distance_j >= 0) {
                if (a2[i - distance_i][j - distance_j] == '.')
                    a2[i - distance_i][j - distance_j] = '#';
                else overlap2[i - distance_i][j - distance_j] = '#';
            }
            x = i;
            y = j;
            i -= distance_i;
            j -= distance_j;
        }
        else if (y < j) {
            if (i - distance_i >= 0 && j + distance_j < size) {
                if (a2[i - distance_i][j + distance_j] == '.')
                    a2[i - distance_i][j + distance_j] = '#';
                else overlap2[i - distance_i][j + distance_j] = '#';
            }
            x = i;
            y = j;
            i -= distance_i;
            j += distance_j;
        }
    }
}

int main() {
    FILE *fptr = fopen("E:\\CL Ion projects\\advent of code 2024\\input.txt", "r");

    int size = -1, sum = 0, sum2 = 0;
    while (fgets(a[++size], 100, fptr)) {
        *a2[size] = a[size];
    }
    fclose(fptr);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (a[i][j] != '.' && a[i][j] != '#') {
                for (int x = i; x < size; x++) {
                    for (int y = 0; y < size; y++) {
                        if (a[x][y] == a[i][j]) {
                            overlap2[x][y] = '#';
                            int distance_i = abs(x - i);
                            int distance_j = abs(y - j);

                            if (y > j) {
                                if (x + distance_i < size && y + distance_j < size) {
                                    if (a[x + distance_i][y + distance_j] == '.')
                                        a[x + distance_i][y + distance_j] = '#';
                                    else overlap[x + distance_i][y + distance_j] = '#';
                                }
                                if (i - distance_i >= 0 && j - distance_j >= 0) {
                                    if (a[i - distance_i][j - distance_j] == '.')
                                        a[i - distance_i][j - distance_j] = '#';
                                    else overlap[i - distance_i][j - distance_j] = '#';
                                }
                            }
                            else if (y < j) {
                                if (x + distance_i < size && y - distance_j >= 0) {
                                    if (a[x + distance_i][y - distance_j] == '.')
                                        a[x + distance_i][y - distance_j] = '#';
                                    else overlap[x + distance_i][y - distance_j] = '#';
                                }

                                if (i - distance_i >= 0 && j + distance_j < size) {
                                    if (a[i - distance_i][j + distance_j] == '.')
                                     a[i - distance_i][j + distance_j] = '#';
                                    else overlap[i - distance_i][j + distance_j] = '#';
                                }
                            }
                            add_extra_antinodes(i, j, x, y, size);
                            add_extra_antinodes2(i, j, x, y, size);
                        }
                    }
                }
            }
        }
    }
    // behold the great curly bracketing

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            sum += a[i][j] == '#' || overlap[i][j] == '#'? 1:0;
            sum2 += a[i][j] == '#' || overlap[i][j] == '#' || a2[i][j] == '#' || overlap2[i][j] == '#'? 1:0;
        }
    }
    printf("%d\n%d", sum, sum2);
}
