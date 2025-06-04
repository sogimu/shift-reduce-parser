#include "nonterminals/function_statment_syntax_node.h"

#include <string>
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "nonterminals/scope_statment_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "utils.h"

FunctionStatmentSyntaxNode::FunctionStatmentSyntaxNode()
   : ISyntaxNode{ Token_Type::FUNCTION_STATMENT }
{
}

FunctionStatmentSyntaxNode::FunctionStatmentSyntaxNode( const std::string& name )
   : ISyntaxNode{ Token_Type::FUNCTION_STATMENT }
   , mName{ name }
{
}

FunctionStatmentSyntaxNode::FunctionStatmentSyntaxNode( const std::string& name, const std::vector< ISyntaxNodeSP >& arguments, const ScopeSyntaxNodeSP& scope )
   : ISyntaxNode{ Token_Type::FUNCTION_STATMENT }
   , mName{ name }
{
   for( const auto& argument : arguments )
   {
      ISyntaxNodeSP child = argument;

      if( check_type< NameSyntaxNode >( argument ) )
      {
         const auto& name_node = std::dynamic_pointer_cast< NameSyntaxNode >( argument );
         child = std::make_shared< VaribleSyntaxNode >( name_node->value() );
      }

      add_back( child );
   }
   add_back( scope );
}

void FunctionStatmentSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool FunctionStatmentSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.function_statment_syntax_node = [ this, &is_equal ]( const FunctionStatmentSyntaxNodeSP& node )
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

std::string FunctionStatmentSyntaxNode::name() const
{
   return mName;
   // return std::dynamic_pointer_cast< NameSyntaxNode >( this->operator[]( 0 ) );
}

ScopeSyntaxNodeSP FunctionStatmentSyntaxNode::scope() const
{
   return std::dynamic_pointer_cast< ScopeSyntaxNode >( this->operator[]( this->Children().size() - 1 ) );
}

std::vector< NameSyntaxNodeSP > FunctionStatmentSyntaxNode::arguments() const
{
   return {};
}
