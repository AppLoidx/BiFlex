#ifndef BIFLEX_INTERFACE_H__
#define BIFLEX_INTERFACE_H__

struct symbol {
    char *name;
    char type;
};


/* size of symtab*/

#define NHASH 9997
//struct symbol symtable__[NHASH];

struct symbol *lookup(char*, int);

/* list of symbols, for an argument list */
struct symlist {
    struct symbol *sym;
    struct symlist *next;
};

struct symlist *newsymlist(char *sym, struct symlist *next);
void symlistsettype(char type, struct symlist *sl);
void symlistfree(struct symlist *sl);

/* node types
 * ♂ P program root node
 * ♂ L list of declarations or statements
 * ♂ B boolean declaration
 * ♂ D decimal declaration
 * ♂ F loop for
 * ♂ I iterator
 * ♂ E iterator list
 * ♂ = assignment
 * ♂ + - * / & | ^ !
 * ♂ 1-3 comparison ops, bit coded 03 equal, 02 less, 01 greater
 * ♂ K number const
 * ♂ N symbol ref
 */

/* ♂Right♂ Nodes and A$$ (AST) */

struct ast
{
    int nodetype;

    struct ast *l;
    struct ast *r;
};

struct numval {
    int nodetype;			/* type K */
    int number;
};

struct symref {
    int nodetype;			/* type N */
    struct symbol *s;
};

struct symasgn {
    int nodetype;			/* type = */
    struct ast *s;          /* variable */
    struct ast *v;		    /* value */
};

struct declaration
{
    int nodetype;           /* type B or D */
    struct symlist *symlist;
};

struct ast *newcmp(int cmptype, struct ast *l, struct ast *r);
struct ast *newasgn(struct ast *s, struct ast *v);
struct ast *newref(char *s);
struct ast *newdeclar(char type, struct symlist *symlist);
struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newnum(int d);

void treefree(struct ast *);

void yyerror (char *s, ...);
extern int yylineno;
int yylex();
int yyparse();

int dumpast(struct ast * a, int level, const char * description);
void toAst(struct ast * a);

#endif
