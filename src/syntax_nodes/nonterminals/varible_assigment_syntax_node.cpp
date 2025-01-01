#include "nonterminals/varible_assigment_syntax_node.h"

#include "terminals/name_syntax_node.h"
#include "nonterminals/computational_expression_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"

VaribleAssigmentSyntaxNode::VaribleAssigmentSyntaxNode()
   : ISyntaxNode{ Token_Type::VARIBLE_ASSIGMENT }
{
}
VaribleAssigmentSyntaxNode::VaribleAssigmentSyntaxNode( const NameSyntaxNodeSP& name, const ComputationalExpressionSyntaxNodeSP& node )
   : ISyntaxNode{ Token_Type::VARIBLE_ASSIGMENT }
{
   const auto& varible = std::make_shared< VaribleSyntaxNode >( name );
   add_back( varible );
   add_back( node );
}

VaribleAssigmentSyntaxNode::VaribleAssigmentSyntaxNode( const NameSyntaxNodeSP& target_name, const NameSyntaxNodeSP& source_name )
   : ISyntaxNode{ Token_Type::VARIBLE_ASSIGMENT }
{
   add_back( target_name );
   const auto& varible = std::make_shared< VaribleSyntaxNode >( source_name );
   add_back( varible );
}
NameSyntaxNodeSP VaribleAssigmentSyntaxNode::target() const
{
   return std::dynamic_pointer_cast< NameSyntaxNode >( this->operator[]( 0 ) );
}

ComputationalExpressionSyntaxNodeSP VaribleAssigmentSyntaxNode::source() const
{
   ComputationalExpressionSyntaxNodeSP argument;
   const auto& value_node = this->operator[]( 1 );
   match( value_node,
          { .computational_expression_syntax_node = [ &argument ]( const ComputationalExpressionSyntaxNodeSP& computational_expression )
            { argument = computational_expression; },
            .name_syntax_node = [ &argument ]( const NameSyntaxNodeSP& name ) { argument = std::make_shared< ComputationalExpressionSyntaxNode >( name ); } } );
   return argument;
}

void VaribleAssigmentSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool VaribleAssigmentSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = true;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.varible_assigment_syntax_node = [ this, &is_equal ]( const VaribleAssigmentSyntaxNodeSP& node )
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
