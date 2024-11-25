#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* fileToString(char* filePath)
{
    FILE* stream = fopen(filePath, "r");
    if (stream == NULL) return NULL;
    
    char* fileContent = malloc(sizeof(char) * 1024);
    int i = 0;
    while (!feof(stream))
    {
        if (fscanf(stream, "%c", &fileContent[i]) == -1)
        {
            fileContent[i] = 0;
        }
        i ++;
    }
    fclose(stream);
    return fileContent;
}

int* contentToMatrix(int n_id, char* token)
{
    int* matrix = malloc(sizeof(int) * n_id * n_id);
    for (int i = 0; i < n_id * n_id; i++) matrix[i] = 0;

    token = strtok(NULL, " ");

    while (token != NULL)
    {
        int id1 = atoi(token);
        token = strtok(NULL, " ");
        char* type = token;
        token = strtok(NULL, "\n");
        int id2 = atoi(token);
        token = strtok(NULL, " ");

        if (!strcmp(type, "donne"))
        {
            matrix[id1 * n_id + id2] = 1;
        }
        else if (!strcmp(type, "requiert"))
        {
            matrix[id2 * n_id + id1] = 1;
        }
    }    
    
    return matrix;
}

int* rechercheLien(int n_id, int* matrix, int id1, int id2)
{
    int currentId = id1;
    int ids[n_id];
    int j = 0;

    for (int i = 0; i < n_id; i++)
    {
        if (matrix[currentId * n_id + i])
        {
            ids[j] = currentId;
            j ++;
            currentId = i;
            i = 0;

            if (currentId == id2)
            {
                int* chemin = malloc(sizeof(int) * (j + 2));
                chemin[0] = j + 1;
                for (int k = 0; k < j; k++)
                {
                    chemin[k + 1] = ids[k];
                }
                chemin[j + 1] = id2;
                return chemin;                
            }
            
        }
        else if (i == n_id - 1 && j > 0)
        {
            j--;
            i = currentId;
            currentId = ids[j];
        }
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    if (argc != 4) return -1;
    
    char* filePath = argv[1];
    int id1 = atoi(argv[2]);
    int id2 = atoi(argv[3]);
    
    if (id1 == id2)
    {
        printf("%d\nLien.\n", id1);
        return 0;
    }
    
    char* content = fileToString(filePath);
    char* token = strtok(content, "\n");
    int n_id = atoi(token);
    int* matrix = contentToMatrix(n_id, token);
    int* lien = rechercheLien(n_id, matrix, id1, id2);
    if (lien == NULL)
    {
        lien = rechercheLien(n_id, matrix, id2, id1);
    }
    if (lien == NULL)
    {
        printf("Pas de lien.\n");
    }
    else
    {
        for (int i = 0; i < lien[0] - 1; i++)
        {
            printf("%d ", lien[i + 1]);
        }
        printf("%d\n", lien[lien[0]]);
        printf("Lien.\n");
    }
    free(lien);
    free(content);
    free(matrix);
    return 0;
}