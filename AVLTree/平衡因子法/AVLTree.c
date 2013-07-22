#include <stdio.h>
#include "AVLTree.h"

void R_Rotate(AVLTree *pAT);
void L_Rotate(AVLTree *pAT);
void LeftBalance(AVLTree *pAT);
void RightBalance(AVLTree *pAT);

void InitAVL(AVLTree *pAT)
{
    DestoryAVL(pAT);
    *pAT = NULL;
}
void DestoryAVL(AVLTree *pAT)
{
    if(!(*pAT))
        return;
    else
    {
        DestoryAVL(&(*pAT)->LChild);
        DestoryAVL(&(*pAT)->RChild);
        free(*pAT);
        *pAT = NULL;               //只能用后序free
    }
}
void R_Rotate(AVLTree *pAT)
{
    //对以*pAT为根的二叉树作右旋转处理，处理之后pAT指向新的树根结点
    //即旋转处理之前的左子树的根结点
    AVLTree lc = (*pAT)->LChild;
    (*pAT)->LChild = lc->RChild;
    lc->RChild = *pAT;
    *pAT = lc;
}
void L_Rotate(AVLTree *pAT)
{
    //对以*pAT为根的二叉树作左旋转处理，处理之后pAT指向新的树根结点
    //即旋转处理之前的右子树的根结点
    AVLTree rc = (*pAT)->RChild;
    (*pAT)->RChild = rc->LChild;
    rc->LChild = *pAT;
    *pAT = rc;
}
void LeftBalance(AVLTree *pAT)
{
    //对以指针pAT所指结点为根的二叉树作左平衡旋转处理，
    //本算法结束时指针pAT指向新的结点
    AVLTree lc = (*pAT)->LChild;    //lc指向*pAT的左子树根结点
    AVLTree rd = NULL;
    if(lc)
    switch(lc->nBf)     //检查*pAT的左子树的平衡度，并作相应平衡处理
    {
        case LH:    //新结点插入在*pAT的左孩子的左子树上，要作单右旋转处理
            (*pAT)->nBf = lc->nBf = EH;
            R_Rotate(pAT);
            break;
        case RH:    //新结点插入在*pAT的左孩子的右子树上，要作双旋转处理
            rd = lc->RChild;
            switch(rd->nBf) //修改*pAT及其左孩子的平衡因子
            {
                case LH:
                    (*pAT)->nBf = RH;
                    lc->nBf = EH;
                    break;
                case EH:
                    (*pAT)->nBf = lc->nBf = EH;
                    break;
                case RH:
                    (*pAT)->nBf = EH;
                    lc->nBf = LH;
                    break;
                default:;
            }
            rd->nBf = EH;
            L_Rotate(&(*pAT)->LChild);  //对*pAT的左子树作左平衡处理
            R_Rotate(pAT);      //对*pAT作右平衡处理
            break;
        default:;
    }
}
void RightBalance(AVLTree *pAT)
{
    //对以指针pAT所指结点为根的二叉树作右平衡旋转处理，
    //本算法结束时指针pAT指向新的结点
    AVLTree rc = (*pAT)->RChild;
    AVLTree rd = NULL;
    if(rc)
    switch(rc->nBf)
    {
        case RH:
            (*pAT)->nBf = rc->nBf = EH;
            L_Rotate(pAT);
            break;
        case LH:
            rd = rc->LChild;
            switch(rd->nBf)
            {
                case LH:
                    (*pAT)->nBf = EH;
                    rc->nBf = RH;
                    break;
                case EH:
                    (*pAT)->nBf = rc->nBf = EH;
                    break;
                case RH:
                    (*pAT)->nBf = LH;
                    rc->nBf = EH;
                    break;
            }
            rd->nBf = EH;
            R_Rotate(&(*pAT)->RChild);
            L_Rotate(pAT);
        default:;
    }
}
BOOL InsertATNode(AVLTree *pAT, DataType c)
{
    //若在平衡的二叉树pAT中不存在和c相同的关键字结点，
    //则插入一个以c为数据元素的新结点，并返回1，否则返回0
    //若因插入而使二叉排序树失去平衡，则作平衡旋转处理
    static int taller = FALSE;  //反映pAT树是否长高
    if(!(*pAT))
    {
        //插入新结点，树长高，taller为TRUE;
        (*pAT) = (AVLTree)malloc(sizeof(AVLNode));
        (*pAT)->cData = c;
        (*pAT)->LChild = (*pAT)->RChild = NULL;
        (*pAT)->nBf = EH;
        taller = TRUE;
    }
    else
    {
        if((*pAT)->cData == c)
        {
            //树中已存在和e相同关键字的结点，不插入
            taller = FALSE;
            return 0;
        }
        if(c < (*pAT)->cData)
        {
            //应该在*pAT的左子树中进行搜索
            if(!InsertATNode(&(*pAT)->LChild, c))   //未插入
                return 0;
            if(taller)  //已插入到树pAT并且左子树长高
            {
                switch((*pAT)->nBf) //检查*pAT的平衡因子
                {
                    case LH:    //原本左子树比右子树高，作左平衡处理
                        LeftBalance(pAT);
                        taller = FALSE;
                        break;
                    case EH:    //原本左右子树等高，现左子树比右子树高1
                        (*pAT)->nBf = LH;
                        taller = TRUE;
                        break;
                    case RH:    //原本右子树比左子树高，现左右子树等高
                        (*pAT)->nBf = EH;
                        taller = FALSE;
                        break;
                }
            }
        }
        else
        {
            //应该在*pAT的右子树中进行搜索
            if(!InsertATNode(&(*pAT)->RChild, c))   //未插入
                return 0;
            if(taller)  //已插入到树pAT并且右子树长高
            {
                switch((*pAT)->nBf) //检查*pAT的平衡因子
                {
                    case LH:    //原本左子树比右子树高，现左右子树等高
                        (*pAT)->nBf = EH;
                        taller = FALSE;
                        break;
                    case EH:    //原本左右子树等高，现右子树比左子树高1
                        (*pAT)->nBf = RH;
                        taller = TRUE;
                        break;
                    case RH:    //原本右子树比左子树高，作右平衡处理
                        RightBalance(pAT);
                        taller = FALSE;
                        break;
                }
            }
        }
    }
    return 1;
}
BOOL DeleteNode(AVLTree *pAT, DataType c)
{
    //若在平衡的二叉树pAT中存在和c相同的关键字结点，
    //则删除一个以c为数据元素的结点，并返回1，否则返回0
    //若因删除而使二叉排序树失去平衡，则作平衡旋转处理
    static int lower = FALSE;   //反映pAT树是否变矮
    if(!(*pAT))     //树为空或结点不存在返回0
        return 0;
    if(c == (*pAT)->cData)
    {
        //存在要删除的结点
        //查找用作替换的结点
        AVLTree Min = FindMin((*pAT)->RChild);
        if(Min != NULL) //存在右子树
        {
            //找到可以用作替换的点
            (*pAT)->cData = Min->cData;
            if(Min != (*pAT)->RChild)
            {
                AVLTree Parent = GetParent((*pAT)->RChild, Min->cData);
                Parent->LChild = Min->RChild;
            }
            else
            {
                (*pAT)->RChild = Min->RChild;
            }

            free(Min);
        }
        else //不存在右子树
        {
            //找不到删除的结点
            Min = *pAT;
            *pAT = (*pAT)->LChild;
            free(Min);
        }
        lower = TRUE;
    }
    else if(c < (*pAT)->cData)
    {
        //应该在*pAT的左子树中进行搜索
        if(!DeleteNode(&(*pAT)->LChild, c)) //未删除
            return 0;

        if(lower)   //树变矮
        {
            switch((*pAT)->nBf)
            {
                case LH:    //原本左子树比右子树高，现在等高
                    (*pAT)->nBf = EH;
                    lower = TRUE;
                    break;
                case EH:    //原本左右子树等高，现右子树比左子树高1
                    (*pAT)->nBf = RH;
                    lower = FALSE;
                    break;
                case RH:    //原本右子树比左子树高，则作右平衡处理
                    RightBalance(pAT);
                    lower = TRUE;
                    break;
            }
        }

    }
    else if(c > (*pAT)->cData)
    {
        //应该在*pAT的右子树中进行搜索
        if(!DeleteNode(&(*pAT)->RChild, c))
            return 0;
        if(lower)
        {
            switch((*pAT)->nBf)
            {
                case LH:    //原本左子树比右子树高，则作左平衡处理
                    LeftBalance(pAT);
                    lower = TRUE;
                    break;
                case EH:    //原本左右子树等高，现左子树比右子树高1
                    (*pAT)->nBf = LH;
                    lower = FALSE;
                    break;
                case RH:    //原本右子树比左子树高，现左左子树等高
                    (*pAT)->nBf = EH;
                    lower = TRUE;
                    break;
            }
        }
    }

    return 1;
}
AVLTree FindMin(AVLTree AT)
{
    //查找AT中最小的元素
    while(AT && AT->LChild)
    {
        AT = AT->LChild;
    }
    return AT;
}
AVLTree GetParent(AVLTree AT, DataType c)
{
    if(!AT || AT->cData == c)
        return NULL;
    if((AT->LChild && AT->LChild->cData == c) ||
            (AT->RChild && AT->RChild->cData == c))
        return AT;
    else if((AT->LChild && c < AT->LChild->cData))
        return GetParent(AT->LChild, c);
    else
        return GetParent(AT->RChild, c);
}

