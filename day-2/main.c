#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    FILE *fp;
    char levels[100];
    int numOfSafeLevels = 0;
    int *levelsArr;
    fp = fopen("./test-data.txt", "r");
    if (fp == NULL)
    {
        printf("File not found.");
        return 1;
    }

    while (fgets(levels, sizeof(levels), fp))
    {
        int sizeOfLevelsArr = 1;
        // count number of words in a string
        // for overall number of levels in levels string
        for (int i = 0; levels[i] != '\0'; i++)
        {
            if (levels[i] == ' ')
            {
                sizeOfLevelsArr++;
            }
        }

        int bufferSizeOfLevelsArr = sizeOfLevelsArr * sizeof(int);
        levelsArr = malloc(bufferSizeOfLevelsArr);
        char *levelP = strtok(levels, " ");
        int index = 0;

        while (levelP != NULL)
        {
            int levelInt = atoi(levelP);
            levelsArr[index] = levelInt;

            index++;
            levelP = strtok(NULL, " ");
        }

        int level = levelsArr[0];
        int nextLevel = levelsArr[1];

        // we are checking for increasing levels here
        if (nextLevel > level && nextLevel <= level + 3)
        {
            for (int i = 1; i < bufferSizeOfLevelsArr / sizeof(int) - 1; i++)
            {
                int lev = levelsArr[i];
                int nextLev = levelsArr[i + 1];

                if (nextLev > lev && nextLev <= lev + 3)
                {
                    if (i == bufferSizeOfLevelsArr / sizeof(int) - 2)
                    {
                        numOfSafeLevels++;
                        break;
                    }
                    continue;
                }
                else
                {
                    break;
                }
            }
        }

        // checking for decreasing levels here
        else if (nextLevel < level && nextLevel >= level - 3)
        {
            for (int i = 1; i < bufferSizeOfLevelsArr / sizeof(int) - 1; i++)
            {
                int lev = levelsArr[i];
                int nextLev = levelsArr[i + 1];

                if (nextLev < lev && nextLev >= lev - 3)
                {
                    if (i == bufferSizeOfLevelsArr / sizeof(int) - 2)
                    {
                        numOfSafeLevels++;
                        break;
                    }
                    continue;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            continue;
        }

        free(levelsArr);
        levelsArr = NULL;
        index = 0;
    }

    printf("Number of safe levels: %i", numOfSafeLevels);

    return 0;
}
