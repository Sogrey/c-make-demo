#include <iostream>
#include <stdio.h>
#include <string>
#include <thread>
#include <chrono>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv)
{
    cout << argc << endl; // 命令参数长度
    for (int i = 0; i < argc; i++)
    {
        cout << argv[i] << endl;
    }
    // 参数0 argv[0] 是 可执行文件名， 后面为参数
    int total = atoi(argv[1]); //将字符型argv[1]转换为整型，并赋值给i。 
    int duration = atoi(argv[2]); // milliseconds
    //  atof(argv[1]); // 参数转为 float

    return 0;
}