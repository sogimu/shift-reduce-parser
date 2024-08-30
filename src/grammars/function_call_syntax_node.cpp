#include "function_call_syntax_node.h"

#include "base/name_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

FunctionCallSyntaxNode::FunctionCallSyntaxNode()
   : ISyntaxNode{ Token_Type::FUNCTION_CALL_EXPRESSION }
{
}

FunctionCallSyntaxNode::FunctionCallSyntaxNode( const NameSyntaxNodeSP& name )
   : ISyntaxNode{ Token_Type::FUNCTION_CALL_EXPRESSION }
{
   Add( name );
}

void FunctionCallSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool FunctionCallSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.function_call_syntax_node = [ this, &is_equal ]( const FunctionCallSyntaxNodeSP& node )
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

NameSyntaxNodeSP FunctionCallSyntaxNode::name() const
{
   return std::dynamic_pointer_cast< NameSyntaxNode >( this->operator[]( 0 ) );
}

std::vector< NameSyntaxNodeSP > FunctionCallSyntaxNode::arguments() const
{
   return {};
}
