#include "nonterminals/function_call_or_definition_syntax_node.h"

#include "i_syntax_node_visitor.h"
#include "is_last_nodes.h"
#include "syntax_node_empty_visitor.h"
#include "terminals/name_syntax_node.h"

FunctionCallOrDefinitionSyntaxNode::FunctionCallOrDefinitionSyntaxNode()
   : ISyntaxNode{ Token_Type::FUNCTION_CALL }
{
}

FunctionCallOrDefinitionSyntaxNode::FunctionCallOrDefinitionSyntaxNode( const std::string& name )
   : ISyntaxNode{ Token_Type::FUNCTION_CALL }
   , mName{ name }
{
   // add_back( name );
}

FunctionCallOrDefinitionSyntaxNode::FunctionCallOrDefinitionSyntaxNode( const std::string& name, const std::vector< ISyntaxNodeSP >& arguments )
   : ISyntaxNode{ Token_Type::FUNCTION_CALL }
   , mName{ name }
{
   for( const auto& argument : arguments )
   {
      // ISyntaxNodeSP child = argument;

      // const auto& name_node = std::dynamic_pointer_cast< NameSyntaxNode >( argument );
      // if( IsNode< NameSyntaxNode >( argument ) )
      // {
      //    const auto& name_node = std::dynamic_pointer_cast< NameSyntaxNode >( argument );
      //    child = std::make_shared< VaribleSyntaxNode >( name_node->value() );
      // }

      add_back( argument );
   }
}
void FunctionCallOrDefinitionSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool FunctionCallOrDefinitionSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.function_call_or_definition_syntax_node = [ this, &is_equal ]( const FunctionCallOrDefinitionSyntaxNodeSP& node )
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
      is_equal = true;
   };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );

   return is_equal;
}

std::string FunctionCallOrDefinitionSyntaxNode::name() const
{
   // return std::dynamic_pointer_cast< NameSyntaxNode >( this->operator[]( 0 ) );
   return mName;
}

std::vector< NameSyntaxNodeSP > FunctionCallOrDefinitionSyntaxNode::arguments() const
{
   return {};
}
