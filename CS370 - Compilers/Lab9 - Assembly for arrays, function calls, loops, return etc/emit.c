/**
 * @file emit.c
 * @author Joey Troyer
 * @date 2022-04-29
 * @Lab  Lab9
 * @brief Program that that uses a pointer to an astnode. 
 *        Depending on the case in the ast it will output 
 *        formatted MIPS code to the designated output file.
 * 
 *        GRADE REQUEST
 *        GREADE REQUEST
 *        Requesting to be graded at level E
 *        E) Can do a-d and handle function calls
 * 
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "AST.h"
#include "emit.h"

int GLABEL= 0;        /* Global Label counter */
char *function_name;  /* Global name of current function */



//PRE: Strings to print formatted
//POST: outputs formatted mips code
void emit(char *label, char *command, char *comment, FILE *fp){
    if(strcmp(label,"") == 0) {
        if(strcmp(comment, "") == 0)
            //label and comment are empty
            fprintf(fp, "\t\t%-25s\n", command);
        else
            //label empty comment full
            fprintf(fp, "\t\t%-25s#%s\n", command, comment);
    }
    else {//label has comment
        if(strcmp(comment, "") == 0)
            //label full and comment empty
            fprintf(fp, "%s:\t%-25s\n", label, command);
        else
            //label and comment full
            fprintf(fp, "%s:\t%-25s#%s\n", label, command, comment);
    }
}//end emit



//PRE: ptr to AST and ptr to outputfile
//POST: .data and start of .text segment for the mips code
//      All strings go in the .data section and all global 
//      variables go above the .text
void EMIT_Header(struct ASTnode *p, FILE *fp) {

    fprintf(fp,".data # start of the DATA section, strings first\n\n");

    //find all strings
    EMIT_Global_Strings(p, fp);

    fprintf(fp,"_NL: .asciiz \"\\n\"# New line\n");
    fprintf(fp,".align 2 # start all of global variables aligned\n\n");

    //find all variables at level 0
    EMIT_Global_Variables(p, fp);

    fprintf(fp,"\n.text\n");
    fprintf(fp,"\n.globl main\n\n");
}//end EMIT_Header



//PRE: ptr to A_FUNDEC and ptr to output file
//POST: output mips code to the designated file which will store 
//      the return address and stack pointer then do all the statments
//      inside the function. After the statments we reset the sp and ra 
//      to what we stored at the start of the function. If in main we 
//      end the whole program
void EMIT_Function(struct ASTnode *p, FILE *fp){
    char s[100];

    //save function name everytime entering a new function
    //needed if returning in main
    function_name = p->name;
    
    emit(p->name,"", "Start of Function", fp);
    
    sprintf(s, "subu $t0 $sp %d", p->symbol->mysize * WSIZE);
    emit("", s,"set up $t0 to be the new spot for SP", fp);

    emit("", "sw $ra ($t0)","Store the return address", fp);
    emit("","sw $sp 4($t0)", "Store the old stack pointer", fp);
    emit("", "move $sp $t0", "set the stack pointer to the new value\n", fp);

    //do all the statments in the function
    EMITAST(p->s2, fp);

    emit("", "li $v0 0", "return NULL", fp);
    emit("", "lw $ra ($sp)", "reset the return address", fp);
    emit("", "lw $sp 4($sp)", "reset stack pointer\n", fp);

    //if in main end the whole program
    if(strcmp(p->name, "main") == 0){
        emit("", "li $v0, 10", "set up end of main function", fp);
        emit("", "syscall", "end main function", fp);
    }//end if
    else { 
        //jump back to function it was called from
        emit("", "jr $ra", "jump back to function\n", fp);
    }//end else
}//end EMIT_Function_Head



//PRE: ptr to AST and ptr to output file
//POST Switch statment that handles all of the statment 
//     in a the program. For each case it will call the 
//     coresponding function and move on the next connection 
//     in the node
void EMITAST (struct ASTnode *p, FILE *fp){
    if(p == NULL)
        return;

    //every statment is next connected
    switch(p->MyType) {

        case A_VARDEC: //taken care of in EMIT_Global_Variables
            EMITAST(p->next, fp);
            break;

        case A_FUNDEC: 
            EMIT_Function(p, fp);
            EMITAST(p->next, fp);
            break;

        case A_BLOCK:
            EMITAST(p->s2, fp);
            EMITAST(p->next, fp);
            break;

        case A_WRITE:
            EMIT_Write(p, fp);
            EMITAST(p->next, fp);
            break;

        case A_READ:
            EMIT_Read(p, fp);
            EMITAST(p->next, fp);
            break;

        case A_ASSIGN:
            EMIT_Assign(p, fp);
            EMITAST(p->next, fp);
            break;

        case A_IF:
            EMIT_If(p, fp);
            EMITAST(p->next, fp);
            break;

        case A_WHILE:
            EMIT_While(p, fp);
            EMITAST(p->next, fp);
            break;

        case A_EXPRSTMT:
            EMIT_Expr(p->s1, fp);
            EMITAST(p->next, fp);
            break;

        case A_RETURN:
            EMIT_Return(p, fp);
            EMITAST(p->next, fp);
            break;

        default:
            printf("EMITAST UNKNOWN TYPE  [%s]  ERROR! ERROR! ERROR!", p->MyType);
            exit(1);
    }//end MyType switch
}//end EMITAST



