#include <stdio.h>
#include <stdlib.h>

#include "tp4.h"

#define NMAX 50


ListNode **tabLists;
int tailleTab=1;    //le tableau commence à la case 1 pour suivre l'énoncé


Node* createNode(char letter)
{
    Node *n;
    n=(Node*)malloc(sizeof(Node));
    n->letter=letter;
    n->parent=NULL;
    n->left=NULL;
    n->right=NULL;
    n->next=NULL;
    return n;
}

void generateChilds(Node *node)
{
    if(node->letter == 'A')
        {
            Node *l;
            l = createNode('B');
            node->left = l;
            l->parent = node;
        }
    else
        {
            Node *l,*r;
            l = createNode('A');
            r = createNode('B');
            l->next = r;
            node->left = l;
            node->right = r;
            l->parent = node;
            r->parent = node;
        }
}

void freeTree(Node *root)
{
    int i;
    Node *tempSon=NULL,*tempNext=NULL;
    while(root != NULL)
        {
            tempSon=root->left;
            while(root != NULL)
                {
                    tempNext=root->next;
                    free(root);
                    root=tempNext;
                }
            root=tempSon;
        }
    tailleTab = 1;
}

void displayTree(Node *root)
{
    if((root->left != NULL)||(root->right != NULL))
        {
            printf("{");
            displayTree(root->left);
            printf(",%c,",root->letter);
            if(root->right == NULL)
                printf("-}");
            else
                {
                    displayTree(root->right);
                    printf("}");
                }

        }
    else
        printf("%c",root->letter);

}

ListNode* createList()
{
    ListNode *L;
    L=(ListNode*)malloc(sizeof(ListNode));
    L->start=NULL;
    L->number=0;
    L->last=NULL;
    return L;
}

void addEndList(ListNode* list, Node* node)
{
    if(list->number == 0)       //si liste vide
        list->start = node;
    else
        list->last->next=node;
    if(node->next != NULL)      //si on ajoute un A et un B
        {
            list->last=node->next;
            list->number += 2;
        }

    else                        //si on ajoute juste un B
        {
            list->last=node;
            (list->number)++;
        }
}

ListNode* generateList(ListNode *list)
{
    Node *temp=list->start;
    ListNode *newList;
    newList=createList();
    while(temp != NULL)
        {
            generateChilds(temp);
            addEndList(newList,temp->left);
            temp = temp->next;
        }
    tailleTab++;
    tabLists[tailleTab]=newList;
    return newList;
}

void removeList(ListNode *list)
{
    Node *temp=list->start;
    while(temp != NULL)
        {
            if(temp == temp->parent->left)      //s'il s'agit d'un fils gauche, on "réinitialise" le fils gauche de son père
                temp->parent->left=NULL;
            else                                //s'il s'agit d'un fils droit, on "réinitialise" le fils droit de son père
                temp->parent->right=NULL;
            temp = temp->next;
            free(list->start);
            list->start = temp;
        }
    free(list);
    tailleTab--;
}

int calculateSizeList(ListNode *list)
{
    return list->number;
}

/*----fonctions du menu----*/

ListNode* initialiserArbre()
{
    ListNode *root;
    root = createList();
    root->start=createNode('A');
    root->number = 1;
    tabLists[1]=root;       //le tableau commence à la case 1 pour suivre l'énoncé
    return root;
}

void genererArbre(int n)
{
    int i;
    for(i=tailleTab;i<n;i++)
        generateList(tabLists[i]);
}

void displayList(ListNode *list)
{
    int i;
    Node *temp;
    temp = list->start;
    for(i=0;i<tabLists[tailleTab]->number;i++)
        {
            printf("%c",temp->letter);
            if ((temp = temp->next) != NULL)
                printf(",");
        }
}

void echange(Node *node)       //change la lettre de node
{
    if (node->letter == 'A')
        node->letter = 'B';
    else
        node->letter = 'A';
}

Node* inverse(Node *node)
{
    int i;
    Node *temp = NULL;
    for (i=1; i<=tailleTab; i++)
        {
            temp = tabLists[i]->start;
            while (temp != NULL)
                {
                    echange(temp);
                    temp = temp->next;
                }
        }
    return (tabLists[1]->start);
}
