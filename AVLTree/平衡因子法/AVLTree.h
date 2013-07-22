#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

#include <stdlib.h>

typedef char DataType;
typedef int BOOL;

typedef struct AVLNode
{
    DataType cData;
    int nBf;        //结点的平衡因子，-1表示右子树的深度比左子树高1
                    //0表示左子树与右子树深度相等
                    //1表示左子树的深度比右子树高1
    struct AVLNode *LChild;
    struct AVLNode *RChild;
}AVLNode,*AVLTree;

enum enumHight{LH = 1, EH = 0, RH = -1} eHight;
enum enumBool{FALSE = 0, TRUE = 1} eBool;

void InitAVL(AVLTree *pAT);
void DestoryAVL(AVLTree *pAT);
BOOL InsertATNode(AVLTree *pAT, DataType c);
BOOL DeleteNode(AVLTree *pAT, DataType c);
AVLTree GetParent(AVLTree AT, DataType c);
void PrintATree(AVLTree AT, int nHight);
AVLTree FindATNode(AVLTree AT, DataType c);
AVLTree FindMin(AVLTree AT);
int Num(AVLTree AT);
/**
AVLTree MargeATree(AVLTree AT1, AVLTree AT2);
AVLTree SplibATree(AVLTree *pAT);
**/

#endif // AVLTREE_H_INCLUDED
