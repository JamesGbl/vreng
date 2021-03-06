/* A Bison parser, made by GNU Bison 3.0.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "vred.y" /* yacc.c:339  */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "input.hpp"

#define YYDEBUG 1
//extern int yy_flex_debug;  // pour le debogage

extern FILE* yyin;
int yylineno;
extern int yyerror(char*);
extern int yylex();

void mix_texture(Tex* t1, Tex* t2);
void mix_app(App* a1, App* a2);
void moveCenter(Vect& center, Vect& size);
double deg(const double );

int curtype;

/* le groupe racine cree */ 
Group *gr;
/* pour obtenir les valeurs par defaut */
App *a;

struct structBoxProps
  {
    Vect* bp_box_size;
    Tex* bp_box_tex;
    App* bp_app;
  };

struct structSpherProps
  {
    double sp_spher_size;
    char* sp_spher_tex;
    App* sp_app;
  };

void free_box_props (struct structBoxProps *bp) {
  if (bp->bp_box_size != NULL) delete(bp->bp_box_size);
  if (bp->bp_box_tex != NULL) delete(bp->bp_box_tex);
  if (bp->bp_app != NULL) delete(bp->bp_app);
  free(bp);
}

void free_spher_props (struct structSpherProps *sp) {
  if (sp->sp_spher_tex != NULL) free(sp->sp_spher_tex);
  if (sp->sp_app != NULL) delete(sp->sp_app);
  free(sp);
}


#line 122 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
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
    COMMA = 258,
    NUMBER = 259,
    STRING = 260,
    TK_WALL = 261,
    TK_GATE = 262,
    TK_EARTH = 263,
    TK_WEB = 264,
    TK_BOARD = 265,
    TK_STEP = 266,
    TK_HOST = 267,
    TK_DOC = 268,
    TK_END = 269,
    TK_BOX_SIZE = 270,
    TK_SPHER_SIZE = 271,
    TK_TOR_SIZE = 272,
    TK_TOR_SIZE2 = 273,
    TK_DIFFUSE = 274,
    TK_AMBIENT = 275,
    TK_SPECULAR = 276,
    TK_EMISSION = 277,
    TK_SHININESS = 278,
    TEX_XP = 279,
    TEX_YP = 280,
    TEX_ZP = 281,
    TEX_XN = 282,
    TEX_YN = 283,
    TEX_ZN = 284,
    SPHER_TEX = 285,
    TLNT = 286
  };
#endif
/* Tokens.  */
#define COMMA 258
#define NUMBER 259
#define STRING 260
#define TK_WALL 261
#define TK_GATE 262
#define TK_EARTH 263
#define TK_WEB 264
#define TK_BOARD 265
#define TK_STEP 266
#define TK_HOST 267
#define TK_DOC 268
#define TK_END 269
#define TK_BOX_SIZE 270
#define TK_SPHER_SIZE 271
#define TK_TOR_SIZE 272
#define TK_TOR_SIZE2 273
#define TK_DIFFUSE 274
#define TK_AMBIENT 275
#define TK_SPECULAR 276
#define TK_EMISSION 277
#define TK_SHININESS 278
#define TEX_XP 279
#define TEX_YP 280
#define TEX_ZP 281
#define TEX_XN 282
#define TEX_YN 283
#define TEX_ZN 284
#define SPHER_TEX 285
#define TLNT 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 57 "vred.y" /* yacc.c:355  */

  double dval;
  char*  sval;
  double* dpval;
  Vect* vectval;
  Tex*  texval;
  struct structBoxProps* bpval;
  struct structSpherProps* spval;
  App* appval;

