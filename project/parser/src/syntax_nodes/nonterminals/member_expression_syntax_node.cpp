#include "nonterminals/member_expression_syntax_node.h"

#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "terminals/f_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "utils.h"
#include <stdexcept>

MemberExpressionSyntaxNode::MemberExpressionSyntaxNode( const MemberExpressionSyntaxNode& scope )
   : ISyntaxNode{ Token_Type::MEMBER_EXPRESSION }
{
   mTokens = scope.lexical_tokens();
}

MemberExpressionSyntaxNode::MemberExpressionSyntaxNode( const ISyntaxNodeSP& target, const ISyntaxNodeSP& key_or_index_node, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens )
   : ISyntaxNode{ Token_Type::MEMBER_EXPRESSION }
{
    mTokens = lexical_tokens;
    add_back( target );
    add_back( key_or_index_node );

    // mContainerVaribleName = std::dynamic_pointer_cast< NameSyntaxNode >( target )->value();
    // if( check_type<NameSyntaxNode>( key_or_index_node ) )
    // {
    //     mKeyOrIndex = std::dynamic_pointer_cast< NameSyntaxNode >( key_or_index_node )->value();
    // }
    // else if( check_type<FSyntaxNode>( key_or_index_node ) )
    // {
    //     const auto& f = std::dynamic_pointer_cast< FSyntaxNode >( key_or_index_node );
    //     if( !check_type<IntSyntaxNode>( f->operator[]( 0 ) ) )
    //     {
    //         throw std::runtime_error("Index of element in MemberExpressionSyntaxNode must be IntSyntaxNode!");
    //     }
    //     const auto& i = std::dynamic_pointer_cast< IntSyntaxNode >( f->operator[](0) );
    //     mKeyOrIndex = static_cast< size_t >( i->value() );
    // }
}

const std::string MemberExpressionSyntaxNode::container_varible_name() const
{
  return mContainerVaribleName;
}

const std::variant<size_t, std::string>& MemberExpressionSyntaxNode::key_or_index() const
{
  return mKeyOrIndex;
}

void MemberExpressionSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

std::vector< LexicalTokens::LexicalToken > MemberExpressionSyntaxNode::lexical_tokens() const
{ 
    return mTokens; 
}

bool MemberExpressionSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = true;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.member_expression_syntax_node = [ this, &is_equal ]( const MemberExpressionSyntaxNodeSP& node )
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
