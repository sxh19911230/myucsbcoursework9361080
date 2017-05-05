#include "typecheck.hpp"

//Help Functions
CompoundType getType(TypeCheck*, TypeNode* t);
VariableInfo* getVar(TypeCheck*, std::string t, std::string s="");
MethodInfo*   getMeth(TypeCheck*, std::string t, std::string s="");
bool typeEqual(CompoundType a,CompoundType b);
CompoundType findType(TypeCheck*, ExpressionNode* t);

//std::string c1="class1";

// Defines the function used to throw type errors. The possible
// type errors are defined as an enumeration in the header file.
void typeError(TypeErrorCode code) {
  switch (code) {
    case undefined_variable:
      std::cerr << "Undefined variable." << std::endl;
      break;
    case undefined_method:
      std::cerr << "Method does not exist." << std::endl;
      break;
    case undefined_class:
      std::cerr << "Class does not exist." << std::endl;
      break;
    case undefined_member:
      std::cerr << "Class member does not exist." << std::endl;
      break;
    case not_object:
      std::cerr << "Variable is not an object." << std::endl;
      break;
    case expression_type_mismatch:
      std::cerr << "Expression types do not match." << std::endl;
      break;
    case argument_number_mismatch:
      std::cerr << "Method called with incorrect number of arguments." << std::endl;
      break;
    case argument_type_mismatch:
      std::cerr << "Method called with argument of incorrect type." << std::endl;
      break;
    case while_predicate_type_mismatch:
      std::cerr << "Predicate of while loop is not boolean." << std::endl;
      break;
    case repeat_predicate_type_mismatch:
      std::cerr << "Predicate of repeat loop is not boolean." << std::endl;
      break;
    case if_predicate_type_mismatch:
      std::cerr << "Predicate of if statement is not boolean." << std::endl;
      break;
    case assignment_type_mismatch:
      std::cerr << "Left and right hand sides of assignment types mismatch." << std::endl;
      break;
    case return_type_mismatch:
      std::cerr << "Return statement type does not match declared return type." << std::endl;
      break;
    case constructor_returns_type:
      std::cerr << "Class constructor returns a value." << std::endl;
      break;
    case no_main_class:
      std::cerr << "The \"Main\" class was not found." << std::endl;
      break;
    case main_class_members_present:
      std::cerr << "The \"Main\" class has members." << std::endl;
      break;
    case no_main_method:
      std::cerr << "The \"Main\" class does not have a \"main\" method." << std::endl;
      break;
    case main_method_incorrect_signature:
      std::cerr << "The \"main\" method of the \"Main\" class has an incorrect signature." << std::endl;
      break;
  }
  exit(1);
}

//get Type
CompoundType getType(TypeCheck* tc,TypeNode* t){
  CompoundType tmp;
	
  if (dynamic_cast<IntegerTypeNode*>(t))	
    tmp.baseType=bt_integer;
  
  if (dynamic_cast<BooleanTypeNode*>(t))
    tmp.baseType=bt_boolean;

  if (dynamic_cast<ObjectTypeNode*>(t)) {
    tmp.baseType=bt_object;
	tmp.objectClassName=(dynamic_cast<ObjectTypeNode*>(t))->identifier->name;
	if (tc->classTable->count(tmp.objectClassName) == 0) typeError(undefined_class);
  }
  
  if (dynamic_cast<NoneNode*>(t))
    tmp.baseType=bt_none;

  return tmp;
}

VariableInfo* getVar(TypeCheck* tc, std::string t, std::string s){
	ClassInfo ci;
	
	if (s.compare("") == 0){
		if (tc->currentVariableTable->count(t))
		  return &(*tc->currentVariableTable)[t];
		ci = (*tc->classTable)[tc->currentClassName];
	} else 
		ci = (*tc->classTable)[s];
	
	while (1) {
		if (ci.members->count(t)) return &(*ci.members)[t];
		if (ci.superClassName.compare("") != 0) ci = (*tc->classTable)[ci.superClassName];
		else break;
	}
	
	if (s.compare("") == 0) typeError(undefined_variable);
	else typeError(undefined_member);
	return NULL;
}

