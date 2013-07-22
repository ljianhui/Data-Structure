#include <stdio.h>
#include "BiTree.h"

//----------------------------------------------------------------------
BiTree InitBiTree()
{
    //��ʼ������ָ��
    return NULL;
}
//----------------------------------------------------------------------
BiTree DestoryBiTree(BiTree BT)
{
    //�ͷ����е�����㣬����ָ��������ָ���ÿ�
    //ֻ���ú���free��������Ҫ1�������򣩻�2����ǰ����ʱ����
    //������BT->LChild��BT->RChild
    if(BT)
    {
        DestoryBiTree(BT->LChild);
        DestoryBiTree(BT->RChild);
        free(BT);
    }
    return NULL;
}
//----------------------------------------------------------------------
BiTree CreateBiTree()
{
    //�������������������н���ֵ���ַ���#����ʾ������
    //�������빹�������
    char c = getchar();
    while(c == '\n')
        c= getchar();
    if(c == '#' || c== ' ')
        return NULL;
    else
    {
        BiTree BT = NULL;
        BT = (BiTree)malloc(sizeof(BiNode));
        if(BT == NULL)
            return NULL;
        BT->cData = c;
        BT->LChild = CreateBiTree(BT->LChild);
        BT->RChild = CreateBiTree(BT->RChild);
        return BT;
    }
}
//----------------------------------------------------------------------
BOOL BiTreeEmpty(BiTree BT)
{
    //��Ϊ�������򷵻�1�����򷵻�0
    if(BT == NULL)
        return TRUE;
    else
        return FALSE;
}
//----------------------------------------------------------------------
int BiTreeDepth(BiTree BT)
{
    //���������
    //�Ӷ�������ȵĶ����֪�������������ӦΪ������������ȵ����ֵ��1��
    //��Ϊ��������1�㡣
    if(BT == NULL)  //��Ϊ�������򷵻�0
        return 0;
    else
    {
        int nLDepth = BiTreeDepth(BT->LChild); //�����������
        int nRDepth = BiTreeDepth(BT->RChild); //�����������
        if(nLDepth >= nRDepth)
        {
            return nLDepth+1;
        }
        else
        {
            return nRDepth+1;
        }
    }
}
//----------------------------------------------------------------------
BiTree Root(BiTree BT)
{
    //����������ָ��
    return BT;
}
//----------------------------------------------------------------------
DataType Value(BiNode *pBN)
{
    //���ؽ������Ӧ��ֵ
    return pBN->cData;
}
//----------------------------------------------------------------------
BOOL Assign(BiNode *pBN, DataType value)
{
    //����Ӧ�Ľ�㸳ֵ
    if(pBN == NULL)
        return FALSE;
    pBN->cData = value;
    return TRUE;
}

//----------------------------------------------------------------------
BiTree GetLeftChild(BiTree BT, DataType value)
{
    //���һ���������ӣ��򲻴��ڷ���NULL
    BiNode *pBN = FindNode(BT, value); //���Ҹý��
    if(pBN != NULL)
        return pBN->LChild; //����������
    return NULL;
}
//----------------------------------------------------------------------
BiTree GetRightChild(BiTree BT, DataType value)
{
    //���һ�������Һ��ӣ��򲻴��ڷ���NULL
    BiNode *pBN = FindNode(BT, value); //���Ҹý��
    if(pBN != NULL)
        return pBN->RChild; //�������Һ���
    return NULL;
}
//----------------------------------------------------------------------
BiTree GetLeftSibling(BiTree BT, DataType value)
{
    //����value�����ֵܣ���value��BT�����ӣ�
    //��value�����ֵܣ�����NULL
    BiNode *pParent = GetParent(BT, value);
    if(pParent != NULL && pParent->LChild != NULL &&
       pParent->LChild->cData != value)
        return pParent->LChild;
    return NULL;
}
//----------------------------------------------------------------------
BiTree GetRightSibling(BiTree BT, DataType value)
{
    //����value�����ֵܣ���value��BT���Һ��ӣ�
    //��value�����ֵܣ�����NULL
    BiNode *pParent = GetParent(BT, value);
    if(pParent != NULL && pParent->RChild != NULL &&
       pParent->RChild->cData != value)
        return pParent->RChild;
    return NULL;
}
//----------------------------------------------------------------------
BiTree InsertChild(BiNode *pBN, BOOL LR, BiTree c)
{
    //c����pBN���ཻ�����Һ���Ϊ�գ���LRΪ0��1������cΪpBN�������������
    //pBN��ָ����ԭ��������������Ϊc��������
    BiTree BiChild  = NULL;
    if(LR == 0)
    {
        BiChild = pBN->LChild;
        pBN->LChild = c;
        c->RChild = BiChild;
    }
    else
    {
        BiChild = pBN->RChild;
        pBN->RChild = c;
        c->RChild = BiChild;
    }
    return c;
}
//----------------------------------------------------------------------
void DeleteChild(BiNode *pBN, BOOL LR)
{
    //����LRΪ0��1��ɾ��pBN��ָ�����������
    if(pBN == NULL)
        return;
    if(LR == 0)
    {
        pBN->LChild = DestoryBiTree(pBN->LChild);
    }
    else
    {
        pBN->RChild = DestoryBiTree(pBN->RChild);
    }
}

