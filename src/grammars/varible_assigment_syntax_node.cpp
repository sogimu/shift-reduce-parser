#include "varible_assigment_syntax_node.h"

#include "base/name_syntax_node.h"
#include "computational_expression_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

#include <string>
#include <vector>

VaribleAssigmentSyntaxNode::VaribleAssigmentSyntaxNode( const NameSyntaxNodeSP& name,
                                                        const ComputationalExpressionSyntaxNodeSP& node ):
    ISyntaxNode{ Token_Type::VARIBLE_ASSIGMENT }
{
    Add( name );
    Add( node );
}

std::string VaribleAssigmentSyntaxNode::name() const
{
    return std::dynamic_pointer_cast<NameSyntaxNode>( this->operator[]( 0 ) )->value();
}

ComputationalExpressionSyntaxNodeSP VaribleAssigmentSyntaxNode::computational_expression() const
{
    return std::dynamic_pointer_cast<ComputationalExpressionSyntaxNode>( this->operator[]( 1 ) );
}

void VaribleAssigmentSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor ) { visitor->visit( shared_from_this() ); }

bool VaribleAssigmentSyntaxNode::compare( const ISyntaxNode& node ) const
{
    bool is_equal = true;
    SyntaxNodeEmptyVisitor::Handlers handlers;
    handlers.varible_assigment_syntax_node = [this, &is_equal]( const VaribleAssigmentSyntaxNodeSP& node ) {
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