MethodInfo* getMeth(TypeCheck* tc, std::string t, std::string s){
	
	ClassInfo ci;
    if (s.compare("") == 0) ci = (*tc->classTable)[tc->currentClassName];
	else ci = (*tc->classTable)[s];
	
	while (1) {
		if (ci.methods->count(t)) return &(*ci.methods)[t];
		if (ci.superClassName.compare("") != 0) ci = (*tc->classTable)[ci.superClassName];
		else break;
	}
	
	
	return NULL;
}

//compare two compindType
bool typeEqual(CompoundType a,CompoundType b){
	if (a.baseType != b.baseType)
		return false;
	if (a.baseType == bt_object && a.objectClassName.compare(b.objectClassName) != 0)
		return false;
	return true;
}

//find Type
CompoundType findType(TypeCheck* tc,ExpressionNode* t){
  CompoundType tmp1;
  CompoundType tmp2;
	
  if (dynamic_cast<PlusNode*>(t)) {
    PlusNode* pn = dynamic_cast<PlusNode*>(t);
	tmp1=findType(tc, pn->expression_1);
	tmp2=findType(tc, pn->expression_2);
	if (tmp1.baseType != bt_integer || tmp2.baseType != bt_integer)
		typeError(expression_type_mismatch);
	return tmp1;	
  }
  
  if (dynamic_cast<MinusNode*>(t)) {
    MinusNode* mn = dynamic_cast<MinusNode*>(t);
	tmp1=findType(tc, mn->expression_1);
	tmp2=findType(tc, mn->expression_2);
	if (tmp1.baseType != bt_integer || tmp2.baseType != bt_integer)
		typeError(expression_type_mismatch);
	return tmp1;	
  }
  
  if (dynamic_cast<TimesNode*>(t)) {
    TimesNode* tn = dynamic_cast<TimesNode*>(t);
	tmp1=findType(tc, tn->expression_1);
	tmp2=findType(tc, tn->expression_2);
	if (tmp1.baseType != bt_integer || tmp2.baseType != bt_integer)
		typeError(expression_type_mismatch);
	return tmp1;	
  }
  
  if (dynamic_cast<DivideNode*>(t)) {
    DivideNode* dn = dynamic_cast<DivideNode*>(t);
	tmp1=findType(tc, dn->expression_1);
	tmp2=findType(tc, dn->expression_2);
	if (tmp1.baseType != bt_integer || tmp2.baseType != bt_integer)
		typeError(expression_type_mismatch);
	return tmp1;	
  }
  
  if (dynamic_cast<LessNode*>(t)) {
    LessNode* ln = dynamic_cast<LessNode*>(t);
	tmp1=findType(tc, ln->expression_1);
	tmp2=findType(tc, ln->expression_2);
	if (tmp1.baseType != bt_integer || tmp2.baseType != bt_integer)
		typeError(expression_type_mismatch);
	tmp1.baseType=bt_boolean;
	return tmp1;	
  }
  
  if (dynamic_cast<LessEqualNode*>(t)) {
    LessEqualNode* ln = dynamic_cast<LessEqualNode*>(t);
	tmp1=findType(tc, ln->expression_1);
	tmp2=findType(tc, ln->expression_2);
	if (tmp1.baseType != bt_integer || tmp2.baseType != bt_integer)
		typeError(expression_type_mismatch);
	tmp1.baseType=bt_boolean;
	return tmp1;	
  }
  
  if (dynamic_cast<EqualNode*>(t)) {
    EqualNode* en = dynamic_cast<EqualNode*>(t);
	tmp1=findType(tc, en->expression_1);
	tmp2=findType(tc, en->expression_2);
	if ((tmp1.baseType != bt_integer && tmp1.baseType != bt_boolean)
	|| (tmp2.baseType != bt_integer && tmp2.baseType != bt_boolean)
	|| tmp1.baseType != tmp2.baseType)
		typeError(expression_type_mismatch);
	tmp1.baseType=bt_boolean;
	return tmp1;	
  }
  
   if (dynamic_cast<AndNode*>(t)) {
    AndNode* an = dynamic_cast<AndNode*>(t);
	tmp1=findType(tc, an->expression_1);
	tmp2=findType(tc, an->expression_2);
	if (tmp1.baseType != bt_boolean || tmp2.baseType != bt_boolean)
		typeError(expression_type_mismatch);
	return tmp1;	
  }
  
  if (dynamic_cast<OrNode*>(t)) {
    OrNode* on = dynamic_cast<OrNode*>(t);
	tmp1=findType(tc, on->expression_1);
	tmp2=findType(tc, on->expression_2);
	if (tmp1.baseType != bt_boolean || tmp2.baseType != bt_boolean)
		typeError(expression_type_mismatch);
	return tmp1;	
  }
  
  if (dynamic_cast<NotNode*>(t)) {
    NotNode* nn = dynamic_cast<NotNode*>(t);
	tmp1=findType(tc, nn->expression);
	if (tmp1.baseType != bt_boolean)
		typeError(expression_type_mismatch);
	return tmp1;	
  }
  
  if (dynamic_cast<NegationNode*>(t)) {
    NegationNode* nn = dynamic_cast<NegationNode*>(t);
	tmp1=findType(tc, nn->expression);
	if (tmp1.baseType != bt_integer)
		typeError(expression_type_mismatch);
	return tmp1;	
  }
  
  if (dynamic_cast<MethodCallNode*>(t)) {
    MethodCallNode * md = dynamic_cast<MethodCallNode*>(t);
	VariableInfo* vi;
	MethodInfo* mi;
	if (md->identifier_2) {
		vi = getVar(tc, md->identifier_1->name);
		if(vi->type.baseType != bt_object) typeError(not_object);
		mi = getMeth(tc, md->identifier_2->name, vi->type.objectClassName);
	} 
	else {
		mi = getMeth(tc, md->identifier_1->name);
	}
	
	if (!mi) typeError(undefined_method);
	
	
	if (md->expression_list == NULL && mi->parameters->size() == 0) {
		return mi->returnType;
	}
	
	
	
	std::list<CompoundType>::iterator it1 = mi->parameters->begin();
	std::list<ExpressionNode*>::iterator it2 = md->expression_list->begin();
		
	while(1) {
		if (it1 == mi->parameters->end() && it2 == md->expression_list->end()) break;
		if (it1 == mi->parameters->end() && it2 != md->expression_list->end()) typeError(argument_number_mismatch);
		if (it1 != mi->parameters->end() && it2 == md->expression_list->end()) typeError(argument_number_mismatch);
		
		if (!typeEqual(*it1, findType(tc, *it2))) typeError(argument_type_mismatch);
		
		it1++; it2++;
	}
	return mi->returnType;
	
  }
  
  if (dynamic_cast<NewNode*>(t)) {
	MethodInfo* mi;
    NewNode* nn = dynamic_cast<NewNode*>(t);
    tmp1.baseType=bt_object;
	tmp1.objectClassName=nn->identifier->name;
	
	mi = getMeth(tc, tmp1.objectClassName, tmp1.objectClassName);
	
	if (nn->expression_list == NULL && (!mi || mi->parameters->size() == 0)) {
		return tmp1;
	}
	
	std::list<CompoundType>::iterator it1 = mi->parameters->begin();
	std::list<ExpressionNode*>::iterator it2 = nn->expression_list->begin();
	
	while(1) {
		if (it1 == mi->parameters->end() && it2 == nn->expression_list->end()) break;
		if (it1 == mi->parameters->end() && it2 != nn->expression_list->end()) typeError(argument_number_mismatch);
		if (it1 != mi->parameters->end() && it2 == nn->expression_list->end()) typeError(argument_number_mismatch);
		
		if (!typeEqual(*it1, findType(tc, *it2))) typeError(argument_type_mismatch);
		
		it1++; it2++;
	}
	
	return tmp1;
  }
  
  if (dynamic_cast<MemberAccessNode*>(t)) {
    MemberAccessNode * mn = dynamic_cast<MemberAccessNode*>(t);
	
	VariableInfo* vi;
	
	vi =getVar(tc,mn->identifier_1->name);
  
    if(vi->type.baseType != bt_object) typeError(not_object);
	
	
    return getVar(tc, mn->identifier_2->name,vi->type.objectClassName)->type;	
	
  }
  
  if (dynamic_cast<VariableNode*>(t)) {
    VariableNode * vn = dynamic_cast<VariableNode*>(t);
    return getVar(tc, vn->identifier->name)->type;
  }
  
  if (dynamic_cast<IntegerLiteralNode*>(t)) {
    tmp1.baseType=bt_integer;
	return tmp1;
  }
  
  if (dynamic_cast<BooleanLiteralNode*>(t)) {
    tmp1.baseType=bt_boolean;
	return tmp1;
  }
  
  
  
  return tmp1;
}