//----------------------------------------------------------------------
BiTree MinNode(BiTree BT)
{
    //���ض�����BT�н�����Сֵ
    if(BT == NULL)  //�����򷵻�NULL
        return NULL;

    BiNode *pMin = BT;  //Ĭ����������Ϊ��ǰ��С���
    BiNode *tmp = MinNode(BT->LChild);  //�ҳ�����������С���
    if(tmp != NULL)
    {
        //���������ڣ������ӶԵ���С���С�ڵ�ǰ��С���
        if(tmp->cData < pMin->cData)
            pMin = tmp;
    }

    tmp = MinNode(BT->RChild);  //�ҳ�����������С���
    if(tmp != NULL)
    {
        //���������ڣ�������������С���С�ڵ�ǰ��С���
        if(tmp->cData < pMin->cData)
            pMin = tmp;
    }
    return pMin;
}
//----------------------------------------------------------------------
BiTree MaxNode(BiTree BT)
{
    //���ض�����BT�н������ֵ
    if(BT == NULL)  //�����򷵻�NULL
        return NULL;

    BiNode *pMax = BT;  //Ĭ����������Ϊ��ǰ�����
    BiNode *tmp = MaxNode(BT->LChild);  //�ҳ��������������
    if(tmp != NULL)
    {
        //���������ڣ������ӶԵ��������ڵ�ǰ�����
        if(tmp->cData > pMax->cData)
            pMax = tmp;
    }

    tmp = MaxNode(BT->RChild);  //�ҳ��������������
    if(tmp != NULL)
    {
        //���������ڣ������������������ڵ�ǰ�����
        if(tmp->cData > pMax->cData)
            pMax = tmp;
    }
    return pMax;
}
//----------------------------------------------------------------------
BiTree GetParent(BiTree BT, DataType c)
{
    //���ֵΪc�Ľ���˫�׽�㣬
    //��cΪ�����򲻴��������У��򷵻�NULL
    if(!BT || BT->cData == c)
        return NULL;
    if((BT->LChild && BT->LChild->cData == c) ||
        (BT->RChild && BT->RChild->cData == c))
        return BT;

    BiTree Parent = NULL;
    Parent = GetParent(BT->LChild, c);
    if(Parent == NULL)
        Parent = GetParent(BT->RChild, c);
    return Parent;
}
//----------------------------------------------------------------------
static void __PrintBiTree(BiTree BT, int nHight)
{
    int i = 0;
    if(!BT)
        return;
    printf("-");
    for(i = 1; i < nHight; ++i)
        printf("--");
    printf("%c\n", BT->cData);

    __PrintBiTree(BT->LChild, nHight+1);
    __PrintBiTree(BT->RChild, nHight+1);
}
void PrintBiTree(BiTree BT)
{
    //������ͻ��ʽ��ӡ������
    __PrintBiTree(BT, 1);
}
//----------------------------------------------------------------------
BiTree FindNode(BiTree BT, DataType c)
{
    //���ض�����BT��ֵΪc�Ľ���ָ��
    //��c��������BT�У��򷵻�NULL
    if(!BT)
        return NULL;
    else if(BT->cData == c) //�ҵ���Ӧ�Ľ�㣬������ָ��
        return BT;

    BiTree BN = NULL;
    BN = FindNode(BT->LChild, c);   //�����������н��в���
    if(BN == NULL)      //û���ҵ�������������������н��в���
        BN = FindNode(BT->RChild, c);
    return BN;
}
//----------------------------------------------------------------------
int NotLeavesCount(BiTree BT)
{
    //���ض�����BT�з�Ҷ�ӽ��ĸ���
    if(BT == NULL || (!(BT->LChild || BT->RChild)))
        return 0;   //��ΪBTΪ������ΪҶ�ӽ�㣬����0
    else
    {
        int nCount = 1; //��ʱ�����Ҳ��һ����Ҷ�ӽ��
        //�ۼ����������ķ�Ҷ�ӽ�����
        nCount += NotLeavesCount(BT->LChild);
        //�ۼ����������ķ�Ҷ�ӽ�����
        nCount += NotLeavesCount(BT->RChild);
        return nCount;
    }
}
//----------------------------------------------------------------------
int LeavesCount(BiTree BT)
{
    //���ض�����BT��Ҷ�ӽ��ĸ���
    if(BT == NULL)
        return 0;   //BTΪ����������0

    int nCount = 0;
    if(!(BT->LChild || BT->RChild))
        ++nCount;   //BTΪҶ�ӽ�㣬��1
    else
    {
        //�ۼ����������ϵ�Ҷ�ӽ��
        nCount += LeavesCount(BT->LChild);
        //�ۼ����������ϵ�Ҷ�ӽ��
        nCount += LeavesCount(BT->RChild);
    }
    return nCount;
}
//----------------------------------------------------------------------
BOOL PreOrderTraverse(BiTree BT, BOOL(*Visit)(BiNode*))
{
    //�������������
    if(BT != NULL)
    {
        if((*Visit)(BT))
        {
            if(PreOrderTraverse(BT->LChild, Visit))
                if(PreOrderTraverse(BT->RChild, Visit))
                    return TRUE;
            return FALSE;
        }
    }
    else
        return TRUE;
}
//----------------------------------------------------------------------
BOOL InOrderTraverse(BiTree BT, BOOL(*Visit)(BiNode*))
{
    //�������������
    if(BT != NULL)
    {
        if(InOrderTraverse(BT->LChild, Visit))
        {
            if((*Visit)(BT))
                if(InOrderTraverse(BT->RChild, Visit))
                    return TRUE;
            return FALSE;
        }
    }
    else
        return TRUE;
}
//----------------------------------------------------------------------
BOOL PostOrderTraverse(BiTree BT, BOOL(*Visit)(BiNode*))
{
    //�������������
    if(BT != NULL)
    {
        if(PostOrderTraverse(BT->LChild, Visit))
        {
            if(PostOrderTraverse(BT->RChild, Visit))
                if((*Visit)(BT))
                    return TRUE;
            return FALSE;
        }
    }
    else
        return TRUE;
}
//----------------------------------------------------------------------
BOOL LevelOrderTraverse(BiTree BT, BOOL(*Visit)(BiNode*))
{
    //����Ա���������
    //ʹ������ģ��һ��ѭ������
    if(BT == NULL)
        return TRUE;

    const int nCapicity = 300;
    BiTree DT[nCapicity];
    int nFront = 0, nRear = 1;
    DT[0] = BT;
    int nSize = 1;

    while(nSize != 0)   //���зǿ�
    {
        if(DT[nFront]->LChild)
        {
            //�������ǿգ����������
            DT[nRear] = DT[nFront]->LChild;
            ++nRear;
            ++nSize;
        }
        if(DT[nFront]->RChild)
        {
            //�������ǿգ����������
            DT[nRear] = DT[nFront]->RChild;
            ++nRear;
            ++nSize;
        }

        //���ʶ�ͷԪ�أ�������
        if(!(*Visit)(DT[nFront]))
            return FALSE;
        ++nFront;
        --nSize;

        if(nSize > nCapicity)
            return FALSE;

        if(nRear == nCapicity)
            nRear = 0;
        if(nFront == nCapicity)
            nFront = 0;
    }
    return TRUE;
}
