#include "expression_syntax_node.h"

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

#include <string>
#include <vector>

void ExpressionSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor ) { visitor->visit( shared_from_this() ); }

bool ExpressionSyntaxNode::compare( const ISyntaxNode& node ) const
{
    bool is_equal = true;
    SyntaxNodeEmptyVisitor::Handlers handlers;
    handlers.expression_syntax_node = [this, &is_equal]( const ExpressionSyntaxNodeSP& node ) {
        if ( node->Children().size() != this->Children().size() )
        {
            is_equal = false;
            return;
        }
    };
    const auto& visitor = std::make_shared<SyntaxNodeEmptyVisitor>( handlers );
    const_cast<ISyntaxNode&>( node ).accept( visitor );

    // node.accept( visitor );
    return is_equal;
}
