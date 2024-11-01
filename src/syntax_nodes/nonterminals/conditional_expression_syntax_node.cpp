#include "nonterminals/conditional_expression_syntax_node.h"

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "terminals/name_syntax_node.h"
#include "nonterminals/computational_expression_syntax_node.h"

ConditionalExpressionSyntaxNode::ConditionalExpressionSyntaxNode()
   : ISyntaxNode{ Token_Type::CONDITIONAL_EXPRESSION }
{
}
ConditionalExpressionSyntaxNode::ConditionalExpressionSyntaxNode( const ComputationalExpressionSyntaxNodeSP& f0, const ComputationalExpressionSyntaxNodeSP& f1,
                                                                  Type type )
   : ISyntaxNode{ Token_Type::CONDITIONAL_EXPRESSION }
   , mType{ type }
{
   Add( f0 );
   Add( f1 );
}

ConditionalExpressionSyntaxNode::ConditionalExpressionSyntaxNode( const NameSyntaxNodeSP& f0, const ComputationalExpressionSyntaxNodeSP& f1, Type type )
   : ISyntaxNode{ Token_Type::CONDITIONAL_EXPRESSION }
   , mType{ type }
{
   Add( f0 );
   Add( f1 );
}

ConditionalExpressionSyntaxNode::ConditionalExpressionSyntaxNode( const NameSyntaxNodeSP& f0, const NameSyntaxNodeSP& f1, Type type )
   : ISyntaxNode{ Token_Type::CONDITIONAL_EXPRESSION }
   , mType{ type }
{
   Add( f0 );
   Add( f1 );
}

void ConditionalExpressionSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool ConditionalExpressionSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.conditional_expression_syntax_node = [ this, &is_equal ]( const ConditionalExpressionSyntaxNodeSP& node )
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
ConditionalExpressionSyntaxNode::Type ConditionalExpressionSyntaxNode::type() const
{
   return mType;
}

ComputationalExpressionSyntaxNodeSP ConditionalExpressionSyntaxNode::first_apperand() const
{
   ComputationalExpressionSyntaxNodeSP result;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.f_syntax_node = [ &result ]( const FSyntaxNodeSP& f ) { result = std::make_shared< ComputationalExpressionSyntaxNode >( f ); };
   handlers.name_syntax_node = [ &result ]( const NameSyntaxNodeSP& f ) { result = std::make_shared< ComputationalExpressionSyntaxNode >( f ); };
   handlers.computational_expression_syntax_node = [ &result ]( const ComputationalExpressionSyntaxNodeSP& computational_expression )
   { result = computational_expression; };

   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const auto& node = this->operator[]( 0 );
   node->accept( visitor );
   return result;
}

ComputationalExpressionSyntaxNodeSP ConditionalExpressionSyntaxNode::second_apperand() const
{
   ComputationalExpressionSyntaxNodeSP result;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.f_syntax_node = [ &result ]( const FSyntaxNodeSP& f ) { result = std::make_shared< ComputationalExpressionSyntaxNode >( f ); };
   handlers.name_syntax_node = [ &result ]( const NameSyntaxNodeSP& f ) { result = std::make_shared< ComputationalExpressionSyntaxNode >( f ); };
   handlers.computational_expression_syntax_node = [ &result ]( const ComputationalExpressionSyntaxNodeSP& computational_expression )
   { result = computational_expression; };

   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const auto& node = this->operator[]( 1 );
   node->accept( visitor );
   return result;
}
