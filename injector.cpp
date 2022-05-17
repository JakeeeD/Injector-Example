#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <iostream>
using namespace std;

DWORD get_process_id(string_view process_name) {
	HANDLE thSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (thSnapShot == INVALID_HANDLE_VALUE) {
		cout << "rip";
		return NULL;
	}
	PROCESSENTRY32 procEntry;
	procEntry.dwSize = sizeof(PROCESSENTRY32);

	do {
		if (process_name == procEntry.szExeFile) {
			return procEntry.th32ProcessID;
		}
	} while (Process32Next(thSnapShot, &procEntry));
	return NULL;
}

int main() {
	auto test_process_id = get_process_id("process.exe");
	if (!test_process_id) {
		cout << "Failed getting process id! Make sure .process. is running!";
		return 1;
	}
	cout << "process id: " << test_process_id << endl;
	auto process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, csgo_process_id);
	if (!process) {
		cout << "Failed opening handle to process!";
		return 1;
	}
	char full_path[MAX_PATH];
	GetFullPathName("test.dll", MAX_PATH, full_path, nullptr);
	const char* full_path = R"(yourpath ;))";
	cout << "full path name: " << full_path << endl;
	auto LoadLib = reinterpret_cast<LPTHREAD_START_ROUTINE>(GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA"));
	
	LPVOID RemoteString = VirtualAllocEx(process, nullptr, strlen(full_path), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE); /*Allocate space in the process for our DLL name*/

	WriteProcessMemory(process, RemoteString, full_path, strlen(full_path), nullptr); /* Write the string name of our DLL in the memory allocated*/

	auto thread = CreateRemoteThread(process, nullptr, 0, LoadLib, RemoteString, NULL, nullptr); 	/* Load our DLL by calling loadlibrary in the other process and passing our dll name*/
	if (!thread) {
		cout << "error: " << GetLastError();
	} else cout << hex << thread << '\n';
	cout << "done!";

	CloseHandle(process);
	
	char full_path[MAX_PATH];
	GetFullPathName("test.dll", MAX_PATH, full_path, nullptr);
}		cout << "Failed getting process id! Make sure .process. is running!";
	CloseHandle(process);
		}
	}	
}
