/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

    #include<stdio.h>
    #include<stdlib.h>
    #include<stdbool.h>
    #include<ctype.h>
    #include<string.h>

    
    #define YYSTYPE double
    #define TABLE_SIZE 100
    #define INT_MIN -2147483648
    #define INTTYPE 2
    #define FLOATTYPE 3
    #define STRINGTYPE 2
    #define CHARTYPE 1
    #define DOUBLETYPE 4
    int yylex();
    extern int yyparse();
    FILE* yyin;
    void yyerror(const char* s);
    double ComputeValue=0;
    int LeftBrackets=0;
    char LastChar=' ';
    char LastKind=' ';
    char DeclID[100]="";
    char LastID[100]="";
    int LastLength=0;
    char AssnID[100]="";
    struct KeyValue {
        char* key;
        double value;
        YYSTYPE* VALUEPTR;
        bool isFunction;
        int kind;
        };
    struct HashTable {
        struct KeyValue table[TABLE_SIZE];
        };
    bool DeclFlag=false;
    bool isAssignment=false;
    struct HashTable ht;
    double get(struct HashTable* ht, const char* key);

#line 115 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NUMBER = 258,                  /* NUMBER  */
    ADD = 259,                     /* ADD  */
    MINUS = 260,                   /* MINUS  */
    DIVIDE = 261,                  /* DIVIDE  */
    MOD = 262,                     /* MOD  */
    TIMES = 263,                   /* TIMES  */
    INT = 264,                     /* INT  */
    FLOAT = 265,                   /* FLOAT  */
    ID = 266,                      /* ID  */
    VOID = 267,                    /* VOID  */
    CONST = 268,                   /* CONST  */
    IF = 269,                      /* IF  */
    ELSE = 270,                    /* ELSE  */
    RETURN = 271,                  /* RETURN  */
    CONTINUE = 272,                /* CONTINUE  */
    BREAK = 273,                   /* BREAK  */
    CHAR = 274,                    /* CHAR  */
    DOUBLE = 275,                  /* DOUBLE  */
    UMINUS = 276                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define NUMBER 258
