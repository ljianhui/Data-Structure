#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

typedef int BOOL;
typedef char DataType;

typedef struct AVLNode
{
    DataType Data;      //����ֵ
    struct AVLNode *LChild; //ָ����������ָ��
    struct AVLNode *RChild; //ָ����������ָ��
    int Height;
}AVLNode, *AVLTree;

AVLNode* GetParent(AVLTree AT, DataType x);
AVLNode* Find(AVLTree AT, DataType x);
AVLNode* FindMin(AVLTree AT);
AVLNode* InsertNode(AVLTree AT, DataType x);
AVLNode* DeleteNode(AVLTree AT, DataType x);
DataType Retrieve(AVLNode *pAN);

#endif // AVLTREE_H_INCLUDED
