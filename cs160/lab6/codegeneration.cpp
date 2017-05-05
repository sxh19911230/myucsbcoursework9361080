#include "codegeneration.hpp"

//help functions


// CodeGenerator Visitor Functions: These are the functions
// you will complete to generate the x86 assembly code. Not
// all functions must have code, many may be left empty.

void CodeGenerator::visitProgramNode(ProgramNode* node) {
    std::cout << " # Start" << std::endl;
	std::cout << " .data" << std::endl;
	std::cout << " printstr: .asciz \"%d\\n\"" << std::endl;
	std::cout << " .text" << std::endl;
	std::cout << " .globl Main_main" << std::endl;
	
	node->visit_children(this);
}

void CodeGenerator::visitClassNode(ClassNode* node) {
	currentClassName = node->identifier_1->name;
	currentClassInfo = (*classTable)[currentClassName];
    node->visit_children(this);
}

void CodeGenerator::visitMethodNode(MethodNode* node) {
	currentMethodName = node->identifier->name;
	currentMethodInfo = (*currentClassInfo.methods)[currentMethodName];
	node->visit_children(this);
}

void CodeGenerator::visitMethodBodyNode(MethodBodyNode* node) {
	//label:
	std::cout << currentClassName << "_" << currentMethodName << ":" << std::endl;
	//Method Prologue
	std::cout << "  # Method Prologue" << std::endl;
    std::cout << "  push %ebp" << std::endl;
	std::cout << "  mov %esp, %ebp" << std::endl;
	//Stack Size
	std::cout << "  sub $" << currentMethodInfo.localsSize <<", %esp" << std::endl;
	
	node->visit_children(this);
	
	std::cout << "  # Method epilogue" << std::endl;
	std::cout << "  add $" << currentMethodInfo.localsSize <<", %esp" << std::endl;
	std::cout << "  pop %ebp" << std::endl;
	std::cout << "  ret" << std::endl;
}