#line 235 "y.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 250 "y.tab.c" /* yacc.c:358  */

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

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
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
#define YYFINAL  45
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   110

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  124

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    91,    91,    93,    93,    96,    97,    98,    99,   100,
     101,   102,   103,   107,   108,   108,   109,   122,   123,   123,
     124,   139,   140,   140,   141,   153,   154,   154,   155,   169,
     170,   170,   171,   184,   185,   185,   186,   199,   200,   200,
     201,   215,   216,   216,   217,   234,   243,   252,   261,   272,
     281,   290,   299,   311,   322,   326,   331,   332,   339,   340,
     341,   342,   343,   344,   347,   348,   355,   359,   365,   371
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "COMMA", "NUMBER", "STRING", "TK_WALL",
  "TK_GATE", "TK_EARTH", "TK_WEB", "TK_BOARD", "TK_STEP", "TK_HOST",
  "TK_DOC", "TK_END", "TK_BOX_SIZE", "TK_SPHER_SIZE", "TK_TOR_SIZE",
  "TK_TOR_SIZE2", "TK_DIFFUSE", "TK_AMBIENT", "TK_SPECULAR", "TK_EMISSION",
  "TK_SHININESS", "TEX_XP", "TEX_YP", "TEX_ZP", "TEX_XN", "TEX_YN",
  "TEX_ZN", "SPHER_TEX", "TLNT", "$accept", "start", "solid",
  "solid_single", "wall_section", "wall", "wall_single", "gate_section",
  "gate", "gate_single", "earth_section", "earth", "earth_single",
  "web_section", "web", "web_single", "board_section", "board",
  "board_single", "step_section", "step", "step_single", "host_section",
  "host", "host_single", "doc_section", "doc", "doc_single", "box_props",
  "spher_props", "pos_ang", "box_size", "spher_size", "box_tex",
  "box_tex_single", "app", "app_single", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286
};
# endif

#define YYPACT_NINF -68

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-68)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      56,     5,     5,     5,     5,     5,     5,     5,     5,    10,
      47,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,
      11,     5,   -68,     2,     5,   -68,    13,     5,   -68,     3,
       5,   -68,    15,     5,   -68,     2,     5,   -68,     2,     5,
     -68,   -10,     5,   -68,    19,   -68,   -68,   -68,    22,   -68,
      25,   -68,    24,   -68,    27,   -68,    26,   -68,    32,   -68,
       2,   -68,   -68,   -68,   -68,   -68,     2,   -68,     2,    69,
      72,    23,     2,   -68,    -7,   -68,   -68,   -68,    73,    74,
      76,    77,    78,    79,   -68,   -68,   -68,   -68,   -68,   -68,
      80,   -68,    81,   -68,   -68,    82,    81,   -68,    83,    84,
      85,    86,    87,    23,    51,    51,    88,    90,    91,    92,
      93,   -68,    81,   -68,    81,   -68,    94,    95,    96,    97,
     -68,   -68,   -68,   -68
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     3,     5,     6,     7,     8,     9,    10,    11,    12,
       0,    13,    14,     0,    17,    18,     0,    21,    22,     0,
      25,    26,     0,    29,    30,     0,    33,    34,     0,    37,
      38,     0,    41,    42,     0,     1,     2,     4,     0,    15,
       0,    16,    48,    19,     0,    23,     0,    24,    49,    27,
       0,    31,    32,    35,    36,    39,     0,    43,     0,     0,
       0,     0,     0,    55,     0,    28,    40,    44,     0,     0,
       0,     0,     0,     0,    58,    60,    62,    59,    61,    63,
      46,    56,    47,    64,    20,    50,    51,    53,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    57,    45,    65,    52,    54,     0,     0,     0,     0,
      67,    66,    69,    68
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -68,   -68,   -68,    66,   -68,   -68,    89,   -68,   -68,    63,
     -68,   -68,    70,   -68,   -68,    75,   -68,   -68,    71,   -68,
     -68,    67,   -68,   -68,    68,   -68,   -68,    60,   -27,   -68,
      -2,   -68,   -68,   -68,     6,   -67,     4
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     9,    10,    11,    12,    21,    22,    13,    24,    25,
      14,    27,    28,    15,    30,    31,    16,    33,    34,    17,
      36,    37,    18,    39,    40,    19,    42,    43,    51,    57,
      23,    52,    58,    90,    91,    92,    93
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      26,    29,    32,    35,    38,    41,    44,    96,    62,    20,
      45,    64,    80,    81,    82,    48,    83,    50,    54,    56,
      60,    66,    26,    95,    68,    29,    69,    71,    32,    70,
      73,    35,    72,    75,    38,    74,   112,    41,   114,    76,
      44,    77,    80,    81,    82,    94,    83,    84,    85,    86,
      87,    88,    89,     1,     2,     3,     4,     5,     6,     7,
       8,    46,     1,     2,     3,     4,     5,     6,     7,     8,
      80,    81,    82,    78,    83,    79,    47,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,    53,   107,   108,
     109,   110,   115,   116,   117,   118,   119,    55,   120,   121,
     122,   123,    67,    63,    61,    59,     0,    65,   113,   111,
      49
};

