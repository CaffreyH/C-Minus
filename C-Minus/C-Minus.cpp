// C-Minus.cpp : �������̨Ӧ�ó������ڵ㡣
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
	printf("%s\n", "�����ɨ�貢���浽myresult.txt...");
	return 0;
}

