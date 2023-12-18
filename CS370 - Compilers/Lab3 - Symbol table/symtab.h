/**
 * lab3
 * @file   symtab.h
 * @author Joey Troyer
 * @brief  Declared methods and other definitions to be shared with source files
 * @date   2022-01-31
 */

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#ifndef SYMTAB
#define SYMTAB

int size = 0;
struct SymbTab * Insert(char *symbol, int address);
void Display();
void Delete();
struct SymbTab * Search(char *mySymbol );
void Modify();

struct SymbTab {
    char *symbol;
    int addr;
    struct SymbTab *next;
};
struct SymbTab *first, *last;

#endif