void CodeGenerator::visitParameterNode(ParameterNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitDeclarationNode(DeclarationNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitReturnStatementNode(ReturnStatementNode* node) {
    node->visit_children(this);
	std::cout << "  # ReturnStatement" << std::endl;
	std::cout << "  pop %eax" << std::endl;
}

void CodeGenerator::visitAssignmentNode(AssignmentNode* node) {
    int offset;
	
	node->visit_children(this);
	
	std::string id1ClassName = currentClassName;
	std::string id2ClassName;
	
	std::cout << "  # Assignment" << std::endl;
	
	//identifier_1 is local
    if (currentMethodInfo.variables->count(node->identifier_1->name)) {
		offset = (*currentMethodInfo.variables)[node->identifier_1->name].offset;
		if (node->identifier_2) {
			std::cout << "  mov "<< offset <<"(%ebp), %ecx" << std::endl;
			id2ClassName = (*currentMethodInfo.variables)[node->identifier_1->name].type.objectClassName;
		}
		else {
			std::cout << "  pop %eax" << std::endl;
			std::cout << "  mov %eax, "<< offset <<"(%ebp)" << std::endl;
		}
	}
	//identifier_1 is member
	else {
		while (1) {
			if ((*classTable)[id1ClassName].members->count(node->identifier_1->name)) {
				offset = (*(*classTable)[id1ClassName].members)[node->identifier_1->name].offset;
				if (node->identifier_2) id2ClassName = (*(*classTable)[id1ClassName].members)[node->identifier_1->name].type.objectClassName;
				
				break;
			}
			id1ClassName = (*classTable)[id1ClassName].superClassName;
		}
		id1ClassName = (*classTable)[id1ClassName].superClassName;
		while (id1ClassName.compare("")) {
			offset+= (*classTable)[id1ClassName].membersSize;
			id1ClassName = (*classTable)[id1ClassName].superClassName;
		}
		if (node->identifier_2) {
			std::cout << "mov 8(%ebp), %ebx" << std::endl;
			std::cout << "mov " << offset << "(%ebx), %ecx" << std::endl;
		}
		else {
			std::cout << "pop %eax" << std::endl;
			std::cout << "mov 8(%ebp), %ebx" << std::endl;
			std::cout << "mov %eax, " << offset << "(%ebx)" << std::endl;
		}
	}
	//identifier_2
	if (node->identifier_2) {
		while (1) {
				if ((*classTable)[id2ClassName].members->count(node->identifier_2->name)) {
					offset = (*(*classTable)[id2ClassName].members)[node->identifier_2->name].offset;
					break;
				}
				id2ClassName = (*classTable)[id2ClassName].superClassName;
			}
			id2ClassName = (*classTable)[id2ClassName].superClassName;
			while (id2ClassName.compare("")) {
				offset+= (*classTable)[id2ClassName].membersSize;
				id2ClassName = (*classTable)[id2ClassName].superClassName;
			}
			std::cout << "  pop %eax" << std::endl;
			std::cout << "  mov %eax, "<< offset << "(%ecx)" << std::endl;
	}
}

void CodeGenerator::visitCallNode(CallNode* node) {
	node->visit_children(this);
	std::cout << "  # CallNode" << std::endl;
    std::cout << "  add $4, %esp" << std::endl;
}

void CodeGenerator::visitIfElseNode(IfElseNode* node) {
	int labelFalse,labelNext;

	node->expression->accept(this);
	
	labelFalse = nextLabel();
	labelNext = nextLabel();
	
	std::cout << "  # IfElse" << std::endl;
	std::cout << "  pop %eax" << std::endl;
	std::cout << "  mov $0, %ebx" << std::endl;
	std::cout << "  cmp %eax, %ebx" << std::endl;
	std::cout << "  je .L" << labelFalse << std::endl;
	
	
  if (node->statement_list_1) {
    for(std::list<StatementNode*>::iterator iter = node->statement_list_1->begin();
        iter != node->statement_list_1->end(); iter++) {
      (*iter)->accept(this);
    }
  }
  std::cout << "  jmp .L" << labelNext << std::endl;
  std::cout << ".L" << labelFalse << ":" << std::endl;
  
  if (node->statement_list_2) {
    for(std::list<StatementNode*>::iterator iter = node->statement_list_2->begin();
        iter != node->statement_list_2->end(); iter++) {
      (*iter)->accept(this);
    }
  }
  std::cout << ".L" << labelNext << ":" << std::endl;
  
}

void CodeGenerator::visitWhileNode(WhileNode* node) {
	int labelWhile = nextLabel(), labelFalse = nextLabel();
	
	std::cout << "  # While" << std::endl;
	std::cout << ".L" << labelWhile << ":" << std::endl;

   node->expression->accept(this);
   std::cout << "  pop %eax" << std::endl;
   std::cout << "  mov $0, %ebx" << std::endl;
   std::cout << "  cmp %eax, %ebx" << std::endl;
   std::cout << "  je .L" << labelFalse << std::endl;
   
  if (node->statement_list) {
    for(std::list<StatementNode*>::iterator iter = node->statement_list->begin();
        iter != node->statement_list->end(); iter++) {
      (*iter)->accept(this);
    }
  }
  std::cout << "  jmp .L" << labelWhile << std::endl;
  std::cout << ".L" << labelFalse << ":" << std::endl;
  
}

void CodeGenerator::visitRepeatNode(RepeatNode* node) {
	int labelTrue = nextLabel();
	std::cout << "  # Repeat" << std::endl;
	std::cout << ".L" << labelTrue << ":" << std::endl;
    node->visit_children(this);
	std::cout << "  jnz .L" << labelTrue << std::endl;
	
}

void CodeGenerator::visitPrintNode(PrintNode* node) {
	
	node->visit_children(this);
	std::cout << "  # Print" << std::endl;
    std::cout << "  push $printstr" << std::endl;
	std::cout << "  call printf" << std::endl;
	std::cout << "  add $8, %esp" << std::endl;
}

void CodeGenerator::visitPlusNode(PlusNode* node) {
    node->visit_children(this);
    std::cout << "  # Plus" << std::endl;
    std::cout << "  pop %edx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  add %edx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitMinusNode(MinusNode* node) {
    node->visit_children(this);
    std::cout << "  # Minus" << std::endl;
    std::cout << "  pop %edx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  sub %edx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitTimesNode(TimesNode* node) {
    node->visit_children(this);
    std::cout << "  # Times" << std::endl;
    std::cout << "  pop %edx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  imul %edx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitDivideNode(DivideNode* node) {
    node->visit_children(this);
    std::cout << "  # Divide" << std::endl;
    std::cout << "  pop %ebx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
	std::cout << "  cdq" << std::endl;
    std::cout << "  idiv %ebx" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitLessNode(LessNode* node) {
	int labelTrue,labelNext;
	
    node->visit_children(this);
	
	labelTrue = nextLabel();
	labelNext = nextLabel();
	
	std::cout << "  # Less" << std::endl;
	std::cout << "  pop %eax" << std::endl;
	std::cout << "  pop %ebx" << std::endl;
	std::cout << "  cmp %eax, %ebx" << std::endl;
	
    std::cout << "  jl .L" << labelTrue << std::endl;
	std::cout << "  push $0" << std::endl;
	std::cout << "  jmp .L" << labelNext << std::endl;
	std::cout << ".L" << labelTrue << ":" << std::endl;
	std::cout << "  push $1" << std::endl;
	std::cout << ".L" << labelNext << ":" << std::endl;

}

void CodeGenerator::visitLessEqualNode(LessEqualNode* node) {
	int labelTrue,labelNext;
	
    node->visit_children(this);
	
	labelTrue = nextLabel();
	labelNext = nextLabel();
	
	std::cout << "  # LessEqual" << std::endl;
	std::cout << "  pop %eax" << std::endl;
	std::cout << "  pop %ebx" << std::endl;
	std::cout << "  cmp %eax, %ebx" << std::endl;
	
    std::cout << "  jle .L" << labelTrue << std::endl;
	std::cout << "  push $0" << std::endl;
	std::cout << "  jmp .L" << labelNext << std::endl;
	std::cout << ".L" << labelTrue << ":" << std::endl;
	std::cout << "  push $1" << std::endl;
	std::cout << ".L" << labelNext << ":" << std::endl;
}

void CodeGenerator::visitEqualNode(EqualNode* node) {
	int labelTrue,labelNext;
	
    node->visit_children(this);
	
	labelTrue = nextLabel();
	labelNext = nextLabel();
	
	std::cout << "  # Equal" << std::endl;
	std::cout << "  pop %eax" << std::endl;
	std::cout << "  pop %ebx" << std::endl;
	std::cout << "  cmp %ebx, %eax" << std::endl;
    std::cout << "  je .L" << labelTrue << std::endl;
	std::cout << "  push $0" << std::endl;
	std::cout << "  jmp .L" << labelNext << std::endl;
	std::cout << ".L" << labelTrue << ":" << std::endl;
	std::cout << "  push $1" << std::endl;
	std::cout << ".L" << labelNext << ":" << std::endl;
}

void CodeGenerator::visitAndNode(AndNode* node) {
    int labelFirstFalse,labelSecondFalse,labelNext;
	
	node->visit_children(this);
	
	labelFirstFalse = nextLabel();
	labelSecondFalse = nextLabel();
	labelNext = nextLabel();
	
	std::cout << "  # And" << std::endl;
	std::cout << "  pop %eax" << std::endl;
	std::cout << "  mov $0, %ebx" << std::endl;
	std::cout << "  cmp %eax, %ebx" << std::endl;
	std::cout << "  je .L" << labelFirstFalse << std::endl;
	
	std::cout << "  pop %eax" << std::endl;
	std::cout << "  mov $0, %ebx" << std::endl;
	std::cout << "  cmp %eax, %ebx" << std::endl;
	std::cout << "  je .L" << labelSecondFalse << std::endl;
	
	std::cout << "  push $1" << std::endl;
	std::cout << "  jmp .L" << labelNext << std::endl;
	std::cout << ".L" << labelFirstFalse << ":" << std::endl;
	std::cout << "  add $4, %esp" << std::endl;
	std::cout << ".L" << labelSecondFalse << ":" << std::endl;
	std::cout << "  push $0" << std::endl;
	std::cout << ".L" << labelNext << ":" << std::endl;
}

void CodeGenerator::visitOrNode(OrNode* node) {
    int labelFirstTrue,labelSecondTrue,labelNext;
	
	node->visit_children(this);
	
	labelFirstTrue = nextLabel();
	labelSecondTrue = nextLabel();
	labelNext = nextLabel();
	
	std::cout << "  # Or" << std::endl;
	std::cout << "  pop %eax" << std::endl;
	std::cout << "  mov $0, %ebx" << std::endl;
	std::cout << "  cmp %eax, %ebx" << std::endl;
	std::cout << "  jne .L" << labelFirstTrue << std::endl;
	
	std::cout << "  pop %eax" << std::endl;
	std::cout << "  mov $0, %ebx" << std::endl;
	std::cout << "  cmp %eax, %ebx" << std::endl;
	std::cout << "  jne .L" << labelSecondTrue << std::endl;
	
	std::cout << "  push $0" << std::endl;
	std::cout << "  jmp .L" << labelNext << std::endl;
	std::cout << ".L" << labelFirstTrue << ":" << std::endl;
	std::cout << "  add $4, %esp" << std::endl;
	std::cout << ".L" << labelSecondTrue << ":" << std::endl;
	std::cout << "  push $1" << std::endl;
	std::cout << ".L" << labelNext << ":" << std::endl;
}

void CodeGenerator::visitNotNode(NotNode* node) {
    int labelTrue,labelNext;
	
	node->visit_children(this);
	
	labelTrue = nextLabel();
	labelNext = nextLabel();
	
	std::cout << "  # Not" << std::endl;
	std::cout << "  pop %eax" << std::endl;
	std::cout << "  mov $0, %ebx" << std::endl;
	std::cout << "  cmp %eax, %ebx" << std::endl;
	std::cout << "  je .L" << labelTrue << std::endl;
	std::cout << "  push $0" << std::endl;
	std::cout << "  jmp .L" << labelNext << std::endl;
	std::cout << ".L" << labelTrue << ":" << std::endl;
	std::cout << "  push $1" << std::endl;
	std::cout << ".L" << labelNext << ":" << std::endl;
	
	
}

void CodeGenerator::visitNegationNode(NegationNode* node) {
    node->visit_children(this);
    std::cout << "  # Negation" << std::endl;
    std::cout << "  mov $-1, %edx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  imul %edx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitMethodCallNode(MethodCallNode* node) {
	std::string thisClassName, thisMethodName;
    
	//Pre-call sequence
	std::cout << "  #Pre-call sequence" << std::endl;
	//push arguments
	//node->visit_children(this);
	
	if (node->expression_list) {
      for(std::list<ExpressionNode*>::reverse_iterator iter = node->expression_list->rbegin();
          iter != node->expression_list->rend(); iter++) {
        (*iter)->accept(this);
      }
    }
	
	//push self pointer
	//not member method
	if (node->identifier_2) {
		int offset;
		std::string id1ClassName = currentClassName;
		
		thisMethodName = node->identifier_2->name;
		
		//id_1 is local
		if (currentMethodInfo.variables->count(node->identifier_1->name)) {
		
			std::cout << "  mov "
			<< (*currentMethodInfo.variables)[node->identifier_1->name].offset
			<< "(%ebp), %eax" << std::endl;
			
			thisClassName = (*currentMethodInfo.variables)[node->identifier_1->name].type.objectClassName;
			
		} 
		//id_1 is member
		else {
			
			while (1) {
				if ((*classTable)[id1ClassName].members->count(node->identifier_1->name)) {
					offset = (*(*classTable)[id1ClassName].members)[node->identifier_1->name].offset;
					thisClassName = (*(*classTable)[id1ClassName].members)[node->identifier_1->name].type.objectClassName;
					break;
				}
				id1ClassName = (*classTable)[id1ClassName].superClassName;
			}
			id1ClassName = (*classTable)[id1ClassName].superClassName;
			while (id1ClassName.compare("")) {
				offset+= (*classTable)[id1ClassName].membersSize;
				id1ClassName = (*classTable)[id1ClassName].superClassName;
			}
			std::cout << "  mov 8(%ebp), %ebx" << std::endl;
			std::cout << "  mov " << offset	<< "(%ebx), %eax" << std::endl;
			
			
		}
		
	}
	//member method
	else {
		std::cout << "  mov 8(%ebp), %eax" << std::endl;
		thisClassName = currentClassName;
		thisMethodName = node->identifier_1->name;
	}
	
	std::cout << "  push %eax" << std::endl;
	
	//find the exact class name
	while (1) {
		if ((*classTable)[thisClassName].methods->count(thisMethodName)) break;
		thisClassName = (*classTable)[thisClassName].superClassName;
	}
	
	//Call
	std::cout << "  call " << thisClassName << "_" << thisMethodName << std::endl;
	
	
	//Post-Return Sequence
	std::cout << "  #Post-Return Sequence" << std::endl;
	
	//remove arguments
	if (node->expression_list)
		std::cout << "  add $" << node->expression_list->size() * 4 + 4 << ", %esp" << std::endl;
	else 
		std::cout << "  add $" << 4 << ", %esp" << std::endl;
	
	//push return value
	std::cout << "  push %eax" << std::endl;	
}

void CodeGenerator::visitMemberAccessNode(MemberAccessNode* node) {
	int offset;
	
	std::string id1ClassName = currentClassName;
	std::string id2ClassName;
	
	std::cout << "  # MemberAcces" << std::endl;
	
	//identifier_1 is local
    if (currentMethodInfo.variables->count(node->identifier_1->name)) {
		offset = (*currentMethodInfo.variables)[node->identifier_1->name].offset;
		std::cout << "mov "<< offset <<"(%ebp), %ecx" << std::endl;
		id2ClassName = (*currentMethodInfo.variables)[node->identifier_1->name].type.objectClassName;
	}
	//identifier_1 is member
	else {
		while (1) {
			if ((*classTable)[id1ClassName].members->count(node->identifier_1->name)) {
				offset = (*(*classTable)[id1ClassName].members)[node->identifier_1->name].offset;
				id2ClassName = (*(*classTable)[id1ClassName].members)[node->identifier_1->name].type.objectClassName;
				break;
			}
			id1ClassName = (*classTable)[id1ClassName].superClassName;
		}
		id1ClassName = (*classTable)[id1ClassName].superClassName;
		while (id1ClassName.compare("")) {
			offset+= (*classTable)[id1ClassName].membersSize;
			id1ClassName = (*classTable)[id1ClassName].superClassName;
		}
		
		std::cout << "mov 8(%ebp), %ebx" << std::endl;
		std::cout << "mov " << offset << "(%ebx), %ecx" << std::endl;
	}
	
	//identifier_2
	while (1) {
			if ((*classTable)[id2ClassName].members->count(node->identifier_2->name)) {
				offset = (*(*classTable)[id2ClassName].members)[node->identifier_2->name].offset;
				break;
			}
			id2ClassName = (*classTable)[id2ClassName].superClassName;
		}
		id2ClassName = (*classTable)[id2ClassName].superClassName;
		while (id2ClassName.compare("")) {
			offset+= (*classTable)[id2ClassName].membersSize;
			id2ClassName = (*classTable)[id2ClassName].superClassName;
		}
		
		std::cout << "  mov "<< offset << "(%ecx), %eax" << std::endl;
		std::cout << "  push %eax" << std::endl;

}

void CodeGenerator::visitVariableNode(VariableNode* node) {
	int offset;
	
	std::string id1ClassName = currentClassName;
	
	std::cout << "  # Variable" << std::endl;
	
    //identifier is local
    if (currentMethodInfo.variables->count(node->identifier->name)) {
		offset = (*currentMethodInfo.variables)[node->identifier->name].offset;
		std::cout << "  mov "<< offset <<"(%ebp), %eax" << std::endl;
	}
	//identifier is member
	else {
		while (1) {
			if ((*classTable)[id1ClassName].members->count(node->identifier->name)) {
				offset = (*(*classTable)[id1ClassName].members)[node->identifier->name].offset;
				break;
			}
			id1ClassName = (*classTable)[id1ClassName].superClassName;
		}
		id1ClassName = (*classTable)[id1ClassName].superClassName;
		while (id1ClassName.compare("")) {
			offset+= (*classTable)[id1ClassName].membersSize;
			id1ClassName = (*classTable)[id1ClassName].superClassName;
		}
		
		std::cout << "  mov 8(%ebp), %ebx" << std::endl;
		std::cout << "  mov " << offset << "(%ebx), %eax" << std::endl;
		
	}
	std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitIntegerLiteralNode(IntegerLiteralNode* node) {
    std::cout << "  # IntegerLiteral" << std::endl;
	std::cout << "  push $" << node->integer->value << std::endl;
}

void CodeGenerator::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    std::cout << "  # BooleanLiteral" << std::endl;
	std::cout << "  push $" << node->integer->value << std::endl;
}

void CodeGenerator::visitNewNode(NewNode* node) {
    int size = 0;
	
	std::string thisClassName = node->identifier->name;
	
	while (thisClassName.compare("")) {
		size+= (*classTable)[thisClassName].membersSize;
		thisClassName = (*classTable)[thisClassName].superClassName;
	}
	
	std::cout << "  push $" << size << std::endl;
	std::cout << "  call malloc" << std::endl;
	std::cout << "  add $4, %esp" << std::endl;
	std::cout << "  push %eax" << std::endl;
	
	
	//if have constructor
	if ((*classTable)[node->identifier->name].methods->count(node->identifier->name)) {
		//Pre-call sequence
		std::cout << "  #Pre-call sequence" << std::endl;
		//push arguments
		//node->visit_children(this);
		if (node->expression_list) {
          for(std::list<ExpressionNode*>::reverse_iterator iter = node->expression_list->rbegin();
            iter != node->expression_list->rend(); iter++) {
              (*iter)->accept(this);
          }
        }
		
		//self pointer
		if (node->expression_list)
			std::cout << "  mov " << node->expression_list->size() * 4 << "(%esp), %eax" << std::endl;
		else
			std::cout << "  mov " << "(%esp), %eax" << std::endl;
		std::cout << "  push %eax" << std::endl;
		std::cout << "  call " << node->identifier->name << "_" << node->identifier->name << std::endl;
		//Post-Return Sequence
		std::cout << "  #Post-Return Sequence" << std::endl;
		
		//remove arguments
		if (node->expression_list)
			std::cout << "  add $" << node->expression_list->size() * 4 + 4 << ", %esp" << std::endl;
		else 
			std::cout << "  add $" << 4 << ", %esp" << std::endl;
	}
}

void CodeGenerator::visitIntegerTypeNode(IntegerTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitBooleanTypeNode(BooleanTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitObjectTypeNode(ObjectTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitNoneNode(NoneNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitIdentifierNode(IdentifierNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitIntegerNode(IntegerNode* node) {
    // WRITEME: Replace with code if necessary
}
