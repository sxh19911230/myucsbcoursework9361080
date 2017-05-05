%option yylineno
%pointer

%{
    #include <cstdlib>
    #include <cerrno>
    #include <climits>
    #include <limits>
    #include "parser.hpp"
    
	void yyerror(const char *);
%}

/* WRITEME: Write any definitions here. You can find information on
            definitions here:
            http://flex.sourceforge.net/manual/Definitions-Section.html */

DIGIT    [0-9]
ID       [a-z][a-z0-9]*

/* WRITEME: If you are going to use start conditions, write them here.
            You can find more information on start conditions here:
            http://flex.sourceforge.net/manual/Start-Conditions.html
            You will probably want to use exclusive conditions rather
            than inclusive conditions (use the %x instead of the %s). */

%x comment

%%


  /* WRITEME: Write your Flex token rules here */


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

{DIGIT}+    { return T_NUMBER; }
{ID}        { return T_ID; }
          
[ \n\t]       ;



.           { yyerror("invalid character"); }

%%


int yywrap(void) {
  return 1;
}
