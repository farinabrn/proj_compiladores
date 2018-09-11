/**<@lexer.c>::**/
#include <ctype.h>
#include <stdio.h>
#include <tokens.h>
#include <lexer.h>

void skipspaces(FILE * tape)
{
	int head;
	while( isspace(head = getc(tape)) );
	ungetc(head, tape);
}

char lexeme[MAXIDLEN+1];

/*
 * ID = [A-Za-z][_A-Za-z0-9]*
 */
int isID(FILE *tape)
{
	lexeme[0] = getc(tape);
	if (isalpha(lexeme[0])) {
		int i = 1;
		while(
		  isalnum(lexeme[i] = getc(tape))
		  ||
		  lexeme[i] == '_' // tem que tirar do meu essa merda de _
		) i++;
		ungetc(lexeme[i], tape);
		lexeme[i] = 0;
		return ID;
	}
	ungetc(lexeme[0], tape);
	return 0;
}

/* regex :
 * NUM = UINT | FLTP
 * UINT = [1-9][0-9]* | 0
 * FLTP = ( UINT'.'FRAC? | '.'FRAC ) EE? | UINT EE
 	FRAC =>TEM PELO MENOS UM DIGITO
 */

int isNUM(FILE *tape)
{
	int token = 0;
	int i;

	if (isdigit(lexeme[0] = getc(tape))) {
		if (lexeme[0] == '0') {
			i = 1;
		} else {
			for (i = 1;
				isdigit(lexeme[0] = getc(tape));
				i++
			);
			ungetc(lexeme[i], tape);
		}
		token = UINT;
		if((lexeme[i]=getc(tape)) == '.'){
			token = FLTP;
			i++;
			while(isdigit(lexeme[i] = getc(tape))) i++;
			ungetc(lexeme[i],tape);
		} else {
			ungetc(lexeme[i], tape);
		}
	} else if (lexeme[0] == '.') {
		if (isdigit(lexeme[1] = getc(tape))) {
			i = 2;
			token = FLTP;
			while(isdigit(lexeme[i] = getc(tape))) i++;
			ungetc(lexeme[i], tape);
		} else {
			ungetc(lexeme[1],tape);
			ungetc(lexeme[0],tape);
		}
		if(token){
			/*if we're here we have a NUM*/
			/** check if scientific notation **/
			int i0 = i;
			i = chkEE(i, tape);
			if (i > i0 && token == UINT) token = FLTP;
			lexeme[i] = 0;
			return token;
		}
	}

	/* epsilon transition is simulated here: */
	ungetc(lexeme[0], tape);
	return token;
}

int chkEE(int i, FILE* tape){
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
