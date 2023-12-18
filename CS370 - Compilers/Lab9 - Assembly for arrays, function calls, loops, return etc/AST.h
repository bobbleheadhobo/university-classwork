/**
 * @file AST.h
 * @Lab  Lab9
 * @author Joey Troyer
 * @brief Declared methods and other definitions to be shared with source files
 * @date 2022-04-06
 */

#ifndef AST_H
#define AST_H

//enum which allows us to distiguish each node type
enum AST_Node_Type{
    A_SPACES,
    A_VARDEC,
    A_FUNDEC,
    A_PARAM,
    A_BLOCK,
    A_LOCALDEC,
    A_STMTLIST,
    A_EXPRSTMT,
    A_EXPR,
    A_BOOLEAN,
    A_NUMBER,
    A_IF,
    A_WHILE,
    A_RETURN,
    A_ASSIGN,
    A_IDENT,
    A_CALL,
    A_ARGSLIST,
    A_READ,
    A_WRITE
};//end of enum

//enum to know the type of variable, function or parameter
enum AST_Declared_Type{
    A_INT_TYPE,
    A_VOID_TYPE,
    A_BOOLEAN_TYPE
};

//enum to know to the operator type
enum AST_Operator_Type {
    A_EQ,
	A_LE,
	A_GE,
	A_NE,
    A_GT,
    A_LT, 
    A_PLUS,
    A_MINUS,
    A_TIMES,
    A_DIVIDE,
    A_AND,
    A_OR,
    A_NOT
};

//main structure of AST_H
struct ASTnode{
    enum AST_Node_Type MyType;
    enum AST_Declared_Type DeclType;
    enum AST_Operator_Type operator;
    enum AST_Declared_Type calculated_type;
    char *name;
    char *label;
    struct SymbTab *symbol;
    struct ASTnode *s1, *s2, *next;
    int size;
};

struct ASTnode *AST_Create_Node(enum AST_Node_Type);

void AST_Print (struct ASTnode *p, int indent);

void Print_Declared_Type(enum AST_Declared_Type DeclType);

void Print_Operator_Type(enum AST_Operator_Type operator);

int CompareFormals(struct ASTnode *p, struct ASTnode *q);


#endif //ast_h
