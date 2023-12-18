/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "lab9.y" /* yacc.c:339  */

/*
            Joey troyer
			Lab9
            4/25/22
            Purpose: Implemention of a context free grammer for the language algol-C. It will handle basic declaration of scalars
					 or arrays, assigning values to those variables, returning those variables and functions declarations. Basic 
					 if then else statments and while do. There is syntax directed symantic action for every line that will create 
					 nodes from AST.c and add them to the abstract syntax tree. Introduced a symbol table which will add symbol to 
					 the table, preform type checking and create temp variable for calculating expressions. Will print the symbol 
					 tables variables along with some attributes during and after parsing.
					 !! WONT WORK lines like "int var = 5;". Variables must be delcared and assigned a value on diffent lines
					 !! For loops are NOT supported
					 !! parameters in functions must be declared like "main(x of int)" NOT "main(int x)"
					 !! 1 shift/reduce conflict with selection_stmt but no need to fix
*/


	/* begin specs */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "symtable.h"
#include "AST.h"
#include "emit.h"

#define FUNCTION_MIN_SIZE 2 

struct ASTnode *program = NULL; 

int yylex(); //prototype to get rid of error


extern int lineno; //global line number
extern int mydebug; //global debug variable
int level = 0; //static scope level
int offset = 0; //offset from declarations
int goffset = 0; //offset from all declaratoins used to hold values when we go in and out of functions
int maxoffset = 0; //keeps track of the size of functions

void yyerror (s)  //barfs if there is an error.
char *s; 
{
  printf ("%s on line number: %d\n", s, lineno); //prints error from yyerror and line that error occurred on
}


#line 115 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_NUM = 258,
    T_INT = 259,
    T_VOID = 260,
    T_READ = 261,
    T_WRITE = 262,
    T_RETURN = 263,
    T_IF = 264,
    T_THEN = 265,
    T_ELSE = 266,
    T_WHILE = 267,
    T_DO = 268,
    T_EQ = 269,
    T_LE = 270,
    T_GE = 271,
    T_NE = 272,
    T_ID = 273,
    T_STRING = 274,
    T_BOOLEAN = 275,
    T_END = 276,
    T_BEGIN = 277,
    T_OF = 278,
    T_AND = 279,
    T_OR = 280,
    T_TRUE = 281,
    T_FALSE = 282,
    T_NOT = 283
  };
#endif
/* Tokens.  */
#define T_NUM 258
#define T_INT 259
#define T_VOID 260
#define T_READ 261
#define T_WRITE 262
#define T_RETURN 263
#define T_IF 264
#define T_THEN 265
#define T_ELSE 266
#define T_WHILE 267
#define T_DO 268
#define T_EQ 269
#define T_LE 270
#define T_GE 271
#define T_NE 272
#define T_ID 273
#define T_STRING 274
#define T_BOOLEAN 275
#define T_END 276
#define T_BEGIN 277
#define T_OF 278
#define T_AND 279
#define T_OR 280
#define T_TRUE 281
#define T_FALSE 282
#define T_NOT 283

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 55 "lab9.y" /* yacc.c:355  */

	int value;
	char *ID;
	struct ASTnode *astnode;
	enum AST_Declared_Type DeclType;
	enum AST_Operator_Type operator;
       

#line 220 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 237 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   135

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  132

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      33,    34,    40,    38,    32,    39,     2,    41,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    29,
      37,    35,    36,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    30,     2,    31,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    77,    77,    81,    82,    89,    90,    94,   106,   121,
     137,   154,   173,   174,   175,   179,   191,   179,   208,   209,
     215,   216,   223,   243,   264,   264,   284,   285,   293,   294,
     302,   303,   304,   305,   306,   307,   308,   309,   313,   319,
     325,   333,   343,   351,   353,   360,   367,   372,   378,   396,
     401,   425,   451,   452,   474,   475,   476,   477,   478,   479,
     484,   485,   506,   507,   512,   513,   534,   535,   536,   537,
     541,   543,   547,   549,   551,   555,   559,   569,   605,   606,
     610,   619
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_NUM", "T_INT", "T_VOID", "T_READ",
  "T_WRITE", "T_RETURN", "T_IF", "T_THEN", "T_ELSE", "T_WHILE", "T_DO",
  "T_EQ", "T_LE", "T_GE", "T_NE", "T_ID", "T_STRING", "T_BOOLEAN", "T_END",
  "T_BEGIN", "T_OF", "T_AND", "T_OR", "T_TRUE", "T_FALSE", "T_NOT", "';'",
  "'['", "']'", "','", "'('", "')'", "'='", "'>'", "'<'", "'+'", "'-'",
  "'*'", "'/'", "$accept", "program", "declaration_list", "declaration",
  "var_declaration", "var_list", "type_specifier", "fun_declaration",
  "$@1", "$@2", "params", "param_list", "param", "compound_stmt", "$@3",
  "local_declarations", "statment_list", "statment", "expression_stmt",
  "selection_stmt", "iteration_stmt", "return_stmt", "read_stmt",
  "write_stmt", "assignment_stmt", "expression", "var",
  "simple_expression", "relop", "additive_expression", "addop", "term",
  "multop", "factor", "call", "args", "args_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    59,
      91,    93,    44,    40,    41,    61,    62,    60,    43,    45,
      42,    47
};
# endif

