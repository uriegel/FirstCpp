#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <chrono>
#ifdef WINDOWS
#include <Windows.h>
#endif
#include <thread>

using namespace std;
using namespace filesystem;

uintmax_t ComputeFileSize(const path& pathToCheck) {
	if (exists(pathToCheck) && is_regular_file(pathToCheck)) {
		auto err = error_code{};
		auto filesize = file_size(pathToCheck, err);
		if (filesize != static_cast<uintmax_t>(-1))
			return filesize;
	}

	return static_cast<uintmax_t>(-1);
}

template <typename TP>
time_t to_time_t(TP tp)
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
              + system_clock::now());
    return system_clock::to_time_t(sctp);
}

void DisplayFileInfo(const directory_entry& entry, string& lead, path& filename) { 

    auto ftime = last_write_time(entry);
    time_t cftime = to_time_t(ftime);
	cout << lead << " " << filename << ", "  << ComputeFileSize(entry) << ", time: " << asctime(localtime(&cftime));
}

void DisplayDirectoryTree(const path& pathToShow, int level) {
	if (exists(pathToShow) && is_directory(pathToShow)) {
		auto lead = string(level * 3, ' ');
		for (const auto& entry : directory_iterator(pathToShow)) {
			auto filename = entry.path().filename();
			// if (is_directory(entry.status())) {
			// 	cout << lead << "[+] " << filename << "\n";
			// 	DisplayDirectoryTree(entry, level + 1);
			// 	cout << "\n";
			// }
			if (is_regular_file(entry.status()))
			 	DisplayFileInfo(entry, lead, filename);
			else {
#ifdef WINDOWS                
                wstring tst{filename};
          		wcout << L"   " << L" [?]" << tst << L"\n";
#else            
		    	cout << lead << " [?]" << filename << "\n";
#endif
            }
		}
	}
}

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
    test_windows();
#endif

    auto helloworld {"Hallöchen Wörlt👶"s};

    cout << helloworld << ", " << helloworld.length() << endl;

    vector<string> msg {"Hello", "C++", "World", "from", "VS Code!"};

    for (const string& word : msg)
        cout << word << " ";
    cout << endl;

    cout << boolalpha;

    cout << "all(): " << all() << endl;
    cout << "all(true): " << all(true) << endl;
    cout << "all(true, true, true, false): " << all(true, true, true, false) << endl;
#ifdef WINDOWS
    path root{R"(A:\Ubuntu\test🤣)"s};
#else
    path root{"/home/uwe/test🙀"s};
#endif


    cout << "exists() = " << exists(root) << "\n"
     << "root_name() = " << root.root_name() << "\n"
     << "root_path() = " << root.root_path() << "\n"
     << "relative_path() = " << root.relative_path() << "\n"
     << "parent_path() = " << root.parent_path() << "\n"
     << "filename() = " << root.filename() << "\n"
     << "stem() = " << root.stem() << "\n"
     << "extension() = " << root.extension() << "\n";
#ifdef WINDOWS
        DisplayDirectoryTree(R"(A:\Ubuntu)"s, 0);
#else
    DisplayDirectoryTree("/home/uwe"s, 0);
#endif
    string line;
    getline(cin, line);
}