#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <thread>

using namespace std;

int main()
{
    HKEY key{0};
    RegOpenKey(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", &key);

    DWORD value{0};
    DWORD cbData = sizeof(DWORD);
    RegQueryValueEx(key, L"SystemUsesLightTheme", nullptr, nullptr, (LPBYTE)&value, &cbData);
    
    auto runChageDetection{true};
    thread thread([key, &runChageDetection, &value] {
        while (runChageDetection)
        {
            RegNotifyChangeKeyValue(key, FALSE, REG_NOTIFY_CHANGE_LAST_SET, nullptr, FALSE);
            DWORD new_value{0};
            DWORD cbData = sizeof(DWORD);
            RegQueryValueEx(key, L"SystemUsesLightTheme", nullptr, nullptr, (LPBYTE)&new_value, &cbData);
            if (new_value != value)
                cout << "Theme: " << new_value << endl;
            value = new_value;
        }
    });
    
    string line;
    getline(cin, line);
    
    runChageDetection = false;
    RegCloseKey(key);
    thread.join();

    vector<string> msg {"Hello", "C++", "World", "from", "VS Code!"};

    for (const string& word : msg)
    {
        cout << word << " ";

    }
    cout << endl;
}