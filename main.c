#include <stdio.h>
#include <stdlib.h>

#include "tp4.h"
#include "tp4.c"

/*Chaque n�ud contient une lettre, soit A ou B, et peut avoir au maximum 2 fils, not� fils gauche et fils droit.
A l�initialisation, l�arbre contient un seul n�ud avec la lettre A. Ensuite la construction de l'arbre se fait �tape par �tape
en g�n�rant � chaque fois les fils des feuilles de l'�tape pr�c�dente.
La r�gle de g�n�ration est la suivante : une feuille A va g�n�rer un fils gauche B et pas de fils droit, une feuille B va
g�n�rer un fils gauche A et un fils droit B.

En utilisant le L-System, nous g�n�rons un arbre binaire dont le nombre de symboles pr�sents sur chaque niveau i repr�sente
le nombre correspondant � Fibo(i). */

int main()
{
    tabLists=(ListNode*)malloc(sizeof(ListNode*)*NMAX);
    //tableau contenant pour chaque niveau un pointeur vers la liste correspondante
    ListNode *root=NULL,*temp;
    Node *tempNode;
    int n, i, rep=9;
    int arbreInitialise=0, arbreDetruit=1;  //bool�ens servant � l'ex�cution/non �x�cution des fonctions

    do
        {
            system("cls");      //�cran effac�
            printf("Que voulez-vous faire ?\n");
            printf("1- Initialiser un arbre \n2- Generer un arbre\n3- Ajouter un niveau \n4- Supprimer le dernier niveau\n");
            printf("5- Afficher la liste des feuilles de l arbre \n6- Afficher l arbre\n7- Calculer le Fibo d un nombre\n");
            printf("8 - Inverser les lettres \n9 - Detruire l arbre \n10- Quitter\n");
            scanf("%d",&rep);
            switch(rep)
                {
                    case 1: //Initialiser un arbre
                        if (arbreInitialise == 1)
                            printf("\nL'arbre a deja ete initialise !\n");
                        else
                            {
                                root = initialiserArbre();
                                printf("Arbre initialise !\n\n");
                                arbreInitialise=1;  //avant d'ex�cuter les autres fonctions, on doit v�rifier que l'abre a �t� initialis�
                                arbreDetruit=0;     //avant de quitter, l'utilisateur devra d�truire l'arbre
                            }
                        system("PAUSE");    //pause
                        break;
                    case 2: //Generer un arbre
                        if (arbreInitialise)
                            {
                                do
                                    {
                                        printf("Combien de niveaux l'arbre doit-il avoir ? ");
                                        scanf("%d",&n);
                                        fflush(stdin);
                                    }
                                while (!((0 < n )&&(n < NMAX)));        //blindage
                                if (tailleTab < n)
                                    {
                                        genererArbre(n);
                                        printf("\nArbre genere (l'arbre a desormais %d niveau(x)) !\n",tailleTab);
                                    }
                                else
                                    printf("Votre arbre contient deja %d niveaux.\n",n);
                            }
                        else
                            printf("\nVeuillez commencer par initialiser l'arbre.\n\n");
                        system("PAUSE");      //pause
                        break;
                    case 3: //Ajouter un niveau
                        if (arbreInitialise)
                            {
                                generateList(tabLists[tailleTab]);
                                printf("\nNiveau %d ajoute !\n",tailleTab);
                            }
                        else
                            printf("\nVeuillez commencer par initialiser l'arbre.\n\n");
                        system("PAUSE");      //pause
                        break;
                    case 4: //Supprimer le dernier niveau
                        if (arbreInitialise)
                            {
                                if (tailleTab > 1)
                                    {
                                        removeList(tabLists[tailleTab]);
                                        printf("\nNiveau %d supprime !\n",tailleTab+1);
                                    }
                                else
                                    {
                                        printf("\nIl ne reste que le premier niveau. Suppression de l'arbre.\n");
                                        freeTree(root->start);
                                        printf("\nArbre detruit !\n\n");
                                        arbreInitialise = 0;//une fois l'arbre d�truit, il faut r�-initialiser l'arbre pour acc�der aux fonctions
                                        arbreDetruit = 1;
                                    }

                            }
                        else
                            printf("\nVeuillez commencer par initialiser l'arbre.\n\n");
                        system("PAUSE");      //pause
                        break;
                    case 5: //Afficher la liste des feuilles de l arbre
                        if (arbreInitialise)
                            {
                                printf("\nAffichage du dernier niveau (niveau %d) : \n\n",tailleTab);
                                displayList(tabLists[tailleTab]);
                                printf("\n\n");
                            }
                        else
                            printf("\nVeuillez commencer par initialiser l'arbre.\n\n");
                        system("PAUSE");      //pause
                        break;
                    case 6: //Afficher l arbre
                        if (arbreInitialise)
                            {
                                printf("\nAffichage de l'arbre (comportant %d niveaux) : \n\n",tailleTab);
                                displayTree(root->start);
                                printf("\n\n");
                            }
                        else
                            printf("\nVeuillez commencer par initialiser l'arbre.\n\n");
                        system("PAUSE");      //pause
                        break;
                    case 7: //Calculer le Fibo d un nombre
                            //si le nombre de niveaux est > � n, calcul imm�diat. Sinon, on doit cr�er les niveaux restants
                        if (arbreInitialise)
                            {
                                do
                                    {
                                        printf("\nDe quel nombre calculer le Fibonacci ? ");
                                        scanf("%d",&n);
                                        fflush(stdin);
                                    }
                                while (!((0 < n )&&(n < NMAX)));        //blindage
                                if (tailleTab >= n)
                                    printf("\nFibo(%d) = %d\n",n,calculateSizeList(tabLists[n]));
                                else
                                    {
                                        printf("\nL'arbre ne contient pas encore assez de niveaux pour le calcul.\n");
                                        printf("Dernier niveau de l'arbre actuel : niveau %d.\n",tailleTab);
                                        printf("Creation de %d niveaux supplementaires ...\n",n-tailleTab);
                                        for (i=tailleTab;i<n;i++)
                                            generateList(tabLists[i]);
                                        printf("Votre arbre contient desormais %d niveaux !\n",tailleTab);
                                        printf("\nFibo(%d) = %d\n",n,calculateSizeList(tabLists[n]));
                                    }
                            }
                        else
                            printf("\nVeuillez commencer par initialiser l'arbre.\n\n");
                        system("PAUSE");      //pause
                        break;
                    case 8: //Inverser les lettres
                        if (arbreInitialise)
                            {
                                printf("\nAffichage de l'ancien arbre  : \n\n",tailleTab);
                                displayTree(root->start);
                                printf("\n");
                                root->start = inverse(root->start);
                                printf("\nAffichage du nouvel arbre  : \n\n",tailleTab);
                                displayTree(root->start);
                                printf("\n\n");
                            }
                        else
                            printf("\nAucun arbre a modifier.\n\n");
                        system("PAUSE");      //pause
                        break;
                    case 9: //Detruire l arbre
                        if (arbreInitialise)
                            {
                                freeTree(root->start);
                                printf("\nArbre detruit !\n");
                                arbreInitialise = 0;//une fois l'arbre d�truit, il faut r�-initialiser l'arbre pour acc�der aux fonctions
                                arbreDetruit = 1;
                            }
                        else
                            printf("\nAucun arbre a detruire.\n\n");
                        system("PAUSE");      //pause
                        break;
                    case 10: //Quitter
                        if (!arbreDetruit)
                            {
                                printf("\nVeuillez detruire l'arbre avant de quitter.\n\n");
                                rep = 0;
                            }
                        else
                            printf("\n\n----------------- EXIT ----------------\n\n");
                        system("PAUSE");      //pause
                        break;
                    default:
                        printf("\nVous vous etes trompe de touche...\n");
                        system("PAUSE");      //pause
                }
        }
    while(rep != 10);

    return 0;
}
