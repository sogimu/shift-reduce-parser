#include "nonterminals/return_statment_syntax_node.h"

#include "is_last_nodes.h"
#include "terminals/name_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"

ReturnStatmentSyntaxNode::ReturnStatmentSyntaxNode( const ReturnStatmentSyntaxNode& return_statment_syntax_node )
   : ISyntaxNode{ Token_Type::RETURN_STATMENT }
{
   mTokens = return_statment_syntax_node.lexical_tokens();
}
ReturnStatmentSyntaxNode::ReturnStatmentSyntaxNode( const ISyntaxNodeSP& argument, const LexicalTokens::LexicalToken& lexical_tokens )
   : ISyntaxNode{ Token_Type::RETURN_STATMENT }
{
   mTokens = { lexical_tokens };
   add_back( argument );
}

void ReturnStatmentSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool ReturnStatmentSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = true;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.return_statment_syntax_node = [ this, &is_equal ]( const ReturnStatmentSyntaxNodeSP& node )
   {
      if( node->Children().size() != this->Children().size() )
         return;
      if( node->lexical_tokens() != this->lexical_tokens() )
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

// ComputationalExpressionSyntaxNodeSP ReturnStatmentSyntaxNode::computational_expression() const
// {
//    ComputationalExpressionSyntaxNodeSP argument;
//    const auto& value_node = this->operator[]( 0 );
//    match( value_node,
//           { .computational_expression_syntax_node = [ &argument ]( const ComputationalExpressionSyntaxNodeSP& computational_expression )
//             { argument = computational_expression; },
//             .name_syntax_node = [ &argument ]( const NameSyntaxNodeSP& name ) { argument = std::make_shared< ComputationalExpressionSyntaxNode >( name ); } } );
//    return argument;
// }
