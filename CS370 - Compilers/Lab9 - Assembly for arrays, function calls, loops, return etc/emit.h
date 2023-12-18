/**
 * @file emit.h
 * @author Joey Troyer
 * @date 2022-04-26
 * @Lab  Lab9
 * @brief Declared methods and other definitions to be shared with source files
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef EMIT_H
#define EMIT_H

#include "AST.h"
#include "symtable.h"

#define WSIZE 4 // number of bytes in a word
#define LOGWSIZE 2 // number of shifts to get to WSIZE
#define FUNCTION_MIN_SIZE 2 //min function size
FILE * fp;

void EMITAST (struct ASTnode *p, FILE *fp);

void EMIT_Header (struct ASTnode *p, FILE *fp);

void EMIT_Global_Strings(struct ASTnode *p, FILE *fp);

void EMIT_Global_Variables(struct ASTnode *p, FILE *fp);

char * CreateLabel();

void EMIT_Write(struct ASTnode *p, FILE *fp);

void EMIT_Read(struct ASTnode *p, FILE *fp);

void EMIT_Ident (struct ASTnode *p, FILE *fp);

void EMIT_Expr (struct ASTnode *p, FILE *fp);

void EMIT_Assign(struct ASTnode *p, FILE *fp);

void EMIT_If(struct ASTnode *p, FILE *fp);

void EMIT_While(struct ASTnode *p, FILE *fp);

void EMIT_Call(struct ASTnode *p, FILE *fp);

void EMIT_Return(struct ASTnode *p, FILE *fp);

#endif //end EMIT.h

