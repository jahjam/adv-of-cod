#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils.c"

int main(int argc, char const *argv[])
{
    FILE *fp;
    char location_codes[100];
    char *code_a;
    char *code_b;
    int size_of_array = 0;

    // handle file opening
    fp = fopen("./example-data.txt", "r");
    if (fp == NULL)
    {
        printf("File not found.");
    }
    // dirty way of getting size of array
    // defo not optimal but cba writing an
    // array list from scratch right now
    while (fgets(location_codes, sizeof(location_codes), fp))
    {
        size_of_array++;
    }

    // resets file pointer back to beginning
    // of file
    fseek(fp, 0, SEEK_SET);

    int codes_for_a[size_of_array];
    int codes_for_b[size_of_array];
    int index = 0;
    while (fgets(location_codes, sizeof(location_codes), fp))
    {
        // handle splitting the string
        code_a = strtok(location_codes, " ");
        code_b = strtok(NULL, " ");

        // convert string to int
        // (not recommended way)
        int int_a = atoi(code_a);
        int int_b = atoi(code_b);

        codes_for_a[index] = int_a;
        codes_for_b[index] = int_b;

        index++;
    }

    // apply sorting
    // all of this could defo be more optimal
    int nA = sizeof(codes_for_a) / sizeof(int);
    int nB = sizeof(codes_for_b) / sizeof(int);
    qsort(codes_for_a, nA, sizeof(int), compare);
    qsort(codes_for_b, nB, sizeof(int), compare);

    if (nA != nB)
    {
        printf("Input lists must be the same size");
        return 0;
    }

    int sum_of_all = 0;
    for (int i = 0; i < nA; i++)
    {
        int num_a = codes_for_a[i];
        int num_b = codes_for_b[i];

        if (num_a >= num_b)
        {
            int ans = num_a - num_b;
            sum_of_all += ans;
            continue;
        }
        else
        {
            int ans = num_b - num_a;
            sum_of_all += ans;
        }
    }

    printf("%i\n", sum_of_all);

    fclose(fp);
    return 0;
}
