#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include "exp.h"
#include <vector> 
#include <stack>

using namespace std;

int fields = 1;

extern "C" ofstream xml_out;

  // the constructor for node links the node to its children,
  // and stores the character representation of the operator.

  operator_node::operator_node(exp_node *L, exp_node *R) {
    left    = L;
    right   = R;
  }

  
int_node::int_node(int value) 
{
    num = value;
}
  
void int_node:: print() 
{
    xml_out << "<integer value='" << num << "'/>" << endl;
}

int int_node::evaluate() 
{ 
    return 1; 
}

boolean_node::boolean_node(bool value) 
{
    num = value;
}
  
void boolean_node:: print() 
{
	if(num)
    		xml_out << "<boolean value='true'/>" << endl;
	else
		xml_out << "<boolean value='false'/>" << endl;
}

int boolean_node::evaluate() 
{ 
    return 3; 
}

char_node::char_node(char value) 
{
    num = value;
}
  
void char_node:: print() 
{
    xml_out << "character value='" << num << "'/>" << endl;
}

int char_node::evaluate() 
{ 
    return 2; 
}

id_node::id_node(string value)
{
    id = value;
    int flag = 0;
    for(list<pair<string, pair<string, int> > >::iterator it = decl_table.begin(); it != decl_table.end(); it++)
    {
	if((*it).first == id)
		flag = 1; 
    }
    if(flag == 0)
	cout << "Variable '" << id << "' used before declaration" << endl;	
}

void id_node:: print() 
{
    xml_out << "<id value='" << id << "'/>" << endl;
}

int id_node::evaluate() 
{ 
    for(list<pair<string, pair<string, int> > >::iterator it = decl_table.begin();it != decl_table.end(); it++)
    {
	if((*it).second.second == 0 && (*it).first == id)
	{
		if((*it).second.first == "integer")
			return 1;
		if((*it).second.first == "boolean")
			return 3;
	}				    
    }
    return -1; 
}

ids_node::ids_node(string value, exp_node *expnode)
{
    id = value;
    expnode = expnode;    
}

void ids_node:: print() 
{
    xml_out << "<id value='" << id << "'/>" << endl;
}

int ids_node::evaluate() 
{ 
     for(list<pair<string, pair<string, int> > >::iterator it = decl_table.begin();it != decl_table.end(); it++)
    {
	if((*it).first == id)
	{
		if((*it).second.first == "integer")
			return 1;
		if((*it).second.first == "boolean")
			return 3;
	}				    
    }
  /*  int pos = expnode->evaluate();
    id = id + '[' + str(pos) + ']';
    cout << "id_node: " << id << " = " << idTable[id] << endl;  */
    return -1; 
}

greater_node::greater_node(exp_node *L, exp_node *R) : operator_node(L,R) {}

void greater_node:: print() 
{
  if(left->evaluate() != right->evaluate())
 {
	cout << "Operation with incompatible types " << endl;
	return;
 } 
 
  xml_out << "<binary_expression type='greater_than'>" << endl;
  left->print();
  right->print();
  xml_out << "</binary_expression>" << endl;
}

int greater_node:: evaluate()
{
	if(left->evaluate() == right->evaluate())
		return left->evaluate();
	return -1;
}

lesser_node::lesser_node(exp_node *L, exp_node *R) : operator_node(L,R) {}

void lesser_node:: print() 
{
  if(left->evaluate() != right->evaluate())
 {
	cout << "Operation with incompatible types " << endl;
	return;
 } 
 
  xml_out << "<binary_expression type='less_than'>" << endl;
  left->print();
  right->print();
  xml_out << "</binary_expression>" << endl;
}

int lesser_node:: evaluate()
{
	if(left->evaluate() == right->evaluate())
		return left->evaluate();
	return -1;
}

greater_equal_node::greater_equal_node(exp_node *L, exp_node *R) : operator_node(L,R) {}

void greater_equal_node:: print() 
{
  if(left->evaluate() != right->evaluate())
 {
	cout << "Operation with incompatible types " << endl;
	return;
 } 
 
  xml_out << "<binary_expression type='greater_equal'>" << endl;
  left->print();
  right->print();
  xml_out << "</binary_expression>" << endl;
}

