#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string.h>

using namespace std;

bool ReadFileToVector(const char *fileName, vector<int> &vecData);
//打开文件fileName，并把文件中的整形数据读到vector数组中。
void BubbleSortDown(vector<int> &vecData);
//用冒泡法把vector数组中的数据按从小到大（升序）排序
void BubbleSortUp(vector<int> &vecData);
//用冒泡法把vector'数组中的数据按从大到小（降序）排序
bool WriteVectorToFile(const char *fileName, const vector<int> &vecData);
//把vector中的数据写入fileName中，每个数据以空格分隔

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        //输入的参数个数不正确，则退出程序
        cerr<<"The count of parameters is ERROR!"<<endl;
        exit(EXIT_FAILURE);
    }

    vector<int> vecData;
    //把指定文件的数据读入vector中
    ReadFileToVector(argv[1], vecData);

    if(strcmp(argv[3], "1") == 0)
    {
        //若输入“1”，则从大到小排序
        BubbleSortUp(vecData);
    }
    else
    {
        //否则，从小到大排序
        BubbleSortDown(vecData);
    }
    //把vector中的数据保存到指定文件中
    WriteVectorToFile(argv[2], vecData);

    exit(EXIT_SUCCESS);
}

bool ReadFileToVector(const char *fileName, vector<int> &vecData)
{
    //以只读方式，打开文件fileName
    ifstream inputFile(fileName);
    if(!inputFile)
    {
        //打开文件失败
        cerr<<"error: unable to open input file: "
            <<fileName<<endl;
        return false;
    }

    int number = 0;
    while(!inputFile.eof())
    {
        //把文件中的数据复制到vector数组中
        inputFile >> number;
        vecData.push_back(number);
    }
    //关闭文件流
    inputFile.close();
    return true;
}

bool WriteVectorToFile(const char *fileName, const vector<int> &vecData)
{
    //以只写方式，打开文件fileName
    ofstream outputFile(fileName);
    if(!outputFile)
    {
        //打开文件失败
        cerr<<"error: unable to open input file: "
            <<fileName<<endl;
        return false;
    }
    //把vector中的数据写入文件中
    vector<int>::const_iterator it(vecData.begin());
    for(;it != vecData.end(); ++it)
    {
        outputFile<<*it<<" ";
    }
    //关闭文件流
    outputFile.close();
    return true;
}

void BubbleSortDown(vector<int> &vecData)
{
    bool hasSwap = true;//用于指示在一趟比较中，是否存在交换
    int sizeOfVec = vecData.size();//用于记录数组的大小
    for(int count = 0; count < sizeOfVec -1; ++count)
    {
        //若在一趟的比较中，不存在数据交换，则数据有序，退出循环
        if(hasSwap == false)
            break;
        hasSwap = false;
        for(int i = 0; i < sizeOfVec - count -1; ++i)
        {
            hasSwap = false;
            if(vecData[i] > vecData[i+1])
            {
                //交换数据
                int tmp = vecData[i];
                vecData[i] = vecData[i+1];
                vecData[i+1] = tmp;
                hasSwap = true;
            }
        }
    }
}

void BubbleSortUp(vector<int> &vecData)
{
    bool hasSwap = true;
    int sizeOfVec = vecData.size();
    for(int count = 0; count < sizeOfVec -1; ++count)
    {
        if(hasSwap == false)
            break;
        hasSwap = false;
        for(int i = 0; i < sizeOfVec - count -1; ++i)
        {
            if(vecData[i] < vecData[i+1])
            {
                int tmp = vecData[i];
                vecData[i] = vecData[i+1];
                vecData[i+1] = tmp;
                hasSwap = true;
            }
        }
    }
}
