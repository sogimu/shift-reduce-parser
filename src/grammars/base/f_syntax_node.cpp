#include "base/f_syntax_node.h"

// #include <vector>
// #include <string>
//
// #include "enums.h"
// #include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

void FSyntaxNode::accept(const ISyntaxNodeVisitorSP& visitor)
{
    visitor->visit(shared_from_this());
}

bool FSyntaxNode::operator==(const ISyntaxNodeSP& node) const
{
  bool is_equal = false;
  SyntaxNodeEmptyVisitor::Handlers handlers;
  handlers.f_syntax_node = [this, &is_equal](const FSyntaxNodeSP& node)
  {
      is_equal = node->value() == this->value();
     // std::cout << "Tree A: " << node->text() << std::endl;
  };
  const auto& visitor = std::make_shared<SyntaxNodeEmptyVisitor>( handlers );
  node->accept(visitor);
  return false;
}