int greater_equal_node:: evaluate()
{
	if(left->evaluate() == right->evaluate())
		return left->evaluate();
	return -1;
}

lesser_equal_node::lesser_equal_node(exp_node *L, exp_node *R) : operator_node(L,R) {}

void lesser_equal_node:: print() 
{
  if(left->evaluate() != right->evaluate())
 {
	cout << "Operation with incompatible types " << endl;
	return;
 } 
 
  xml_out << "<binary_expression type='lesser_than'>" << endl;
  left->print();
  right->print();
  xml_out << "</binary_expression>" << endl;
}

int lesser_equal_node:: evaluate()
{
	if(left->evaluate() == right->evaluate())
		return left->evaluate();
	return -1;
}

and_node::and_node(exp_node *L, exp_node *R) : operator_node(L,R) {}

void and_node:: print() 
{
  if(left->evaluate() != right->evaluate())
 {
	cout << "Operation with incompatible types " << endl;
	return;
 } 
 
  xml_out << "<expression_type binary='and'>" << endl;
  left->print();
  right->print();
  xml_out << "</binary_expression>" << endl;
}

int and_node:: evaluate()
{
	if(left->evaluate() == right->evaluate())
		return left->evaluate();
	return -1;
}

or_node::or_node(exp_node *L, exp_node *R) : operator_node(L,R) {}

void or_node:: print() 
{
  if(left->evaluate() != right->evaluate())
 {
	cout << "Operation with incompatible types " << endl;
	return;
 } 
 
  xml_out << "<binary_expression type='or'>" << endl;
  left->print();
  right->print();
  xml_out << "</binary_expression>" << endl;
}

int or_node:: evaluate()
{
	if(left->evaluate() == right->evaluate())
		return left->evaluate();
	return -1;
}

equal_node::equal_node(exp_node *L, exp_node *R) : operator_node(L,R) {}

void equal_node:: print() 
{
  xml_out << "<binary_expression type='is_equal'>" << endl;
  left->print();
  right->print();
  xml_out << "</binary_expression>" << endl;
}

int equal_node:: evaluate()
{
	if(left->evaluate() == right->evaluate())
		return left->evaluate();
	return -1;
}

not_equal_node::not_equal_node(exp_node *L, exp_node *R) : operator_node(L,R) {}

void not_equal_node:: print() 
{
   xml_out << "<binary_expression type='is_not_equal'>" << endl;
  left->print();
  right->print();
  xml_out << "</binary_expression>" << endl;
}

int not_equal_node:: evaluate()
{
	if(left->evaluate() == right->evaluate())
		return left->evaluate();
	return -1;
}

// plus_node inherits the characteristics of node and adds its own evaluate function
  // plus_node's constructor just uses node's constructor
plus_node::plus_node(exp_node *L, exp_node *R) : operator_node(L,R) {}

void plus_node:: print() 
{
  if(left->evaluate() != right->evaluate())
	cout << "Operation with incompatible types " << endl;
  else
  {
  xml_out << "<binary_expression type='addition'>" << endl;
  left->print();
  right->print();
  xml_out << "</binary_expression>" << endl;
  }
}

int plus_node::evaluate() 
{
    if(left->evaluate() == right->evaluate())
	return left->evaluate();
/*int left_num, right_num;
    left_num  = left->evaluate();
    right_num = right->evaluate();

    num = left_num + right_num;
    cout << "plus_node: " << left_num << " + " << right_num << " = " << num << "\n"; */
    return -1;
}


// minus_node inherits the characteristics of node and adds its own evaluate function
minus_node::minus_node(exp_node *L, exp_node *R) : operator_node(L,R) {}

void minus_node:: print() 
{
 if(left->evaluate() != right->evaluate())
 {
	cout << "Operation with incompatible types " << endl;
	return;
 } 
  xml_out << "<binary_expression type='subtraction'>" << endl;
  left->print();
  right->print();
  xml_out << "</binary_expression>" << endl;
}

int minus_node::evaluate() 
{
    if(left->evaluate() == right->evaluate())
	return left->evaluate();
/*int left_num, right_num;

    left_num  = left->evaluate();
    right_num = right->evaluate();

    num = left_num - right_num;
    cout << "minus_node: " << left_num << " - " << right_num << " = " << num << "\n"; */
    return -1;
}

