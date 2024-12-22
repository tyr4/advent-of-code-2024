#include <stdio.h>

int* bubblesort(int *v, int n) {
    int aux;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (v[i] > v[j])
            {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
    return v;
}

int main(void) {
    FILE *fptr = fopen("E:\\CL Ion projects\\advent of code 2024\\input.txt", "r");
    int unu[1000], doi[1000];
    int i = 0, s = 0;

    while (fscanf(fptr, "%d %d", &unu[i], &doi[i]) == 2)
        i++;

    fclose(fptr);

    // part 1
    bubblesort(unu, i);
    bubblesort(doi, i);

    for (i = 0; i < 1000; i++)
    {
        if (unu[i] > doi[i])
            s += unu[i] - doi[i];
        else s += doi[i] - unu[i];
    }
    printf("%d", s);

    // part 2
    long int s2 = 0;
    int freq[100000];

    for (i = 0; i < 1000; i++)
        freq[doi[i]]++;

    for (i = 0; i < 1000; i++)
        s2 += unu[i] * freq[unu[i]];

    printf("\n%ld", s2);
}
