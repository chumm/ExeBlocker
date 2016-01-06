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
void menuValidation(char* user_choice);

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
		cout << "Current Blocked Exes\n";

		for (int i = 0; i < exesToBlock.size(); ++i)
		{
			cout << exesToBlock[i] + "\n";
		}
	}
}
void displayMenu(void)
{
	system("cls");
	cout << "1)Run Exe Blocker\n2)Add Blacklisted Exes\n3)Remove Blacklisted Exes\n4)Exit Program";
}

void menuValidation(char* user_choice)
{
	for (;;)
	{
		*user_choice = _getch();
		switch (*user_choice)
		{
		case 'y':
			return;
			break;
		case 'Y':
			return;
			break;
		case 'n':
			return;
			break;
		case 'N':
			return;
			break;
		default:
			break;
		}
	}
	return;
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
				break;
			case '2':
				addExes();
				break;
			case '3':
				removeExes();
				break;
			case '4':
				exitProgram();
				break;
		}
	}
	else
	{
	}

}
void addExes(void)
{ 
	for (;;)
	{
		system("cls");
		displayExes();

		char user_choice = ' ';
		cout << "Do you want to block an exe? Y/N?";
		menuValidation(&user_choice);
		if (user_choice == 'y' || user_choice == 'Y')
		{
			cout << "\nWrite exe name: ";
			std::string exeName = "";
			cin >> exeName;

			bool added_exe = false;
			std::string::size_type pos = exeName.find(".exe");
			if (pos == std::string::npos)
			{
				cout << "\nNo extension found, was this a mistake? Y/N";
				menuValidation(&user_choice);
				if (user_choice == 'y' || user_choice == 'Y')
				{
					exeName.append(".exe");
				}
				else
				{
					cout << "\nDo you still want to continue? Y/N";
					menuValidation(&user_choice);
					if (user_choice == 'y' || user_choice == 'Y')
					{
						added_exe = true;
					}
				}
			}
			else
			{
				added_exe = true;
			}
			if (added_exe == true)
			{
				exesToBlock.push_back(exeName);
				added_exe = false;
			}
		}
		else
		{
			cout << "\nDo you wish to exit? Y/N";
			menuValidation(&user_choice);
			if (user_choice == 'y' || user_choice == 'Y')
			{
				displayMenu();
				return;
			}
		}
	}
}
void removeExes(void){ system("cls"); }
void exitProgram(void){ system("cls"); }
void runBlockingExes(void)
{
	for (;;)
	{
		entry.dwSize = sizeof(PROCESSENTRY32);
		SleepEx(100, 0);
		snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		for (int i = 0; i < exesToBlock.size(); ++i)
		{
			if (Process32First(snapshot, &entry) == TRUE)
			{
				while (Process32Next(snapshot, &entry) == TRUE)
				{
					if (strcmp(entry.szExeFile, exesToBlock[i].c_str()) == 0)
					{
						CloseHandle(snapshot);
						snapshot = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

						#ifndef DEBUG
							OutputDebugStringA("\nTerminated ");
							OutputDebugStringA(exesToBlock[i].c_str());
						#endif

						TerminateProcess(snapshot, 9);
						CloseHandle(snapshot);

					}
				}
			}
		}
	}
}