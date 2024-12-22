#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int valid(int *v, int size) {
    int step_mode;
    step_mode = (v[0] - v[1] > 0)? 1:0; // 1 - decreasing, 0 - increasing
    for (int i = 0; i < size - 1; i++)
    {
        int rez = v[i] - v[i + 1];
        if (abs(rez) > 3 || abs(rez) < 1 || rez > 0 != step_mode)
            return 0;
    }
    return 1;
}

int problem_dampener(int *v, int size) {
    int aux[10];
    for (int yeet = 0; yeet < size; yeet++)
    {
        for (int i = 0; i < size - 1; i++)
        {
            if (i < yeet)
                aux[i] = v[i];
            else aux[i] = v[i + 1];
        }
        if ((valid(aux, size - 1)) == 1)
           return 1;
    }
    return 0;
}


int main(void) {
    FILE *fptr = fopen("E:\\CL Ion projects\\advent of code 2024\\input.txt", "r");
    char line[100];
    int v[10], size = 0, s = 0, s2 = 0;
    while (fgets(line, sizeof(line), fptr))
    {
        size = 0;
        char *p;
        p = strtok(line, " ");
        while (p)
        {
            v[size++] = atoi(p);
            p = strtok(NULL, " ");
        }

        // part 1
        s += valid(v, size);
        // part 2
        s2 += problem_dampener(v, size);
    }
    fclose(fptr);
    printf("%d\n", s);
    printf("%d", s2);
}
