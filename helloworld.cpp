#include <iostream>
#include <vector>
#include <string>
#ifdef WINDOWS
#include <Windows.h>
#endif
#include <thread>

using namespace std;

#ifdef WINDOWS

void test_windows() {
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
}
#endif

template<typename... Args>
bool all(Args... args) { return (... && args); }

int main()
{
#ifdef WINDOWS
    test_widows();
#endif

    auto helloworld {"Hallöchen Wörlt👶"s};

    cout << helloworld << ", " << helloworld.length() << endl;

    vector<string> msg {"Hello", "C++", "World", "from", "VS Code!"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;

    std::cout << std::boolalpha;

    std::cout << "all(): " << all() << std::endl;
    std::cout << "all(true): " << all(true) << std::endl;
    std::cout << "all(true, true, true, false): " << all(true, true, true, false) << std::endl;

    string line;
    getline(cin, line);
}