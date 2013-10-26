#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string.h>

using namespace std;

bool ReadFileToVector(const char *fileName, vector<int> &vecData);
//打开文件fileName，并把文件中的整形数据读到vector数组中。
void SelectSortDown(vector<int> &vecData);
//用选择法把vector数组中的数据按从小到大（升序）排序
void SelectSortUp(vector<int> &vecData);
//用选择法把vector'数组中的数据按从大到小（降序）排序
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
        SelectSortUp(vecData);
    }
    else
    {
        //否则，从小到大排序
        SelectSortDown(vecData);
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

void SelectSortDown(vector<int> &vecData)
{
    int sizeOfVec = vecData.size();//用于记录数组的大小
    for(int i = 0; i < sizeOfVec-1; ++i)
    {
        int minIndex = i;//用于记录当前最小元素的下标
        for(int j = i+1; j < sizeOfVec; ++j)
        {
            if(vecData[minIndex] > vecData[j])
                minIndex = j;
        }
        if(minIndex != i)
        {
            //如果最小的元素不在要放入的位置i上，则交换数据。
            int tmp = vecData[i];
            vecData[i] = vecData[minIndex];
            vecData[minIndex] = tmp;
        }
    }
}

void SelectSortUp(vector<int> &vecData)
{
    int sizeOfVec = vecData.size();
    for(int i = 0; i < sizeOfVec-1; ++i)
    {
        int maxIndex = i;//用于记录当前最大元素的下标
        for(int j = i+1; j < sizeOfVec; ++j)
        {
            if(vecData[maxIndex] < vecData[j])
                maxIndex = j;
        }
        if(maxIndex != i)
        {
            int tmp = vecData[i];
            vecData[i] = vecData[maxIndex];
            vecData[maxIndex] = tmp;
        }
    }
}
