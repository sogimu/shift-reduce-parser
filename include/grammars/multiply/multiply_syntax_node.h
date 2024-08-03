#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <vector>

class E;
class T;
class P;

class MultiplySyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< MultiplySyntaxNode >
{
public:
   MultiplySyntaxNode();
   bool compare( const ISyntaxNode& node ) const override;
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using MultiplySyntaxNodeSP = std::shared_ptr< MultiplySyntaxNode >;
using MultiplySyntaxNodeCSP = std::shared_ptr< const MultiplySyntaxNode >;
