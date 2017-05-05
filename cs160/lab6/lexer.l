%option yylineno
%pointer

%{
    #include <stdlib.h>
    #include <errno.h>
    #include <limits.h>
    #include "ast.hpp"
    #include "parser.hpp"
    void yyerror(const char *);
%}

/* WRITEME: Copy any definitions and start conditions from Project 3 here */
DIGIT    [0-9]
ID       [a-zA-Z][a-zA-Z0-9]*

%x comment


%%

  /* WRITEME: Copy your Flex rules from Project 3 here */
"/*"                    BEGIN(comment);

<comment>[^*\n\Z]*        ;/* eat anything that's not a '*' */
<comment>"*"+[^*/\n\Z]*   ;/* eat up '*'s not followed by '/'s */
<comment>\n             ;
<comment>"*"+"/"        { BEGIN(INITIAL); } 
<comment><<EOF>>        { yyerror("unexpected eof"); }
  
"return"    { return T_RETURN; }
"if"        { return T_IF; }
"while"     { return T_WHILE; }
"extends"   { return T_EXTENDS; }
"else"      { return T_ELSE; }
"repeat"    { return T_REPEAT; }
"until"     { return T_UNTIL; }
"print"     { return T_PRINT; }
"true"      { return T_TRUE; }
"false"     { return T_FALSE; }
"and"       { return T_AND; }
"or"        { return T_OR; }
"not"       { return T_NOT; }
"new"       { return T_NEW; }

"integer"   { return T_INTEGER; }
"boolean"   { return T_BOOLEAN; }
"none"      { return T_NONE; }

"\."        { return T_DOT; }
";"         { return T_SEMICOLON; }
":"         { return T_COLON; }
","         { return T_COMMA; }
"\("        { return T_OPENPAREN; }
"\)"        { return T_CLOSEPAREN; }
"\{"        { return T_OPENCURLYBRACKET;}
"\}"        { return T_CLOSECURLYBRACKET;}
"->"        { return T_POINTTO; }

"equals"    { return T_EQUAL; }
"="         { return T_ASSIGN; }
"\+"        { return T_PLUS; }
"-"         { return T_MINUS; }
"**"        { return T_EXP; }
"*"         { return T_MULTIPLY; }
"/"         { return T_DIVIDE; }
"%"         { return T_MODULO; }
">="        { return T_GREATEQUAL; }
">"         { return T_GREAT; }
"<="        { return T_LESSEQUAL; }
"<"         { return T_LESS; }

{DIGIT}+    { yylval.integerliteral_ptr = new IntegerLiteralNode(new IntegerNode(atoi( yytext ))); return T_NUMBER; }
{ID}        { yylval.identifier_ptr = new IdentifierNode(yytext); return T_ID; }
          
[ \n\r\t]       ;
.                 { yyerror("invalid character"); }

%%

int yywrap(void) {
  return 1;
}
