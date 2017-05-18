#ifndef SCAN_H
#define SCAN_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "globals.h"           //input and output file
#include "util.h"			  //printToken ����
#endif

extern FILE* source;
extern FILE* listing;
extern FILE* code;

extern int lineno;
extern int TraceScan;
extern int EchoSource;

typedef enum
{
	START, INASSIGN, INCOMMENT, INNUM, INID, DONE,
}StateType;

char tokenString[MAXTOKENLEN + 1];
#define BUFLEN 256
#define EOF_FILE -1

static char lineBuf[BUFLEN];		//�洢һ��
static int linepos = 0;
static int bufsize = 0;
static int EOF_flag = false;   //  int Ҳ����ʹ��true��

static char getNextChar(void)		//��ȡ��һ���ǿ��ַ���lineBuf���˾�װ��һ��������
{
	if (!(linepos < bufsize))
	{
		lineno++;
		if (fgets(lineBuf, BUFLEN - 1, source))  //     fgets(_Out_writes_z_(_MaxCount) char * _Buf, _In_ int _MaxCount, _Inout_ FILE * _File)
			//                 ����ļ����������������ļ�ָ��
		{
			if (EchoSource)
			{
				fprintf(listing, "%4d:%s", lineno, lineBuf);
			}
			bufsize = strlen(lineBuf);
			linepos = 0;
			return lineBuf[linepos++];
		}
		else
		{
			EOF_flag = true;
			return EOF;
		}
	}
	else return lineBuf[linepos++];
}

static void ungetNextChar(void)
{
	if (!EOF_flag)
	{
		linepos--;
	}
}

static struct
{
	char* str;
	TokensType tok;
}reservedWords[MAXRESERVED]
= { { "if", IF }, { "else", ELSE }, { "int", INT }, { "return", RETURN }, { "void", VOID }, { "while", WHILE } };

static TokensType reservedLookup(char* s)
{
	int i;
	for (int i = 0; i < MAXRESERVED; i++)
	{
		if (!strcmp(s, reservedWords[i].str))           //strcmp��S1,S2��  S1 > S2 ����ֵ����0,S1 <S2 ����ֵС��0����ȷ���0
		{
			return reservedWords[i].tok;
		}
	}
	return ID;
}
TokensType getToken(void)
{
	int tokenStringIndex = 0;
	TokensType currentToken;
	StateType state = START;
	int save;
	while (state != DONE)
	{
		int c = getNextChar();
		save = true;
		switch (state)
		{
		case START:
			if (isdigit(c))
			{
				state = INNUM;
			}
			else if (isalpha(c))
			{
				state = INID;
			}
			else if (c == ':')
			{
				state = INASSIGN;
			}
			else if ((c == ' ') || (c == '\t') || (c == '\n'))
			{
				save = false;
			}
			else if (c == '/')
			{
				int next = getNextChar();
				if (next == '*')
				{
					save = false;
					state = INCOMMENT;
				}	
				else
				{
					currentToken = OVER;
				}
				ungetNextChar();
			}
			else
			{
				state = DONE;
				switch (c)
				{
				case EOF_FILE:
					save = false;
					currentToken = ENDFILE;
					break;

				case '+':
					currentToken = PLUS;
					break;
				case '-':
					currentToken = MINUS;
					break;
				case '*':
					currentToken = TIMES;
					break;
				case '/':
					currentToken = OVER;
					break;
				case '<':
					save = false;
					if (getNextChar() == '=')
					{
						tokenString[tokenStringIndex++] = '<';
						tokenString[tokenStringIndex++] = '=';
						currentToken = LTP;
					}
					else
					{
						currentToken = LT;
						tokenString[tokenStringIndex++] = '<';
					}
					break;
				case '>':
					save = false;
					if (char dydy =getNextChar() == '=')
					{
						tokenString[tokenStringIndex++] = '>';
						tokenString[tokenStringIndex++] = '=';
				
						currentToken = RTP;
					}
					else
					{
						currentToken = RT;
						tokenString[tokenStringIndex++] = '>';
					}
					break;
				case '=':
					
					if ( getNextChar() == '=')
					{
						tokenString[tokenStringIndex++] = '=';
						currentToken = EQUAL;
					}
					else
					{
						currentToken = EQ;
					}
					break;
				case '!':
					save = false;
					if (getNextChar() == '=')
					{
						tokenString[tokenStringIndex++] = '!';
						tokenString[tokenStringIndex++] = '=';
						currentToken = NEQUAL;
					}
					break;
				case ';':
					currentToken = SEMI;
					break;
				case ',':
					currentToken = COMMA;
					break;
				case '[':
					currentToken = LFKH;
					break;
				case ']':
					currentToken = RFLH;
					break;
				case '(':
					currentToken = LPAREN;
					break;
				case ')':
					currentToken = RPAREN;
					break;
				case '{':
					currentToken = LHKH;
					break;
				case '}':
					currentToken = RHKH;
					break;
	
				default:
					currentToken = ERROR;
					break;
				}
			}
			break;

		case INCOMMENT:
			save = false;
			if (c == EOF)
			{
				state = DONE;
				currentToken = ENDFILE;
			}
			else if (c == '*')
			{
				int next = getNextChar();
				save = false;
				if (next == '/')
				{
					state = START;
				}
				else
				{
					ungetNextChar();
				}
			}
			break;
		case INASSIGN:
			state = DONE;
			if (c == '=')
			{
				currentToken = ASSIGN;
			}
			else
			{
				ungetNextChar();
				save = false;
				currentToken = ERROR;
			}
			break;
		case INNUM:
			if (!isdigit(c))
			{
				ungetNextChar();
				save = false;
				state = DONE;
				currentToken = NUM;
			}
			break;
		case INID:
			if (!isalpha(c))
			{
				ungetNextChar();
				save = false;
				state = DONE;
				currentToken = ID;
			}
			break;
		case DONE:
		default:
			fprintf(listing, "Scanner Bug:state=%d\n", state);
			state = DONE;
			currentToken = ERROR;
			break;
		}
		if ((save) && (tokenStringIndex <= MAXTOKENLEN))
		{
			tokenString[tokenStringIndex++] = (char)c;
		}
		if (state == DONE)
		{
			tokenString[tokenStringIndex] = '\0';
			if (currentToken == ID)
			{
				currentToken = reservedLookup(tokenString);
			}
		}
	}
	if (TraceScan)
	{
		fprintf(listing, "\t%d:", lineno);
		printToken(currentToken, tokenString);
	}

	return currentToken;
}