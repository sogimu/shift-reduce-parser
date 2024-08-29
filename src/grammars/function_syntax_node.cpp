#include "function_syntax_node.h"

#include "base/name_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

FunctionSyntaxNode::FunctionSyntaxNode()
   : ISyntaxNode{ Token_Type::FUNCTION_EXPRESSION }
{
}

FunctionSyntaxNode::FunctionSyntaxNode( const NameSyntaxNodeSP& name, const ScopeSyntaxNodeSP& scope )
   : ISyntaxNode{ Token_Type::FUNCTION_EXPRESSION }
{
   Add( name );
   Add( scope );
}

void FunctionSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool FunctionSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.function_syntax_node = [ this, &is_equal ]( const FunctionSyntaxNodeSP& node )
   {
      if( node->Children().size() != this->Children().size() )
         return;
      for( int i = 0; i < Children().size(); ++i )
      {
         const auto& lft_child = ( *this )[ i ];
         const auto& rht_child = ( *node )[ i ];
         if( !lft_child->compare( *rht_child ) )
         {
            return;
         }
      }
      is_equal = true;
   };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );

   return is_equal;
}

NameSyntaxNodeSP FunctionSyntaxNode::name() const
{
   return std::dynamic_pointer_cast< NameSyntaxNode >( this->operator[]( 0 ) );
}

ScopeSyntaxNodeSP FunctionSyntaxNode::scope() const
{
   return std::dynamic_pointer_cast< ScopeSyntaxNode >( this->operator[]( 1 ) );
}

std::vector< NameSyntaxNodeSP > FunctionSyntaxNode::arguments() const
{
   return {};
}
