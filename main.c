#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include <wchar.h>
#include "commandes.h"

int main(int argc, char* argv[])
{
	
	
	int quit = 0;
	char entry[100];

	while (!quit)
	{
		wchar_t cwd[MAX_PATH];
		if (GetCurrentDirectory(MAX_PATH, cwd) != 0)
		{
			char* command = NULL;
			wchar_t* arguments = NULL;
			char* context = NULL;
			wprintf(L"%ls>", cwd);

			if (fgets(entry, sizeof(entry), stdin))
			{
				size_t len = strlen(entry);
				if (len > 0 && entry[len - 1] == '\n')
				{
					entry[len - 1] = '\0';// suppression du caractéer de fin indésirable

					
					command = strtok_s(entry, " ", &context);// recuperation de la cmmande
					arguments = strtok_s(NULL, " ", &context);// recuperation de l'argument
				}
				if (entry[0] == '\0') //l'utilsateur appuie sur entré sans avoir ecrit
				{
					wprintf(L"%ls>", cwd);
				}
				else if (arguments == NULL)
				{
					if (strcmp(command, "ls") == 0)
					{
						ls();
					}
					else if (strcmp(command, "cls") == 0)
					{
						cls();
					}
					else if (strcmp(command, "help") == 0)
					{
						help();
					}
					else if (strcmp(command, "cd") == 0)
					{
						printf("Commande 'cd' mal formulée. Utilisation : cd <nom_du_dossier>\n");
					}
				}
				else if (arguments != NULL)
				{
					int wchars_num = MultiByteToWideChar(CP_UTF8, 0, arguments, -1, NULL, 0);
					if (wchars_num > 0)
					{
						wchar_t* arguments_w = (wchar_t*)malloc(wchars_num * sizeof(wchar_t));
						if (arguments_w != NULL)
						{
							if (MultiByteToWideChar(CP_UTF8, 0, arguments, -1, arguments_w, wchars_num) > 0)
							{
								if (strcmp(command, "cd") == 0)
								{
									if (cd(arguments_w) != 0)
									{
										perror("Erreur lors du changement de repertoire");
									}
								}
								else if (strcmp(command, "cat") == 0)
								{
									if (cat(arguments_w) != 0)
									{
										perror("Erreur lors de l'ouverture du fichier");
									}
								}
								else if (strcmp(command, "run") == 0)
								{
									if (start(arguments_w) != 0)
									{
										perror("Erreur lors de l'execution du fichier");
									}
								}
							}
							free(arguments_w);
						}
					}	
					else
					{
						perror("Erreur lors de la conversion des arguments en UTF-16");
						return 1;
					}
				}		
				
			}
			else
			{
				perror("Erreur lors de la lecture de l'entré utilisateur");
				return 1;
			}
		}
		else
		{
			perror("Erreur lors de la réccupération du répertoir actuel");
			return 1;
		}
	}
	return 0;
}