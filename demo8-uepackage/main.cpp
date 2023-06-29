#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "unistd.h"
#include "Format.h"

using namespace std;

int main(int argc, const char *argv[])
{

    char cmd[2048];
    std::string test = StringFormat::Format("CALL \"{0}\" BuildCookRun -project=\"{1}\" -noP4 -platform=Win64 -clientconfig=Development -serverconfig=Development -cook -allmaps -build -stage -pak -archive -archivedirectory=\"{2}\"", "D:\\Program Files\\Epic Games\\UE_5.0\\Engine\\Build\\BatchFiles\\RunUAT.bat", "F:\\workspace\\GLUE_Engine\\GL_UEngine_trunk_m9\\GL_UEngine.uproject", "F:\\GL_UEngine_Dist");
    strcpy(cmd, test.c_str());
    // 将命令行作为参数
    system(cmd);
    std::cout << "Done!\n";
    return 0;
}