#define ADD 259
#define MINUS 260
#define DIVIDE 261
#define MOD 262
#define TIMES 263
#define INT 264
#define FLOAT 265
#define ID 266
#define VOID 267
#define CONST 268
#define IF 269
#define ELSE 270
#define RETURN 271
#define CONTINUE 272
#define BREAK 273
#define CHAR 274
#define DOUBLE 275
#define UMINUS 276

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUMBER = 3,                     /* NUMBER  */
  YYSYMBOL_ADD = 4,                        /* ADD  */
  YYSYMBOL_MINUS = 5,                      /* MINUS  */
  YYSYMBOL_DIVIDE = 6,                     /* DIVIDE  */
  YYSYMBOL_MOD = 7,                        /* MOD  */
  YYSYMBOL_TIMES = 8,                      /* TIMES  */
  YYSYMBOL_INT = 9,                        /* INT  */
  YYSYMBOL_FLOAT = 10,                     /* FLOAT  */
  YYSYMBOL_ID = 11,                        /* ID  */
  YYSYMBOL_VOID = 12,                      /* VOID  */
  YYSYMBOL_CONST = 13,                     /* CONST  */
  YYSYMBOL_IF = 14,                        /* IF  */
  YYSYMBOL_ELSE = 15,                      /* ELSE  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_CONTINUE = 17,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 18,                     /* BREAK  */
  YYSYMBOL_CHAR = 19,                      /* CHAR  */
  YYSYMBOL_DOUBLE = 20,                    /* DOUBLE  */
  YYSYMBOL_UMINUS = 21,                    /* UMINUS  */
  YYSYMBOL_22_ = 22,                       /* '{'  */
  YYSYMBOL_23_ = 23,                       /* '}'  */
  YYSYMBOL_24_ = 24,                       /* ';'  */
  YYSYMBOL_25_ = 25,                       /* '('  */
  YYSYMBOL_26_ = 26,                       /* ')'  */
  YYSYMBOL_27_ = 27,                       /* '-'  */
  YYSYMBOL_28_ = 28,                       /* ','  */
  YYSYMBOL_29_ = 29,                       /* '='  */
  YYSYMBOL_YYACCEPT = 30,                  /* $accept  */
  YYSYMBOL_compunit = 31,                  /* compunit  */
  YYSYMBOL_block = 32,                     /* block  */
  YYSYMBOL_lines = 33,                     /* lines  */
  YYSYMBOL_stmt = 34,                      /* stmt  */
  YYSYMBOL_expr = 35,                      /* expr  */
  YYSYMBOL_keyword = 36,                   /* keyword  */
  YYSYMBOL_decl = 37,                      /* decl  */
  YYSYMBOL_assn = 38,                      /* assn  */
  YYSYMBOL_paras = 39,                     /* paras  */
  YYSYMBOL_funcdecl = 40                   /* funcdecl  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   114

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  11
/* YYNRULES -- Number of rules.  */
#define YYNRULES  34
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  61

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   276


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      25,    26,     2,     2,    28,    27,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    24,
       2,    29,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    22,     2,    23,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    53,    53,    54,    57,    58,    61,    62,    63,    64,
      67,    70,    71,    74,    78,    82,    86,    90,    94,    96,
      97,    98,   110,   114,   115,   116,   117,   118,   129,   140,
     152,   166,   167,   170,   173
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUMBER", "ADD",
  "MINUS", "DIVIDE", "MOD", "TIMES", "INT", "FLOAT", "ID", "VOID", "CONST",
  "IF", "ELSE", "RETURN", "CONTINUE", "BREAK", "CHAR", "DOUBLE", "UMINUS",
  "'{'", "'}'", "';'", "'('", "')'", "'-'", "','", "'='", "$accept",
  "compunit", "block", "lines", "stmt", "expr", "keyword", "decl", "assn",
  "paras", "funcdecl", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-37)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -16,   -37,     8,   -37,    40,    17,   -37,   -37,   -37,   -37,
     -37,   -20,   -37,   -37,   -37,   -37,    20,    20,   -37,    64,
       2,   -10,    15,   -37,   -37,    20,    40,   -37,    69,     4,
      20,    20,    20,    20,    20,   -37,    20,   -18,   -37,   -37,
      74,   -37,    -3,    -3,     4,     4,     4,    74,    81,    20,
     -16,    35,   -37,     7,    74,   -37,    25,   -16,    94,   -37,
      28
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       9,     9,     9,     2,     5,     0,     1,     3,    13,    23,
      24,    21,    25,    27,    26,     9,     0,     0,     6,     0,
       0,     0,     0,     8,     4,     0,     7,    21,     0,    20,
       0,     0,     0,     0,     0,    10,     0,    28,    11,    12,
      30,    19,    14,    15,    17,    18,    16,    22,     0,     0,
       9,     0,    31,     0,    29,    34,    28,     9,     0,    33,
      32
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -37,   -37,    -2,    23,   -37,   -15,   -36,     5,   -37,    -1,
     -37
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     4,    18,    19,    20,    21,    22,    53,
      23
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
       7,    28,    29,    32,    33,    34,     1,    48,     6,    25,
      40,    49,    51,    37,    38,    42,    43,    44,    45,    46,
       8,    47,    51,     8,     5,    36,     9,    10,    11,    12,
       1,    27,    36,    57,    54,    58,    13,    14,    26,    39,
      24,    15,    16,     8,    17,    16,    56,    17,    55,     9,
      10,    11,    12,    52,    49,    59,    58,    60,     0,    13,
      14,     0,     0,    52,    15,    16,     0,    17,    30,    31,
      32,    33,    34,    30,    31,    32,    33,    34,    30,    31,
      32,    33,    34,     0,     0,     0,     0,     0,    35,     0,
       9,    10,    36,    12,     0,    41,     0,    36,     0,     0,
      13,    14,    36,     9,    10,     0,    12,    50,     0,     0,
       0,     0,     0,    13,    14
};