void PrintATree(AVLTree AT, int nHight)
{
    int i = 0;
    if(!AT)
        return;
    printf("-");
    for(i = 1; i < nHight; ++i)
        printf("--");
    printf("%c\n", AT->cData);

    PrintATree(AT->LChild, nHight+1);
    PrintATree(AT->RChild, nHight+1);
}
AVLTree FindATNode(AVLTree AT, DataType c)
{
    if(!AT)
        return NULL;
    else if(AT->cData == c)
        return AT;
    else if(c < AT->cData)
    {
        return FindATNode(AT->LChild, c);
    }
    else
    {
        return FindATNode(AT->RChild, c);
    }
}
AVLTree Marge(AVLTree AT1, AVLTree AT2)
{
    if(!AT2)
        return AT1;
    else
    {
        InsertATNode(&AT1, AT2->cData);
        Marge(AT1, AT2->LChild);
        Marge(AT1, AT2->RChild);
    }
}
/**
AVLTree MargeATree(AVLTree *pAT1, AVLTree *pAT2)
{
    *pAT1 = Marge(*pAT1, *pAT2);
    DestoryAVL(pAT2);
    return *pAT1
}
AVLTree SplibATree(AVLTree *pAT, DataType c)
{
    if(!(*pAT))
        return NULL;
}
**/

int Num(AVLTree AT)
{

    if(AT == NULL || (!(AT->LChild || AT->RChild)))
        return 0;
    else
    {
        int nL = Num(AT->LChild);
        int nR = Num(AT->RChild);
        return nL + nR + 1;
    }

}
