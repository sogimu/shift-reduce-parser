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
ConditionalExpressionSyntaxNode::ConditionalExpressionSyntaxNode( Type type )
   : ISyntaxNode{ Token_Type::CONDITIONAL_EXPRESSION }
   , mType{ type }
{
}
ConditionalExpressionSyntaxNode::ConditionalExpressionSyntaxNode( const ComputationalExpressionSyntaxNodeSP& expression0,
                                                                  const ComputationalExpressionSyntaxNodeSP& expression1, Type type )
   : ISyntaxNode{ Token_Type::CONDITIONAL_EXPRESSION }
   , mType{ type }
{
   add_back( expression0 );
   add_back( expression1 );
}

ConditionalExpressionSyntaxNode::ConditionalExpressionSyntaxNode( const NameSyntaxNodeSP& name, const ComputationalExpressionSyntaxNodeSP& expression, Type type )
   : ISyntaxNode{ Token_Type::CONDITIONAL_EXPRESSION }
   , mType{ type }
{
   const auto& varible = std::make_shared< VaribleSyntaxNode >( name );
   add_back( varible );
   add_back( expression );
}

ConditionalExpressionSyntaxNode::ConditionalExpressionSyntaxNode( const ComputationalExpressionSyntaxNodeSP& expression, const NameSyntaxNodeSP& name, Type type )
   : ISyntaxNode{ Token_Type::CONDITIONAL_EXPRESSION }
   , mType{ type }
{
   add_back( expression );
   const auto& varible = std::make_shared< VaribleSyntaxNode >( name );
   add_back( varible );
}

ConditionalExpressionSyntaxNode::ConditionalExpressionSyntaxNode( const NameSyntaxNodeSP& name0, const NameSyntaxNodeSP& name1, Type type )
   : ISyntaxNode{ Token_Type::CONDITIONAL_EXPRESSION }
   , mType{ type }
{
   const auto& varible0 = std::make_shared< VaribleSyntaxNode >( name0 );
   const auto& varible1 = std::make_shared< VaribleSyntaxNode >( name1 );
   add_back( varible0 );
   add_back( varible1 );
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
