#include "nonterminals/computational_expression_syntax_node.h"

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "terminals/name_syntax_node.h"

VaribleSyntaxNode::VaribleSyntaxNode()
   : ISyntaxNode{ Token_Type::VARIBLE }
{
}

VaribleSyntaxNode::VaribleSyntaxNode( const NameSyntaxNodeSP& name_syntax_node )
   : ISyntaxNode{ Token_Type::VARIBLE }
   , mName{ name_syntax_node->value() }
{
}
VaribleSyntaxNode::VaribleSyntaxNode( const std::string& name )
   : ISyntaxNode{ Token_Type::VARIBLE }
   , mName{ name }
{
}

std::string VaribleSyntaxNode::name() const
{
   return mName;
}

void VaribleSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool VaribleSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.varible_syntax_node = [ this, &is_equal ]( const VaribleSyntaxNodeSP& node )
   {
      if( node->Children().size() == this->Children().size() )
      {
         is_equal = true;
         return;
      }
   };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );

   return is_equal;
}
