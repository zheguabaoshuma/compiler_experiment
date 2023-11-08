%option noyywrap
%option nounput
%option noinput
%top{
    #include <stdarg.h>
    #include "common.h"
    #include "parser.h"
}
%{
    extern dump_type_t dump_type;

    inline void dump_tokens(const char* format, ...){
        va_list args;
        va_start(args, format);
        if (dump_type == TOKENS)
            vfprintf(yyout, format, args);
        va_end(args);
    }

    /* Your code here, if desired (lab3). */
%}

/* definitions section */
DECIMIAL ([1-9][0-9]*|0)
ID [[:alpha:]_][[:alpha:][:digit:]_]*
EOL (\r\n|\n|\r)
INT_BINARY (0[b|B][0|1]+)
INT_HEX [0][Xx]([0-9a-fA-F]+)
INT_OCT [0][0-7]+
FLOAT ([0-9]|[1-9][0-9]+)[.][0-9][0-9]*
FLOATS ([0-9]|[1-9][0-9]+)[.][0-9][0-9]*[eE][+-]([0-9]|[1-9][0-9]+)
COMMENT "//"(.)*{EOL}
COMMENT2 "/*"(.)*"*/"
WHITE [\t ]
/*  Your code here (lab3). */

%%
    /* rules section */
"int" {
    dump_tokens("INT\t%s\n", yytext);
    return INT;
}

"void" {
    dump_tokens("VOID\t%s\n", yytext);
    return VOID;
}

"if" {
    dump_tokens("IF\t%s\n", yytext);
    return IF;
}

"else" {
    dump_tokens("ELSE\t%s\n", yytext);
    return ELSE;
}

"while" {
    dump_tokens("WHILE\t%s\n", yytext);
    return WHILE;
}

"return" {
    dump_tokens("RETURN\t%s\n", yytext);
    return RETURN;
}

"break" {
    dump_tokens("BREAK\t%s\n", yytext);
    return BREAK;
}

"continue" {
    dump_tokens("CONTINUE\t%s\n", yytext);
    return CONTINUE;
}

"=" {
    dump_tokens("ASSIGN\t%s\n", yytext);
    return ASSIGN;
}

"<" {
    dump_tokens("LESS\t%s\n", yytext);
    return LESS;
}

">" {
    dump_tokens("GREATER\t%s\n", yytext);
    return GREATER;
}

"+" {
    dump_tokens("ADD\t%s\n", yytext);
    return ADD;
}

"-" {
    dump_tokens("SUB\t%s\n", yytext);
    return SUB;
}

"*" {
    dump_tokens("MUL\t%s\n", yytext);
    return MUL;
}

"/" {
    dump_tokens("DIV\t%s\n", yytext);
    return DIV;
}

";" {
    dump_tokens("SEMICOLON\t%s\n", yytext);
    return SEMICOLON;
}

"(" {
    dump_tokens("LPAREN\t%s\n", yytext);
    return LPAREN;
}

")" {
    dump_tokens("RPAREN\t%s\n", yytext);
    return RPAREN;
}

"{" {
    dump_tokens("LBRACE\t%s\n", yytext);
    return LBRACE;
}

"}" {
    dump_tokens("RBRACE\t%s\n", yytext);
    return RBRACE;
}

"!" {
    dump_tokens("NOT\t%s\n", yytext);
    return NOT;
}

"," {
    dump_tokens("COMMA\t%s\n", yytext);
    return COMMA;
}

"==" {
    dump_tokens("EQUAL\t%s\n", yytext);
    return EQ;
}

"!=" {
    dump_tokens("NOTEQUAL\t%s\n", yytext);
    return NOTEQ;
}

"<=" {
    dump_tokens("LESSEQUAL\t%s\n", yytext);
    return LESSANDEQ;
}

">=" {
    dump_tokens("GREATEREQUAL\t%s\n", yytext);
    return GREATERANDEQ;
}

"&&" {
    dump_tokens("AND\t%s\n", yytext);
    return AND;
}

"||" {
    dump_tokens("OR\t%s\n", yytext);
    return OR;
}

"++" {
    dump_tokens("INC\t%s\n", yytext);
    return INC;
}

"--" {
    dump_tokens("DEC\t%s\n", yytext);
    return DEC;
}

"float" {
    dump_tokens("FLOAT\t%s\n", yytext);
    return FLOAT;
}

"const" {
    dump_tokens("CONST\t%s\n", yytext);
    return CONST;
}

{DECIMIAL} {
    int decimal;
    decimal = atoi(yytext);
    dump_tokens("DECIMAL\t%s\t%d\n", yytext, decimal);
    yylval.itype = decimal;
    return INTEGER;
}

{ID} {
    char *lexeme;
    dump_tokens("ID\t%s\n", yytext);
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    return ID;
}

{COMMENT} {
    return COMMENT;
}
{COMMENT2} {
    return COMMENT2;
}

{EOL} yylineno++;

{WHITE}

{INT_BINARY} {
    int binary;
    binary = strtol(yytext + 2, NULL, 2);
    dump_tokens("BINARY\t%s\t%d\n", yytext, binary);
    yylval.itype = binary;
    return INTEGER;
}

{INT_HEX} { 
    int hex;
    hex = strtol(yytext + 2, NULL, 16);
    dump_tokens("HEX\t%s\t%d\n", yytext, hex);
    yylval.itype = hex;
    return INTEGER;
}

{INT_OCT} {
    int oct;
    oct = strtol(yytext + 1, NULL, 8);
    dump_tokens("OCT\t%s\t%d\n", yytext, oct);
    yylval.itype = oct;
    return INTEGER;
}

{FLOAT} {
    float f;
    f = atof(yytext);
    dump_tokens("FLOAT\t%s\t%f\n", yytext, f);
    yylval.ftype = f;
    return FLOAT;
}

{FLOATS} {
    float f;
    f = atof(yytext);
    dump_tokens("FLOAT\t%s\t%f\n", yytext, f);
    yylval.ftype = f;
    return FLOAT;
}

    /*  Your code here (lab3). */
%%
/* user code section */
