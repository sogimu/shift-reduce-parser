#include "nonterminals/scope_statment_syntax_node.h"

#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

ScopeSyntaxNode::ScopeSyntaxNode()
   : ISyntaxNode{ Token_Type::SCOPE_STATMENT }
{
}

ScopeSyntaxNode::ScopeSyntaxNode( const ISyntaxNodeSP& expression )
   : ISyntaxNode{ Token_Type::SCOPE_STATMENT }
{
   add_back( expression );
}

ScopeSyntaxNode::ScopeSyntaxNode( const std::vector< ISyntaxNodeSP >& expressions )
   : ISyntaxNode{ Token_Type::SCOPE_STATMENT }
{
   for( const auto& expression : expressions )
      add_back( expression );
}
void ScopeSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool ScopeSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = true;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.scope_statment_syntax_node = [ this, &is_equal ]( const ScopeSyntaxNodeSP& node )
   {
      if( node->Children().size() != this->Children().size() )
      {
         is_equal = false;
         return;
      }
   };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );

   return is_equal;
}
