#include <stdio.h>
#include "BiTree.h"

//----------------------------------------------------------------------
BiTree InitBiTree()
{
    //初始化树根指针
    return NULL;
}
//----------------------------------------------------------------------
BiTree DestoryBiTree(BiTree BT)
{
    //释放所有的树结点，并把指向树根的指针置空
    //只能用后序free，否则需要1个（中序）或2个（前序）临时变量
    //来保存BT->LChild和BT->RChild
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
    //按先序次序输入二叉树中结点的值（字符‘#’表示空树）
    //根据输入构造二叉树
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
    //若为空树，则返回1，否则返回0
    if(BT == NULL)
        return TRUE;
    else
        return FALSE;
}
//----------------------------------------------------------------------
int BiTreeDepth(BiTree BT)
{
    //求树的深度
    //从二叉树深度的定义可知，二叉树的深度应为其左、右子树深度的最大值加1，
    //因为根结点算第1层。
    if(BT == NULL)  //若为空树，则返回0
        return 0;
    else
    {
        int nLDepth = BiTreeDepth(BT->LChild); //求左树的深度
        int nRDepth = BiTreeDepth(BT->RChild); //求右树的深度
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
    //返回树根的指针
    return BT;
}
//----------------------------------------------------------------------
DataType Value(BiNode *pBN)
{
    //返回结点所对应的值
    return pBN->cData;
}
//----------------------------------------------------------------------
BOOL Assign(BiNode *pBN, DataType value)
{
    //对相应的结点赋值
    if(pBN == NULL)
        return FALSE;
    pBN->cData = value;
    return TRUE;
}

//----------------------------------------------------------------------
BiTree GetLeftChild(BiTree BT, DataType value)
{
    //获得一个结点的左孩子，则不存在返回NULL
    BiNode *pBN = FindNode(BT, value); //查找该结点
    if(pBN != NULL)
        return pBN->LChild; //返回其左孩子
    return NULL;
}
//----------------------------------------------------------------------
BiTree GetRightChild(BiTree BT, DataType value)
{
    //获得一个结点的右孩子，则不存在返回NULL
    BiNode *pBN = FindNode(BT, value); //查找该结点
    if(pBN != NULL)
        return pBN->RChild; //返回其右孩子
    return NULL;
}
//----------------------------------------------------------------------
BiTree GetLeftSibling(BiTree BT, DataType value)
{
    //返回value的左兄弟，若value是BT的左孩子，
    //或value无左兄弟，返回NULL
    BiNode *pParent = GetParent(BT, value);
    if(pParent != NULL && pParent->LChild != NULL &&
       pParent->LChild->cData != value)
        return pParent->LChild;
    return NULL;
}
//----------------------------------------------------------------------
BiTree GetRightSibling(BiTree BT, DataType value)
{
    //返回value的右兄弟，若value是BT的右孩子，
    //或value无右兄弟，返回NULL
    BiNode *pParent = GetParent(BT, value);
    if(pParent != NULL && pParent->RChild != NULL &&
       pParent->RChild->cData != value)
        return pParent->RChild;
    return NULL;
}
//----------------------------------------------------------------------
BiTree InsertChild(BiNode *pBN, BOOL LR, BiTree c)
{
    //c与树pBN不相交，且右孩子为空，若LR为0或1，插入c为pBN的左或右子树。
    //pBN所指结点的原有左或右子树则成为c的右子树
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
    //根据LR为0或1，删除pBN所指的左或右子树
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
    //返回二叉树BT中结点的最小值
    if(BT == NULL)  //空树则返回NULL
        return NULL;

    BiNode *pMin = BT;  //默认以树根作为当前最小结点
    BiNode *tmp = MinNode(BT->LChild);  //找出左子树的最小结点
    if(tmp != NULL)
    {
        //左子树存在，且左子对的最小结点小于当前最小结点
        if(tmp->cData < pMin->cData)
            pMin = tmp;
    }

    tmp = MinNode(BT->RChild);  //找出右子树的最小结点
    if(tmp != NULL)
    {
        //右子树存在，且右子树的最小结点小于当前最小结点
        if(tmp->cData < pMin->cData)
            pMin = tmp;
    }
    return pMin;
}
//----------------------------------------------------------------------
BiTree MaxNode(BiTree BT)
{
    //返回二叉树BT中结点的最大值
    if(BT == NULL)  //空树则返回NULL
        return NULL;

    BiNode *pMax = BT;  //默认以树根作为当前最大结点
    BiNode *tmp = MaxNode(BT->LChild);  //找出左子树的最大结点
    if(tmp != NULL)
    {
        //左子树存在，且左子对的最大结点大于当前最大结点
        if(tmp->cData > pMax->cData)
            pMax = tmp;
    }

    tmp = MaxNode(BT->RChild);  //找出右子树的最大结点
    if(tmp != NULL)
    {
        //右子树存在，且右子树的最大结点大于当前最大结点
        if(tmp->cData > pMax->cData)
            pMax = tmp;
    }
    return pMax;
}
//----------------------------------------------------------------------
BiTree GetParent(BiTree BT, DataType c)
{
    //获得值为c的结点的双亲结点，
    //若c为根结点或不存在于树中，则返回NULL
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
    //以先序凹突方式打印二叉树
    __PrintBiTree(BT, 1);
}
//----------------------------------------------------------------------
BiTree FindNode(BiTree BT, DataType c)
{
    //返回二叉树BT中值为c的结点的指针
    //若c不存在于BT中，则返回NULL
    if(!BT)
        return NULL;
    else if(BT->cData == c) //找到相应的结点，返回其指针
        return BT;

    BiTree BN = NULL;
    BN = FindNode(BT->LChild, c);   //在其左子树中进行查找
    if(BN == NULL)      //没有找到，则继续在其右子树中进行查找
        BN = FindNode(BT->RChild, c);
    return BN;
}
//----------------------------------------------------------------------
int NotLeavesCount(BiTree BT)
{
    //返回二叉树BT中非叶子结点的个数
    if(BT == NULL || (!(BT->LChild || BT->RChild)))
        return 0;   //若为BT为空树或为叶子结点，返回0
    else
    {
        int nCount = 1; //此时根结点也是一个非叶子结点
        //累加上左子树的非叶子结点个数
        nCount += NotLeavesCount(BT->LChild);
        //累加上右子树的非叶子结点个数
        nCount += NotLeavesCount(BT->RChild);
        return nCount;
    }
}
//----------------------------------------------------------------------
int LeavesCount(BiTree BT)
{
    //返回二叉树BT中叶子结点的个数
    if(BT == NULL)
        return 0;   //BT为空树，返回0

    int nCount = 0;
    if(!(BT->LChild || BT->RChild))
        ++nCount;   //BT为叶子结点，加1
    else
    {
        //累加上左子树上的叶子结点
        nCount += LeavesCount(BT->LChild);
        //累加上右子树上的叶子结点
        nCount += LeavesCount(BT->RChild);
    }
    return nCount;
}
//----------------------------------------------------------------------
BOOL PreOrderTraverse(BiTree BT, BOOL(*Visit)(BiNode*))
{
    //先序遍历二叉树
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
    //中序遍历二叉树
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
    //后序遍历二叉树
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
    //层次性遍历二叉树
    //使用数组模拟一个循环队列
    if(BT == NULL)
        return TRUE;

    const int nCapicity = 300;
    BiTree DT[nCapicity];
    int nFront = 0, nRear = 1;
    DT[0] = BT;
    int nSize = 1;

    while(nSize != 0)   //队列非空
    {
        if(DT[nFront]->LChild)
        {
            //左子树非空，左子树入队
            DT[nRear] = DT[nFront]->LChild;
            ++nRear;
            ++nSize;
        }
        if(DT[nFront]->RChild)
        {
            //右子树非空，右子树入队
            DT[nRear] = DT[nFront]->RChild;
            ++nRear;
            ++nSize;
        }

        //访问队头元素，并出队
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
