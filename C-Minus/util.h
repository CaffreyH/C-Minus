#ifndef UTIL_H
#define UTIL_H

#include"globals.h"

#endif
extern FILE *listing;
extern FILE *source;
void printToken(TokensType token, char *tokenString)
{
	switch (token)
	{
	case IF:
	case INT:
	case ELSE:
	case VOID:
	case RETURN:
	case WHILE:
		fprintf(listing, "\treserved word:%s\n", tokenString);
		break;
	case ID:
		fprintf(listing, "\tID, name = %s\n", tokenString);
		break;
	case NUM:
		fprintf(listing, "\tNUM, val = %s\n", tokenString);
		break;
	case ASSIGN:
	case PLUS:
	case MINUS:
	case TIMES:
	case OVER:
	case LT:
	case LTP:
	case RT:
	case RTP:
	case EQUAL:
	case NEQUAL:
	case EQ:
	case SEMI:
	case COMMA:
	case LFKH:
	case RFLH:
	case LPAREN:
	case RPAREN:
	case LHKH:
	case RHKH:
	case LZS:
	case RLS:
		fprintf(listing, "\t%s\n", tokenString);
	}
}