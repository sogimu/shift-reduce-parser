#include "nonterminals/print_statment_syntax_node.h"

#include "terminals/name_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"
#include <iterator>

PrintStatmentSyntaxNode::PrintStatmentSyntaxNode()
   : ISyntaxNode{ Token_Type::PRINT_STATMENT }
{
}

PrintStatmentSyntaxNode::PrintStatmentSyntaxNode( const NameSyntaxNodeSP& name_syntax_node )
   : ISyntaxNode{ Token_Type::PRINT_STATMENT }
{
   add_back( name_syntax_node );
}

PrintStatmentSyntaxNode::PrintStatmentSyntaxNode( const ISyntaxNodeSP& argument )
   : ISyntaxNode{ Token_Type::PRINT_STATMENT }
{
   add_back( argument );
}

ISyntaxNodeSP& PrintStatmentSyntaxNode::add_back( const ISyntaxNodeSP& child )
{
   // ISyntaxNodeSP node = child;
   // SyntaxNodeEmptyVisitor::Handlers handlers;
   // handlers.name_syntax_node = [ &node ]( const NameSyntaxNodeSP& name ) { node = std::make_shared< VaribleSyntaxNode >( name ); };
   //
   // const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   // child->accept( visitor );

   return ISyntaxNode::add_back( child );
}
void PrintStatmentSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool PrintStatmentSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = true;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.print_statment_syntax_node = [ this, &is_equal ]( const PrintStatmentSyntaxNodeSP& node )
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

// ComputationalExpressionSyntaxNodeSP PrintStatmentSyntaxNode::computational_expression() const
// {
//    ComputationalExpressionSyntaxNodeSP argument;
//    const auto& value_node = this->operator[]( 0 );
//    match( value_node,
//           { .computational_expression_syntax_node = [ &argument ]( const ComputationalExpressionSyntaxNodeSP& computational_expression )
//             { argument = computational_expression; },
//             .name_syntax_node = [ &argument ]( const NameSyntaxNodeSP& name ) { argument = std::make_shared< ComputationalExpressionSyntaxNode >( name ); } } );
//    return argument;
// }