#define YYPACT_NINF -96

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-96)))

#define YYTABLE_NINF -16

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      49,   -96,   -96,   -96,     4,   -96,    49,   -96,    13,   -96,
     -96,   -96,    48,     9,    30,    22,    25,   -96,    52,   -11,
     -96,    -3,    31,   -96,     7,    59,   -96,    62,    22,    49,
      64,   -96,    47,   -96,   -96,    74,    76,   -96,    49,   -96,
     -96,   -96,    49,    49,    22,    17,   -96,   -96,    81,    29,
      46,    33,    33,   -20,   -96,   -96,    33,   -96,    33,   -96,
      80,    17,   -96,   -96,   -96,   -96,   -96,   -96,   -96,    73,
      68,    75,    32,   -13,   -96,   -96,    83,    77,    85,    86,
     -96,   -96,    87,    94,   104,    33,    33,   -96,    84,   -96,
     -96,   -96,    33,   -96,   -96,   -96,   -96,   -96,   -96,    33,
     -96,   -96,    33,   -96,   -96,   -96,   -96,    33,   -96,   -96,
     -96,   -96,    17,    17,    88,    89,    90,   -96,   -96,    71,
      32,   -13,   -96,   109,   -96,   -96,    33,   -96,   -96,    17,
     -96,   -96
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    12,    13,    14,     0,     2,     3,     5,     0,     6,
       1,     4,     8,     0,     0,     0,     0,     7,     0,     8,
      10,     0,     9,    18,     0,     0,    19,    20,     0,     0,
       0,    16,     0,    11,    22,     0,     0,    21,     0,    24,
      17,    23,    26,    26,     0,    28,    27,    71,     0,     0,
       0,     0,     0,    50,    74,    75,     0,    39,     0,    31,
       0,    28,    30,    32,    33,    35,    36,    37,    34,     0,
      72,    49,    52,    60,    64,    73,    50,     0,     0,     0,
      72,    43,     0,     0,     0,     0,    79,    76,     0,    25,
      29,    38,     0,    54,    55,    56,    57,    58,    59,     0,
      62,    63,     0,    68,    69,    66,    67,     0,    45,    47,
      46,    44,     0,     0,     0,    80,     0,    78,    70,     0,
      53,    61,    65,    40,    42,    51,     0,    77,    48,     0,
      81,    41
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -96,   -96,   116,   -96,    34,    -6,    67,   -96,   -96,   -96,
     -96,    91,   -96,    92,   -96,    82,    65,   -95,   -96,   -96,
     -96,   -96,   -96,   -96,   -96,   -44,   -45,    35,   -96,    36,
     -96,    27,   -96,   -55,   -96,   -96,     5
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    13,     8,     9,    16,    36,
      25,    26,    27,    59,    42,    45,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    80,    71,    99,    72,
     102,    73,   107,    74,    75,   116,   117
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,    87,    23,    77,    10,    79,    82,    83,    84,    20,
      85,   103,   104,    86,    88,    24,    70,   123,   124,    14,
      47,    15,    33,    48,    49,    50,    51,   105,   106,    52,
      29,    12,    47,    18,   131,    53,    47,    30,    17,    39,
      19,   114,   115,    54,    55,    56,    57,    53,    78,    47,
      58,    53,   122,     1,     2,    54,    55,    56,    21,    54,
      55,    56,    58,    28,    53,    24,    58,    70,    70,     3,
     100,   101,    54,    55,    56,    81,    43,    43,    14,    58,
      15,   -15,   115,    22,    70,    93,    94,    95,    96,    93,
      94,    95,    96,    31,    32,    35,    34,    38,    39,    76,
     128,    89,    91,    92,   112,    41,   108,    97,    98,    44,
      44,    97,    98,    85,   109,   110,   111,   113,   118,   125,
     129,   126,    11,    37,   127,    46,    90,   119,    40,   121,
       0,   130,     0,     0,     0,   120
};

