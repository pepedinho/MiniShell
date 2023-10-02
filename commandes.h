#pragma once
#include <wchar.h>

void ls();
int cd(wchar_t* folder);
void cls();
void help();
int cat(const wchar_t* filename);
int start(wchar_t* file);