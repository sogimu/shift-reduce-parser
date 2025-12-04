#include "nonterminals/varible_assigment_statment_syntax_node.h"

#include "terminals/name_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"

VaribleAssigmentStatmentSyntaxNode::VaribleAssigmentStatmentSyntaxNode( const VaribleAssigmentStatmentSyntaxNode& node )
   : ISyntaxNode{ node }
   , mTokens{ node.mTokens }
{

}

VaribleAssigmentStatmentSyntaxNode::VaribleAssigmentStatmentSyntaxNode( const NameSyntaxNodeSP& name, const ISyntaxNodeSP& node, LexicalTokens::LexicalToken token, Context context )
   : ISyntaxNode{ Token_Type::VARIBLE_ASSIGMENT_STATMENT }
   , mContext{ context }
{
    add_back( name );
    add_back( node );
    add_lexical_token(token);
}

VaribleAssigmentStatmentSyntaxNode::VaribleAssigmentStatmentSyntaxNode( const NameSyntaxNodeSP& target_name, const NameSyntaxNodeSP& source_name, LexicalTokens::LexicalToken token, Context context )

   : ISyntaxNode{ Token_Type::VARIBLE_ASSIGMENT_STATMENT }
   , mContext{ context }
{
    add_back( target_name );
    add_back( source_name );
    add_lexical_token(token);
}
NameSyntaxNodeSP VaribleAssigmentStatmentSyntaxNode::target() const
{
   return std::dynamic_pointer_cast< NameSyntaxNode >( this->operator[]( 0 ) );
}

// ComputationalExpressionSyntaxNodeSP VaribleAssigmentStatmentSyntaxNode::source() const
// {
//    ComputationalExpressionSyntaxNodeSP argument;
//    const auto& value_node = this->operator[]( 1 );
//    match( value_node,
//           { .computational_expression_syntax_node = [ &argument ]( const ComputationalExpressionSyntaxNodeSP& computational_expression )
//             { argument = computational_expression; },
//             .name_syntax_node = [ &argument ]( const NameSyntaxNodeSP& name ) { argument = std::make_shared< ComputationalExpressionSyntaxNode >( name ); } } );
//    return argument;
// }

VaribleAssigmentStatmentSyntaxNode::Context VaribleAssigmentStatmentSyntaxNode::context() const
{
   return mContext;
}

void VaribleAssigmentStatmentSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool VaribleAssigmentStatmentSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = true;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.varible_assigment_statment_syntax_node = [ this, &is_equal ]( const VaribleAssigmentStatmentSyntaxNodeSP& node )
   {
      if( node->lexical_tokens() != this->lexical_tokens() )
      {
         is_equal = false;
         return;
      }
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

std::vector< LexicalTokens::LexicalToken > VaribleAssigmentStatmentSyntaxNode::lexical_tokens() const
{ 
    return { mTokens }; 
}

void VaribleAssigmentStatmentSyntaxNode::add_lexical_token(const LexicalTokens::LexicalToken& token)
{
  mTokens.push_back( token );
}