static const yytype_int8 yycheck[] =
{
       2,    16,    17,     6,     7,     8,    22,    25,     0,    29,
      25,    29,    48,    11,    24,    30,    31,    32,    33,    34,
       3,    36,    58,     3,     1,    28,     9,    10,    11,    12,
      22,    11,    28,    26,    49,    28,    19,    20,    15,    24,
      23,    24,    25,     3,    27,    25,    11,    27,    50,     9,
      10,    11,    12,    48,    29,    57,    28,    58,    -1,    19,
      20,    -1,    -1,    58,    24,    25,    -1,    27,     4,     5,
       6,     7,     8,     4,     5,     6,     7,     8,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,    24,    -1,
       9,    10,    28,    12,    -1,    26,    -1,    28,    -1,    -1,
      19,    20,    28,     9,    10,    -1,    12,    26,    -1,    -1,
      -1,    -1,    -1,    19,    20
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    22,    31,    32,    33,    33,     0,    32,     3,     9,
      10,    11,    12,    19,    20,    24,    25,    27,    34,    35,
      36,    37,    38,    40,    23,    29,    33,    11,    35,    35,
       4,     5,     6,     7,     8,    24,    28,    11,    24,    24,
      35,    26,    35,    35,    35,    35,    35,    35,    25,    29,
      26,    36,    37,    39,    35,    32,    11,    26,    28,    32,
      39
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    30,    31,    31,    32,    32,    33,    33,    33,    33,
      34,    34,    34,    35,    35,    35,    35,    35,    35,    35,
      35,    35,    35,    36,    36,    36,    36,    36,    37,    37,
      38,    39,    39,    40,    40
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     3,     1,     2,     3,     2,     0,
       2,     2,     2,     1,     3,     3,     3,     3,     3,     3,
       2,     1,     3,     1,     1,     1,     1,     1,     2,     4,
       3,     1,     3,     6,     5
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 10: /* stmt: expr ';'  */
#line 67 "parser.y"
                     {
        printf("Expression value is %f\n",(yyvsp[-1]));
        }
#line 1266 "y.tab.c"
    break;

  case 13: /* expr: NUMBER  */
#line 74 "parser.y"
                   {
                (yyval)=ComputeValue;
                // printf("%f ",ComputeValue);
                }
#line 1275 "y.tab.c"
    break;

  case 14: /* expr: expr ADD expr  */
#line 78 "parser.y"
                          {
                (yyval)=(yyvsp[-2])+(yyvsp[0]);
                // printf("+ ");
                }
#line 1284 "y.tab.c"
    break;

  case 15: /* expr: expr MINUS expr  */
#line 82 "parser.y"
                            {
                (yyval)=(yyvsp[-2])-(yyvsp[0]);
                // printf("- ");
                }
#line 1293 "y.tab.c"
    break;

  case 16: /* expr: expr TIMES expr  */
#line 86 "parser.y"
                            {
                (yyval)=(yyvsp[-2])*(yyvsp[0]);
                // printf("* ");
                }
#line 1302 "y.tab.c"
    break;

  case 17: /* expr: expr DIVIDE expr  */
#line 90 "parser.y"
                             {
                (yyval)=(yyvsp[-2])/(yyvsp[0]);
                // printf("/ ");
                }
#line 1311 "y.tab.c"
    break;

  case 18: /* expr: expr MOD expr  */
#line 94 "parser.y"
                          {
                (yyval)=(int)(yyvsp[-2])%(int)(yyvsp[0]);}
#line 1318 "y.tab.c"
    break;

  case 19: /* expr: '(' expr ')'  */
#line 96 "parser.y"
                       {(yyval)=(yyvsp[-1]);}
#line 1324 "y.tab.c"
    break;

  case 20: /* expr: '-' expr  */
#line 97 "parser.y"
                                  {(yyval)=-(yyvsp[0]);}
#line 1330 "y.tab.c"
    break;

  case 21: /* expr: ID  */
#line 98 "parser.y"
              {
                double value=get(&ht,LastID);
                int k=get_kind(&ht,LastID);
                if(value==INT_MIN)yyerror("varible not found");
                switch(k){
                        case INTTYPE:break;
                        case DOUBLETYPE:break;
                        case FLOATTYPE:break;
                        case CHARTYPE:break;
                }
                (yyval)=value;
                }
#line 1347 "y.tab.c"
    break;

  case 22: /* expr: expr ',' expr  */
#line 110 "parser.y"
                         {(yyval)=(yyvsp[-2]);}
#line 1353 "y.tab.c"
    break;

  case 28: /* decl: keyword ID  */
#line 129 "parser.y"
                        {printf("variable ");
                        if(get_kind(&ht,DeclID)==INTTYPE)
                                printf("int ");
                        else if(get_kind(&ht,DeclID)==FLOATTYPE)
                                printf("float ");
                        else if(get_kind(&ht,DeclID)==DOUBLETYPE)
                                printf("double ");
                        else if(get_kind(&ht,DeclID)==CHARTYPE)
                                printf("char ");
                        printf(DeclID);printf(" is added and set to %f\n",0);
                        }
#line 1369 "y.tab.c"
    break;

  case 29: /* decl: keyword ID '=' expr  */
#line 140 "parser.y"
                                {modify(&ht,DeclID,yyvsp[0]);printf("variable ");
                        if(get_kind(&ht,DeclID)==INTTYPE)
                                printf("int ");
                        else if(get_kind(&ht,DeclID)==FLOATTYPE)
                                printf("float ");
                        else if(get_kind(&ht,DeclID)==DOUBLETYPE)
                                printf("double ");
                        else if(get_kind(&ht,DeclID)==CHARTYPE)
                                printf("char ");
                        printf(DeclID);printf(" is added and set to %f\n",(yyvsp[0]));}
#line 1384 "y.tab.c"
    break;

  case 30: /* assn: ID '=' expr  */
#line 152 "parser.y"
                        {
        double last_value=get(&ht,AssnID);
        modify(&ht,AssnID,(double)(yyvsp[0]));
        int k=get_kind(&ht,LastID);
                switch(k){
                        case INTTYPE:printf("variable %s is set to %d from %d\n",AssnID,(int)(yyvsp[0]),(int)last_value);break;
                        case DOUBLETYPE:printf("variable %s is set to %f from %f\n",AssnID,(yyvsp[0]),last_value);break;
                        case FLOATTYPE:printf("variable %s is set to %f from %f\n",AssnID,(yyvsp[0]),last_value);break;
                        case CHARTYPE:printf("variable %s is set to %c from %c\n",AssnID,(char)(yyvsp[0]),(char)last_value);break;
                }
        isAssignment=false;
        }
#line 1401 "y.tab.c"
    break;

  case 31: /* paras: decl  */
#line 166 "parser.y"
                {printf("in paras\n");}
#line 1407 "y.tab.c"
    break;

  case 33: /* funcdecl: keyword ID '(' paras ')' block  */
#line 170 "parser.y"
                                          {
                                        printf("in function block\n");
                                        }
#line 1415 "y.tab.c"
    break;

  case 34: /* funcdecl: keyword ID '(' ')' block  */
#line 173 "parser.y"
                                    {
                printf("In function block\n");
                }
#line 1423 "y.tab.c"
    break;


#line 1427 "y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 181 "parser.y"



unsigned int hash(const char* key) {
    unsigned int hashValue = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hashValue += (key[i]);
    }

    return hashValue % TABLE_SIZE;
}

