%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>

    #include "ast.hpp"
    #define YYINITDEPTH 500    
    #define YYDEBUG 1
    int yylex(void);
    void yyerror(const char *);
    
    extern ASTNode* astRoot;
	
	bool wrong1 = false;
	ASTNode* tmp1;
	bool wrong2 = false;
	ASTNode* tmp2;
%}

%error-verbose

/* WRITEME: Copy your token and precedence specifiers from Project 3 here */
%token T_RETURN T_IF T_WHILE T_EXTENDS T_ELSE T_REPEAT T_UNTIL T_PRINT
%token T_TRUE T_FALSE T_AND T_OR T_NOT T_NEW T_INTEGER T_BOOLEAN T_NONE
%token T_DOT T_SEMICOLON T_COLON T_COMMA T_OPENPAREN T_CLOSEPAREN
%token T_OPENCURLYBRACKET T_CLOSECURLYBRACKET T_POINTTO T_EQUAL
%token T_ASSIGN T_PLUS T_MINUS T_MULTIPLY T_DIVIDE T_MODULO T_LESSEQUAL
%token T_LESS T_NUMBER T_ID T_GREATEQUAL T_GREAT T_EXP


%left T_OR
%left T_AND
%left T_LESS T_LESSEQUAL T_EQUAL
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE
%right T_NOT
%right UMINUS

/* WRITEME: Specify types for all nonterminals and necessary terminals here */

%type <class_list_ptr> ClassList
%type <class_ptr> Class
%type <declaration_list_ptr> MemberList 
%type <method_list_ptr> MethodList
%type <parameter_list_ptr> ParaListP ParaList
%type <methodbody_ptr> MethodBody
%type <program_ptr> Start
%type <declaration_list_ptr> DecList
%type <type_ptr> TypeID
%type <statement_list_ptr> StatList Else
%type <expression_list_ptr> ArguList ArguListP
%type <methodcall_ptr> MethodCall
%type <expression_ptr> Expression
%type <identifier_ptr> ExtendsID T_ID IdentifierP
%type <method_ptr> Method
%type <returnstatement_ptr> ReturnOp
%type <assignment_ptr> Assignment
%type <ifelse_ptr> IfElse
%type <while_ptr>  WhileLoop
%type <repeat_ptr> RepeatUntil
%type <print_ptr> Print
%type <statement_ptr> Statement
%type <integerliteral_ptr> T_NUMBER
%type <identifier_list_ptr> IDList


%%

/* WRITEME: This rule is a placeholder. Replace it with your grammar
            rules from Project 3 */

Start      : ClassList {$$ = new ProgramNode($1); astRoot = $$; }
           ;

/* WRITME: Write your Bison grammar specification here */

ClassList  : Class ClassList { $$ = $2; $$->push_front($1); }
           |				 { $$ = new std::list<ClassNode*>(); }
		   ;

Class      : T_ID ExtendsID T_OPENCURLYBRACKET MemberList MethodList T_CLOSECURLYBRACKET {if(wrong1) $5->push_front(dynamic_cast<MethodNode*>(tmp1)); wrong1 = false; $$ = new ClassNode($1, $2,$4,$5);}
		   ;
		   
ExtendsID  : T_EXTENDS T_ID {$$ = $2;}
		   | {$$ = NULL;}
		   ;

MemberList : TypeID T_ID T_SEMICOLON MemberList { $$ = $4; std::list<IdentifierNode*>* t = new std::list<IdentifierNode*>(); t->push_front($2); $$->push_front(new DeclarationNode($1, t)); }
           | Method { $$ = new std::list<DeclarationNode*>(); wrong1 = true; tmp1 = $1;}
		   | { $$ = new std::list<DeclarationNode*>(); }
           ;
		   

MethodList : Method MethodList {$$ = $2; $$->push_front($1); }
		   | {$$ = new std::list<MethodNode*>(); }
		   ;
		   
Method	   : T_ID T_OPENPAREN ParaList T_CLOSEPAREN T_POINTTO TypeID T_OPENCURLYBRACKET MethodBody T_CLOSECURLYBRACKET {$$ = new MethodNode($1, $3, $6, $8);}
		   ;
		   
ParaList    : T_ID T_COLON TypeID ParaListP {$$ = $4; $$->push_front(new ParameterNode($3, $1));}
           | {$$ = new std::list<ParameterNode*>();}
		   ;
		 
ParaListP  : T_COMMA T_ID T_COLON TypeID ParaListP {$$ = $5; $$->push_front(new ParameterNode($4,$2));}
           |  {$$ = new std::list<ParameterNode*>();}
		   ;

MethodBody  : DecList StatList ReturnOp { if (wrong2) $2->push_front(dynamic_cast<StatementNode*>(tmp2)); wrong2 = false; $$ = new MethodBodyNode($1,$2,$3); }
		    ;
			