//Check member or local
bool member;


// TypeCheck Visitor Functions: These are the functions you will
// complete to build the symbol table and type check the program.
// Not all functions must have code, many may be left empty.

void TypeCheck::visitProgramNode(ProgramNode* node) {
  this->classTable = new ClassTable();
  node->visit_children(this);
  if (classTable->count("Main") == 0) typeError(no_main_class);
  if ((*classTable)["Main"].methods->count("main") == 0) typeError(no_main_method);
  if ((*(*classTable)["Main"].methods)["main"].returnType.baseType != bt_none
  || (*(*classTable)["Main"].methods)["main"].parameters->size() > 0) typeError(main_method_incorrect_signature);;
}

void TypeCheck::visitClassNode(ClassNode* node) {
  //Insert ClassInfo
  ClassInfo tmp;

  
  if (node->identifier_2) {
    if (this->classTable->count(node->identifier_2->name) == 0) typeError(undefined_class);
    tmp.superClassName=node->identifier_2->name;
  }
  else
    tmp.superClassName="";

  tmp.methods=new MethodTable();
  tmp.members=new VariableTable();
  tmp.membersSize=0;
  
  
  
  
  this->classTable->insert(std::pair<std::string,ClassInfo>(node->identifier_1->name, tmp));
  

  //current
  this->currentClassName=node->identifier_1->name;
  this->currentMethodTable=tmp.methods;
  this->currentVariableTable=tmp.members;
  this->currentMemberOffset = tmp.membersSize;
  
  //Check Main
  if (currentClassName.compare("Main") == 0 && node->declaration_list->size() > 0)
	  typeError(main_class_members_present);
  
  //now member declaration
  member = true;

  
  //visit next
  node->visit_children(this);
  
  //update member size
  (*this->classTable)[node->identifier_1->name].membersSize=this->currentMemberOffset;
  
}

