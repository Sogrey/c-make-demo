#include <iostream>
#include <string>
#include <cstdio>

bool CheckDotNetCoreRuntime()
{
    std::string command = "dotnet --version";
    std::string output;
    char buffer[128];
    FILE* pipe = _popen(command.c_str(), "r");

    if (!pipe)
    {
        std::cout << "Failed to execute command." << std::endl;
        return false;
    }

    while (!feof(pipe))
    {
        if (fgets(buffer, 128, pipe) != NULL)
        {
            output += buffer;
        }
    }

    _pclose(pipe);

    if (!output.empty())
    {
        std::cout << ".NET Core Runtime version: " << output;
        return true;
    }
    else
    {
        std::cout << ".NET Core Runtime is not installed." << std::endl;
    }

    return false;
}

int main()
{
    if (CheckDotNetCoreRuntime())
    {
        std::cout << ".NET Core Runtime is installed." << std::endl;
    }
    else
    {
        std::cout << ".NET Core Runtime is not installed." << std::endl;
    }

    return 0;
}