static const yytype_int16 yycheck[] =
{
      45,    56,     5,    48,     0,    49,    50,    51,    52,    15,
      30,    24,    25,    33,    58,    18,    61,   112,   113,    30,
       3,    32,    28,     6,     7,     8,     9,    40,    41,    12,
      23,    18,     3,     3,   129,    18,     3,    30,    29,    22,
      18,    85,    86,    26,    27,    28,    29,    18,    19,     3,
      33,    18,   107,     4,     5,    26,    27,    28,    33,    26,
      27,    28,    33,    32,    18,    18,    33,   112,   113,    20,
      38,    39,    26,    27,    28,    29,    42,    43,    30,    33,
      32,    33,   126,    31,   129,    14,    15,    16,    17,    14,
      15,    16,    17,    34,    32,    31,    29,    23,    22,    18,
      29,    21,    29,    35,    10,    38,    29,    36,    37,    42,
      43,    36,    37,    30,    29,    29,    29,    13,    34,    31,
      11,    32,     6,    32,    34,    43,    61,    92,    36,   102,
      -1,   126,    -1,    -1,    -1,    99
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    20,    43,    44,    45,    46,    48,    49,
       0,    44,    18,    47,    30,    32,    50,    29,     3,    18,
      47,    33,    31,     5,    18,    52,    53,    54,    32,    23,
      30,    34,    32,    47,    48,    31,    51,    53,    23,    22,
      55,    48,    56,    46,    48,    57,    57,     3,     6,     7,
       8,     9,    12,    18,    26,    27,    28,    29,    33,    55,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    71,    73,    75,    76,    18,    68,    19,    67,
      68,    29,    67,    67,    67,    30,    33,    75,    67,    21,
      58,    29,    35,    14,    15,    16,    17,    36,    37,    70,
      38,    39,    72,    24,    25,    40,    41,    74,    29,    29,
      29,    29,    10,    13,    67,    67,    77,    78,    34,    69,
      71,    73,    75,    59,    59,    31,    32,    34,    29,    11,
      78,    59
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    46,    47,    47,
      47,    47,    48,    48,    48,    50,    51,    49,    52,    52,
      53,    53,    54,    54,    56,    55,    57,    57,    58,    58,
      59,    59,    59,    59,    59,    59,    59,    59,    60,    60,
      61,    61,    62,    63,    63,    64,    65,    65,    66,    67,
      68,    68,    69,    69,    70,    70,    70,    70,    70,    70,
      71,    71,    72,    72,    73,    73,    74,    74,    74,    74,
      75,    75,    75,    75,    75,    75,    75,    76,    77,    77,
      78,    78
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     1,     4,
       3,     6,     1,     1,     1,     0,     0,     8,     1,     1,
       1,     3,     3,     5,     0,     5,     0,     2,     0,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       4,     6,     4,     2,     3,     3,     3,     3,     4,     1,
       1,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     1,     2,     4,     1,     0,
       1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 77 "lab9.y" /* yacc.c:1646  */
    {program = (yyvsp[0].astnode);}
#line 1415 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 81 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode) = (yyvsp[0].astnode);}
#line 1421 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 82 "lab9.y" /* yacc.c:1646  */
    {
					 							 (yyval.astnode) = (yyvsp[-1].astnode); 
				 								 (yyvsp[-1].astnode)->next = (yyvsp[0].astnode);
												}
#line 1430 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 89 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode) = (yyvsp[0].astnode);}
#line 1436 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 90 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode) = (yyvsp[0].astnode);}
#line 1442 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 94 "lab9.y" /* yacc.c:1646  */
    { (yyval.astnode) = (yyvsp[-1].astnode);
												//need to update type in varlist and pass up to parrent 
												struct ASTnode *p = (yyval.astnode);
			 					  				while(p != 	NULL) {
													  p->DeclType = (yyvsp[-2].DeclType);
													  p->symbol->Type = (yyvsp[-2].DeclType);
													  p = p->s1;
												   }//end while
											  }
#line 1456 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 106 "lab9.y" /* yacc.c:1646  */
    { //Search symbol to make sure variable is not already there then create not and insert into symbtab
								  if(Search((yyvsp[0].ID), level, 0)) {
									 yyerror("error");
								  	 printf("Variable %s already in the symbol table\n", (yyvsp[0].ID));
									 exit(1);
								  }//end if 

								  (yyval.astnode) = AST_Create_Node(A_VARDEC);
								  (yyval.astnode)->symbol = Insert((yyvsp[0].ID), 0, 0, level, 1, offset);
								  (yyval.astnode)->calculated_type = Search((yyvsp[0].ID), level, 1)->Type; //search symbol table for variable so we can get its type
								  (yyval.astnode)->name = (yyvsp[0].ID);
								  (yyval.astnode)->size = 1;  
								  offset += 1;
								}
#line 1475 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 121 "lab9.y" /* yacc.c:1646  */
    { //expl: int a[100];
		 					      //check if $1 is already in the symbol table if it is barf
								  if(Search((yyvsp[-3].ID), level, 0)) {
								     yyerror("error");
								  	 printf("Variable %s already in the symbol table\n", (yyvsp[-3].ID));
									 exit(1);
								  }//end if

			 					  (yyval.astnode) = AST_Create_Node(A_VARDEC);
								  (yyval.astnode)->symbol = Insert((yyvsp[-3].ID), 0, 1, level, (yyvsp[-1].value), offset);
								  (yyval.astnode)->calculated_type = Search((yyvsp[-3].ID), level, 1)->Type;
		 						  (yyval.astnode)->name = (yyvsp[-3].ID);
								  (yyval.astnode)->size = (yyvsp[-1].value);
								  offset += (yyvsp[-1].value);
								}
#line 1495 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 137 "lab9.y" /* yacc.c:1646  */
    { //expl: int a, b, c;
		 						   //check if T_ID is already in the symbol table if it is barf
								  if(Search((yyvsp[-2].ID), level, 0)) {
								     yyerror("error");
								  	 printf("Variable %s already in the symbol table\n", (yyvsp[-2].ID));
									   exit(1);
								  }//end if

			 					  (yyval.astnode) = AST_Create_Node(A_VARDEC);
								  (yyval.astnode)->symbol = Insert((yyvsp[-2].ID), 0, 0, level, 1, offset);
								  (yyval.astnode)->calculated_type = Search((yyvsp[-2].ID), level, 1)->Type;
		 						  (yyval.astnode)->name = (yyvsp[-2].ID);
								  (yyval.astnode)->s1 = (yyvsp[0].astnode);
								  (yyval.astnode)->size = 1;
								  offset += 1;
								}
#line 1516 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 154 "lab9.y" /* yacc.c:1646  */
    { //expl: int a[100], b[100], c[100];
		 									  //check if T_ID is already in the symbol table if it is barf
								  			 if(Search((yyvsp[-5].ID), level, 0)) {
												yyerror("error");
								  	 			printf("Variable %s already in the symbol table\n", (yyvsp[-5].ID));
									   			exit(1);
								  			 }//end if

			 								  (yyval.astnode) = AST_Create_Node(A_VARDEC);
											  (yyval.astnode)->symbol = Insert((yyvsp[-5].ID), 0, 1, level, (yyvsp[-3].value), offset);
								  			  (yyval.astnode)->calculated_type = Search((yyvsp[-5].ID), level, 1)->Type;
		 						  			  (yyval.astnode)->name = (yyvsp[-5].ID);
								  			  (yyval.astnode)->size = (yyvsp[-3].value);
											  (yyval.astnode)->s1 = (yyvsp[0].astnode); 
											  offset += (yyvsp[-3].value);
											}
#line 1537 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 173 "lab9.y" /* yacc.c:1646  */
    {(yyval.DeclType) = A_INT_TYPE;}
#line 1543 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 174 "lab9.y" /* yacc.c:1646  */
    {(yyval.DeclType) = A_VOID_TYPE;}
#line 1549 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 175 "lab9.y" /* yacc.c:1646  */
    {(yyval.DeclType) = A_BOOLEAN_TYPE;}
#line 1555 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 179 "lab9.y" /* yacc.c:1646  */
    {		//we need to add the ID into the symbtab before we take in params or compund statments because we may need to know the type and length of it
											if(Search((yyvsp[0].ID), level, 0)) {
					   						   yyerror("error");
											   printf("Function name %s already in use!!!\n", (yyvsp[0].ID));
											   exit(1);
											}//end if

											Insert((yyvsp[0].ID), (yyvsp[-1].DeclType), 2, level, 0, 0);
											goffset = offset;
											offset = FUNCTION_MIN_SIZE;
											maxoffset = 0;
									  }
#line 1572 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 191 "lab9.y" /* yacc.c:1646  */
    {					    //update symbtab to have pointer to formal parameters
											(Search((yyvsp[-4].ID), 0, 0)) -> fparams = (yyvsp[-1].astnode); }
#line 1579 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 194 "lab9.y" /* yacc.c:1646  */
    { 						 
											(yyval.astnode) = AST_Create_Node(A_FUNDEC);
											(yyval.astnode)->DeclType = (yyvsp[-7].DeclType);
											(yyval.astnode)->calculated_type = (yyvsp[-7].DeclType);
											(yyval.astnode)->name = (yyvsp[-6].ID);
											(yyval.astnode)->s1 = (yyvsp[-3].astnode); //params
											(yyval.astnode)->s2 = (yyvsp[0].astnode); //compund stmt
											(yyval.astnode)->symbol = Search((yyvsp[-6].ID), 0, 0); //get symbol table enrty 
											(yyval.astnode)->symbol->mysize = maxoffset;
											offset = goffset; 
					}
#line 1595 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 208 "lab9.y" /* yacc.c:1646  */
    { (yyval.astnode) = NULL; /*no paramater list */}
#line 1601 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 209 "lab9.y" /* yacc.c:1646  */
    { (yyval.astnode) = (yyvsp[0].astnode);}
#line 1607 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 215 "lab9.y" /* yacc.c:1646  */
    { (yyval.astnode) = (yyvsp[0].astnode);}
#line 1613 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 216 "lab9.y" /* yacc.c:1646  */
    {
			         				(yyval.astnode) = (yyvsp[-2].astnode);
			         				(yyval.astnode)->next = (yyvsp[0].astnode); 
					 			  }
#line 1622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 223 "lab9.y" /* yacc.c:1646  */
    {      /* expl: a of int */
										//Make sure variable isnt already in use
										if(Search((yyvsp[-2].ID), level + 1, 0)) {
											yyerror("error");
									    	printf("Variable name %s already in use!!!\n", (yyvsp[-2].ID));
											exit(1);
										}

                              	 		(yyval.astnode) = AST_Create_Node(A_PARAM);
										(yyval.astnode)->symbol = Insert((yyvsp[-2].ID), (yyvsp[0].DeclType), 0, level + 1, 1, offset); //level + 1 because everything in the function will be on the next level
                              	 		(yyval.astnode)->name = (yyvsp[-2].ID);
										(yyval.astnode)->DeclType = (yyvsp[0].DeclType);
										(yyval.astnode)->calculated_type = (yyvsp[0].DeclType);
                              	 		(yyval.astnode)->size = 0; /* not an array */
										offset += 1;

										if(mydebug)
										   printf("Inserted param %s at level %d\n", (yyvsp[-2].ID), level + 1);
                           		  }
#line 1646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 243 "lab9.y" /* yacc.c:1646  */
    { /* expl: a[] of int */
										   if(Search((yyvsp[-4].ID), level + 1, 0)) {
										  	  yyerror("error");
									      	  printf("Variable name %s already in use!!!\n", (yyvsp[-4].ID));
										  	  exit(1);
										    }

                              	 		   (yyval.astnode) = AST_Create_Node(A_PARAM);
										   (yyval.astnode)->symbol = Insert((yyvsp[-4].ID), (yyvsp[0].DeclType), 1, level + 1, 1, offset); //level + 1 because everything in the function will be on the next level
                              	 		   (yyval.astnode)->name = (yyvsp[-4].ID);
										   (yyval.astnode)->DeclType = (yyvsp[0].DeclType);
										   (yyval.astnode)->calculated_type = (yyvsp[0].DeclType);
                              	 		   (yyval.astnode)->size = -1; /* is an array */
										   offset += 1;

										   if(mydebug)
										      printf("Inserted param %s[] at level %d\n", (yyvsp[-4].ID), level + 1);
                           		  		 }
#line 1669 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 264 "lab9.y" /* yacc.c:1646  */
    {//increment level when entering function
						 level++;}
#line 1676 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 267 "lab9.y" /* yacc.c:1646  */
    {  /*expl: BEGIN stuff END */
								    (yyval.astnode) = AST_Create_Node(A_BLOCK);
                                    (yyval.astnode)->s1 = (yyvsp[-2].astnode);
                                    (yyval.astnode)->s2 = (yyvsp[-1].astnode);

									if(mydebug)
									   Display();
									
									if(offset > maxoffset) maxoffset = offset;
									offset -= Delete(level); /* remove all the symbols from what we put in from the function call*/
                                    level--; //decrement level when leaving function

									
                                 }
#line 1695 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 284 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode) = NULL;}
#line 1701 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 286 "lab9.y" /* yacc.c:1646  */
    {
									(yyval.astnode) = (yyvsp[-1].astnode);
					   				(yyval.astnode)->next = (yyvsp[0].astnode);
								  }
#line 1710 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 293 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode) = NULL;}
#line 1716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 294 "lab9.y" /* yacc.c:1646  */
    {
				  						 (yyval.astnode) = (yyvsp[-1].astnode); 
			  							 (yyval.astnode)->next = (yyvsp[0].astnode);
									   }
#line 1725 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 302 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode) = (yyvsp[0].astnode);}
#line 1731 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 303 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode) = (yyvsp[0].astnode);}
#line 1737 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 304 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode) = (yyvsp[0].astnode);}
#line 1743 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 305 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode) = (yyvsp[0].astnode);}
#line 1749 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 306 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode) = (yyvsp[0].astnode);}
#line 1755 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 307 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode) = (yyvsp[0].astnode);}
#line 1761 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 308 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode) = (yyvsp[0].astnode);}
#line 1767 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 309 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode) = (yyvsp[0].astnode);}
#line 1773 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 313 "lab9.y" /* yacc.c:1646  */
    { 
								   (yyval.astnode) = AST_Create_Node(A_EXPRSTMT);
                                   (yyval.astnode)->s1 = (yyvsp[-1].astnode); 
								   (yyval.astnode)->calculated_type = (yyvsp[-1].astnode)->calculated_type;
								 }
#line 1783 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 319 "lab9.y" /* yacc.c:1646  */
    { //expl: ;;;;;;
								   (yyval.astnode) = AST_Create_Node(A_EXPRSTMT); 
								 }
#line 1791 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 325 "lab9.y" /* yacc.c:1646  */
    { //expl: if(x==3) then x+1;
												  (yyval.astnode) = AST_Create_Node(A_IF);
												  (yyval.astnode)->s1 = (yyvsp[-2].astnode);
												  (yyval.astnode)->s2 = AST_Create_Node(A_IF);
												  (yyval.astnode)->s2->s1=(yyvsp[0].astnode);
												  (yyval.astnode)->s2->s2=NULL;
												 }
#line 1803 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 333 "lab9.y" /* yacc.c:1646  */
    { //expl: if(x==3) then x+1 else x-3;
				   								 (yyval.astnode) = AST_Create_Node(A_IF);
												 (yyval.astnode)->s1 = (yyvsp[-4].astnode);
												 (yyval.astnode)->s2 = AST_Create_Node(A_IF);
												 (yyval.astnode)->s2->s1=(yyvsp[-2].astnode);
												 (yyval.astnode)->s2->s2=(yyvsp[0].astnode);
												 }
#line 1815 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 343 "lab9.y" /* yacc.c:1646  */
    { //expl: while(true) Do x + 3;
												   (yyval.astnode)=AST_Create_Node(A_WHILE);
                               					   (yyval.astnode)->s1=(yyvsp[-2].astnode);
                                				   (yyval.astnode)->s2=(yyvsp[0].astnode);
												  }
#line 1825 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 351 "lab9.y" /* yacc.c:1646  */
    { //expl: return
									  (yyval.astnode) = AST_Create_Node(A_RETURN); }
#line 1832 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 353 "lab9.y" /* yacc.c:1646  */
    {//expl: return x-5+6;
									  (yyval.astnode) = AST_Create_Node(A_RETURN);
									  (yyval.astnode)->s1 = (yyvsp[-1].astnode);
									 }
#line 1841 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 360 "lab9.y" /* yacc.c:1646  */
    { //expl: READ x;
							(yyval.astnode) = AST_Create_Node(A_READ);
							(yyval.astnode)->s1 = (yyvsp[-1].astnode);
						   }
#line 1850 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 367 "lab9.y" /* yacc.c:1646  */
    { //expl: Write  x[100] + 200;
									 (yyval.astnode) = AST_Create_Node(A_WRITE);
									 (yyval.astnode)->s1 = (yyvsp[-1].astnode);
									}
#line 1859 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 372 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode) = AST_Create_Node(A_WRITE);
			  					    (yyval.astnode)->name = (yyvsp[-1].ID);
									(yyval.astnode)->label = CreateLabel();}
