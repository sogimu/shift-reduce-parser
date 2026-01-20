#pragma once

#include <iostream>
#include <string>
#include <iostream>
#include "i_syntax_node.h"
#include "lexical_tokens.h"
#include "utils.h"
#include "i_grammar.h"

class AbstractSyntaxTree
{
public:
   AbstractSyntaxTree( const LexicalTokens& lexical_tokens );

   AbstractSyntaxTree( const ISyntaxNodeSP& root );

   ISyntaxNodeSP root() const;

   bool operator==( const AbstractSyntaxTree& syntax_tree ) const;

   std::string to_string() const;

private:
   Stack mStack;
   ISyntaxNodeSP mRoot;
};

inline std::ostream& operator<<( std::ostream& o, const AbstractSyntaxTree& rhs )
{
   o << rhs.to_string();
   return o;
}