void TypeCheck::visitMethodNode(MethodNode* node) {
	
  
 
  
  //Init MethodInfo
  MethodInfo tmp;  
  VariableInfo paratmp;
  tmp.returnType=getType(this,node->type);
  
  tmp.variables=new VariableTable();
  tmp.parameters=new std::list<CompoundType>();
  
  tmp.localsSize=0;
  
  //Check constuctor return type
  if (this->currentClassName.compare(node->identifier->name) == 0 && tmp.returnType.baseType != bt_none)
	  typeError(constructor_returns_type);
  
  //Insert MethodInfo
  this->currentMethodTable->insert(std::pair<std::string,MethodInfo>(node->identifier->name, tmp));
  
  //current
  this->currentLocalOffset = -4;
  this->currentVariableTable=tmp.variables;
  
  //Insert parameters
  currentParameterOffset = 12;
  for(std::list<ParameterNode*>::iterator iter = node->parameter_list->begin();
        iter != node->parameter_list->end(); iter++) {
      CompoundType t = getType(this, (*iter)->type);
      tmp.parameters->push_back(t);
	  paratmp.type = t;
	  paratmp.offset = currentParameterOffset;
	  paratmp.size = 4;	  
	  this->currentVariableTable->insert(std::pair<std::string,VariableInfo>((*iter)->identifier->name,paratmp));
	  currentParameterOffset+=4;
    }
  
  //now local declaration
  member = false;
  
  //visit next
  node->visit_children(this);
  
  
  //Check returnType
  if (!node->methodbody->returnstatement && tmp.returnType.baseType != bt_none) typeError(return_type_mismatch);
  
  
  if (node->methodbody->returnstatement){
	  
	  CompoundType woca = findType(this, node->methodbody->returnstatement->expression);
	  
	  while (1) {
		  if (typeEqual(tmp.returnType, woca)) break;
		  
		  if ((*classTable)[woca.objectClassName].superClassName.compare("") != 0) woca.objectClassName = (*classTable)[woca.objectClassName].superClassName;
		  
		  //if (ci.superClassName.compare("") != 0) ci = (*tc->classTable)[ci.superClassName];

		  else typeError(return_type_mismatch);
	  }
  }


  /*
  //Check Main return Type
  //In Main?
  
  if (this->currentClassName.compare("Main")==0 && node->identifier->name.compare("main") == 0
  && (tmp.returnType.baseType != bt_none || node->parameter_list->size() > 0)) {
	  typeError(main_method_incorrect_signature);
  }
  */
  //update local size;
  (*this->currentMethodTable)[node->identifier->name].localsSize=currentLocalOffset/(-1)-4;
}

