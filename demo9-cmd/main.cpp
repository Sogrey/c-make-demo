#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Format.h"

#ifdef _WIN32
#include "unistd.h"
#else
#endif

using namespace std;

int main(int argc, const char *argv[])
{

#ifdef _WIN32
    char cmd[2048];
    std::string test = StringFormat::Format("CALL ping \"{0}\"", "www.baidu.com");
    strcpy(cmd, test.c_str());
    // 将命令行作为参数
    system(cmd);
#else
    char line[300];
    std::string test = StringFormat::Format("ping \"{0}\"", "www.baidu.com");
    FILE* fp;
    int count = 0;
    // system call
    const char* sysCommand = test.data();
    if ((fp = popen(sysCommand, "r")) == NULL) {
        cout << "error" << endl;
        return 0;
    }


    while (fgets(line, sizeof(line) - 1, fp) != NULL) {
        cout << count << " -> " << line;
        count++;
    }
    pclose(fp);
#endif
    std::cout << "Done!\n";
    return 0;
}