// times_node inherits the characteristics of node and adds its own evaluate function
times_node::times_node(exp_node *L, exp_node *R) : operator_node(L,R) {}

void times_node:: print() 
{
  if(left->evaluate() != right->evaluate())
 {
	cout << "Operation with incompatible types " << endl;
	return;
 } 
 
  xml_out << "<binary_expression type='multiplication'>" << endl;
  left->print();
  right->print();
  xml_out << "</binary_expression>" << endl;
}

int times_node::evaluate() 
{
    if(left->evaluate() == right->evaluate())
	return left->evaluate();
/*int left_num, right_num;

    left_num = left->evaluate();
    right_num = right->evaluate();

    num = left_num * right_num;
    cout << "times_node: " << left_num << " * " << right_num << " = " << num << "\n"; */
    return -1;
}

// divide_node inherits the characteristics of node and adds its own evaluate function

divide_node::divide_node(exp_node *L, exp_node *R) : operator_node(L,R) {}

void divide_node:: print() 
{
  if(left->evaluate() != right->evaluate())
 {
	cout << "Operation with incompatible types " << endl;
	return;
 } 
 
  xml_out << "<binary_expression type='division'>" << endl;
  left->print();
  right->print();
  xml_out << "</binary_expression>" << endl;
}

int divide_node::evaluate() 
{
    if(left->evaluate() == right->evaluate())
	return left->evaluate();
/*int left_num, right_num;

    left_num = left->evaluate();
    right_num = right->evaluate();

    if(right_num)
      {
        num = (int)left_num / (int)right_num;
        cout << "divide_node: " << left_num << " / " << right_num << " = " << num << "\n";
        return (num);
      }
    else
      {
	cout << "divide_node: division by zero -> " << left_num << " / " << 0 << endl;
	// you have to include stdlib.h for exit
	exit(1);
      } */
return -1;
}

mod_node::mod_node(exp_node *L, exp_node *R) : operator_node(L,R) {}

void mod_node:: print() 
{
  if(left->evaluate() != right->evaluate())
 {
	cout << "Operation with incompatible types " << endl;
	return;
 } 
 
  xml_out << "<binary_expression type='remainder'>";
  left->print();
  right->print();
  xml_out << "</binary_expression>" << endl;
}

int mod_node::evaluate() 
{
    if(left->evaluate() == right->evaluate())
	return left->evaluate();
 /*   int left_num, right_num;

    left_num = left->evaluate();
    right_num = right->evaluate();

    if(right_num)
      {
        num = (int)left_num % (int)right_num;
        cout << "mod_node: " << left_num << " % " << right_num << " = " << num << "\n";
        return (num);
      }
    else
      {
	cout << "mod_node: division by zero -> " << left_num << " % " << 0 << endl;
	// you have to include stdlib.h for exit
	exit(1);
      } */
     return -1; 
}


// unary_minus_node inherits the characteristics of node and adds its own evaluate function
unary_minus_node::unary_minus_node(exp_node *L) : exp(L) {}

void unary_minus_node:: print() {
  xml_out << "<unary_expression type='minus'>" << endl;
  exp->print();
  xml_out << "</unary_expression>" << endl;
}

int unary_minus_node::evaluate() {
 /* int expValue = exp->evaluate();
  num = -expValue;

  cout << "unary_minus_node: " << "-\t" << expValue << " = " << num << "\n";  */
    return exp->evaluate();
}

not_node::not_node(exp_node *L) : exp(L) {}

void not_node:: print() {
  xml_out << "<unary_expression type='not'>" << endl;
  exp->print();
  xml_out << "</unary_expression>" << endl;
}

int not_node::evaluate() 
{
 /* int expValue = exp->evaluate();
  num = !expValue;

  cout << "unary_minus_node: " << "!\t" << expValue << " = " << num << "\n";   */
    return exp->evaluate();
}

calloutEXP::calloutEXP(exp_node *expression)
  : exp(expression) {}

void calloutEXP::print() {
   exp->print();
}

void calloutEXP::evaluate()
{
     return;
}

calloutSTR::calloutSTR(string argument)
  : arg(argument) {}

void calloutSTR::print() {
   xml_out << arg << endl;
}

