#include <iostream>

using namespace std;

/**********
最基本的快速排序算法，选取最后一个元素作为枢纽
**********/

typedef int DataType;
void QuickSort(DataType *data, int data_size);
void QSort(DataType *data, int left, int right);
void Swap(DataType &x, DataType &y);

int main()
{
    DataType data[12]= {3,2,1,4,6,5,9,8,7,10,12,11};
    QuickSort(data, 12);
    for(int i = 0; i < 12; ++i)
        cout<<data[i]<<endl;
    return 0;
}

void QuickSort(DataType *data, int data_size)
{
    //快速排序启动函数
    QSort(data, 0, data_size-1);
}

void QSort(DataType *data, int left, int right)
{
    //如果数据的个小数为1或0则不需要排序
    if(left >= right)
        return;
    //取最后一个元素作为枢纽
    DataType centre = data[right];
    int i = left;
    int j = right-1;
    while(i < j)
    {
        //从前向后扫描，找到第一个小于枢纽的值，
        //在到达数组末尾前，必定结果循环,因为最后一个值为centre
        while(data[i] < centre)
            ++i;
        //从后向前扫描，此时要检查下标，防止数组越界
        while(j >= left && data[j] > centre)
            --j;
        //如果没有完成一趟交换，则交换
        if(i < j)
            Swap(data[i], data[j]);
    }
    //把枢纽放在正确的位置
    Swap(data[i], data[right]);
    QSort(data, left, i - 1);
    QSort(data, i + 1, right);
}

void Swap(DataType &x, DataType &y)
{
    //用于交换x和y的值
    DataType tmp(x);
    x = y;
    y = tmp;
}
