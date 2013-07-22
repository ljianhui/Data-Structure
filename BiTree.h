#ifndef BITREE_H_INCLUDED
#define BITREE_H_INCLUDED

#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef char DataType;
typedef int BOOL;

typedef struct BiNode
{
    DataType cData;
    struct BiNode *LChild;
    struct BiNode *RChild;
}BiNode, *BiTree;

BiTree InitBiTree();
//构造返回一棵空的二叉树

BiTree DestoryBiTree(BiTree BT);
//销毁二叉树

BiTree CreateBiTree();
//按先序次序输入二叉树中结点的值（字符‘#’表示空树），
//根据输入构造二叉树

BOOL BiTreeEmpty(BiTree BT);
//BT为空树返回TRUE，否则返加FALSE

int BiTreeDepth(BiTree BT);
//返回二叉树BT的深度

BiTree Root(BiTree BT);
//返回二叉树BT的根的指针

DataType Value(BiNode *pBN);
//返回结点的值

BOOL Assign(BiNode *pBN, DataType value);
//对结点BN赋值

BiTree GetLeftChild(BiTree BT, DataType value);
//获得BT的左孩子，若无，则返回NULL

BiTree GetRightChild(BiTree BT, DataType value);
//获得BT的右孩子，若无，则返回NULL

BiTree GetLeftSibling(BiTree BT, DataType value);
//返回value的左兄弟，若value是BT的左孩子，
//或value无左兄弟，返回NULL

BiTree GetRightSibling(BiTree BT, DataType value);
//返回value的右兄弟，若value是BT的右孩子，
//或value无右兄弟，返回NULL

BiTree InsertChild(BiNode *pBN, BOOL LR, BiTree c);
//c与树pBN不相交，且右孩子为空，若LR为0或1，插入c为pBN的左或右子树。
//pBN所指结点的原有左或右子树则成为c的右子树

void DeleteChild(BiNode *pBN, BOOL LR);
//根据LR为0或1，删除pBN所指的左或右子树

BiTree GetParent(BiTree BT, DataType c);
//获得值为c的结点的双亲结点，
//若c为根结点或不存在于树中，则返回NULL

void PrintBiTree(BiTree BT);
//以先序凹突方式打印二叉树

BiTree FindNode(BiTree BT, DataType c);
//返回二叉树BT中值为c的结点的指针
//若c不存在于BT中，则返回NULL

BiTree MinNode(BiTree BT);
//返回二叉树BT中结点的最小值

BiTree MaxNode(BiTree BT);
//返回二叉树BT中结点的最大值

int NotLeavesCount(BiTree BT);
//返回二叉树BT中非叶子结点的个数

int LeavesCount(BiTree BT);
//返回二叉树BT中叶子结点的个数

BOOL PreOrderTraverse(BiTree BT, BOOL(*Visit)(BiNode*));
//先序遍历二叉树

BOOL InOrderTraverse(BiTree BT, BOOL(*Visit)(BiNode*));
//中序遍历二叉树

BOOL PostOrderTraverse(BiTree BT, BOOL(*Visit)(BiNode*));
//后序遍历二叉树

BOOL LevelOrderTraverse(BiTree BT, BOOL(*Visit)(BiNode*));
//层次性遍历二叉树


#endif // BITREE_H_INCLUDED
