#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "format.h"

#ifdef _WIN32
#include "unistd.h"
#include <Windows.h>
#else
#endif
#include <format>

#include <locale>
#include <codecvt>



using namespace std;

std::wstring charArrayToWstring(const CHAR* charArray)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(charArray);
}


std::wstring charArrayToWstring2(const CHAR* charArray)
{
    int length = MultiByteToWideChar(CP_UTF8, 0, charArray, -1, nullptr, 0);
    std::wstring result(length - 1, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, charArray, -1, &result[0], length);
    return result;
}

std::wstring ExecuteCommand(const std::wstring& command)
{
    HANDLE hPipeRead, hPipeWrite;
    SECURITY_ATTRIBUTES sa;
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&sa, sizeof(SECURITY_ATTRIBUTES));
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&hPipeRead, &hPipeWrite, &sa, 0))
    {
        std::cout << "Failed to create pipe." << std::endl;
        return L"";
    }

    ZeroMemory(&si, sizeof(STARTUPINFOW));
    si.cb = sizeof(STARTUPINFOW);
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.wShowWindow = SW_HIDE;
    si.hStdError = hPipeWrite;
    si.hStdOutput = hPipeWrite;

    if (CreateProcessW(NULL, const_cast<LPWSTR>(command.c_str()), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        WaitForSingleObject(pi.hProcess, INFINITE);

        DWORD bytesRead;
        CHAR buffer[4096];
        std::wstring output;

        if (ReadFile(hPipeRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
            buffer[bytesRead] = '\0';
            output += charArrayToWstring(buffer);
        }

        CloseHandle(hPipeRead);
        CloseHandle(hPipeWrite);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        return output;
    }
    else
    {
        std::cout << "Failed to execute command." << std::endl;
        CloseHandle(hPipeRead);
        CloseHandle(hPipeWrite);
        return L"";
    }
}


int main(int argc, const char *argv[])
{

#ifdef _WIN32
    std::wstring command = L"cmd /C dotnet --version";
    std::wstring result = ExecuteCommand(command);
    std::wcout << result << std::endl;


    //char cmd[2048];
    //std::string test = stringformat::format("call ping \"{0}\"", "baidu.com");
    //strcpy(cmd, test.c_str());
    //// 将命令行作为参数
    //system(cmd);
#else
    char line[300];
    std::string test = stringformat::format("ping \"{0}\"", "baidu.com");
    file* fp;
    int count = 0;
    // system call
    const char* syscommand = test.data();
    if ((fp = popen(syscommand, "r")) == null) {
        cout << "error" << endl;
        return 0;
    }


    while (fgets(line, sizeof(line) - 1, fp) != null) {
        cout << count << " -> " << line;
        count++;
    }
    pclose(fp);
#endif
    std::cout << "done!\n";
    return 0;
}