//PRE: ptr to astnode A_VARDEC and ptr to output file
//POST: prints all global variable and space allocated for each
void EMIT_Global_Variables(struct ASTnode *p, FILE *fp){
    //base case
    if(p == NULL)
        return;

    //find all global variable declaration 
    if(p->MyType == A_VARDEC && p->symbol->level == 0) {
        fprintf(fp, "%s: .space %-5d   # define a global variable\n", p->name, p->symbol->mysize * WSIZE);
    }//end if

    //recurse through the tree
    EMIT_Global_Variables(p->next, fp);
    EMIT_Global_Variables(p->s1, fp);

}//end EMIT_Global_Variables



//PRE: ptr to astnode A_WRITE and ptr to output file
//POST: prints all global strings and their label
void EMIT_Global_Strings(struct ASTnode *p, FILE *fp){
    //base case
    if(p == NULL)
        return;

    //find all the strings in the file
    if(p->MyType == A_WRITE && p->name != NULL) {
        fprintf(fp, "%s: .asciiz %s   # define a global string\n", p->label, p->name);
    }//end if

    //recurse through the tree
    EMIT_Global_Strings(p->next, fp);
    EMIT_Global_Strings(p->s1, fp);
    EMIT_Global_Strings(p->s2, fp);

}//end EMIT_Global_Strings



//PRE: none
//POST: creates unique labels for all 
//      strings and other statments
char * CreateLabel()
{    char hold[100];
     char *s;
     sprintf(hold,"_L%d",GLABEL++);
     s = strdup(hold);
     return (s);
}//end CreateLabel



//PRE: ptr to astnode A_EXPR and ptr to the output file
//POST: saves result of expression in $a0
void EMIT_Expr (struct ASTnode *p, FILE *fp) {
    //needed to catch any null connections that could 
    //be sent while recursing through the tree
    if(p == NULL)
        return;

    char s[100];

    // switch for base cases
    switch (p->MyType) {
        case A_NUMBER: 
            sprintf(s ,"li $a0 %d", p->size);
            emit("",s ,"load a number for expression", fp);
            return;
        break;

        case A_IDENT:
            EMIT_Ident(p, fp);
            emit("", "lw $a0 ($a0)", "load from memory location", fp);
            return;
        break;

        case A_BOOLEAN:
            sprintf(s, "li $a0, %d", p->size);
            emit("", s, "expression boolean", fp);
            return;
        break;

        case A_CALL:
            EMIT_Call(p, fp);
            return;
        break;
    }//end switch


    //will run anytime there is an expression involving an operator
    //stores LHS in $a0 
    //stores RHS in $a1
    EMIT_Expr(p->s1, fp);
    sprintf(s, "sw $a0, %d($sp)", p->symbol->offset * WSIZE);
    emit("", s, "Store left hand side in memory at sp + offset", fp);
    EMIT_Expr(p->s2, fp);
    emit("", "move $a1, $a0", "move right hand side to a1", fp);
    sprintf(s,"lw $a0 %d($sp)", p->symbol->offset * WSIZE);
    emit("", s, "fetch left hand side from memory", fp);
    

    //switch for operators
    switch(p->operator){
              case A_PLUS:
                emit("", "add $a0, $a0, $a1", "add numbers and store in a0", fp);
              break;

              case A_MINUS:
                emit("", "sub $a0, $a0, $a1", "subtract numbers and store in a0", fp);
              break;

              case A_TIMES:
                emit("", "mult $a0 $a1", "multiply the two numbers", fp);
                emit("", "mflo $a0", "move from high to low", fp);
              break;

              case A_DIVIDE:
                emit("", "div $a0 $a1", "divide the two numbers", fp);
                emit("", "mflo $a0", "divide", fp);
              break;

              case A_EQ:
                emit("", "seq $a0, $a0, $a1", "expression equal", fp);
              break;

              case A_LT:
                emit("", "slt $a0, $a0, $a1", "expression less than", fp);
             break;

              case A_LE:
                emit("", "sle $a0 ,$a0, $a1", "expression less than or equal", fp);
             break;

             case A_GT:
                emit("", "sgt $a0, $a0, $a1", "expresion greater than", fp);
             break;

             case A_GE:
                emit("", "sge $a0, $a0, $a1", "expression greater than or equal", fp);
             break;

             case A_NE:
                emit("", "sne $a0, $a0, $a1", "expression not equal", fp);
             break;

             case A_AND:
                emit("", "and $a0, $a0, $a1", "logical and", fp);
             break;

             case A_OR:
                emit("", "or $a0, $a0, $a1", "logical or", fp);
             break;

             case A_NOT:
                emit("", "not $a1, $a0", "ones compliment", fp);
                emit("", "add $a1, $a1 1", "if we were 0 we are now 0", fp);
                emit("", "srl $a0, $a0 31", "extract sign bit", fp);
                emit("", "srl $a1, $a1 31", "extract sign bit of neg", fp);
                emit("", "or $a0, $a0 $a1", "result 0 if was 0 otherwise a 1", fp);
                emit("", "xor $a0, $a0 1", "flips the bit to get not\n", fp);
             break;
        }//end switch for operators
}//end EMIT_EXPR



