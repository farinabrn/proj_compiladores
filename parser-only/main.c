#include <stdio.h>
#include <main.h>

FILE *source_code;

int main(void)
{
	source_code = stdin;

	lookahead = gettoken(source_code);

	E();

	return 0;
}
