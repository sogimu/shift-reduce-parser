#include "nonterminals/varible_syntax_node.h"

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "terminals/name_syntax_node.h"

VaribleSyntaxNode::VaribleSyntaxNode( const NameSyntaxNodeSP& name_syntax_node, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens )
   : ISyntaxNode{ Token_Type::VARIBLE }
   , mName{ name_syntax_node->value() }
{
   mTokens = lexical_tokens;
}

std::string VaribleSyntaxNode::name() const
{
   return mName;
}

std::vector< LexicalTokens::LexicalToken > VaribleSyntaxNode::lexical_tokens() const
{ 
    return mTokens; 
}

void VaribleSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool VaribleSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.varible_syntax_node = [ this, &is_equal ]( const VaribleSyntaxNodeSP& node )
   {
      if( node->Children().size() == this->Children().size() )
      {
         is_equal = true;
         return;
      }
   };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );

   return is_equal;
}