void insert(struct HashTable* ht, const char* key, double value, int kind) {
    unsigned int index = hash(key);
    ht->table[index].key = strdup(key);
    //ht->table[index].value = value;
    ht->table[index].VALUEPTR=(double*)malloc(sizeof(double));
    *(ht->table[index].VALUEPTR)=value;
    ht->table[index].kind = kind;
}

double get(struct HashTable* ht, const char* key) {
    unsigned int index = hash(key);
    
    if (ht->table[index].key != NULL && strcmp(ht->table[index].key, key) == 0) {
        return *(ht->table[index].VALUEPTR);
    } else {
        return INT_MIN; 
    }
}

int get_kind(struct HashTable* ht, const char* key) {
    unsigned int index = hash(key);
    
    if (ht->table[index].key != NULL && strcmp(ht->table[index].key, key) == 0) {
        return ht->table[index].kind;
    } else {
        return INT_MIN; 
    }
}

void modify(struct HashTable* ht, const char* key, double newValue) {
    unsigned int index = hash(key);
    printf("new value is %f\n",newValue);
    if (ht->table[index].key != NULL && strcmp(ht->table[index].key, key) == 0) {
        *(ht->table[index].VALUEPTR) = newValue;
        
    } 
}

void modifyFuctionTag(struct HashTable* ht,const char* key){
        unsigned int index=hash(key);
        printf("%s is a function\n",key);
        if(ht->table[index].key!=NULL&&strcmp(ht->table[index].key,key)==0){
                ht->table[index].isFunction=true;
        }
}


