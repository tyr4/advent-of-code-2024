#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int mul(char *p) {
    int s = 0, virgula = 0, index1 = 0, index2 = 0;
    char nr1[5] = "", nr2[5] = "";

    for (int i = 0; i < 12; i++)
    {
        // nr1 is set
        if (p[i] == ',')
            virgula = 1;

        // valid input? add up nr1 * nr2
        else if ((p[i] == ')' && virgula))
        {
            s += atoi(nr1) * atoi(nr2);
            break;
        }
        // invalid 2nd half
        else if (virgula && !(p[i] - '0' <= 9 && p[i] - '0' >= 0) && p[i] != ')')
            break;

        // assign the numbers to nr1 and nr2
        else if (p[i] - '0' <= 9 && p[i] - '0' >= 0 && !virgula)
            nr1[index1++] = p[i];
        else if (p[i] - '0' <= 9 && p[i] - '0' >= 0 && virgula)
            nr2[index2++] = p[i];

        // check for number length
        if (index1 > 3 || index2 > 3)
            break;
    }
    return s;
}

int add_all_mul(char *input) {
    int s = 0;
    char *p;
    p = strstr(input, "mul(");
    s += mul(p);
    while (p)
    {
        p = strstr(p + 1, "mul(");
        if (p)
            s += mul(p);
    }
    return s;
}

int main(void) {
    FILE *fptr = fopen("E:\\CL Ion projects\\advent of code 2024\\input.txt", "r");

    char mega_input[18000], a[18000] = "", no_dont[18000];
    long long int s = 0, s2 = 0;
    int flag = 1, index = 0;

    while (fgets(mega_input, sizeof(mega_input), fptr))
    {
        // part 1
        s += add_all_mul(mega_input);
        strcat(a, mega_input);
    }

    // part 2
    for (int i = 0; i < strlen(a); i++)
    {
        if (a[i] == 'd' && a[i + 1] == 'o' && a[i + 2] == 'n' && a[i + 3] == '\'' && a[i + 4] == 't' && a[i + 5] == '('
            && a[i + 6] == ')')  // i hate this
            flag = 0;

        else if (a[i] == 'd' && a[i + 1] == 'o' && a[i + 2] == '(' && a[i + 3] == ')')  // i hate this pt2
            flag = 1;

        if (flag == 1)
            no_dont[index++] = a[i];
    }

    s2 += add_all_mul(no_dont);

    printf("%lld\n%lld", s, s2);
    fclose(fptr);
}