static const yytype_int8 yycheck[] =
{
       2,     3,     4,     5,     6,     7,     8,    74,    35,     4,
       0,    38,    19,    20,    21,     4,    23,    15,     5,    16,
       5,    31,    24,    30,     5,    27,     4,     3,    30,     4,
       4,    33,     5,    60,    36,     3,   103,    39,   105,    66,
      42,    68,    19,    20,    21,    72,    23,    24,    25,    26,
      27,    28,    29,     6,     7,     8,     9,    10,    11,    12,
      13,    14,     6,     7,     8,     9,    10,    11,    12,    13,
      19,    20,    21,     4,    23,     3,    10,     4,     4,     3,
       3,     3,     3,     3,     3,     3,     3,    24,     4,     4,
       4,     4,     4,     3,     3,     3,     3,    27,     4,     4,
       4,     4,    42,    36,    33,    30,    -1,    39,   104,   103,
      21
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,     8,     9,    10,    11,    12,    13,    33,
      34,    35,    36,    39,    42,    45,    48,    51,    54,    57,
       4,    37,    38,    62,    40,    41,    62,    43,    44,    62,
      46,    47,    62,    49,    50,    62,    52,    53,    62,    55,
      56,    62,    58,    59,    62,     0,    14,    35,     4,    38,
      15,    60,    63,    41,     5,    44,    16,    61,    64,    47,
       5,    50,    60,    53,    60,    56,    31,    59,     5,     4,
       4,     3,     5,     4,     3,    60,    60,    60,     4,     3,
      19,    20,    21,    23,    24,    25,    26,    27,    28,    29,
      65,    66,    67,    68,    60,    30,    67,     4,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     4,     4,
       4,    66,    67,    68,    67,     4,     3,     3,     3,     3,
       4,     4,     4,     4
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    35,    35,
      35,    35,    35,    36,    37,    37,    38,    39,    40,    40,
      41,    42,    43,    43,    44,    45,    46,    46,    47,    48,
      49,    49,    50,    51,    52,    52,    53,    54,    55,    55,
      56,    57,    58,    58,    59,    60,    60,    60,    60,    61,
      61,    61,    61,    62,    63,    64,    65,    65,    66,    66,
      66,    66,    66,    66,    67,    67,    68,    68,    68,    68
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     2,     2,     2,     1,     2,
       4,     2,     1,     2,     2,     2,     1,     2,     3,     2,
       1,     2,     2,     2,     1,     2,     2,     2,     1,     2,
       3,     2,     1,     2,     3,     5,     3,     3,     1,     1,
       3,     3,     5,     5,     6,     2,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     5,     5,     5,     5
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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
        case 16:
#line 109 "vred.y" /* yacc.c:1646  */
    {
  Vect center((yyvsp[-1].dpval)[0], (yyvsp[-1].dpval)[1], (yyvsp[-1].dpval)[2]);
  Vect size(*((yyvsp[0].bpval)->bp_box_size));
  size *= 2;
  Vect o(0,0,deg((yyvsp[-1].dpval)[3]));
  Tex* t = (yyvsp[0].bpval)->bp_box_tex;
  App* a = (yyvsp[0].bpval)->bp_app;
  Wall *w = new Wall("myWall", center, o, size, TEXTURED, Color::white, *t, *a);
  gr->Add(w);
  free_box_props((yyvsp[0].bpval)); // libere aussi les objets pointes
  delete[]((yyvsp[-1].dpval));
}
#line 1406 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 124 "vred.y" /* yacc.c:1646  */
    {
  Vect center((yyvsp[-3].dpval)[0], (yyvsp[-3].dpval)[1], (yyvsp[-3].dpval)[2]);
  Vect size(*((yyvsp[0].bpval)->bp_box_size));
  size *= 2;
  Vect o(0,0,deg((yyvsp[-3].dpval)[3]));
  Tex* t = (yyvsp[0].bpval)->bp_box_tex;
  App* a = (yyvsp[0].bpval)->bp_app;
  Gate *g = new Gate("myWall", center, o, size, TEXTURED, Color::white, *t, *a,
		     (yyvsp[-2].sval), (yyvsp[-1].sval));
  gr->Add(g);
  cout << *g;
  free_box_props((yyvsp[0].bpval));
  delete[]((yyvsp[-3].dpval));
}
#line 1425 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 141 "vred.y" /* yacc.c:1646  */
    {
  Vect center((yyvsp[-1].dpval)[0], (yyvsp[-1].dpval)[1], (yyvsp[-1].dpval)[2]);
  Vect size((yyvsp[0].spval)->sp_spher_size,(yyvsp[0].spval)->sp_spher_size,(yyvsp[0].spval)->sp_spher_size);
  App* a = (yyvsp[0].spval)->sp_app;
  Earth *s = new Earth("mySphere", center, Vect::null, size, TEXTURED,
		       Color::white, Tex((yyvsp[0].spval)->sp_spher_tex), *a);
  gr->Add(s);
  cout << *s;
  free_spher_props((yyvsp[0].spval));
  delete[]((yyvsp[-1].dpval));
}
#line 1441 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 155 "vred.y" /* yacc.c:1646  */
    {
  Vect center((yyvsp[-2].dpval)[0], (yyvsp[-2].dpval)[1], (yyvsp[-2].dpval)[2]);
  Vect size(*((yyvsp[0].bpval)->bp_box_size));
  size *= 2;
  Vect o(0,0,deg((yyvsp[-2].dpval)[3]));
  Tex* t = (yyvsp[0].bpval)->bp_box_tex;
  App* a = (yyvsp[0].bpval)->bp_app;
  Web *w = new Web("myWall", center, o, size, 
		   TEXTURED, Color::white, *t, *a, (yyvsp[-1].sval));
  gr->Add(w);
  free_box_props((yyvsp[0].bpval));
  delete[]((yyvsp[-2].dpval));
}
#line 1459 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 171 "vred.y" /* yacc.c:1646  */
    {
  Vect center((yyvsp[-1].dpval)[0], (yyvsp[-1].dpval)[1], (yyvsp[-1].dpval)[2]);
  Vect size(*((yyvsp[0].bpval)->bp_box_size));
  size *= 2;
  Vect o(0,0,deg((yyvsp[-1].dpval)[3]));
  Tex* t = (yyvsp[0].bpval)->bp_box_tex;
  App* a = (yyvsp[0].bpval)->bp_app;
  Board *b = new Board("myWall", center, o, size, TEXTURED, Color::white, *t, *a);
  gr->Add(b);
  free_box_props((yyvsp[0].bpval));
  delete[]((yyvsp[-1].dpval));
}
#line 1476 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 186 "vred.y" /* yacc.c:1646  */
    {
  Vect center((yyvsp[-1].dpval)[0], (yyvsp[-1].dpval)[1], (yyvsp[-1].dpval)[2]);
  Vect size(*((yyvsp[0].bpval)->bp_box_size));
  size *= 2;
  Vect o(0,0,deg((yyvsp[-1].dpval)[3]));
  Tex* t = (yyvsp[0].bpval)->bp_box_tex;
  App* a = (yyvsp[0].bpval)->bp_app;
  Step *s = new Step("myWall", center, o, size, TEXTURED, Color::white, *t, *a);
  gr->Add(s);
  free_box_props((yyvsp[0].bpval));
  delete[]((yyvsp[-1].dpval));
}
#line 1493 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 201 "vred.y" /* yacc.c:1646  */
    {
  Vect center((yyvsp[-2].dpval)[0], (yyvsp[-2].dpval)[1], (yyvsp[-2].dpval)[2]);
  Vect size(*((yyvsp[0].bpval)->bp_box_size));
  size *= 2;
  Vect o(0,0,deg((yyvsp[-2].dpval)[3]));
  Tex* t = (yyvsp[0].bpval)->bp_box_tex == NULL ? new Tex() : new Tex(*((yyvsp[0].bpval)->bp_box_tex));
  App* a = (yyvsp[0].bpval)->bp_app == NULL ? new App() : new App(*((yyvsp[0].bpval)->bp_app));
  Host *h = new Host("myWall", center, o, size, 
		   TEXTURED, Color::white, *t, *a, (yyvsp[-1].sval));
  gr->Add(h);
  free_box_props((yyvsp[0].bpval));
  delete[]((yyvsp[-2].dpval));
}
#line 1511 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 217 "vred.y" /* yacc.c:1646  */
    {
  Vect center((yyvsp[-2].dpval)[0], (yyvsp[-2].dpval)[1], (yyvsp[-2].dpval)[2]);
  Vect size(*((yyvsp[0].bpval)->bp_box_size));
  size *= 2;
  Vect o(0,0,deg((yyvsp[-2].dpval)[3]));
  Tex* t = (yyvsp[0].bpval)->bp_box_tex;
  App* a = (yyvsp[0].bpval)->bp_app;
  Doc *d = new Doc("myWall", center, o, size, 
		   TEXTURED, Color::white, *t, *a, (yyvsp[-1].sval));
  gr->Add(d);
  free_box_props((yyvsp[0].bpval));
  delete[]((yyvsp[-2].dpval));
}
#line 1529 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 234 "vred.y" /* yacc.c:1646  */
    {
      struct structBoxProps *res;
      res = (struct structBoxProps *)malloc(sizeof(struct structBoxProps));
      res->bp_box_size = (yyvsp[-4].vectval) ;
      res->bp_box_tex = (yyvsp[-2].texval);
      res->bp_app = (yyvsp[0].appval);
      
      (yyval.bpval) = res;
   }
#line 1543 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 243 "vred.y" /* yacc.c:1646  */
    {
      struct structBoxProps *res;
      res = (struct structBoxProps *)malloc(sizeof(struct structBoxProps));
      res->bp_box_size = (yyvsp[-2].vectval) ;
      res->bp_box_tex = (yyvsp[0].texval);
      res->bp_app = new App();
      
      (yyval.bpval) = res;
   }
#line 1557 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 252 "vred.y" /* yacc.c:1646  */
    {
      struct structBoxProps *res;
      res = (struct structBoxProps *)malloc(sizeof(struct structBoxProps));
      res->bp_box_size = (yyvsp[-2].vectval) ;
      res->bp_box_tex = new Tex();
      res->bp_app = (yyvsp[0].appval);
      
      (yyval.bpval) = res;
   }
#line 1571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 261 "vred.y" /* yacc.c:1646  */
    { 
      struct structBoxProps *res;
      res = (struct structBoxProps *)malloc(sizeof(struct structBoxProps));
      res->bp_box_size = (yyvsp[0].vectval) ;
      res->bp_box_tex = new Tex();
      res->bp_app = new App();
      
      (yyval.bpval) = res;
    }
#line 1585 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 272 "vred.y" /* yacc.c:1646  */
    {
      struct structSpherProps *res;
      res = (struct structSpherProps *)malloc(sizeof(struct structSpherProps));
      res->sp_spher_size = (yyvsp[0].dval) ;
      res->sp_spher_tex = NULL;
      res->sp_app = new App();
      
      (yyval.spval) = res;
   }
#line 1599 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 281 "vred.y" /* yacc.c:1646  */
    {
      struct structSpherProps *res;
      res = (struct structSpherProps *)malloc(sizeof(struct structSpherProps));
      res->sp_spher_size = (yyvsp[-2].dval) ;
      res->sp_spher_tex = (yyvsp[0].sval);
      res->sp_app = new App();
      
      (yyval.spval) = res;
   }
#line 1613 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 290 "vred.y" /* yacc.c:1646  */
    {
      struct structSpherProps *res;
      res = (struct structSpherProps *)malloc(sizeof(struct structSpherProps));
      res->sp_spher_size = (yyvsp[-2].dval) ;
      res->sp_spher_tex = NULL;
      res->sp_app = (yyvsp[0].appval);
      
      (yyval.spval) = res;
   }
#line 1627 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 299 "vred.y" /* yacc.c:1646  */
    {
      struct structSpherProps *res;
      res = (struct structSpherProps *)malloc(sizeof(struct structSpherProps));
      res->sp_spher_size = (yyvsp[-4].dval) ;
      res->sp_spher_tex = (yyvsp[-2].sval);
      res->sp_app = (yyvsp[0].appval);
      
      (yyval.spval) = res;
   }
#line 1641 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 311 "vred.y" /* yacc.c:1646  */
    {
     double *res = new double[5];
     res[0]=(yyvsp[-4].dval); 
     res[1]=(yyvsp[-3].dval); 
     res[2]=(yyvsp[-2].dval); 
     res[3]=(yyvsp[-1].dval); 
     res[4]=(yyvsp[0].dval); 

     (yyval.dpval) = res;
  }
#line 1656 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 322 "vred.y" /* yacc.c:1646  */
    {
  (yyval.vectval) = new Vect((yyvsp[-4].dval), (yyvsp[-2].dval), (yyvsp[0].dval));
}
#line 1664 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 326 "vred.y" /* yacc.c:1646  */
    {
  (yyval.dval) = (yyvsp[0].dval);
}
#line 1672 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 331 "vred.y" /* yacc.c:1646  */
    { (yyval.texval) = (yyvsp[0].texval); }
#line 1678 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 332 "vred.y" /* yacc.c:1646  */
    { 
    mix_texture((yyvsp[0].texval), (yyvsp[-2].texval));
    delete((yyvsp[0].texval));
    (yyval.texval) = (yyvsp[-2].texval);
   }
#line 1688 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 339 "vred.y" /* yacc.c:1646  */
    { (yyval.texval) = new Tex((yyvsp[0].sval), NULL, NULL, NULL, NULL, NULL); }
#line 1694 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 340 "vred.y" /* yacc.c:1646  */
    { (yyval.texval) = new Tex(NULL, (yyvsp[0].sval), NULL, NULL, NULL, NULL); }
#line 1700 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 341 "vred.y" /* yacc.c:1646  */
    { (yyval.texval) = new Tex(NULL, NULL, (yyvsp[0].sval), NULL, NULL, NULL); }
#line 1706 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 342 "vred.y" /* yacc.c:1646  */
    { (yyval.texval) = new Tex(NULL, NULL, NULL, (yyvsp[0].sval), NULL, NULL); }
#line 1712 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 343 "vred.y" /* yacc.c:1646  */
    { (yyval.texval) = new Tex(NULL, NULL, NULL, NULL, (yyvsp[0].sval), NULL); }
#line 1718 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 344 "vred.y" /* yacc.c:1646  */
    { (yyval.texval) = new Tex(NULL, NULL, NULL, NULL, NULL, (yyvsp[0].sval)); }
#line 1724 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 347 "vred.y" /* yacc.c:1646  */
    { (yyval.appval) = (yyvsp[0].appval); }
#line 1730 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 348 "vred.y" /* yacc.c:1646  */
    {
    mix_app((yyvsp[0].appval), (yyvsp[-2].appval));
    delete((yyvsp[0].appval));
    (yyval.appval) = (yyvsp[-2].appval);
  }
#line 1740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 355 "vred.y" /* yacc.c:1646  */
    {
    Color v((yyvsp[-4].dval), (yyvsp[-2].dval), (yyvsp[0].dval), 1.0);
    (yyval.appval) = new App(v);
  }
#line 1749 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 359 "vred.y" /* yacc.c:1646  */
    {
    Color v((yyvsp[-4].dval), (yyvsp[-2].dval), (yyvsp[0].dval), 1.0);
    App *a = new App();
    a->SetDiffuse(v);
    (yyval.appval) = a;
  }
#line 1760 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 365 "vred.y" /* yacc.c:1646  */
    {
    Color v((yyvsp[-4].dval), (yyvsp[-2].dval), (yyvsp[0].dval), 1.0);
    App *a = new App();
    a->SetShininess(v);
    (yyval.appval) = a;
  }
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 371 "vred.y" /* yacc.c:1646  */
    {
    Color v((yyvsp[-4].dval), (yyvsp[-2].dval), (yyvsp[0].dval), 1.0);
    App *a = new App();
    a->SetSpecular(v);
    (yyval.appval) = a;
  }
#line 1782 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1786 "y.tab.c" /* yacc.c:1646  */
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
#line 377 "vred.y" /* yacc.c:1906  */


/*
  Mixe 2 textures : une texture t1 a un seul element, et une texture t2 quelconque.
  ex : t1(a1, NULL, ..., NULL) et t2(b1, ..., b6)
  resultat : t2(a1, b2, ..., b6)
 */
void mix_texture(Tex* t1, Tex* t2){
  if(t1->GetTex_xp() != NULL){
    t2->SetTex_xp(t1->GetTex_xp());
    return ;
  }
  if(t1->GetTex_xn() != NULL){
    t2->SetTex_xn(t1->GetTex_xn());
    return ;
  }
  if(t1->GetTex_yp() != NULL){
    t2->SetTex_yp(t1->GetTex_yp());
    return ;
  }
  if(t1->GetTex_yn() != NULL){
    t2->SetTex_yn(t1->GetTex_yn());
    return ;
  }
  if(t1->GetTex_zp() != NULL){
    t2->SetTex_zp(t1->GetTex_zp());
    return;
  }
  if(t1->GetTex_zn() != NULL){
    t2->SetTex_zn(t1->GetTex_zn());
    return ;
  }
  return ;
}

void mix_app(App* a1, App* a2){
  if(!(a1->GetDiffuse() == a->GetDiffuse())){
    a2->SetDiffuse(a1->GetDiffuse());
    return ;
  }
  if(!(a1->GetAmbient() == a->GetAmbient())){
    a2->SetAmbient(a1->GetAmbient());
    return ;
  }
  if(!(a1->GetSpecular() == a->GetSpecular())){
    a2->SetSpecular(a1->GetSpecular());
    return ;
  }
  if(!(a1->GetShininess() == a->GetShininess())){
    a2->SetShininess(a1->GetShininess());
    return ;
  }
}

double deg(const double rad) {
  return (rad * 180.0 / M_PI);
}

void moveCenter(Vect& center, Vect& size)
{
  center += Vect(size[0], -size[1], size[2]);
}

int FileToGroup(FILE *in, Group *gp) { 
  a = new App();
  //yydebug = 0;   // debogage (yacc)
  //yy_flex_debug = 0;  // pour le debogage (lex)
  // le pointeur global pr pointe vers gp, donc c'est a *gp qu'on ajoute les objects du fichier
  gr = gp;

  yyin = in;
  yylineno = 0;
  delete(a);
  return yyparse();
}

int yyerror(char *s) {
  fprintf(stderr, "line %d:%s\n", yylineno, s);
  return 0;
}

