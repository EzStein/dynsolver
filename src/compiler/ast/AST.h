#ifndef AST_GUARD
#define AST_GUARD
#include <cstddef>
#include <iostream>
#include "compiler/ast/expression_node.h"
#include "compiler/ast/variable_leaf_node.h"
class AST {
public:
  explicit AST(expression_node*);

  /*Destroys the AST*/
  ~AST();

  /*Copy constructor. Performs a deep copy of the tree*/
  AST(const AST&);

  /*Move constructor*/
  AST(AST&&);

  /*Assignment operator which performs a deep copy*/
  AST& operator=(const AST&);

  /*Move assignment*/
  AST& operator=(AST&&);

  /*Constructs the binary operator of the appropriate type whose children are given by the provided pointers.
  * The function returns a pointer to the constructed node*/
  template<class NODE_TYPE>
  static expression_node* make_binary_operator_node(expression_node* leftChild, expression_node* rightChild);

  /*Constructs the unary operator of the appropriate type whose child is given by the provided pointer.
  * The function returns a pointer to the constructed node*/
  template<class NODE_TYPE>
  static expression_node* make_unary_operator_node(expression_node* child);

  static expression_node* make_variable_leaf_node(symbol::ptr_type);
  static expression_node* make_number_leaf_node(double val);

  double evaluate() const;

  std::ostream& emit_code(std::ostream&, unsigned char *) const;
  unsigned int code_size() const;

  friend std::ostream& operator<<(std::ostream&, const AST&);
private:
  expression_node * root;
};

std::ostream& operator<<(std::ostream&, const AST&);

#endif