#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>

using namespace std;

class exp_node {
  public:
//    float num;

    // print function for pretty printing an expression
    virtual void print() = 0;

    // evaluation function for a leaf, replaced for interior nodes
    virtual int evaluate() = 0;
};

class operator_node : public exp_node {
public:
    exp_node *left;
    exp_node *right;

  // the constructor for node links the node to its children,
  // and stores the character representation of the operator.
    operator_node(exp_node *L, exp_node *R);
};

class int_node : public exp_node {
  
public:
  int num;
  int_node(int value);
  void print();
  int evaluate();
};

class boolean_node : public exp_node {
  
public:
  bool num;
  boolean_node(bool value);
  void print();
  int evaluate();
};

class char_node : public exp_node {
  
public:
  char num;
  char_node(char value);
  void print();
  int evaluate();
};

class unary_minus_node : public exp_node {
 protected:
  exp_node *exp;
 public:
  unary_minus_node(exp_node *exp);
  void print();
  int evaluate();
};

class not_node : public exp_node {
 protected:
  exp_node *exp;
 public:
  not_node(exp_node *exp);
  void print();
  int evaluate();
};

class id_node : public exp_node {
protected:
  string id;

public:
  id_node(string value);
  void print();
  int evaluate();
};

class ids_node : public exp_node {
protected:
  string id;
  exp_node *exp;

public:
  ids_node(string value, exp_node *exp);
  void print();
  int evaluate();
};

class lesser_node : public operator_node {
  public:

  lesser_node(exp_node *L, exp_node *R);
  void print();
  int evaluate();
};

class greater_node : public operator_node {
  public:

  greater_node(exp_node *L, exp_node *R);
  void print();
  int evaluate();
};

class greater_equal_node : public operator_node {
  public:

  greater_equal_node(exp_node *L, exp_node *R);
  void print();
  int evaluate();
};


class lesser_equal_node : public operator_node {
  public:

  lesser_equal_node(exp_node *L, exp_node *R);
  void print();
  int evaluate();
};

class equal_node : public operator_node {
  public:

  equal_node(exp_node *L, exp_node *R);
  void print();
  int evaluate();
};

class not_equal_node : public operator_node {
  public:

  not_equal_node(exp_node *L, exp_node *R);
  void print();
  int evaluate();
};

class and_node : public operator_node {
  public:

  and_node(exp_node *L, exp_node *R);
  void print();
  int evaluate();
};

class or_node : public operator_node {
  public:

  or_node(exp_node *L, exp_node *R);
  void print();
  int evaluate();
};

// plus_node inherits the characteristics of node and adds its own evaluate function
class plus_node : public operator_node {
  public:

  // plus_node's constructor just uses node's constructor
  plus_node(exp_node *L, exp_node *R);
  void print();
  int evaluate();
};

// minus_node inherits the characteristics of node and adds its own evaluate function
class minus_node : public operator_node {
  public:

  minus_node(exp_node *L, exp_node *R);
  void print();
  int evaluate();
};


// times_node inherits the characteristics of node and adds its own evaluate function
class times_node : public operator_node {
  public:

  times_node(exp_node *L, exp_node *R);
  void print();
  int evaluate();
};


// divide_node inherits the characteristics of node and adds its own evaluate function
class divide_node : public operator_node {
  public:

  divide_node(exp_node *L, exp_node *R);
  void print();
  int evaluate();
};

class mod_node : public operator_node {
  public:

  mod_node(exp_node *L, exp_node *R);
  void print();
  int evaluate();
};

class calloutArgs {
 public:
  virtual void print() {}
  virtual void evaluate() = 0;
};

class calloutEXP : public calloutArgs {
 protected:
  exp_node *exp;
 public:
  calloutEXP(exp_node *expression);
  void print();
  void evaluate();
}; 

class calloutSTR : public calloutArgs {
 protected:
  string arg;
 public:
  calloutSTR(string argument);
  void print();
  void evaluate();
}; 

class statement {
 public:
  virtual void print() {}
  virtual void evaluate() = 0;
};

class pgm {
 protected:
  list<statement *> *stmts;
 public:
  pgm(list<statement *> *stmtlist);
  virtual void evaluate();
};

class assignment_stmt1 : public statement {
 protected:
  string id;
  exp_node *exp;
 public:
  assignment_stmt1(string name, exp_node *expression);
  void print();
  void evaluate();
};

class assignment_stmt : public statement {
 protected:
  string id;
  exp_node *exp1;
  exp_node *exp2;
 public:
  assignment_stmt(string name, exp_node *location, exp_node *expression);
  void print();
  void evaluate();
};

class if_stmt : public statement {
 protected:
  exp_node *exp;
  pgm *block;
 public:
  if_stmt(exp_node *condition, pgm *ifblock);
  void print();
  void evaluate();
};

class if_else_stmt : public statement {
 protected:
  exp_node *exp;
  pgm *block1;
  pgm *block2;
 public:
  if_else_stmt(exp_node *condition, pgm *ifblock1, pgm *ifblock2);
  void print();
  void evaluate();
};

class for_stmt : public statement {
 protected:
  string id;
  exp_node *exp1;
  exp_node *exp2;
  pgm *block;
 public:
  for_stmt(string name, exp_node *cond1, exp_node *cond2, pgm *forblock);
  void print();
  void evaluate();
};

class ret_stmt : public statement {
 public:
  ret_stmt();
  void print();
  void evaluate();
};

class ret_exp_stmt : public statement {
 private:
  exp_node *exp;
 public:
  ret_exp_stmt(exp_node *condition);
  void print();
  void evaluate();
};

class break_stmt : public statement {
 public:
  break_stmt();
  void print();
  void evaluate();
};

class continue_stmt : public statement {
 public:
  continue_stmt();
  void print();
  void evaluate();
};

class block_stmt : public statement {
 protected:
  pgm *block;
 public:
  block_stmt(pgm *block);
  void print();
  void evaluate();
};

class method_call_stmt1 : public statement {
 protected:
  string id;
  list<exp_node *> *exp;
 public:
  method_call_stmt1(string name, list<exp_node *> *expression);
  void print();
  void evaluate();
};

class callout_stmt : public statement {
 protected:
  string id;
 public:
  callout_stmt(string name);
  void print();
  void evaluate();
};

class callout_stmt1 : public statement {
 protected:
  string id;
  list<calloutArgs *> Args;
 public:
  callout_stmt1(string name, list<calloutArgs *> *Arguments);
  void print();
  void evaluate();
};


class print_stmt: public statement {
 protected:
  string id;
 public:
  print_stmt(string id);
  void evaluate() ;
};

void update_decl_table(string name, string type, int size);


// the object at the base of our tree
extern list<pair<string, pair< string, int> > > decl_table;
extern map<string, float> idTable;
extern pgm *root;
