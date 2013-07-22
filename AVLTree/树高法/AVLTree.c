#include <stdlib.h>
#include <stdio.h>
#include "AVLTree.h"

static int Max( int a, int b )
{
    return (a > b ? a : b);
}

static int Height( AVLTree AT )
{
    if(AT == NULL)
        return -1;
    return AT->Height;
}
AVLTree GetParent(AVLTree AT, DataType x)
{
    //����ֵΪx�Ľ���˫�׽��
    if(!AT || AT->Data == x)
        return NULL;
    if((AT->LChild && AT->LChild->Data == x) ||
            (AT->RChild && AT->RChild->Data == x))
        return AT;
    else if((AT->LChild && x < AT->LChild->Data))
        return GetParent(AT->LChild, x);
    else
        return GetParent(AT->RChild, x);
}

AVLNode* FindMin(AVLTree AT)
{
    //������С���
    if(AT)
    {
        while(AT->LChild)
        {
            AT = AT->LChild;
        }
    }
    return AT;
}

static AVLTree SingleRotateWithRight(AVLTree AT)
{
    //�ҵ���ת
    if(!AT)
        return NULL;
    AVLTree x = AT->RChild;
    AT->RChild = x->LChild;
    x->LChild = AT;

    AT->Height = Max(Height(AT->LChild), Height(AT->RChild))+1;
    x->Height = Max(Height(x->RChild), AT->Height)+1;
    //�����µ�����
    return x;
}


static AVLTree SingleRotateWithLeft(AVLTree AT)
{
    //����ת
    if(!AT)
        return NULL;
    AVLTree x = AT->LChild;
    AT->LChild = x->RChild;
    x->RChild = AT;

    AT->Height = Max(Height(AT->LChild), Height(AT->RChild))+1;
    x->Height = Max(Height(x->LChild), AT->Height) + 1;
    //�����µ�����
    return x;
}

static AVLTree DoubleRotateWithRight(AVLTree AT)
{
    //��˫��ת�������µ�����
    if(AT->LChild != NULL)
    {
        AT->LChild = SingleRotateWithLeft(AT->LChild);
        return SingleRotateWithRight(AT);
    }
}

static AVLTree DoubleRotateWithLeft(AVLTree AT)
{
    //��˫��ת�������µ�����
    if(AT->RChild != NULL )
    {
        AT->RChild = SingleRotateWithRight(AT->RChild);
        return SingleRotateWithLeft(AT);
    }
}

AVLNode* InsertNode(AVLTree AT, DataType x)
{
    //���x�����ڣ����������
    if(AT == NULL)
    {
        AT = (AVLTree)malloc(sizeof(AVLNode));
        if (AT == NULL)
        {
            //����ʧ��
            return NULL;
        }
        else
        {
            //��ʼ���½��
            AT->Data = x;
            AT->LChild = NULL;
            AT->RChild = NULL;
            AT->Height = 0;
        }
    }
    else
    {
        if (x < AT->Data)
        {
            //���������н��в���
            AT->LChild = InsertNode(AT->LChild, x);

            if (Height(AT->LChild) - Height(AT->RChild) == 2)
            {
                //��ʧȥʧ��
                if (x < AT->LChild->Data)
                {
                    //��������������������е�����ת
                    AT = SingleRotateWithLeft(AT);
                }
                else
                {
                    //������������������Ҫ����˫����ת
                    AT = DoubleRotateWithLeft(AT);
                }
            }
        }
        else if (x > AT->Data)
        {
            //���������н��в���
            AT->RChild = InsertNode(AT->RChild, x);

            if (Height(AT->RChild) - Height(AT->LChild) == 2)
            {
                //��ʧȥʧ��
                if (x > AT->RChild->Data)
                {
                    //��������������������е�����ת
                    AT = SingleRotateWithRight(AT);
                }
                else
                {
                    //���������������������˫����ת
                    AT = DoubleRotateWithRight(AT);
                }
            }
        }
    }
    //��������¼�������
    AT->Height = Max(Height(AT->LChild), Height(AT->RChild))+1 ;
    return AT;
}

AVLNode* DeleteNode(AVLTree AT, DataType x)
{
    //��Ϊ�������򷵻ؿգ����򷵻ر�ɾ���Ľ������������
    if (AT == NULL )
    {
        return NULL;
    }

    if(x == AT->Data)
    {
        //�ҵ�Ҫɾ���Ľ��
        AVLTree Min = FindMin(AT->RChild);
        if(Min != NULL)
        {
            //����������
            AT->Data = Min->Data;
            if(Min != AT->RChild)
            {
                //AT->RChild����������
                AVLTree Parent = GetParent(AT->RChild, Min->Data);
                Parent->LChild = Min->RChild;
            }
            else
            {
                //AT->RChild������������
                AT->RChild = Min->RChild;
            }
        }
        else
        {
            //������������
            Min = AT;
            AT = AT->LChild;
        }
        free(Min);
    }
    else if(x < AT->Data)
    {
        //�����������н���ɾ��
        AT->LChild = DeleteNode(AT->LChild, x);
        if(Height(AT->RChild) - Height(AT->LChild) == 2)
        {
            //ɾ����ʧȥƽ��
            if(AT->RChild)
            {
                //��ɾ����AT->RChild�����������������ߣ��������˫��ת
                if(Height(AT->RChild->LChild) > Height(AT->RChild->RChild))
                    AT = DoubleRotateWithLeft(AT);
                else    //���򣬽�������ת
                    AT = SingleRotateWithLeft(AT);
            }
        }
    }

    else if(x > AT->Data)
    {
        //�����������н���ɾ��
        AT->RChild = DeleteNode(AT->RChild, x);
        if(Height(AT->LChild) - Height(AT->RChild) == 2)
        {
            //ɾ����ʧȥƽ��
            if(AT->LChild)
            {
                //��ɾ����AT->LChild�����������������ߣ��������˫��ת
                if(Height(AT->LChild->RChild) > Height(AT->LChild->LChild))
                    AT = DoubleRotateWithRight(AT);
                else    //���򣬽����ҵ���ת
                    AT = SingleRotateWithRight(AT);
            }
        }
    }
    //���¼���AT�����
    if (AT != NULL)
    {
        AT->Height = Max(Height(AT->LChild), Height(AT->RChild))+1;
    }
    return AT;
}

void PrintATree(AVLTree AT, int nHight)
{
    int i = 0;
    if(!AT)
        return;
    printf("-");
    for(i = 1; i < nHight; ++i)
        printf("--");
    printf("%c\n", AT->Data);

    PrintATree(AT->LChild, nHight+1);
    PrintATree(AT->RChild, nHight+1);
}
