/* parser components */
void E(void);
void T(void);
void F(void);
void assgn(void);
void R(void);
void Q(void);
/* lexer to parser interface */
extern int lookahead;
void match(int expected);
int gettoken(FILE *source_code);
/* main code input/output buffer declaration */
extern FILE *source_code;
extern FILE *object_code;

