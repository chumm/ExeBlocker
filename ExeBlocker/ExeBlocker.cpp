#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#pragma comment(linker, "/Merge:.rdata=.text")
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
using std::cout;
using std::cin;

PROCESSENTRY32 entry;
HANDLE snapshot;
std::vector<std::string> exesToBlock;

void runBlockingExes(void);
void addExes(void);
void removeExes(void);
void exitProgram(void);
void displayExes(void);
void displayMenu(void);
void menuInput(void);


int  _WinMain()
{
	displayMenu();
	for (;;)
	{
		SleepEx(500,false);
		menuInput();
	}
	return 0;
}

void displayExes(void)
{
	if (!(exesToBlock.size() == -0))
	{
		cout << "Current Blocked Exes: ";

		for (int i = 0; i < exesToBlock.size(); ++i)
		{
			cout << exesToBlock[i] + "\n";
		}
	}
}
void displayMenu(void)
{
	cout << "1) Run Exe Blocker\n2)Add Blacklisted Exes\n3)Remove Blacklisted Exes\n4)Exit Program";
}

void menuInput(void)
{
	char user_choice = ' ';
	user_choice = _getch();
	if (user_choice != ' ' && isalpha(user_choice) == false)
	{
		switch (user_choice)
		{
			case '1':
				runBlockingExes();
			case '2':
				addExes();
			case '3':
				removeExes();
			case '4':
				exitProgram();
		}
	}
	else
	{
	}

}
void addExes(void)
{ 
	system("cls");
	cout << "Current blocked Exes:\n";
	displayExes();

	char user_choice = ' ';
	cout << "Do you want to block an exe? Y/N?";
	user_choice = _getch();
	if (user_choice == 'y' || user_choice == 'Y')
	{
		cout << "Write exe name: ";
		cin >> 
	}
	else
		return;
}
void removeExes(void){ system("cls"); }
void exitProgram(void){ system("cls"); }
void runBlockingExes(void){ system("cls"); }
//		{
//			for (;;)
//			{
//				entry.dwSize = sizeof(PROCESSENTRY32);
//				SleepEx(100, 0);
//				snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
//
//				for (int i = 0; i < 3; ++i)
//				{
//					if (Process32First(snapshot, &entry) == TRUE)
//					{
//						while (Process32Next(snapshot, &entry) == TRUE)
//						{
//							if (lstrcmpA(entry.szExeFile, blacklisted_exes[i]) == 0)
//							{
//								CloseHandle(snapshot);
//								snapshot = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
//
//#ifndef DEBUG
//								OutputDebugStringA("\nTerminated ");
//								OutputDebugStringA(blacklisted_exes[i]);
//#endif
//
//								TerminateProcess(snapshot, 9);
//								CloseHandle(snapshot);
//
//							}
//						}
//					}
//				}
//			}
//		}