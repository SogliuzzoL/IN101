#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_index_by_name(char* noms[], int taille, char* nom)
{
    for (int i = 0; i < taille; i++)
    {
        if (!strcmp(noms[i], nom))
        {
            return i;
        }
    }

    return -1;    
}

int* compute_amount(int taille, int donnees[taille][taille])
{
    int* compte = malloc(sizeof(int) * taille);
    for (int i = 0; i < taille; i++)
    {
        compte[i] = 0;        
    }

    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille; j++)
        {
            compte[i] -= donnees[i][j];
            compte[j] += donnees[i][j];
        }
        
    }
    
    return compte;
}

int main(int argc, char* argv[])
{
    FILE* stream = fopen(argv[1], "rb");
    char content[1024];

    if (stream == NULL)
    {
        printf("Erreur lors de la lecture du fichier !\n");
        return 0;
    }

    int i = 0;
    while (!feof(stream))
    {
        if (fscanf(stream, "%c", &content[i]) == -1)
        {
            content[i] = 0;
        }
        i ++;
    }

    fclose(stream);

    char* element = strtok(content, "\n");

    int n_noms = atoi(element);


    char* noms[n_noms];
    element = strtok(NULL, " ");
    for (int i = 0; i < n_noms; i++)
    {
        noms[i] = element;
        if (i == n_noms - 2)
        {
            element = strtok(NULL, "\n");
        }
        else element = strtok(NULL, " ");   
    }    

    int donnees[n_noms][n_noms];
    for (int i = 0; i < n_noms; i++)
    {
        for (int j = 0; j < n_noms; j++)
        {
            donnees[i][j] = 0;
        }
        
    }
    
    while (element != NULL)
    {
        char* nom1; 
        char* nom2;
        int argent;
        for (int i = 0; i < 3; i++)
        {
            switch (i)
            {
            case 0:
                nom1 = element;
                element = strtok(NULL, " ");
                break;
            case 1:
                nom2 = element;
                element = strtok(NULL, "\n");
                break;
            case 2:
                argent = atoi(element);
                element = strtok(NULL, " ");
                break;
            }
        }
        int idx1 = find_index_by_name(noms, n_noms, nom1);
        int idx2 = find_index_by_name(noms, n_noms, nom2);
        donnees[idx1][idx2] = argent;
    }

    int* compte = compute_amount(n_noms, donnees);

    for (int i = 0; i < n_noms; i++)
    {
        printf("%s : %d\n", noms[i], compte[i]);
    }
    
    free(compte);
    return 0;
}