void calloutSTR::evaluate()
{
     return;
}

callout_stmt::callout_stmt(string name)
  : id(name) {}

void callout_stmt::print() {
  xml_out << "<callout function='" << id << "'>" << endl;
  xml_out << "</callout>" << endl;
}

void callout_stmt::evaluate()
{
     return;
}

callout_stmt1::callout_stmt1(string name, list<calloutArgs *> *Arguments)
  : id(name), Args(*(Arguments)) {}

void callout_stmt1::print() {
  xml_out << "<callout function='" << id << "'>" << endl;
  for(list<calloutArgs *>::iterator it = Args.begin(); it!=Args.end(); it++)
	(*it)->print();
  xml_out << "</callout>" << endl;
}

void callout_stmt1::evaluate()
{
     return;
}

assignment_stmt1::assignment_stmt1(string name, exp_node *expression)
  : id(name), exp(expression) {}

void assignment_stmt1::print() {
   int flag = 0;
   for(list<pair<string, pair<string, int> > >::iterator it = decl_table.begin(); it != decl_table.end(); it++)
   {
	if((*it).first == id)
	{
		flag = 1;
		if(!(((*it).second.first == "integer") && (exp->evaluate() == 1)) && !(((*it).second.first == "boolean") && (exp->evaluate() == 3))) {
			cout << "Cannnot equate LHS and RHS" << endl;
			flag = 2;
		}
   	}
   }  
   if(flag == 0)
	cout << "Variable '" << id << "' used before declaration" << endl;
   else if(flag == 1)
   {	
	xml_out << "<assignment>" << endl;
	xml_out << "<location id='" << id << "'/>" << endl;
	exp->print();
	xml_out << "</assignment>" << endl;
   }
}

void assignment_stmt1::evaluate()
{
    return;
}

assignment_stmt::assignment_stmt(string name, exp_node *location, exp_node *expression)
  : id(name), exp1(location), exp2(expression) {}

void assignment_stmt::print() {
  int flag = 0;
   for(list<pair<string, pair<string, int> > >::iterator it = decl_table.begin(); it != decl_table.end(); it++)
   {
	if((*it).first == id)
	{
		flag = 1;
		if(!(((*it).second.first == "integer") && (exp1->evaluate() == 1) && (exp2->evaluate() == 1)) && !(((*it).second.first == "boolean") && (exp1->evaluate() == 3) && (exp2->evaluate() == 3))) {
			cout << "Cannnot equate LHS and RHS" << endl;
			flag = 2;
		}
   	}
   }  
   if(flag == 0)
	cout << "Variable '" << id << "' used before declaration" << endl;
  else if(flag == 1)
  {
  	xml_out << "<assignment>" << endl ;
  	xml_out << "<location id='" << id << "'>" << endl;
	xml_out << "<position>" << endl;
  	exp1->print();
  	xml_out << "</position>" << endl; 
  	xml_out << "</location>" << endl;
  	exp2->print();
  	xml_out << "</assignment>" << endl;
  }
}

void assignment_stmt::evaluate() {
/*  cout << "assignment_node: " << id << " = ";
  exp->evaluate();
  cout << endl;
 // idTable[id] = result; */
 return ;
}

void print_expnode_list(list<exp_node *> *expression)
{
	list<exp_node *>::iterator it = expression->begin(); 
  	while(it != expression->end())
	{
		(*it)->print();
		it++;
	}
	return;
}

if_stmt::if_stmt(exp_node *condition, pgm *ifblock)
  : exp(condition), block(ifblock) {}

void if_stmt::print() {
  xml_out << "<if>" << endl;
  xml_out << "<condition>";
  exp->print();
  xml_out << "<condition/>" << endl;
  block->evaluate();
  xml_out << "</if>" << endl;
}

void if_stmt::evaluate()
{
     return;
}

if_else_stmt::if_else_stmt(exp_node *condition, pgm *ifblock1, pgm *ifblock2)
  : exp(condition), block1(ifblock1), block2(ifblock2) {}

void if_else_stmt::print() {
  xml_out << "<ifelse>" << endl;
  xml_out << "<condition>";
  exp->print();
  xml_out << "<condition/>" << endl;
  block1->evaluate();
  block2->evaluate();
  xml_out << "</ifelse>" << endl;
}

