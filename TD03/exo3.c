#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_index_by_name(char* noms[], int taille, char* nom)
{
    for (int i = 0; i < taille; i++)
    {
        if (strcmp(noms[i], nom))
        {
            return i;
        }
    }

    return -1;    
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

    char* ligne = strtok(content, "\n");
    i = 0;
    int n_noms;
    char* noms[1024];
    int donnees[1024][1024];

    while (ligne != NULL)
    {
        printf("%d\n", i);
        if (i == 0)
        {
            n_noms = atoi(ligne);
        }
        else if (i == 1)
        {
            char* nom = strtok(ligne, " ");
            for (int j = 0; j < n_noms; j ++)
            {
                noms[j] = nom;
                printf("%s\n",nom);
                if (j < n_noms - 1)
                {
                    nom = strtok(NULL, " ");
                }
                
            }
        }
        else
        {
            char* valeur = strtok(ligne, " ");
            printf("%s", valeur);
            char* nom1;
            char* nom2;
            int argent;

            for (int j = 0; j < 3; j ++)
            {
                if (j == 0)
                {
                    nom1 = valeur;
                    valeur = strtok(NULL, " ");
                }
                else if (j == 1)
                {
                    nom2 = valeur;
                    valeur = strtok(NULL, " ");
                }
                else argent = atoi(valeur);
            }

            int index_nom1 = find_index_by_name(noms, n_noms, nom1);
            int index_nom2 = find_index_by_name(noms, n_noms, nom2);
            printf("%s %s %d", nom1, nom2, argent);
            donnees[index_nom1][index_nom2] += argent;
        }

        ligne = strtok(NULL, "\n");

        i ++;
    }
    
    for (int i = 0; i < n_noms; i++)
    {
        for (int j = 0; j < n_noms; j++)
        {
            printf("%d ", donnees[i][j]);
        }
        printf("\n");
    }
    

    return 0;
}