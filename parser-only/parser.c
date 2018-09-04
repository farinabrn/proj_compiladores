#include <stdlib.h>
#include <stdio.h>
#include <tokens.h>
#include <parser.h>

/* LL(1) parser for a simple expression grammar
 *
 * Recalling, the LR(1) grammar is written as 
 *
 * E ->  E (+) T
 *     | T
 * T ->  T (*) F
 *     | F
 * F ->  NUM
 *     | ( E )
 *
 * Its easy to conclude that
 *
 * E =>* T (+) T ... (+) T
 *
 * R =>*  (+) T ... (+) T
 *
 * Thus,
 *
 * R ->  (+) T R
 *     | <>
 *
 * and, consequently:
 *
 * E ->  T R
 *
 * The same conclusion serves to T and F:
 *
 * T ->  F Q
 *
 * Q ->  (*) F Q
 *     | <>
 *
 * Gathering all of above, we find the LL(1) form
 * for expressions:
 *
 * E ->  T R
 * T ->  F Q
 * R ->  (+) T R
 *     | <>
 * Q ->  (*) F Q
 *     | <>
 * F ->  NUM
 *     | ( E )
 */

/*
 * E ->  T R
 */
void E(void) { T(); R(); }
/*
 * T ->  F Q
 */
void T(void) { F(); Q(); }
/*
 * R ->  (+) T R
 *     | <>
 */
/*
 * F ->  ID assgn
 *     | NUM
 *     | ( E )
 */
void F(void)
{
	switch(lookahead){
	   case ID:
		match(ID); assgn();
		break;
	   case NUM:
		match(NUM);
		break;
	   default:
		match('('); E(); match(')');
	}
}
/*
 * assgn ->  = E
 *         | <>
 */
void assgn(void)
{
	if (lookahead == '=') {
		match('='); E();
	} else {
		;
	}
}
void R(void)
{
	if ( lookahead == '+' || lookahead == '-' ) {
		int oplus = lookahead;
		match(oplus); T(); R();
	} else {
		;
	}
}
/*
 * Q ->  (*) F Q
 *     | <>
 */
void Q(void)
{
	if ( lookahead == '*' || lookahead == '/' ) {
		int otimes = lookahead;
		match(otimes); F(); Q();
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