#line 1867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 378 "lab9.y" /* yacc.c:1646  */
    { //expl: x = 5;
												//type checking
					  							if((yyvsp[-3].astnode)->calculated_type != (yyvsp[-1].astnode)->calculated_type) {
										   			yyerror("error");
								  	       			printf("assignment Type mismatch\n");
									       			exit(1);
												}

												 (yyval.astnode) = AST_Create_Node(A_ASSIGN);
												 (yyval.astnode)->s1 = (yyvsp[-3].astnode);
												 (yyval.astnode)->s2 = (yyvsp[-1].astnode); 
												 (yyval.astnode)->name = CreateTemp();
												 (yyval.astnode)->symbol = Insert((yyval.astnode)->name, (yyvsp[-3].astnode)->calculated_type, 0, level, 1, offset);	
												 offset++;
												}
#line 1887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 396 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode) = (yyvsp[0].astnode);}
#line 1893 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 401 "lab9.y" /* yacc.c:1646  */
    { //make sure variable exists on any level
								  struct SymbTab *p;
								  if((p = Search((yyvsp[0].ID), level, 1)) == NULL){
									  yyerror("error");
									  printf("undeclared variable %s \n", (yyvsp[0].ID));
									  exit(1);
								  }

								  //make sure variable is a scalar
								  if(p->IsAFunc != 0){
										 yyerror("error");
									     printf("variable %s not a scalar\n", (yyvsp[0].ID));
									     exit(1);
								  }
								  
								    //create the node
								    (yyval.astnode)=AST_Create_Node(A_IDENT);
	         					    (yyval.astnode)->name=(yyvsp[0].ID);
									(yyval.astnode)->symbol = p;
									(yyval.astnode)->calculated_type = p->Type;

								  
		 						}
