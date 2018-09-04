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
int isNUM(FILE *tape)
{
	int head = getc(tape);

	if ( '0' <= head && head <= '9' ) {
		if (head == '0') {
			return NUM;
		}
		while ( '0' <= (head = getc(tape))
			&& 
			head <= '9' );
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
