/**@<parser.c>::**/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tokens.h>
#include <parser.h>
#include <lexer.h>

/* LL(1) recursive topdown parser
 *
 * E ->  T { oplus T }
 *
 * T ->  F { otimes F }
 *
 * F ->  ID | UINT | FLTP | ( E )
 *
 */

void E(void) {
	/**/int otimes = 0, oplus = 0, isnegate = 0/**/;

	/** ['+''-'] **/

	switch(lookahead) {
		case'+':
			match('+');
			break;
		case'-':
			isnegate = 1;
			match('-');
			break;

	}
T_entry:

F_entry:

	F();

	/**/
	if (isnegate) {
		negate();
		isnegate = 0;
	}

	if (otimes) {
		numoperation(otimes);
		otimes = 0;
	}

	if (oplus) {
		numoperation(oplus);
		oplus = 0;
	}
	/**/


	if ( lookahead == '*' || lookahead == '/' ) {
		otimes = lookahead;
		match(otimes);
		goto F_entry;
	}

	if ( lookahead == '+' || lookahead == '-' ) {
		oplus = lookahead;
		match(oplus);
		goto T_entry;
	}

}
/*
 * F ->  ID assgn
 *     | NUM
 *     | ( E )
 */
void F(void)
{
	/**/int var_access/**/
	/**/char var_name[MAXIDLEN]/**/
	switch(lookahead){
	   case ID:
	   /**/strcpy(var_name,lexeme)/**/;
		match(ID); /**/var_access =/**/ assgn();
		/**/var_operation(var_name, var_access)/**/
		break;
	   case UINT:
	   case FLTP:
	    //match(FLTP);
	   /**/rvalue(atof(lexeme))/**/;
	   	match(lookahead);
	   	break;
	   default:
		match('('); E(); match(')');
	}
}
/*
 * assgn ->  = E
 *         | <>
 */

int assgn(void)
{
	if (lookahead == '=') {
		match('='); E();
	} else {
		;
	}
}

int lookahead;

void match (int expected_token)
{
	if (expected_token == lookahead) {
		lookahead = gettoken(source_code);
	} else {
		fprintf(stderr,
		"token mismatch... exiting\n");
		exit(-2);
	}
}

#define STACKSIZE	128
double acc = 0;
double stack[STACKSIZE];
int stack_top = -1;

#define SYMTABSIZE	1024
char SymTab[SYMTABSIZE][MAXIDLEN+1];
double SymTab_memory[SYMTABSIZE];
int SymTab_nextEntry = 0;

enum {
	RVALUE = 0, //RECALL
	LVALUE,		//STORE
};

void var_operation(char * var_name, int var_access) {
	int address = SymTab_lookup(var_name);
	if (address < 0) {
		SymTab_insert(var_name);
	}

	if (var_access == LVALUE) {
		/** lvalue **/
		SymTab_memory[address] = acc; // store
	} else {
		rvalue(SymTab_memory[address]); 
	}
}

void rvalue(double val) {
	stack[++stack_top] = acc;
	acc = val;
}

void numoperation(int op) {
	switch(op) {
		case '+':
			acc = stack[stack_top--] + acc;
			break;
		case '-':
			acc = stack[stack_top--] - acc;
			break;
		case '*':
			acc = stack[stack_top--] * acc;
			break;
		case '/':
			acc = stack[stack_top--] / acc;
			break;
	}
}

void SymTab_insert(char *varname) {
	strcpy(SymTab[SymTab_nextEntry], varname);
	SymTab_nextEntry++;
}

void SymTab_lookup(char *varname) { // onde estiver indice de array deve haver comentarios
	int i;
	for (i = 0; i < SymTab_nextEntry; i++){
		if (strcmp(SymTab[i], varname) == 0) {
			return i;
		}
	}
	return -1;
}

void negate(void) {
	acc *= -1;
}