#line 1921 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 425 "lab9.y" /* yacc.c:1646  */
    { //make sure variable exists on any level
								  struct SymbTab *p;
								  if((p = Search((yyvsp[-3].ID), level, 1)) == NULL){
									  yyerror("error");
									  printf("undeclared variable %s \n", (yyvsp[-3].ID));
									  exit(1);
								  }

								  //make sure variable is a array
								  if(p->IsAFunc != 1){
										 yyerror("error");
									     printf("variable %s not a array\n", (yyvsp[-3].ID));
									     exit(1);
								  }

								  //create the node
								  (yyval.astnode)=AST_Create_Node(A_IDENT);
								  (yyval.astnode)->name=(yyvsp[-3].ID);
								  (yyval.astnode)->s1 = (yyvsp[-1].astnode); 
								  (yyval.astnode)->calculated_type = p->Type;
								  (yyval.astnode)->symbol = p;

								}
#line 1949 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 451 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode) = (yyvsp[0].astnode);}
#line 1955 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 452 "lab9.y" /* yacc.c:1646  */
    {
					  					//type checking
					  					if((yyvsp[-2].astnode)->calculated_type != (yyvsp[0].astnode)->calculated_type) {
										   yyerror("error");
								  	       printf("Simple Type mismatch\n");
									       exit(1);
										}

										 //create the node
					    				 (yyval.astnode) = AST_Create_Node(A_EXPR);
                        				 (yyval.astnode)->s1=(yyvsp[-2].astnode);
										 (yyval.astnode)->operator=(yyvsp[-1].operator);
										 (yyval.astnode)->calculated_type = (yyvsp[0].astnode)->calculated_type;
                        				 (yyval.astnode)->s2=(yyvsp[0].astnode);
										 (yyval.astnode)->name = CreateTemp();
										 (yyval.astnode)->symbol = Insert((yyval.astnode)->name, A_BOOLEAN_TYPE, 0, level, 1, offset);
										 offset++;
										}
