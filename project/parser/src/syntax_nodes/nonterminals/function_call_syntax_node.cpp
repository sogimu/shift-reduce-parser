#include "nonterminals/function_call_syntax_node.h"

#include "i_syntax_node_visitor.h"
#include "is_last_nodes.h"
#include "syntax_node_empty_visitor.h"
#include "terminals/name_syntax_node.h"

FunctionCallSyntaxNode::FunctionCallSyntaxNode()
   : ISyntaxNode{ Token_Type::FUNCTION_CALL }
{
}

FunctionCallSyntaxNode::FunctionCallSyntaxNode( const std::string& name )
   : ISyntaxNode{ Token_Type::FUNCTION_CALL }
   , mName{ name }
{
   // add_back( name );
}

FunctionCallSyntaxNode::FunctionCallSyntaxNode( const std::string& name, const std::vector< ISyntaxNodeSP >& arguments )
   : ISyntaxNode{ Token_Type::FUNCTION_CALL }
   , mName{ name }
{
   for( const auto& argument : arguments )
   {
      // ISyntaxNodeSP child = argument;
      //
      // if( IsNode< NameSyntaxNode >( argument ) )
      // {
      //    const auto& name_node = std::dynamic_pointer_cast< NameSyntaxNode >( argument );
      //    child = std::make_shared< VaribleSyntaxNode >( name_node->value() );
      // }

      add_back( argument );
   }
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
      for( size_t i = 0; i < Children().size(); ++i )
      {
         const auto& lft_child = ( *this )[ i ];
         const auto& rht_child = ( *node )[ i ];
         if( !lft_child->compare( *rht_child ) )
         {
            return;
         }
      }
      if( node->name() != this->name() )
        return;
      is_equal = true;
   };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );

   return is_equal;
}

std::string FunctionCallSyntaxNode::name() const
{
   return mName;
}

std::vector< NameSyntaxNodeSP > FunctionCallSyntaxNode::arguments() const
{
   return {};
}