//PRE: ptr to astnode A_IDENT and ptr to the output file
//POST: direct memory address of variable in $a0
//      works with global, local, scalar and array
void EMIT_Ident (struct ASTnode *p, FILE *fp) {
    char s[100];

    if(p->s1 != NULL) { //array
        //calculate offset of array index
        EMIT_Expr(p->s1, fp);
        sprintf(s, "sll $t1, $a0 %d", LOGWSIZE);
        emit("", s, "multiply expression by 4", fp);
    }//end if
    
    if (p->symbol->level == 0){ //global var
        //load memory address of global variable into $a0
        sprintf(s,"la $a0 %s", p->name);
        emit("",s,"load global variable address in EMIT_Ident", fp);
    }
    else{ //local var
        //set $a0 to stack ptr + offset of variable
        sprintf(s, "li $a0 %d", p->symbol->offset * WSIZE);
        emit("", s, "get the local var offset", fp);
        emit("", "add $a0, $a0, $sp", "direct memory address of var", fp);
        }

    if(p->s1 != NULL){ //if array 
        //add extra offset of array index to the memory location
        emit("", "add $a0, $a0, $t1", "direct memory address of array index", fp);
    }

    fprintf(fp, "\n");
}//end emit_ident



//PRE: ptr to astnode A_WRITE and ptr to the output file
//POST: prints string or number to terminal
void EMIT_Write(struct ASTnode *p, FILE *fp){
    char s[100];
    if(p->name != NULL){//Prints a string
                emit("", "li $v0, 4", "set up write string", fp);
                sprintf(s, "la $a0, %s", p->label);
                emit("", s, "fetch the string", fp);
                emit("", "syscall", "print the string", fp);
            }
            else{//Prints an expression
                EMIT_Expr(p->s1, fp);
                emit("", "li $v0 1", "set up the write number", fp);
                emit("", "syscall", "print the write statment", fp);
            }

    fprintf(fp, "\n");
}//end EMIT_Write



//PRE: ptr to astnode A_READ and ptr to the output file
//POST: reads in number from user and stores it in $a0
void EMIT_Read(struct ASTnode *p, FILE *fp){
    //get memory address of variable
    EMIT_Ident(p->s1, fp);

    //read number from user
    emit("", "li $v0, 5", "set up read number", fp);
    emit("", "syscall", "read number", fp);

    //store user input in $a0
    //parenthesis dereference memory address
    emit("", "sw $v0, ($a0)", "store input in $a0", fp);

    fprintf(fp, "\n");
}//end EMIT_Read



//PRE: ptr to astnode A_ASSIGN and ptr to the output file
//POST: store the value on RHS into the variable in LHS
void EMIT_Assign(struct ASTnode *p, FILE *fp){
    char s[100];

    //calculate the expression and put it in memory
    EMIT_Expr(p->s2, fp);
    sprintf(s, "sw $a0, %d($sp)", p->symbol->offset * WSIZE);
    emit("", s, "store right hand side in memory", fp);

    //get memory address of variable
    EMIT_Ident(p->s1, fp);
    sprintf(s, "lw $a1, %d($sp)", p->symbol->offset * WSIZE);
    emit("", s, "get right hand side and put it in a1", fp);

    //store result of expression in variable 
    emit("", "sw $a1, ($a0)", "assign value", fp);

    fprintf(fp, "\n");
}//end EMIT_Assign



