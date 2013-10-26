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
//���췵��һ�ÿյĶ�����

BiTree DestoryBiTree(BiTree BT);
//���ٶ�����

BiTree CreateBiTree();
//�������������������н���ֵ���ַ���#����ʾ��������
//�������빹�������

BOOL BiTreeEmpty(BiTree BT);
//BTΪ��������TRUE�����򷵼�FALSE

int BiTreeDepth(BiTree BT);
//���ض�����BT�����

BiTree Root(BiTree BT);
//���ض�����BT�ĸ���ָ��

DataType Value(BiNode *pBN);
//���ؽ���ֵ

BOOL Assign(BiNode *pBN, DataType value);
//�Խ��BN��ֵ

BiTree GetLeftChild(BiTree BT, DataType value);
//���BT�����ӣ����ޣ��򷵻�NULL

BiTree GetRightChild(BiTree BT, DataType value);
//���BT���Һ��ӣ����ޣ��򷵻�NULL

BiTree GetLeftSibling(BiTree BT, DataType value);
//����value�����ֵܣ���value��BT�����ӣ�
//��value�����ֵܣ�����NULL

BiTree GetRightSibling(BiTree BT, DataType value);
//����value�����ֵܣ���value��BT���Һ��ӣ�
//��value�����ֵܣ�����NULL

BiTree InsertChild(BiNode *pBN, BOOL LR, BiTree c);
//c����pBN���ཻ�����Һ���Ϊ�գ���LRΪ0��1������cΪpBN�������������
//pBN��ָ����ԭ��������������Ϊc��������

void DeleteChild(BiNode *pBN, BOOL LR);
//����LRΪ0��1��ɾ��pBN��ָ�����������

BiTree GetParent(BiTree BT, DataType c);
//���ֵΪc�Ľ���˫�׽�㣬
//��cΪ�����򲻴��������У��򷵻�NULL

void PrintBiTree(BiTree BT);
//������ͻ��ʽ��ӡ������

BiTree FindNode(BiTree BT, DataType c);
//���ض�����BT��ֵΪc�Ľ���ָ��
//��c��������BT�У��򷵻�NULL

BiTree MinNode(BiTree BT);
//���ض�����BT�н�����Сֵ

BiTree MaxNode(BiTree BT);
//���ض�����BT�н������ֵ

int NotLeavesCount(BiTree BT);
//���ض�����BT�з�Ҷ�ӽ��ĸ���

int LeavesCount(BiTree BT);
//���ض�����BT��Ҷ�ӽ��ĸ���

BOOL PreOrderTraverse(BiTree BT, BOOL(*Visit)(BiNode*));
//�������������

BOOL InOrderTraverse(BiTree BT, BOOL(*Visit)(BiNode*));
//�������������

BOOL PostOrderTraverse(BiTree BT, BOOL(*Visit)(BiNode*));
//�������������

BOOL LevelOrderTraverse(BiTree BT, BOOL(*Visit)(BiNode*));
//����Ա���������


#endif // BITREE_H_INCLUDED
