#ifndef TP4_H_INCLUDED
#define TP4_H_INCLUDED


typedef struct Node {
                        char letter;            // pour l�arbre
                        struct Node *parent;
                        struct Node *left;
                        struct Node *right;    // pour la liste
                        struct Node *next ;
                    }Node;

typedef struct ListNode {
                            struct Node *start;
                            int number ;
                            struct Node *last; //pour ne pas avoir � parcourir la liste � chaque fois pour ins�rer � la fin)
                        }ListNode;

Node* createNode(char letter);          //cr�e un n�ud avec la lettre donn�e letter (A ou B)
void generateChilds(Node *node);        //g�n�re les fils de la feuille node selon la r�gle de L-system
void freeTree(Node *root);              //lib�re l�arbre
void displayTree(Node *root);           // affiche l�arbre de mani�re � repr�senter chaque noeud v par {g,v,d} o� g est le
                //sous-arbre gauche, v la valeur du n�ud et d le sous-arbre droit. Les "-" indiquent les sous-arbres vides
ListNode* createList();                 //cr�e une liste vide
void addEndList(ListNode *list, Node *node);    //ajoute la feuille node � la fin de la liste list
ListNode* generateList(ListNode *list); //g�n�re la prochaine liste des feuilles en se basant sur la liste actuelle
void removeList(ListNode *list);        //supprime la liste des feuilles list
void displayList(ListNode *list);       //affiche la liste des feuilles list
int calculateSizeList(ListNode *list);  //calcule la taille d�une liste list
void echange(Node *node);               //inverse la lettre d'un noeud
Node* inverse(Node *node);              //inverse la lettre de chaque de noeud de l'arbre

/*----fonctions du menu----*/
ListNode* initialiserArbre();
void genererArbre(int n);
void afficherFeuilles();

#endif // TP4_H_INCLUDED
