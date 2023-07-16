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
    LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Microsoft\\VisualStudio\\16.0", 0, KEY_READ, &hKey);
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

#ifdef _MSC_VER
    int num = _MSC_VER; // get the version
    /*
    
Vs 版本对照关系整理如下（更新至2022.3.26）：

| `VC 版本`| `_MSC_VER`  |`VS 版本`| MSVC toolset version |
| -------- | ----------- | ------- | -------------------- |
| VC6.0    | 1200        | VS 6.0  |                      |
| VC7.0    | 1300        | VS2002  |                      |
| VC7.1    | 1310        | VS2003  |                      |
| VC8.0    | 1400        | VS2005  | 80                   |
| VC9.0    | 1500        | VS2008  | 90                   |
| VC10.0   | 1600        | VS2010  | 100                  |
| VC11.0   | 1700        | VS2012  | 110                  |
| VC12.0   | 1800        | VS2013  | 120                  |
| VC14.0   | 1900        | VS2015  | 140                  |
| VC15.0   | [1910,1916] | VS2017  | 141                  |
| VC16.0   | [1920,1929] | VS2019  | 142                  |
| VC17.0   | [1930,)     | VS2022  | 143                  |

    */
    std::string vsVersion;
    if (num >= 1930) { //VS2022
        vsVersion = "VS2022";
    }
    else if (num >= 1920 && num <= 1929) {// VS2019 
        vsVersion = "VS2019";
    }
    else if (num >= 1910 && num <= 1916) {// VS2017 
        vsVersion = "VS2017";
    }
    else { // 早期版本
        switch (num)
        {
        case 1200: // VS 6.0 
            vsVersion = "VS 6.0";
            break;
        case 1300: // VS2002
            vsVersion = "VS 2002";
            break;
        case 1310: // VS2003
            vsVersion = "VS 2003";
            break;
        case 1400: // VS2005 
            vsVersion = "VS 2005";
            break;
        case 1500: // VS2008
            vsVersion = "VS 2008";
            break;
        case 1600: // VS2010 
            vsVersion = "VS 2010";
            break;
        case 1700: // VS2012 
            vsVersion = "VS 2012";
            break;
        case 1800: // VS2013 
            vsVersion = "VS 2013";
            break;
        case 1900: // VS2015
            vsVersion = "VS 2015";
            break;
        default: // 未識別版本
            vsVersion = "unknown version";
            break;
        }
    }

    std::cout << "Visual Studio installed:" << vsVersion << " - " << num << std::endl;
#endif // _MSC_VER


    //getInstalledSoftwareVersion();
    return 0;
}


/*

MSVC++ 14.30 _MSC_VER == 1933 (Visual Studio 2022 version 17.3.4)
MSVC++ 14.30 _MSC_VER == 1932 (Visual Studio 2022 version 17.2.2)
MSVC++ 14.30 _MSC_VER == 1930 (Visual Studio 2022 version 17.0.2)
MSVC++ 14.30 _MSC_VER == 1930 (Visual Studio 2022 version 17.0.1)
MSVC++ 14.28 _MSC_VER == 1929 (Visual Studio 2019 version 16.11.2)
MSVC++ 14.28 _MSC_VER == 1928 (Visual Studio 2019 version 16.9.2)
MSVC++ 14.28 _MSC_VER == 1928 (Visual Studio 2019 version 16.8.2)
MSVC++ 14.28 _MSC_VER == 1928 (Visual Studio 2019 version 16.8.1)
MSVC++ 14.27 _MSC_VER == 1927 (Visual Studio 2019 version 16.7)
MSVC++ 14.26 _MSC_VER == 1926 (Visual Studio 2019 version 16.6.2)
MSVC++ 14.25 _MSC_VER == 1925 (Visual Studio 2019 version 16.5.1)
MSVC++ 14.24 _MSC_VER == 1924 (Visual Studio 2019 version 16.4)
MSVC++ 14.23 _MSC_VER == 1923 (Visual Studio 2019 version 16.3)
MSVC++ 14.22 _MSC_VER == 1922 (Visual Studio 2019 version 16.2)
MSVC++ 14.21 _MSC_VER == 1921 (Visual Studio 2019 version 16.1)
MSVC++ 14.2  _MSC_VER == 1920 (Visual Studio 2019 version 16.0)
MSVC++ 14.16 _MSC_VER == 1916 (Visual Studio 2017 version 15.9)
MSVC++ 14.15 _MSC_VER == 1915 (Visual Studio 2017 version 15.8)
MSVC++ 14.14 _MSC_VER == 1914 (Visual Studio 2017 version 15.7)
MSVC++ 14.13 _MSC_VER == 1913 (Visual Studio 2017 version 15.6)
MSVC++ 14.12 _MSC_VER == 1912 (Visual Studio 2017 version 15.5)
MSVC++ 14.11 _MSC_VER == 1911 (Visual Studio 2017 version 15.3)
MSVC++ 14.1  _MSC_VER == 1910 (Visual Studio 2017 version 15.0)
MSVC++ 14.0  _MSC_VER == 1900 (Visual Studio 2015 version 14.0)
MSVC++ 12.0  _MSC_VER == 1800 (Visual Studio 2013 version 12.0)
MSVC++ 11.0  _MSC_VER == 1700 (Visual Studio 2012 version 11.0)
MSVC++ 10.0  _MSC_VER == 1600 (Visual Studio 2010 version 10.0)
MSVC++ 9.0   _MSC_FULL_VER == 150030729 (Visual Studio 2008, SP1)
MSVC++ 9.0   _MSC_VER == 1500 (Visual Studio 2008 version 9.0)
MSVC++ 8.0   _MSC_VER == 1400 (Visual Studio 2005 version 8.0)
MSVC++ 7.1   _MSC_VER == 1310 (Visual Studio .NET 2003 version 7.1)
MSVC++ 7.0   _MSC_VER == 1300 (Visual Studio .NET 2002 version 7.0)
MSVC++ 6.0   _MSC_VER == 1200 (Visual Studio 6.0 version 6.0)
MSVC++ 5.0   _MSC_VER == 1100 (Visual Studio 97 version 5.0)

*/