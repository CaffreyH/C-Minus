#ifndef GLOBALS_H
#define GLOBALS_H

#include<stdio.h>
#define MAXRESERVED 6
#define MAXTOKENLEN 50

int lineno = 0;
int EchoSource = false;
int TraceScan = true;

FILE *source = fopen("../test/example.c-", "r");
FILE *listing = fopen("../test/myresult.txt", "w+");

//char tokenString[MAXTOKENLEN + 1];

enum TokensType
{
	ENDFILE, ERROR,
	IF, ELSE, RETURN, INT, VOID, WHILE, ASSIGN,
	ID, NUM,
	PLUS, MINUS, TIMES, OVER, LT, LTP, RT, RTP, EQUAL, NEQUAL, EQ, SEMI, COMMA, LFKH, RFLH, LPAREN, RPAREN, LHKH, RHKH, LZS, RLS
};
#endif
