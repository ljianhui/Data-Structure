#include <iostream>

using namespace std;

/*******
使用三数中值法，选取枢纽值，
并把最小值放在第0个位置
最大值放在最后的位置，
把中值作为枢纽，并与倒数第二个数据交换位置
排序后，数据从小到大
*******/
typedef int DataType;
void QuickSort(DataType *data, int data_size);
void QSort(DataType *data, int left, int right);
DataType Median3(DataType *data, int left, int right);
void Swap(DataType &x, DataType &y);
void BubbleSort(DataType *data, int data_size);

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
    //快排启动函数
    QSort(data, 0, data_size - 1);
}

DataType Median3(DataType *data, int left, int right)
{
    //取数据的头、尾和中间三个数，并对他们进行排序
    //排序结果直接保存在数组中
    int centre = (left + right)/2;
    if(data[left] > data[centre])
        Swap(data[left], data[centre]);
    if(data[left] > data[right])
        Swap(data[left], data[right]);
    if(data[centre] > data[right])
        Swap(data[centre], data[right]);
    //把中值，即枢纽与数组倒数第二个元素交换
    swap(data[centre], data[right - 1]);
    return data[right - 1];//返回枢纽

}

void QSort(DataType *data, int left, int right)
{
    //如果需要排序的数据大于3个则使用快速排序
    if(right - left >= 3)
    {
        //取得枢纽的值
        DataType centre = Median3(data, left, right);
        int begin = left;
        int end = right - 1;
        while(true)
        {
            //向后扫描数组
            //由于在选择枢纽时，已经把比枢纽值大的数据放在right位置
            //所以不会越界
            while(data[++begin] < centre);
            //向前扫描数组
            //由于在选择枢纽时，已经把比枢纽值小的数据放在left位置
            //所以不会越界
            while(data[--end] > centre);
            //把比枢纽小的数据放在前部，大的放到后部
            if(begin < end)
                Swap(data[begin], data[end]);
            else
            {
                //已经对要排序的数据都与枢纽比较了一次
                //把中枢纽保存在适当的位置，因为begin的数一定比枢纽大
                //所以把这个数放在数组后面
                Swap(data[begin], data[right - 1]);
                break;
            }
        }

        QSort(data, left, begin - 1);
        QSort(data, begin + 1, right);
    }
    else //如果要排序的数据很少，少于等于3个，则直接使用冒泡排序
    {
        BubbleSort(data+left, right - left + 1);
    }
}

void Swap(DataType &x, DataType &y)
{
    //交换两个数据的值
    DataType tmp = x;
    x = y;
    y = tmp;
}

void BubbleSort(DataType *data, int data_size)
{
    //冒泡排序算法
    bool hasSwap = true;//用于指示在一趟比较中，是否存在交换
    for(int i = 0; i < data_size-1; ++i)
    {
        //若在一趟的比较中，不存在数据交换，则数据有序，退出循环
        if(hasSwap == false)
            break;
        hasSwap = false;

        for(int j = 0; j < data_size - i - 1; ++j)
        {
            if(data[j] > data[j+1])
            {
                Swap(data[j], data[j+1]);
                hasSwap = true;
            }
        }
    }
}

