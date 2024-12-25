#include <stdio.h>

int isXmas(char a[3][3]) {
    if (a[1][1] == 'A') {
        // case 1
        if (a[0][0] == 'M' && a[0][2] == 'M' && a[2][0] == 'S' && a[2][2] == 'S')
            return 1;
        // case 2
        if (a[0][0] == 'M' && a[0][2] == 'S' && a[2][0] == 'M' && a[2][2] == 'S')
            return 1;
        // case 3
        if (a[0][0] == 'S' && a[0][2] == 'S' && a[2][0] == 'M' && a[2][2] == 'M')
            return 1;
        // case 4
        if (a[0][0] == 'S' && a[0][2] == 'M' && a[2][0] == 'S' && a[2][2] == 'M')
            return 1;
    }
    return 0;
}

int horizontal(char input[140][142]) {
    int total_count = 0;
    for (int i = 0; i < 140; i++)
        for (int j = 0; j < 140 - 3; j++)
        {
            if ((input[i][j] == 'X' && input[i][j + 1] == 'M' && input[i][j + 2] == 'A' && input[i][j + 3] == 'S')
                || (input[i][j] == 'S' && input[i][j + 1] == 'A' && input[i][j + 2] == 'M' && input[i][j + 3] == 'X'))
                total_count++;
        }
    return total_count;
}

int vertical(char input[140][142]) {
    int total_count = 0;
    for (int i = 0; i < 140; i++)
        for (int j = 0; j < 140 - 3; j++)
        {
            if ((input[j][i] == 'X' && input[j + 1][i] == 'M' && input[j + 2][i] == 'A' && input[j + 3][i] == 'S')
                || (input[j][i] == 'S' && input[j + 1][i] == 'A' && input[j + 2][i] == 'M' && input[j + 3][i] == 'X'))
                total_count++;
        }
    return total_count;
}

int horizontal2(char input[279][140]) {
    int total_count = 0;
    for (int i = 0; i < 279; i++)
        for (int j = 0; j < 140 - 3; j++)
        {
            if ((input[i][j] == 'X' && input[i][j + 1] == 'M' && input[i][j + 2] == 'A' && input[i][j + 3] == 'S')
                || (input[i][j] == 'S' && input[i][j + 1] == 'A' && input[i][j + 2] == 'M' && input[i][j + 3] == 'X'))
                total_count++;
        }
    return total_count;
}

int main(void) {
    FILE *fptr = fopen("E:\\CL Ion projects\\advent of code 2024\\input.txt", "r");
    int i = 0, total_count = 0;
    char input[140][142], flipped1[279][140], flipped2[279][140];

    while (fgets(input[i++], 142, fptr));

    // part 1

    // diagonal
    // above the secondary diagonal
    for (i = 0; i < 140; i++)
        for (int j = 0; j <= i; j++)
            flipped1[i][j] = input[j][i - j];

    // below the secondary diagonal
    for (i = 1; i < 140; i++)
        for (int j = 0; j <= 140 - i - 1; j++)
            flipped1[140 + i - 1][j] = input[i + j][140 - j - 1];

    // above the main diagonal
    for (i = 0; i < 140; i++)
        for (int j = 0; j <= i; j++)
            flipped2[i][j] = input[j][140 - 1 - i + j];

    // below the main diagonal
    for (i = 1; i < 140; i++)
        for (int j = 0; j <= 140 - i - 1; j++)
            flipped2[140 + i - 1][j] = input[i + j][j];

    // fill with 0s
    for (i = 0; i < 279; i++)
    {
        for (int j = 0; j < 140; j++)
        {
            if (!flipped1[i][j])
                flipped1[i][j] = '0';
            if (!flipped2[i][j])
                flipped2[i][j] = '0';
            // printf("%c ", flipped2[i][j]);
        }
        // printf("\n");
    }

    total_count += vertical(input);
    total_count += horizontal(input);
    total_count += horizontal2(flipped1);
    total_count += horizontal2(flipped2);
    printf("%d\n", total_count);

    // part 2
    char a[3][3];
    total_count = 0;
    for (i = 0; i < 140 - 2; i++)
        for (int j = 0; j < 140 - 2; j++) {
            a[0][0] = input[i][j];
            a[0][1] = input[i][j + 1];
            a[0][2] = input[i][j + 2];

            a[1][0] = input[i + 1][j];
            a[1][1] = input[i + 1][j + 1];
            a[1][2] = input[i + 1][j + 2];

            a[2][0] = input[i + 2][j];
            a[2][1] = input[i + 2][j + 1];
            a[2][2] = input[i + 2][j + 2];

            total_count += isXmas(a);
        }

    printf("%d\n", total_count);
    fclose(fptr);
}
