#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

int main()
{
    HKEY key{0};
    RegOpenKey(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", &key);

    DWORD value{0};
    DWORD cbData = sizeof(DWORD);
    RegQueryValueEx(key, L"SystemUsesLightTheme", nullptr, nullptr, (LPBYTE)&value, &cbData);

    RegCloseKey(key);

    vector<string> msg {"Hello", "C++", "World", "from", "VS Code!"};

    for (const string& word : msg)
    {
        cout << word << " ";

    }
    cout << endl;
}