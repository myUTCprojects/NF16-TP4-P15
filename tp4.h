#ifndef TP4_H_INCLUDED
#define TP4_H_INCLUDED


typedef struct Node {
                        char letter;            // pour l’arbre
                        struct Node *parent;
                        struct Node *left;
                        struct Node *right;    // pour la liste
                        struct Node *next ;
                    }Node;

typedef struct ListNode {
                            struct Node *start;
                            int number ;
                            struct Node *last; //pour ne pas avoir à parcourir la liste à chaque fois pour insérer à la fin)
                        }ListNode;

Node* createNode(char letter);          //crée un nœud avec la lettre donnée letter (A ou B)
void generateChilds(Node *node);        //génère les fils de la feuille node selon la règle de L-system
void freeTree(Node *root);              //libère l’arbre
void displayTree(Node *root);           // affiche l’arbre de manière à représenter chaque noeud v par {g,v,d} où g est le
                //sous-arbre gauche, v la valeur du nœud et d le sous-arbre droit. Les "-" indiquent les sous-arbres vides
ListNode* createList();                 //crée une liste vide
void addEndList(ListNode *list, Node *node);    //ajoute la feuille node à la fin de la liste list
ListNode* generateList(ListNode *list); //génère la prochaine liste des feuilles en se basant sur la liste actuelle
void removeList(ListNode *list);        //supprime la liste des feuilles list
void displayList(ListNode *list);       //affiche la liste des feuilles list
int calculateSizeList(ListNode *list);  //calcule la taille d’une liste list
void echange(Node *node);               //inverse la lettre d'un noeud
Node* inverse(Node *node);              //inverse la lettre de chaque de noeud de l'arbre

/*----fonctions du menu----*/
ListNode* initialiserArbre();
void genererArbre(int n);
void afficherFeuilles();

#endif // TP4_H_INCLUDED
