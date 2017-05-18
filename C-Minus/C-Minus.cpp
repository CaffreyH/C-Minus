// C-Minus.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "globals.h"
#include "scan.h"


int _tmain(int argc, _TCHAR* argv[])
{
	fprintf(listing, "%s\n", "*****************************************");
	fprintf(listing, "%s\n", "C-Minus Lexical Analazer Result:");
	fprintf(listing, "%s\n", "*****************************************");
	fprintf(listing, "\n");
	TokensType token;
	do
	{
		token = getToken();
	} while (token != ENDFILE);
	fprintf(listing, "\t%s\n", "EOF");
	fclose(listing);
	printf("%s\n", "已完成扫描并保存到myresult.txt...");
	return 0;
}