#line 1978 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 474 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_EQ;}
#line 1984 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 475 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_LE;}
#line 1990 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 476 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_GE;}
#line 1996 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 477 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_NE;}
#line 2002 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 478 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_GT;}
#line 2008 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 479 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_LT;}
#line 2014 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 484 "lab9.y" /* yacc.c:1646  */
    { (yyval.astnode) = (yyvsp[0].astnode); }
#line 2020 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 485 "lab9.y" /* yacc.c:1646  */
    { 
													   //type checking
													   if((yyvsp[-2].astnode)->calculated_type != (yyvsp[0].astnode)->calculated_type){
														   yyerror("error");
								  	                       printf("Additive Type mismatch\n");
									                       exit(1);
													   }
													   
													   //create the node
													   (yyval.astnode) = AST_Create_Node(A_EXPR);
													   (yyval.astnode)->s1 = (yyvsp[-2].astnode);
													   (yyval.astnode)->operator = (yyvsp[-1].operator);
													   (yyval.astnode)->s2 = (yyvsp[0].astnode);
													   (yyval.astnode)->calculated_type = A_INT_TYPE;
													   (yyval.astnode)->name = CreateTemp();
													   (yyval.astnode)->symbol = Insert((yyval.astnode)->name, A_INT_TYPE, 0, level, 1, offset);	
													   offset++;										 
													 }