//PRE: ptr to astnode A_IF and ptr to the output file
//POST: if condition is true fall through and compute 
//      statment then jump over else statment.
//      if condition is false jump to else label and 
//      compute statment
void EMIT_If(struct ASTnode *p, FILE *fp){
    char s[100];

    //create the two labels
    char *L0 = CreateLabel(); //end of if
	char *L1 = CreateLabel(); //else statment 

    //evaluate the condition
    EMIT_Expr(p->s1, fp);
    sprintf(s, "beq $a0 $0 %s", L0);
    emit("", s, "check if condition is false jump to else", fp);
    fprintf(fp, "\n");

    //print if statment
    EMITAST(p->s2->s1, fp);
    sprintf(s, "j %s", L1);
    emit("", s, "jump to end of IF statment", fp);

    //print else statment
    fprintf(fp, "\n");
    sprintf(s, "%s", L0);
    emit(s, "", "else statment", fp);

    //only do else statments if there is an else
    if(p->s2->s2 != NULL)
       EMITAST(p->s2->s2, fp);

    //empty label to end IF
    fprintf(fp, "\n");
    sprintf(s, "%s", L1);
    emit(s, "", "end of IF", fp);

    fprintf(fp, "\n");
 }//end EMIT_If



//PRE: ptr to astnode A_WHILE and ptr to the output file
//POST: Creates two label one at the start of while and one outside after while.
//      check if condition is true at start of while then computes statment then 
//      jumps back to top of while. If condition is true jumps to top of while and 
//      repeats. If false jumps to label outside after of while.
void EMIT_While(struct ASTnode *p, FILE *fp) {
    char s[100];

    //create the two labels
    char *L0 = CreateLabel(); //start of while p->s1
	char *L1 = CreateLabel(); //end of while

    //check condition
    sprintf(s, "%s", L0);
    emit(s, "", "start of while loop", fp);
    EMIT_Expr(p->s1, fp);
    sprintf(s, "beq $a0 $0 %s", L1);
    emit("", s, "if condition false break out of loop\n", fp);

    //do statment inside while
    EMITAST(p->s2, fp);

    //jump back to top of while
    sprintf(s, "j %s", L0);
    emit("", s, "start loop again\n", fp);

    //empty label to end while loop
    sprintf(s, "%s", L1);
    emit(s, "", "empty label to end while loop\n", fp);
}//end while



//PRE: ptr to astnode A_CALL and ptr to the output file
//POST: Stores the arguments of the function in its own designated 
//      location in memory. Uses a temp variable to act as a stack
//      pointer for the where the function will be. Loads the variables 
//      from memory and stores them in the activation record of the function
void EMIT_Call(struct ASTnode *p, FILE *fp) {
    char s[100];

    //needed to count number of arguments passed
    int counter = 2;

    //store memory needed for arguments
    struct ASTnode *cursor = p->s1;

    //store the arguments in there own designated place in memory A_ARGSLIST
    while(cursor != NULL) {
        EMIT_Expr(cursor->s1, fp);
        sprintf(s, "sw $a0, %d($sp)", cursor->symbol->offset * WSIZE);
        emit("", s, "store arguments in memory", fp);
        cursor = cursor->next;
    }//end while

    //use a temp stack pointer to know where the function will start
    sprintf(s, "subu $t2 $sp %d", FUNCTION_MIN_SIZE);
    emit("", s, "carve out memory for the function", fp);

    
    //load expression results from memory and place them 
    //where the function is expecting the args to be
    cursor = p->s1;
    while(cursor != NULL) {
        sprintf(s, "lw $t0, %d($sp)", cursor->symbol->offset * WSIZE);
        emit("", s, "load argument from memory", fp);
        sprintf(s, "sw $t0, %d($t2)", counter * WSIZE);
        emit("", s, "store arguments inside the function", fp);
        counter++;
        cursor = cursor->next;
    }//end while

    //jump to the other function
    sprintf(s, "jal %s", p->name);
    emit("", s, "jump to function", fp);
    
}//end EMIT_Call



//PRE: ptr to astnode A_RETURN and ptr to the output file
//POST: Return will end a function and jump back to the one it was called from
//      if returning a value it will save the expression in $a0
//      if in main it will end the whole function
void EMIT_Return(struct ASTnode *p, FILE *fp) {
    //if returning a value
    if(p->s1 != NULL){
        EMIT_Expr(p->s1, fp);
    }//end if

    emit("", "lw $ra ($sp)", "reset the return address", fp);
    emit("", "lw $sp 4($sp)", "reset stack pointer\n", fp);

    //if returning in main
    if(strcmp(function_name, "main") == 0){
        emit("", "li $v0, 10", "set up end of main function", fp);
        emit("", "syscall", "end main function", fp);
    }//end if
    else { 
        //jump back to function it was called from
        emit("", "jr $ra", "jump back to function\n", fp);
    }//end else

}//end EMIT_Return

