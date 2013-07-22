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
    //返回值为x的结点的双亲结点
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
    //查找最小结点
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
    //右单旋转
    if(!AT)
        return NULL;
    AVLTree x = AT->RChild;
    AT->RChild = x->LChild;
    x->LChild = AT;

    AT->Height = Max(Height(AT->LChild), Height(AT->RChild))+1;
    x->Height = Max(Height(x->RChild), AT->Height)+1;
    //返回新的树根
    return x;
}


static AVLTree SingleRotateWithLeft(AVLTree AT)
{
    //左单旋转
    if(!AT)
        return NULL;
    AVLTree x = AT->LChild;
    AT->LChild = x->RChild;
    x->RChild = AT;

    AT->Height = Max(Height(AT->LChild), Height(AT->RChild))+1;
    x->Height = Max(Height(x->LChild), AT->Height) + 1;
    //返回新的树根
    return x;
}

static AVLTree DoubleRotateWithRight(AVLTree AT)
{
    //右双旋转，返回新的树根
    if(AT->LChild != NULL)
    {
        AT->LChild = SingleRotateWithLeft(AT->LChild);
        return SingleRotateWithRight(AT);
    }
}

static AVLTree DoubleRotateWithLeft(AVLTree AT)
{
    //左双旋转，返回新的树根
    if(AT->RChild != NULL )
    {
        AT->RChild = SingleRotateWithRight(AT->RChild);
        return SingleRotateWithLeft(AT);
    }
}

AVLNode* InsertNode(AVLTree AT, DataType x)
{
    //如果x不存在，则插入树中
    if(AT == NULL)
    {
        AT = (AVLTree)malloc(sizeof(AVLNode));
        if (AT == NULL)
        {
            //插入失败
            return NULL;
        }
        else
        {
            //初始化新结点
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
            //在左子树中进行插入
            AT->LChild = InsertNode(AT->LChild, x);

            if (Height(AT->LChild) - Height(AT->RChild) == 2)
            {
                //若失去失衡
                if (x < AT->LChild->Data)
                {
                    //若插入在左子树，则进行单左旋转
                    AT = SingleRotateWithLeft(AT);
                }
                else
                {
                    //若插入在右子树，则要进行双左旋转
                    AT = DoubleRotateWithLeft(AT);
                }
            }
        }
        else if (x > AT->Data)
        {
            //在右子树中进行插入
            AT->RChild = InsertNode(AT->RChild, x);

            if (Height(AT->RChild) - Height(AT->LChild) == 2)
            {
                //若失去失衡
                if (x > AT->RChild->Data)
                {
                    //若插入在右子树，则进行单右旋转
                    AT = SingleRotateWithRight(AT);
                }
                else
                {
                    //若插入在左子树，则进行双右旋转
                    AT = DoubleRotateWithRight(AT);
                }
            }
        }
    }
    //插入后，重新计算树高
    AT->Height = Max(Height(AT->LChild), Height(AT->RChild))+1 ;
    return AT;
}

AVLNode* DeleteNode(AVLTree AT, DataType x)
{
    //若为空树，则返回空，否则返回被删除的结点所属的树根
    if (AT == NULL )
    {
        return NULL;
    }

    if(x == AT->Data)
    {
        //找到要删除的结点
        AVLTree Min = FindMin(AT->RChild);
        if(Min != NULL)
        {
            //右子树存在
            AT->Data = Min->Data;
            if(Min != AT->RChild)
            {
                //AT->RChild存在左子树
                AVLTree Parent = GetParent(AT->RChild, Min->Data);
                Parent->LChild = Min->RChild;
            }
            else
            {
                //AT->RChild不存在左子树
                AT->RChild = Min->RChild;
            }
        }
        else
        {
            //右子树不存在
            Min = AT;
            AT = AT->LChild;
        }
        free(Min);
    }
    else if(x < AT->Data)
    {
        //在其左子树中进行删除
        AT->LChild = DeleteNode(AT->LChild, x);
        if(Height(AT->RChild) - Height(AT->LChild) == 2)
        {
            //删除后失去平衡
            if(AT->RChild)
            {
                //若删除后，AT->RChild的左子树比右子树高，则进行左双旋转
                if(Height(AT->RChild->LChild) > Height(AT->RChild->RChild))
                    AT = DoubleRotateWithLeft(AT);
                else    //否则，进行左单旋转
                    AT = SingleRotateWithLeft(AT);
            }
        }
    }

    else if(x > AT->Data)
    {
        //在其右子树中进行删除
        AT->RChild = DeleteNode(AT->RChild, x);
        if(Height(AT->LChild) - Height(AT->RChild) == 2)
        {
            //删除后失去平衡
            if(AT->LChild)
            {
                //若删除后，AT->LChild的右子树比左子树高，则进行右双旋转
                if(Height(AT->LChild->RChild) > Height(AT->LChild->LChild))
                    AT = DoubleRotateWithRight(AT);
                else    //否则，进行右单旋转
                    AT = SingleRotateWithRight(AT);
            }
        }
    }
    //重新计算AT的深度
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