#line 2043 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 506 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_PLUS;}
#line 2049 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 507 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_MINUS;}
#line 2055 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 512 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode)=(yyvsp[0].astnode);}
#line 2061 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 513 "lab9.y" /* yacc.c:1646  */
    {
				//type checking
				if((yyvsp[-2].astnode)->calculated_type != (yyvsp[0].astnode)->calculated_type){
					yyerror("error");
					printf("Term Type mismatch\n");
					exit(1);
			    }
				
				//create the node
		 	    (yyval.astnode) = AST_Create_Node(A_EXPR);
		 		(yyval.astnode)->s1 = (yyvsp[-2].astnode);
				(yyval.astnode)->operator = (yyvsp[-1].operator);
				(yyval.astnode)->s2 = (yyvsp[0].astnode);
				(yyval.astnode)->calculated_type = A_INT_TYPE;
				(yyval.astnode)->name = CreateTemp();
 			    (yyval.astnode)->symbol = Insert((yyval.astnode)->name, A_INT_TYPE, 0, level, 1, offset);	
				offset++;
	 					  }
#line 2084 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 534 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_TIMES;}
#line 2090 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 535 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_DIVIDE;}
#line 2096 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 536 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_AND;}
#line 2102 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 537 "lab9.y" /* yacc.c:1646  */
    {(yyval.operator) = A_OR;}
#line 2108 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 541 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode) = (yyvsp[-1].astnode);}
#line 2114 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 543 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode)=AST_Create_Node(A_NUMBER);
                			 (yyval.astnode)->size = (yyvsp[0].value);
							 (yyval.astnode)->calculated_type = A_INT_TYPE;}
