#include "commandes.h"
#include <stdlib.h>
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <string.h>
#include <wchar.h>


void ls()
{
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFile(L"*", &findFileData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("Erreur lors de la recherche des fichier et dossier.\n");
		return;
	}

	do
	{
		if (wcscmp(findFileData.cFileName, L".") != 0 && wcscmp(findFileData.cFileName, L"..") != 0)
		{
			if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				wprintf(L"\x1B[32m%s\x1B[0m\n", findFileData.cFileName);
			}
			else
			{
				wprintf(L"\x1B[34m%s\x1B[0m\n", findFileData.cFileName);
			}
		}
	} while (FindNextFile(hFind, &findFileData) != 0);
	
	FindClose(hFind);
}

void cls()
{
	system("cls");
}

int cd(wchar_t* folder)
{
	wchar_t fullPath[MAX_PATH];

	int wchars_num = MultiByteToWideChar(CP_UTF8, 0, folder, -1, fullPath, MAX_PATH);

	if (wchars_num == 0)
	{
		wprintf(L"Erreur lors de la conversion en UTF-16 : %d\n", GetLastError());
		return 1;
	}

	if (folder[0] != L'\\' && folder[1] != L':')
	{
		wchar_t currentDir[MAX_PATH];
		if (GetCurrentDirectory(MAX_PATH, currentDir) == 0)
		{
			printf("Erreur lors de la recuperation du repertoire actuel : %d\n", GetLastError());
			return 1;
		}

		swprintf(fullPath, MAX_PATH, L"%s\\%s", currentDir, folder);
	}
	else
	{
		wcsncpy_s(fullPath, MAX_PATH, folder, _TRUNCATE);
	}


	if (SetCurrentDirectory(fullPath))
	{
		return 0;
	}
	else
	{
		wprintf("Erreur lors du changement de repertoire: %d\n", GetLastError());
		return 1;
	}
}