bool isDigit(char c){
        if(c>='0'&&c<='9')return true;
        else return false;
}

int yylex(){
    char t;
    while(true){
        t=getchar();
        if(t==' '||t=='\t'||t=='\n'){continue;}
        else if(isDigit(t)){
                double value=(t-'0');
                double resi=0;
                bool Havedot=false;
                t=getc(stdin);
                while(isDigit(t)||t=='.'||t==' '||t=='\n'||t=='\t'){
                        if(!Havedot&&t=='.'){
                                Havedot=true;
                                t=getc(stdin);
                                continue;
                        }
                        else if(t==' '||t=='\n'||t=='\t'){
                                t=getc(stdin);
                                continue;
                        }
                        if(Havedot){
                                //value+=0.1*(t-'0');
                                resi=resi*10+t-'0';
                        }
                        else{
                                value=10*value+t-'0';
                        }

                        if((t=getc(stdin))==EOF){
                                break;       
                        }
                        
                }
                ungetc(t,stdin);

                while(resi>1)resi/=10;
                ComputeValue=value+resi;
                LastChar='0';
                return NUMBER;
        }
        else if(t=='+') {
                printf("ADD \'+\'\n");
                LastChar=t;return ADD;}
        else if(t=='-') {
                if((LastChar>='0'&&LastChar<='9')||LastChar=='d'){//if LastChar is a number or id, means this - should be minus 
                        printf("MINUS \'-\'\n");
                        LastChar=t;
                        return MINUS; 
                }
                else{
                        printf("Negative Number\n");
                        return '-';
                }
                }
        else if(t=='/') {
                printf("DIVIDE \'/\'\n");
                LastChar=t;return DIVIDE;}
        else if(t=='*') {
                printf("TIMES \'*\'\n");
                LastChar=t;return TIMES;}
        else if(t=='%') {
                printf("MOD \'%\'\n");
                LastChar=t;return MOD;}
        else if(t=='(') {
                printf("Left Bracket \'(\'\n");
                LastChar=t;LeftBrackets++;
                if(LastChar=='d')//means a ( appear right after an id, assume it a function
                {
                        modifyFuctionTag(&ht,DeclID);
                }
                return '(';}
        else if(t==')') {
                printf("Right Bracket \')\'\n");
                LastChar=t;LeftBrackets--;return ')';}
        else if(t=='{') {
                printf("Left Brace \'{\'\n");
                LastChar=t;LeftBrackets++;return '{';}
        else if(t=='}') {
                printf("Right Brace \'}\'\n");
                LastChar=t;LeftBrackets--;return '}';}
        else if(t==';') {
                printf("Semicolon \';\'\n");
                return ';';}
        else if(t==',') {
                printf("Comma \',\'\n");
                return ',';}        
        else if((t>='a'&&t<='z')||(t>='A'&&t<='Z')||t=='_'){
                
                char identifier[100]="";
                identifier[0]=t;
                int ptr=1;

                t=getc(stdin);
                while((t>='a'&&t<='z')||(t>='A'&&t<='Z')||t=='_') {
                        identifier[ptr++]=t;
                        t=getc(stdin);
                }
                ungetc(t,stdin);

                if(strcmp(identifier,"int")==0){
                        printf("INT \'int\'\n");
                        DeclFlag=true;
                        LastChar='i';
                        LastKind='i';
                        return INT;
                }
                else if(strcmp(identifier,"float")==0){
                        printf("FLOAT \'float\'\n");
                        DeclFlag=true;
                        LastChar='f';
                        LastKind='f';
                        return FLOAT;
                }
                else if(strcmp(identifier,"double")==0){
                        printf("DOUBLE \'double\'\n");
                        DeclFlag=true;
                        LastChar='D';
                        LastKind='D';//D is double, d is id
                        return DOUBLE;
                }
                else if(strcmp(identifier,"char")==0){
                        printf("CHAR \'char\'\n");
                        DeclFlag=true;
                        LastChar='c';
                        LastKind='c';
                        return CHAR;
                }
                else if(strcmp(identifier,"if")==0){
                        printf("IF \'if\'\n");
                        DeclFlag=true;
                        LastChar='I';
                        LastKind='I';
                        return IF;
                }
                else {
                        if(DeclFlag){
                                if(LastKind=='i')
                                        insert(&ht,identifier,0,INTTYPE);
                                else if(LastKind=='f')
                                        insert(&ht,identifier,0,FLOATTYPE);
                                else if(LastKind=='c')
                                        insert(&ht,identifier,0,CHARTYPE);
                                else if(LastKind=='D')
                                        insert(&ht,identifier,0,DOUBLETYPE);
                                memcpy(DeclID,identifier,(ptr+1)*sizeof(char));
                                DeclFlag=false;
                        }
                        memcpy(LastID,identifier,(100)*sizeof(char));
                        LastLength=ptr+1;
                        printf("Identifier \'");
                        printf(identifier);
                        printf("\'\n");
                        LastChar='d';//d means id
                        return ID;
                }

        }
        else if(t=='='){
                isAssignment=true;
                memcpy(AssnID,LastID,100*sizeof(char));
                printf("Assignment \'=\'\n");
                return '=';
                }
        else if(t=='\''){
                printf("Single Quotation \' \n");
                t=getc(stdin);
                printf("Character %c\n",t);
                char check=getc(stdin);
                if(check!='\'') yyerror("Cannot recognize character");
                else printf("Single Quotation \' \n");
                ComputeValue=(double)t;
                LastChar='0';//same reason as NUMBER
                return NUMBER;
        }
        else return t;
    }
}

int main(){
        yyin=stdin;
        memset(&ht, 0, sizeof(struct HashTable));
        do{
                yyparse();

        }while(!feof(yyin));

        // Clean up allocated memory
        for (int i = 0; i < TABLE_SIZE; ++i) {
                if (ht.table[i].key != NULL) {
                        free(ht.table[i].key);
                }
        }
        return 0;
}
void yyerror(const char* s){
        fprintf(stderr,"parse error: %s\n",s);
        exit(1);
}