#line 2122 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 547 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode) = (yyvsp[0].astnode);}
#line 2128 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 549 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode) = (yyvsp[0].astnode);}
#line 2134 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 551 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode)=AST_Create_Node(A_BOOLEAN);
               				 (yyval.astnode)->size = 1;
							 (yyval.astnode)->calculated_type = A_BOOLEAN_TYPE;}
#line 2142 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 555 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode)=AST_Create_Node(A_BOOLEAN);
               				 (yyval.astnode)->size = 0;
							 (yyval.astnode)->calculated_type = A_BOOLEAN_TYPE;}
#line 2150 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 559 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode)=AST_Create_Node(A_EXPR);
                        	 (yyval.astnode)->operator = A_NOT;
                        	 (yyval.astnode)->s1 = (yyvsp[0].astnode);
							 (yyval.astnode)->name = CreateTemp();
							 (yyval.astnode)->symbol = Insert((yyval.astnode)->name, A_BOOLEAN_TYPE, 0, level, 0, offset);
							 offset++;
							 }
#line 2162 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 569 "lab9.y" /* yacc.c:1646  */
    { 

						struct SymbTab *p;
						//make sure the function exists and is an actual function
						if((p = Search((yyvsp[-3].ID), 0, 0)) != NULL) { 
							if(p->IsAFunc != 2) {
							   yyerror("error");
							   printf("%s is not a defined function\n", (yyvsp[-3].ID));
							   exit(1);
							}

							//Make sure param and argument list is the same
							if(CompareFormals(p->fparams, (yyvsp[-1].astnode)) != 1){
							   yyerror("error");
							   printf("Parameter and argument type or length mismatch\n");
							   exit(1);
							}//end if
						
						   (yyval.astnode)=AST_Create_Node(A_CALL);
            			   (yyval.astnode)->s1=(yyvsp[-1].astnode);
						   (yyval.astnode)->calculated_type = p->Type;
            			   (yyval.astnode)->name=(yyvsp[-3].ID);
						   (yyval.astnode)->symbol = p;
          				 }//end if
						   else{
							   yyerror("error");
							   printf("Function %s not defined\n", (yyvsp[-3].ID));
							   exit(1);
						   }//end else

						if(mydebug)
						   printf("calling function %s\n", (yyvsp[-3].ID));
						}
#line 2200 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 605 "lab9.y" /* yacc.c:1646  */
    { (yyval.astnode) = (yyvsp[0].astnode);}
#line 2206 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 606 "lab9.y" /* yacc.c:1646  */
    {(yyval.astnode)=NULL;}
#line 2212 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 610 "lab9.y" /* yacc.c:1646  */
    {
						  (yyval.astnode) = AST_Create_Node(A_ARGSLIST);
				  		  (yyval.astnode)->s1 = (yyvsp[0].astnode);
						  (yyval.astnode)->calculated_type = (yyvsp[0].astnode)->calculated_type;
						  (yyval.astnode)->next = NULL;
						  (yyval.astnode)->name = CreateTemp();
						  (yyval.astnode)->symbol = Insert((yyval.astnode)->name, A_INT_TYPE, 0, level, 1, offset);
						  offset++;
		                 }
#line 2226 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 619 "lab9.y" /* yacc.c:1646  */
    {
			  			  (yyval.astnode) = AST_Create_Node(A_ARGSLIST);
			  			  (yyval.astnode)->s1 = (yyvsp[-2].astnode);
						  (yyval.astnode)->calculated_type = (yyvsp[-2].astnode)->calculated_type;
			 		      (yyval.astnode)->next = (yyvsp[0].astnode);
						  (yyval.astnode)->name = CreateTemp();
						  (yyval.astnode)->symbol = Insert((yyval.astnode)->name, A_INT_TYPE, 0, level, 1, offset);	
						  offset++;
						             }
#line 2240 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2244 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 630 "lab9.y" /* yacc.c:1906  */
	/* end of rules, start of program */

int main(int argc, char* argv[]) { 
	int i = 1;

	while ( i < argc ) {
		if (strcmp("-d", argv[i]) == 0) mydebug = 1;
		if (strcmp("-o", argv[i] ) == 0) {
			char s[100];

			/* we need to append asm to the filename */
			mydebug && printf("file name is %s\n", argv[i + 1]);

			strcpy(s, argv[i + 1]);
			strcat(s,".asm");
			mydebug && printf ("opening %s\n",s);

			fp = fopen(s, "w");
			if (fp == NULL) { 
				fprintf(stderr, "cannot Open %s\n",s);
				exit(1);
			}
		}
	i++;
	}//end while

	yyparse();
	// prints to know when parsed the whole program
	//printf("PARSING COMPLETE \n");
	if(mydebug) AST_Print(program, 0);
	if (mydebug) Display();

	//open file for emitting things to
	if(fp != NULL) {
		EMIT_Header(program, fp);
		EMITAST(program, fp);
	}

	else 
		printf("No output file defined. No action \n");

}//end main
