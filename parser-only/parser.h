/* parser components */
void E(void);
void F(void);
int assgn(void);

/* lexer to parser interface */
extern int lookahead;
void match(int expected);
int gettoken(FILE *source_code);
/* main code input/output buffer declaration */
extern FILE *source_code;
extern FILE *object_code;

/** semantic actions are temporarily placed here:**/ //vm.h
void var_operation(char *, int);
void rvalue(double);
int SymTab_lookup(char *var_name);
void SymTab_insert(char *var_name);
void rvalue(double val);
void numoperation(int op);
void negate(void);