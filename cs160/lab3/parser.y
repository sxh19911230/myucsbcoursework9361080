%{
    #include <cstdlib>
    #include <cstdio>
    #include <iostream>

    #define YYDEBUG 1

    int yylex(void);
    void yyerror(const char *);
%}

%error-verbose

/* WRITEME: List all your tokens here */

%token T_RETURN T_IF T_WHILE T_EXTENDS T_ELSE T_REPEAT T_UNTIL T_PRINT
%token T_TRUE T_FALSE T_AND T_OR T_NOT T_NEW T_INTEGER T_BOOLEAN T_NONE
%token T_DOT T_SEMICOLON T_COLON T_COMMA T_OPENPAREN T_CLOSEPAREN
%token T_OPENCURLYBRACKET T_CLOSECURLYBRACKET T_POINTTO T_EQUAL
%token T_ASSIGN T_PLUS T_MINUS T_MULTIPLY T_DIVIDE T_MODULO T_LESSEQUAL
%token T_LESS T_NUMBER T_ID T_GREATEQUAL T_GREAT T_EXP




/* WRITEME: Specify precedence here */
%left T_OR
%left T_AND
%left T_LESS T_LESSEQUAL T_EQUAL
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE

%%

/* WRITEME: This rule is a placeholder, since Bison requires
            at least one rule to run successfully. Replace
            this with your appropriate start rules. */
Start      : ClassList
           ;

/* WRITME: Write your Bison grammar specification here */

ClassList  : Class ClassList
           |
		   ;

Class      : T_ID T_OPENCURLYBRACKET MemberList T_CLOSECURLYBRACKET
           | T_ID T_EXTENDS T_ID T_OPENCURLYBRACKET MemberList T_CLOSECURLYBRACKET
		   ;

MemberList : Type T_ID T_SEMICOLON MemberList
	   | MethodList
	   ;

MethodList : T_ID T_OPENPAREN ParaList T_CLOSEPAREN T_POINTTO Type T_OPENCURLYBRACKET DecList  ReturnOp T_CLOSECURLYBRACKET MethodList
	   |
	   ;
		   
ParaList    : T_ID T_COLON Type ParaListP
           |
		   ;
		 
ParaListP   : T_COMMA T_ID T_COLON Type ParaListP
           |
		   ;

DecList    : Type T_ID IDList T_SEMICOLON DecList
           | StatList
		   ;
		   
Type       : T_INTEGER
           | T_BOOLEAN
		   | T_NONE
		   | T_ID
		   ;


IDList     : T_COMMA T_ID IDList
           |
		   ;
		   
StatList   : Statement StatList 
           | 
		   ;

Statement  : Assignment
           | MethodCall
		   | IfElse
		   | WhileLoop
		   | RepeatUntil
		   | Print
		   ;

ReturnOp   : T_RETURN Expression T_SEMICOLON
           |
		   ;

Assignment : T_ID IdentifierP T_ASSIGN Expression T_SEMICOLON
           ;

IdentifierP : T_DOT T_ID
           | 
		   ;
		   
IfElse     : T_IF Expression T_OPENCURLYBRACKET Statement StatList T_CLOSECURLYBRACKET Else
           ;
		   
Else       : T_ELSE T_OPENCURLYBRACKET Statement StatList T_CLOSECURLYBRACKET
           |
		   ;
		   
WhileLoop  : T_WHILE Expression T_OPENCURLYBRACKET Statement StatList T_CLOSECURLYBRACKET
           ;
		   
RepeatUntil : T_REPEAT T_OPENCURLYBRACKET Statement StatList T_CLOSECURLYBRACKET T_UNTIL T_OPENPAREN Expression T_CLOSEPAREN T_SEMICOLON
            ;
			
Print      : T_PRINT Expression T_SEMICOLON
           ;
		   
Expression : Expression T_PLUS Expression
           | Expression T_MINUS Expression
		   | Expression T_MULTIPLY Expression
		   | Expression T_DIVIDE Expression
		   | Expression T_LESS Expression
		   | Expression T_LESSEQUAL Expression
		   | Expression T_EQUAL Expression
		   | Expression T_AND Expression
		   | Expression T_OR Expression
		   | T_NOT Expression
		   | T_MINUS Expression
		   | T_ID
		   | T_ID T_DOT T_ID
		   | MethodCall
		   | T_OPENPAREN Expression T_CLOSEPAREN
		   | T_NUMBER
		   | T_TRUE
		   | T_FALSE
		   | T_NEW T_ID
		   | T_NEW T_ID T_OPENPAREN ArguList T_CLOSEPAREN
		   ;
		
ArguList   : ArguListP
           | 
		   ;
		   
ArguListP  : ArguList T_COMMA Expression
           | Expression
		   ;
		   
MethodCall  : T_ID T_OPENPAREN ArguList T_CLOSEPAREN
            | T_ID T_DOT T_ID T_OPENPAREN ArguList T_CLOSEPAREN
%%

extern int yylineno;

void yyerror(const char *s) {
  fprintf(stderr, "%s at line %d\n", s, yylineno);
  exit(1);
}
