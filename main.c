#include <stdio.h>
#include <main.h>

FILE *source_code, *object_code;

int main(void)
{
	source_code = stdin;
	object_code = stdout;

	lookahead = gettoken(source_code);

	E();

	printf("\n");

	return 0;
}
