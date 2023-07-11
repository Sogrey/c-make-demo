#include <Windows.h>
#include <iostream>

void checkWindowsKits()
{
    HKEY hKey;
    DWORD valueType;
    DWORD valueSize;
    char valueData[1024] = {0};

    // 打开注册表项
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows Kits\\Installed Roots", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        // 读取安装路径
        valueSize = sizeof(valueData);
        if (RegQueryValueEx(hKey, "KitsRoot10", NULL, &valueType, reinterpret_cast<LPBYTE>(valueData), &valueSize) == ERROR_SUCCESS)
        {
            printf("Windows Kits 10 is installed.\n");
            printf("Install path: %s\n", valueData);
        }
        else if (RegQueryValueEx(hKey, "KitsRoot81", NULL, &valueType, reinterpret_cast<LPBYTE>(valueData), &valueSize) == ERROR_SUCCESS)
        {
            printf("Windows Kits 8.1 is installed.\n");
            printf("Install path: %s\n", valueData);
        }
        else if (RegQueryValueEx(hKey, "KitsRoot", NULL, &valueType, reinterpret_cast<LPBYTE>(valueData), &valueSize) == ERROR_SUCCESS)
        {
            printf("Windows Kits 8.0 is installed.\n");
            printf("Install path: %s\n", valueData);
        }
        else
        {
            printf("Windows Kits is not installed.\n");
        }

        // 关闭注册表项
        RegCloseKey(hKey);
    }
    else
    {
        printf("Failed to open registry key.\n");
    }
}
void readRegistrySubKeys()
{
    HKEY hKey;
    DWORD subKeyCount;
    DWORD maxSubKeyNameLen;
    char subKeyName[256] = { 0 };
    std::string subKeyNameLaster;

    // 打开注册表项
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows Kits\\Installed Roots", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        // 获取子目录数量和最大子目录名长度
        if (RegQueryInfoKey(hKey, NULL, NULL, NULL, &subKeyCount, &maxSubKeyNameLen, NULL, NULL, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
        {
            printf("Subkey count: %d\n", subKeyCount);
            printf("Max subkey name length: %d\n", maxSubKeyNameLen);

            if (subKeyCount > 0) {
                int j;
                // 逐个读取子目录的名字
                for (DWORD i = 0; i < subKeyCount; i++)
                {
                    DWORD subKeyNameLen = sizeof(subKeyName);
                    if (RegEnumKeyEx(hKey, i, subKeyName, &subKeyNameLen, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
                    {
                        if (i == 0) {
                            subKeyNameLaster = subKeyName;
                        }
                        else {
                            std::string currentVersion = subKeyName;
                            subKeyNameLaster = subKeyNameLaster.compare(currentVersion) > 0 ? subKeyNameLaster : currentVersion;
                        }
                        printf("Subkey name: %s\n", subKeyName);
                    }
                }
            }
        }

        std::cout << "The last version:" << subKeyNameLaster << std::endl;

        //FString HappyString(subKeyNameLaster.c_str());
        // 关闭注册表项
        RegCloseKey(hKey);
    }
    else
    {
        printf("Failed to open registry key.\n");
    }
}
//bool checkVisualStudioInstalled()
//{
//    HKEY hKey;
//    LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\DevDiv\\VS\\Servicing\\16.0", 0, KEY_READ, &hKey);
//    RegCloseKey(hKey);
//    return (result == ERROR_SUCCESS);
//}
bool checkVisualStudioInstalled()
{
    HKEY hKey;
    LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Microsoft\\VisualStudio", 0, KEY_READ, &hKey);
    RegCloseKey(hKey);
    return (result == ERROR_SUCCESS);
}


void getInstalledSoftwareVersion()
{
    HKEY hKey;
    DWORD subKeyCount;
    DWORD maxSubKeyNameLen;
    char subKeyName[256] = { 0 };

    // 打开注册表项
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        // 获取子目录数量和最大子目录名长度
        if (RegQueryInfoKey(hKey, NULL, NULL, NULL, &subKeyCount, &maxSubKeyNameLen, NULL, NULL, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
        {
            printf("Installed software count: %d\n", subKeyCount);

            // 逐个读取子目录的名字和版本信息
            for (DWORD i = 0; i < subKeyCount; i++)
            {
                DWORD subKeyNameLen = sizeof(subKeyName);
                if (RegEnumKeyEx(hKey, i, subKeyName, &subKeyNameLen, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
                {
                    HKEY subKey;
                    if (RegOpenKeyEx(hKey, subKeyName, 0, KEY_READ, &subKey) == ERROR_SUCCESS)
                    {
                        // 读取版本信息
                        char version[256] = { 0 };
                        DWORD versionLen = sizeof(version);
                        if (RegQueryValueEx(subKey, "DisplayVersion", NULL, NULL, reinterpret_cast<LPBYTE>(version), &versionLen) == ERROR_SUCCESS)
                        {
                            printf("Software name: %s\n", subKeyName);
                            printf("Version: %s\n", version);
                        }
                        RegCloseKey(subKey);
                    }
                }
            }
        }

        // 关闭注册表项
        RegCloseKey(hKey);
    }
    else
    {
        printf("Failed to open registry key.\n");
    }
}

int main()
{
    checkWindowsKits();
    readRegistrySubKeys();

    /*    
Windows Kits 10 is installed.
Install path: C:\Program Files (x86)\Windows Kits\10\
Subkey count: 2
Max subkey name length: 12
Subkey name: 10.0.18362.0
Subkey name: 10.0.19041.0    
    */

    bool isVisualStudioInstalled = checkVisualStudioInstalled();
    if (isVisualStudioInstalled)
    {
        printf("Visual Studio is installed.\n");
    }
    else
    {
        printf("Visual Studio is not installed.\n");
    }

    getInstalledSoftwareVersion();
    return 0;
}