DecList    : TypeID T_ID IDList T_SEMICOLON DecList {$$ = $5; $3->push_front($2);$$->push_front(new DeclarationNode($1, $3));}
           | Statement {$$ = new std::list<DeclarationNode*>(); wrong2 = true; tmp2 = $1;}
		   | {$$ = new std::list<DeclarationNode*>();}
		   ;
		   
TypeID       : T_INTEGER {$$ = new IntegerTypeNode();}
           | T_BOOLEAN {$$ = new BooleanTypeNode();}
		   | T_NONE {$$ = new NoneNode(); }
		   | T_ID {$$ = new ObjectTypeNode($1); }
		   ;


IDList     : T_COMMA T_ID IDList {$$ = $3; $$->push_front($2);}
		   | {$$ = new std::list<IdentifierNode*>();}
		   ;
		   
StatList   : Statement StatList {$$ = $2; $$->push_front($1);}
           | {$$ = new std::list<StatementNode*>();}
		   ;

Statement  : Assignment {$$ = $1;}
           | MethodCall T_SEMICOLON {$$ = new CallNode($1);}
		   | IfElse {$$ = $1;}
		   | WhileLoop {$$ = $1;}
		   | RepeatUntil {$$ = $1;}
		   | Print {$$ = $1;}
		   ;

ReturnOp   : T_RETURN Expression T_SEMICOLON {$$ = new ReturnStatementNode($2);}
           | {$$ = NULL;}
		   ;

Assignment : T_ID IdentifierP T_ASSIGN Expression T_SEMICOLON {$$ = new AssignmentNode($1, $2, $4);}
           ;

IdentifierP : T_DOT T_ID {$$ = $2;}
           | {$$ = NULL;}
		   ;
		   
IfElse     : T_IF Expression T_OPENCURLYBRACKET Statement StatList T_CLOSECURLYBRACKET Else {$5->push_front($4); $$ = new IfElseNode($2,$5,$7);}
           ;
		   
Else       : T_ELSE T_OPENCURLYBRACKET Statement StatList T_CLOSECURLYBRACKET {$$ = $4; $$->push_front($3);}
           | {$$ = NULL; }
		   ;
		   
WhileLoop  : T_WHILE Expression T_OPENCURLYBRACKET Statement StatList T_CLOSECURLYBRACKET {$5->push_front($4); $$ = new WhileNode(($2), $5); }
           ;
		   
RepeatUntil : T_REPEAT T_OPENCURLYBRACKET Statement StatList T_CLOSECURLYBRACKET T_UNTIL T_OPENPAREN Expression T_CLOSEPAREN T_SEMICOLON {$4->push_front($3); $$ = new RepeatNode($4,$8);}
            ;
			
Print      : T_PRINT Expression T_SEMICOLON {$$ = new PrintNode($2);}
           ;
		   
Expression : Expression T_PLUS Expression {$$ = new PlusNode($1,$3);}
           | Expression T_MINUS Expression {$$ = new MinusNode($1,$3);}
		   | Expression T_MULTIPLY Expression {$$ = new TimesNode($1,$3);}
		   | Expression T_DIVIDE Expression {$$ = new DivideNode($1,$3);}
		   | Expression T_LESS Expression {$$ = new LessNode($1,$3); }
		   | Expression T_LESSEQUAL Expression {$$ = new LessEqualNode($1,$3); }
		   | Expression T_EQUAL Expression {$$= new EqualNode($1,$3); }
		   | Expression T_AND Expression {$$ = new AndNode($1,$3); }
		   | Expression T_OR Expression {$$ = new OrNode($1,$3); }
		   | T_NOT Expression {$$ = new NotNode($2); }
		   | T_MINUS Expression %prec UMINUS {$$ = new NegationNode($2);}
		   | T_ID {$$ = new VariableNode($1);}
		   | T_ID T_DOT T_ID  {$$ = new MemberAccessNode($1,$3);}
		   | MethodCall {$$ = $1;}
		   | T_OPENPAREN Expression T_CLOSEPAREN { $$ = $2;}
		   | T_NUMBER {$$ = $1;}
		   | T_TRUE   {$$ = new BooleanLiteralNode(new IntegerNode(1));}
		   | T_FALSE  {$$ = new BooleanLiteralNode(new IntegerNode(0));}
		   | T_NEW T_ID {$$ = new NewNode($2,NULL);}
		   | T_NEW T_ID T_OPENPAREN ArguList T_CLOSEPAREN {$$ = new NewNode($2,$4);}
		   ;
		
		
ArguList   : Expression ArguListP {$$ = $2; $$->push_front($1);}
           | {$$ = NULL;}
		   ;
		   
ArguListP  : T_COMMA Expression ArguListP {$$ = $3; $$->push_front($2);}
           | {$$ = new std::list<ExpressionNode*>();  }
		   ;
		   
MethodCall  : T_ID IdentifierP T_OPENPAREN ArguList T_CLOSEPAREN {$$ = new MethodCallNode($1,$2,$4);}
            ;

%%

extern int yylineno;

void yyerror(const char *s) {
  fprintf(stderr, "%s at line %d\n", s, yylineno);
  exit(0);
}