void if_else_stmt::evaluate()
{
     return;
}

for_stmt::for_stmt(string name, exp_node *cond1, exp_node *cond2, pgm *forblock)
  : id(name), exp1(cond1), exp2(cond2), block(forblock) {}

void for_stmt::print() {
  xml_out << "<for>" << endl;
  xml_out << "<Id = '" << id << "'/>" << endl;
  xml_out << "<condition1>";
  exp1->print();
  xml_out << "<condition1/>" << endl;
  xml_out << "<condition2>";
  exp2->print();
  xml_out << "<condition2/>" << endl;  
  block->evaluate();
  xml_out << "</for>" << endl;
}

void for_stmt::evaluate()
{
     return;
}

ret_stmt::ret_stmt() {}

void ret_stmt::print() {
  xml_out << "<RETURN>" << endl;
}

void ret_stmt::evaluate()
{
     return;
}

ret_exp_stmt::ret_exp_stmt(exp_node *condition)
  : exp(condition) {}

void ret_exp_stmt::print() {
  xml_out << "<RETURN>" << endl;
  xml_out << "<EXPRESSION>";
  exp->print();
  xml_out << "<EXPRESSION/>" << endl;
  xml_out << "</RETURN>" << endl;
}

void ret_exp_stmt::evaluate()
{
     return;
}

break_stmt::break_stmt() {}

void break_stmt::print() {
  xml_out << "<BREAK>" << endl;
}

void break_stmt::evaluate()
{
     return;
}

continue_stmt::continue_stmt() {}

void continue_stmt::print() {
  xml_out << "<CONTINUE>" << endl;
}

void continue_stmt::evaluate()
{
     return;
}

block_stmt::block_stmt(pgm *block)
  :  block(block) {}

void block_stmt::print() {
  xml_out << "<BLOCK>";  
  block->evaluate();
  xml_out << "</BLOCK>" << endl;
}

void block_stmt::evaluate()
{
     return;
}

method_call_stmt1::method_call_stmt1(string name, list<exp_node *> *expression)
  : id(name), exp(expression) {}

void method_call_stmt1::print() {
  xml_out << "<methodcall>" << endl;
  xml_out << "<method name='" << id << "'/>" << endl;
  print_expnode_list(exp);
  xml_out << "</methodcall>" << endl;
}

void method_call_stmt1::evaluate()
{
     return;
}

print_stmt::print_stmt (string name) : id(name) {}

void print_stmt::evaluate() {
  cout << "print_node: " << id << " = " << idTable[id] << endl << endl;
}

void update_decl_table(string name, string type, int size)
{
	pair< string, int > p2;
	p2.first = type;
	p2.second = size;
	pair<string, pair<string, int> > p1;
	p1.first = name;
	p1.second = p2;	
	decl_table.push_back(p1);
	return ;
}

void print_field_decl()
{
    xml_out << "<field_declarations count='" << decl_table.size() << "'>" << endl;
    for(list<pair<string, pair<string, int> > >::iterator it = decl_table.begin();it != decl_table.end(); it++)
    {
	if((*it).second.second == 0)
		xml_out << "<declaration name='" << (*it).first << "' type='" << (*it).second.first << "'>" << endl;
	else
		xml_out << "<declaration name='" << (*it).first << "' count='" << (*it).second.second << "' type='" << (*it).second.first << "'>" << endl;			    
    }
    xml_out << "</field_declarations>" << endl;
    return;
}

pgm::pgm(list<statement *> *stmtList) : stmts(stmtList) {}

void pgm::evaluate() {
  xml_out << "<program>" << endl;
  if(fields)
  {
  	print_field_decl();
  	fields = 0;
  }
  xml_out << "<statement_declarations count='" << stmts->size() << "'>" << endl;
  list<statement *>::iterator stmtIter;
  for (stmtIter = stmts->begin(); stmtIter != stmts->end();
       stmtIter++) {
    (*stmtIter)->print();
 //   (*stmtIter)->evaluate();
  }
  xml_out << "</statement_declarations>" << endl;
  xml_out << "</program>" << endl;
  return;
}

list<pair<string, pair< string, int> > > decl_table;
map<string, float> idTable;
