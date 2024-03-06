#include "base/name_syntax_node.h"

// #include <vector>
#include <string>

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

NameSyntaxNode::NameSyntaxNode(const std::string& value)
    : ISyntaxNode{Token_Type::NAME}
    , mValue{ value }
{
}

void NameSyntaxNode::accept(const ISyntaxNodeVisitorSP& visitor)
{
    visitor->visit(shared_from_this());
}

bool NameSyntaxNode::operator==(const ISyntaxNodeSP& node) const
{
  bool is_equal = false;
  SyntaxNodeEmptyVisitor::Handlers handlers;
  handlers.name_syntax_node = [this, &is_equal](const NameSyntaxNodeSP& node)
  {
      is_equal = node->value() == this->value();
     // std::cout << "Tree A: " << node->text() << std::endl;
  };
  const auto& visitor = std::make_shared<SyntaxNodeEmptyVisitor>( handlers );
  node->accept(visitor);
  return false;
}

std::string NameSyntaxNode::value() const
{
    return mValue;
}
