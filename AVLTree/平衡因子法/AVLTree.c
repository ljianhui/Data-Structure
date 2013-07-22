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
        *pAT = NULL;               //ֻ���ú���free
    }
}
void R_Rotate(AVLTree *pAT)
{
    //����*pATΪ���Ķ�����������ת��������֮��pATָ���µ��������
    //����ת����֮ǰ���������ĸ����
    AVLTree lc = (*pAT)->LChild;
    (*pAT)->LChild = lc->RChild;
    lc->RChild = *pAT;
    *pAT = lc;
}
void L_Rotate(AVLTree *pAT)
{
    //����*pATΪ���Ķ�����������ת��������֮��pATָ���µ��������
    //����ת����֮ǰ���������ĸ����
    AVLTree rc = (*pAT)->RChild;
    (*pAT)->RChild = rc->LChild;
    rc->LChild = *pAT;
    *pAT = rc;
}
void LeftBalance(AVLTree *pAT)
{
    //����ָ��pAT��ָ���Ϊ���Ķ���������ƽ����ת����
    //���㷨����ʱָ��pATָ���µĽ��
    AVLTree lc = (*pAT)->LChild;    //lcָ��*pAT�������������
    AVLTree rd = NULL;
    if(lc)
    switch(lc->nBf)     //���*pAT����������ƽ��ȣ�������Ӧƽ�⴦��
    {
        case LH:    //�½�������*pAT�����ӵ��������ϣ�Ҫ��������ת����
            (*pAT)->nBf = lc->nBf = EH;
            R_Rotate(pAT);
            break;
        case RH:    //�½�������*pAT�����ӵ��������ϣ�Ҫ��˫��ת����
            rd = lc->RChild;
            switch(rd->nBf) //�޸�*pAT�������ӵ�ƽ������
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
            L_Rotate(&(*pAT)->LChild);  //��*pAT������������ƽ�⴦��
            R_Rotate(pAT);      //��*pAT����ƽ�⴦��
            break;
        default:;
    }
}
void RightBalance(AVLTree *pAT)
{
    //����ָ��pAT��ָ���Ϊ���Ķ���������ƽ����ת����
    //���㷨����ʱָ��pATָ���µĽ��
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
    //����ƽ��Ķ�����pAT�в����ں�c��ͬ�Ĺؼ��ֽ�㣬
    //�����һ����cΪ����Ԫ�ص��½�㣬������1�����򷵻�0
    //��������ʹ����������ʧȥƽ�⣬����ƽ����ת����
    static int taller = FALSE;  //��ӳpAT���Ƿ񳤸�
    if(!(*pAT))
    {
        //�����½�㣬�����ߣ�tallerΪTRUE;
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
            //�����Ѵ��ں�e��ͬ�ؼ��ֵĽ�㣬������
            taller = FALSE;
            return 0;
        }
        if(c < (*pAT)->cData)
        {
            //Ӧ����*pAT���������н�������
            if(!InsertATNode(&(*pAT)->LChild, c))   //δ����
                return 0;
            if(taller)  //�Ѳ��뵽��pAT��������������
            {
                switch((*pAT)->nBf) //���*pAT��ƽ������
                {
                    case LH:    //ԭ�����������������ߣ�����ƽ�⴦��
                        LeftBalance(pAT);
                        taller = FALSE;
                        break;
                    case EH:    //ԭ�����������ȸߣ�������������������1
                        (*pAT)->nBf = LH;
                        taller = TRUE;
                        break;
                    case RH:    //ԭ�����������������ߣ������������ȸ�
                        (*pAT)->nBf = EH;
                        taller = FALSE;
                        break;
                }
            }
        }
        else
        {
            //Ӧ����*pAT���������н�������
            if(!InsertATNode(&(*pAT)->RChild, c))   //δ����
                return 0;
            if(taller)  //�Ѳ��뵽��pAT��������������
            {
                switch((*pAT)->nBf) //���*pAT��ƽ������
                {
                    case LH:    //ԭ�����������������ߣ������������ȸ�
                        (*pAT)->nBf = EH;
                        taller = FALSE;
                        break;
                    case EH:    //ԭ�����������ȸߣ�������������������1
                        (*pAT)->nBf = RH;
                        taller = TRUE;
                        break;
                    case RH:    //ԭ�����������������ߣ�����ƽ�⴦��
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
    //����ƽ��Ķ�����pAT�д��ں�c��ͬ�Ĺؼ��ֽ�㣬
    //��ɾ��һ����cΪ����Ԫ�صĽ�㣬������1�����򷵻�0
    //����ɾ����ʹ����������ʧȥƽ�⣬����ƽ����ת����
    static int lower = FALSE;   //��ӳpAT���Ƿ�䰫
    if(!(*pAT))     //��Ϊ�ջ��㲻���ڷ���0
        return 0;
    if(c == (*pAT)->cData)
    {
        //����Ҫɾ���Ľ��
        //���������滻�Ľ��
        AVLTree Min = FindMin((*pAT)->RChild);
        if(Min != NULL) //����������
        {
            //�ҵ����������滻�ĵ�
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
        else //������������
        {
            //�Ҳ���ɾ���Ľ��
            Min = *pAT;
            *pAT = (*pAT)->LChild;
            free(Min);
        }
        lower = TRUE;
    }
    else if(c < (*pAT)->cData)
    {
        //Ӧ����*pAT���������н�������
        if(!DeleteNode(&(*pAT)->LChild, c)) //δɾ��
            return 0;

        if(lower)   //���䰫
        {
            switch((*pAT)->nBf)
            {
                case LH:    //ԭ�����������������ߣ����ڵȸ�
                    (*pAT)->nBf = EH;
                    lower = TRUE;
                    break;
                case EH:    //ԭ�����������ȸߣ�������������������1
                    (*pAT)->nBf = RH;
                    lower = FALSE;
                    break;
                case RH:    //ԭ�����������������ߣ�������ƽ�⴦��
                    RightBalance(pAT);
                    lower = TRUE;
                    break;
            }
        }

    }
    else if(c > (*pAT)->cData)
    {
        //Ӧ����*pAT���������н�������
        if(!DeleteNode(&(*pAT)->RChild, c))
            return 0;
        if(lower)
        {
            switch((*pAT)->nBf)
            {
                case LH:    //ԭ�����������������ߣ�������ƽ�⴦��
                    LeftBalance(pAT);
                    lower = TRUE;
                    break;
                case EH:    //ԭ�����������ȸߣ�������������������1
                    (*pAT)->nBf = LH;
                    lower = FALSE;
                    break;
                case RH:    //ԭ�����������������ߣ������������ȸ�
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
    //����AT����С��Ԫ��
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
