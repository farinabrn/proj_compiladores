#include <ctype.h>
#include <stdio.h>
#include <tokens.h>
//#include <lexer.h>

void skipspaces(FILE * tape)
{
	int head;
	while( isspace(head = getc(tape)) );
	ungetc(head, tape);
}
/*
 * ID = [A-Za-z][_A-Za-z0-9]*
 */
#define 	MAXIDLEN	64
char ID_postfix[MAXIDLEN];
int isID(FILE *tape)
{
	int head = getc(tape);
	if (isalpha(head)) {
		while(
		  isalnum(head = getc(tape))
		  || head == '_'
		);
		ungetc(head, tape);
		return ID;
	}
	ungetc(head, tape);
	return 0;
}
/*
 * NUM = [1-9][0-9]* | 0
 */
#define 	MAXDECLEN	12
char NUM_postfix[MAXDECLEN];
int isNUM(FILE *tape)
{
	int head = getc(tape);
	int i = 0;

	if ( '0' <= head && head <= '9' ) {
		NUM_postfix[i] = head;
		i++;
		if (head == '0') {
			NUM_postfix[i] = 0;
			return NUM;
		}
		while ( '0' <= (head = getc(tape))
			&& 
			head <= '9' ){
			NUM_postfix[i] = head;
			i++;
		}
		NUM_postfix[i] = 0;
		ungetc(head, tape);
		return NUM;
	}
	/* epsilon transition is simulated here: */
	ungetc(head, tape);
	return 0;
}

int gettoken(FILE *tape)
{
	int token;
	skipspaces(tape);
	if ( token = isID(tape) ) return token;
	if ( token = isNUM(tape) ) return token;
	return getc(tape);
}
