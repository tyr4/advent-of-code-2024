#include <stdio.h>
#include <string.h>

#define grid_max 130

int pos[2], sum = 1; // move() doesnt account for the leaving step
int blocked = 0;

int move(char a[grid_max][grid_max], int pos[2], char *guard) {
    int i = pos[0], j = pos[1];

    if (*guard == '^')
        if ((a[i - 1][j] == '#' || a[i - 1][j] == 'O') && i != 0) {
            *guard = '>';
            if (a[i - 1][j] == 'O')
                blocked++;
        }
        else if ((a[i - 1][j] == '.' || a[i - 1][j] == 'X') && i != 0) {
            if (a[i - 1][j] != 'X')
                sum++;
            if (a[i][j] != 'O')
                a[i][j] = 'X';
            a[i - 1][j] = *guard;
            pos[0]--;
        }
        else return 0;

    else if (*guard == '>')
        if ((a[i][j + 1] == '#' || a[i][j + 1] == 'O') && j + 1 != grid_max) {
            *guard = 'v';
            if (a[i][j + 1] == 'O')
                blocked++;
        }
        else if ((a[i][j + 1] == '.' || a[i][j + 1] == 'X') && j + 1 != grid_max) {
            if (a[i][j + 1] != 'X')
                sum++;
            if (a[i][j] != 'O')
                a[i][j] = 'X';
            a[i][j + 1] = *guard;
            pos[1]++;
        }
        else return 0;

    else if (*guard == 'v')
        if ((a[i + 1][j] == '#' || a[i + 1][j] == 'O') && i + 1 != grid_max) {
            *guard = '<';
            if (a[i + 1][j] == 'O')
                blocked++;
        }
        else if ((a[i + 1][j] == '.' || a[i + 1][j] == 'X') && i + 1 != grid_max) {
            if (a[i + 1][j] != 'X')
                sum++;
            if (a[i][j] != 'O')
                a[i][j] = 'X';
            a[i + 1][j] = *guard;
            pos[0]++;
        }
        else return 0;

    else if (*guard == '<')
        if ((a[i][j - 1] == '#' || a[i][j - 1] == 'O') && j != 0) {
            *guard = '^';
            if (a[i][j - 1] == 'O')
                blocked++;
        }
        else if ((a[i][j - 1] == '.' || a[i][j - 1] == 'X') && j != 0) {
            if (a[i][j - 1] != 'X')
                sum++;
            if (a[i][j] != 'O')
                a[i][j] = 'X';
            a[i][j - 1] = *guard;
            pos[1]--;
        }
        else return 0;

    if (blocked == 3)
        return -1;

    return 1;
}

void reset_matrix(char a[grid_max][grid_max], char b[grid_max][grid_max]) {
    for (int i = 0; i < grid_max; i++) {
        for (int j = 0; j < grid_max; j++) {
            b[i][j] = a[i][j];
        }
    }
}

int block_guard(char a[grid_max][grid_max], int start_i, int start_j, char *guard) {
    int total_count = 0, pos[2] = {start_i, start_j};
    char b[grid_max][grid_max], original[grid_max][grid_max];
    for (int i = 0; i < grid_max; i++) {
        for (int j = 0; j < grid_max; j++) {
            b[i][j] = a[i][j];
            original[i][j] = b[i][j];
        }
    }
    for (int i = 0; i < grid_max; i++) {
        for (int j = 0; j < grid_max; j++) {
            if (i != start_i || j != start_j) {
                if (b[i][j] != '#') {
                    b[i][j] = 'O';
                    pos[0] = start_i, pos[1] = start_j;
                    *guard = '^';
                    blocked = 0;

                    int rez = move(b, pos, guard);
                    int iter = 0;
                    while (rez == 1) {
                        if (iter > 10000) { // absurd check when stuck in a loop that doesnt contain an O
                            total_count++;
                            break;
                        }
                        iter++;
                        rez = move(b, pos, guard);
                    }

                    reset_matrix(original, b);

                    if (rez == -1)
                        total_count++;
                }
            }
        }
    }
    return total_count;
}


int main() {
    FILE *fptr = fopen("E:\\CL Ion projects\\advent of code 2024\\input.txt", "r");

    int size = -1;
    int start_i = 0, start_j = 0;
    char a[grid_max][grid_max];

    while (fgets(a[++size], 1000, fptr)) {
        if (strchr(a[size], '^')) {
            start_i = size;
            start_j = strlen(a[size]) - strlen(strchr(a[size], '^')); // NOLINT(*-narrowing-conversions)
        }
    }
    char guard = a[start_i][start_j];
    pos[0] = start_i, pos[1] = start_j;

    // part 1
    while (move(a, pos, &guard)); // sum is being updated globally

    printf("%d\n", sum);

    // part 2
    printf("%d", block_guard(a, start_i, start_j, &guard));

    fclose(fptr);
}