void TypeCheck::visitMethodBodyNode(MethodBodyNode* node) {
  node->visit_children(this);
}

void TypeCheck::visitParameterNode(ParameterNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitDeclarationNode(DeclarationNode* node) {
  VariableInfo tmp;
  tmp.type = getType(this, node->type);
  if (member) tmp.offset=this->currentMemberOffset;
  else tmp.offset=this->currentLocalOffset;
  tmp.size=4;
  for (std::list<IdentifierNode*>::iterator iter = node->identifier_list->begin(); iter != node->identifier_list->end(); iter++){
    this->currentVariableTable->insert(std::pair<std::string,VariableInfo>((*iter)->name,tmp));
	if (member) tmp.offset+=4;
	else tmp.offset-=4;
  }
  if (member) this->currentMemberOffset=tmp.offset;
  else this->currentLocalOffset=tmp.offset;
}

void TypeCheck::visitReturnStatementNode(ReturnStatementNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitAssignmentNode(AssignmentNode* node) {
    CompoundType t;
	
	VariableInfo* vi;
	
	vi =getVar(this,node->identifier_1->name);
	
	if (node->identifier_2) {
      if(vi->type.baseType != bt_object) typeError(not_object);
	  t = getVar(this, node->identifier_2->name,vi->type.objectClassName)->type;	
	} else
	  t = vi->type;
	
    if (!typeEqual(t, findType(this, node->expression))) typeError(assignment_type_mismatch);
}

void TypeCheck::visitCallNode(CallNode* node) {
  findType(this, node->methodcall);
}

void TypeCheck::visitIfElseNode(IfElseNode* node) {
  if (findType(this, node->expression).baseType!=bt_boolean) typeError(if_predicate_type_mismatch);
  node->visit_children(this);
}

void TypeCheck::visitWhileNode(WhileNode* node) {
  if (findType(this, node->expression).baseType!=bt_boolean) typeError(while_predicate_type_mismatch);
  node->visit_children(this);
}

void TypeCheck::visitRepeatNode(RepeatNode* node) {
    if (findType(this, node->expression).baseType!=bt_boolean) typeError(repeat_predicate_type_mismatch);
  node->visit_children(this);
}

void TypeCheck::visitPrintNode(PrintNode* node) {
  // WRITEME: Replace with code if necessary
  findType(this, node->expression);
}

void TypeCheck::visitPlusNode(PlusNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitMinusNode(MinusNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitTimesNode(TimesNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitDivideNode(DivideNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitLessNode(LessNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitLessEqualNode(LessEqualNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitEqualNode(EqualNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitAndNode(AndNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitOrNode(OrNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitNotNode(NotNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitNegationNode(NegationNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitMethodCallNode(MethodCallNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitMemberAccessNode(MemberAccessNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitVariableNode(VariableNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitIntegerLiteralNode(IntegerLiteralNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitBooleanLiteralNode(BooleanLiteralNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitNewNode(NewNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitIntegerTypeNode(IntegerTypeNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitBooleanTypeNode(BooleanTypeNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitObjectTypeNode(ObjectTypeNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitNoneNode(NoneNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitIdentifierNode(IdentifierNode* node) {
  // WRITEME: Replace with code if necessary
}

void TypeCheck::visitIntegerNode(IntegerNode* node) {
  // WRITEME: Replace with code if necessary
}


// The following functions are used to print the Symbol Table.
// They do not need to be modified at all.

std::string genIndent(int indent) {
  std::string string = std::string("");
  for (int i = 0; i < indent; i++)
    string += std::string(" ");
  return string;
}

std::string string(CompoundType type) {
  switch (type.baseType) {
    case bt_integer:
      return std::string("Integer");
    case bt_boolean:
      return std::string("Boolean");
    case bt_none:
      return std::string("None");
    case bt_object:
      return std::string("Object(") + type.objectClassName + std::string(")");
    default:
      return std::string("");
  }
}


void print(VariableTable variableTable, int indent) {
  std::cout << genIndent(indent) << "VariableTable {";
  if (variableTable.size() == 0) {
    std::cout << "}";
    return;
  }
  std::cout << std::endl;
  for (VariableTable::iterator it = variableTable.begin(); it != variableTable.end(); it++) {
    std::cout << genIndent(indent + 2) << it->first << " -> {" << string(it->second.type);
    std::cout << ", " << it->second.offset << ", " << it->second.size << "}";
    if (it != --variableTable.end())
      std::cout << ",";
    std::cout << std::endl;
  }
  std::cout << genIndent(indent) << "}";
}

void print(MethodTable methodTable, int indent) {
  std::cout << genIndent(indent) << "MethodTable {";
  if (methodTable.size() == 0) {
    std::cout << "}";
    return;
  }
  std::cout << std::endl;
  for (MethodTable::iterator it = methodTable.begin(); it != methodTable.end(); it++) {
    std::cout << genIndent(indent + 2) << it->first << " -> {" << std::endl;
    std::cout << genIndent(indent + 4) << string(it->second.returnType) << "," << std::endl;
    std::cout << genIndent(indent + 4) << it->second.localsSize << "," << std::endl;
    print(*it->second.variables, indent + 4);
    std::cout <<std::endl;
    std::cout << genIndent(indent + 2) << "}";
    if (it != --methodTable.end())
      std::cout << ",";
    std::cout << std::endl;
  }
  std::cout << genIndent(indent) << "}";
}

void print(ClassTable classTable, int indent) {
  std::cout << genIndent(indent) << "ClassTable {" << std::endl;
  for (ClassTable::iterator it = classTable.begin(); it != classTable.end(); it++) {
    std::cout << genIndent(indent + 2) << it->first << " -> {" << std::endl;
    if (it->second.superClassName != "")
      std::cout << genIndent(indent + 4) << it->second.superClassName << "," << std::endl;
    print(*it->second.members, indent + 4);
    std::cout << "," << std::endl;
    print(*it->second.methods, indent + 4);
    std::cout <<std::endl;
    std::cout << genIndent(indent + 2) << "}";
    if (it != --classTable.end())
      std::cout << ",";
    std::cout << std::endl;
  }
  std::cout << genIndent(indent) << "}" << std::endl;
}

void print(ClassTable classTable) {
  print(classTable, 0);
}
