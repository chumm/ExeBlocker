#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#pragma comment(linker, "/Merge:.rdata=.text")
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
const char* blacklisted_exes[3] = { "steamwebhelper.exe", "TSVNCache.exe", "SpotifyHelper.exe" };
PROCESSENTRY32 entry;
HANDLE snapshot;
int  _WinMain()
{
	for (;;)
	{
		entry.dwSize = sizeof(PROCESSENTRY32);
		SleepEx(100, 0);
		snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		for (int i = 0; i < 3; ++i)
		{
			if (Process32First(snapshot, &entry) == TRUE)
			{
				while (Process32Next(snapshot, &entry) == TRUE)
				{
					if (lstrcmpA(entry.szExeFile, blacklisted_exes[i]) == 0)
					{
						CloseHandle(snapshot);
						snapshot = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

						#ifndef DEBUG
						OutputDebugStringA("\nTerminated ");
						OutputDebugStringA(blacklisted_exes[i]);
						#endif

						TerminateProcess(snapshot, 9);
						CloseHandle(snapshot);

					}
				}
			}
		}
	}

	return 0;
}
