#pragma once

#include "i_syntax_node_visitor.h"

#include <functional>
#include <map>
#include <memory>
#include <string>

class SyntaxNodeEmptyVisitor : public ISyntaxNodeVisitor
{
        public:
    struct Handlers
    {
        std::function<void( const ISyntaxNodeSP& )> default_handler = []( const ISyntaxNodeSP& ) {
        };
        std::function<void( const BolSyntaxNodeSP& )> bol_syntax_node = [this]( const BolSyntaxNodeSP& node ) {
            default_handler( node );
        };
        std::function<void( const PlusSyntaxNodeSP& )> plus_syntax_node = [this]( const PlusSyntaxNodeSP& node ) {
            default_handler( node );
        };
        std::function<void( const MinusSyntaxNodeSP& )> minus_syntax_node = [this]( const MinusSyntaxNodeSP& node ) {
            default_handler( node );
        };
        std::function<void( const NumberSyntaxNodeSP& )> number_syntax_node = [this]( const NumberSyntaxNodeSP& node ) {
            default_handler( node );
        };
        std::function<void( const FSyntaxNodeSP& )> f_syntax_node = [this]( const FSyntaxNodeSP& node ) {
            default_handler( node );
        };
        std::function<void( const SumSyntaxNodeSP& )> sum_syntax_node = [this]( const SumSyntaxNodeSP& node ) {
            default_handler( node );
        };
        std::function<void( const DiffSyntaxNodeSP& )> diff_syntax_node = [this]( const DiffSyntaxNodeSP& node ) {
            default_handler( node );
        };
        std::function<void( const ESyntaxNodeSP& )> e_syntax_node = [this]( const ESyntaxNodeSP& node ) {
            default_handler( node );
        };
        std::function<void( const EolSyntaxNodeSP& )> eol_syntax_node = [this]( const EolSyntaxNodeSP& node ) {
            default_handler( node );
        };
        std::function<void( const SemicolonSyntaxNodeSP& )> semicolon_syntax_node =
            [this]( const SemicolonSyntaxNodeSP& node ) {
                default_handler( node );
            };
        std::function<void( const ExpressionSyntaxNodeSP& )> expression_syntax_node =
            [this]( const ExpressionSyntaxNodeSP& node ) {
                default_handler( node );
            };
        std::function<void( const ScopeSyntaxNodeSP& )> scope_syntax_node = [this]( const ScopeSyntaxNodeSP& node ) {
            default_handler( node );
        };
        std::function<void( const OpenCurlyBracketSyntaxNodeSP& )> open_curly_bracket_syntax_node =
            [this]( const OpenCurlyBracketSyntaxNodeSP& node ) {
                default_handler( node );
            };
        std::function<void( const CloseCurlyBracketSyntaxNodeSP& )> close_curly_bracket_syntax_node =
            [this]( const CloseCurlyBracketSyntaxNodeSP& node ) {
                default_handler( node );
            };
        std::function<void( const OpenCircleBracketSyntaxNodeSP& )> open_circle_bracket_syntax_node =
            [this]( const OpenCircleBracketSyntaxNodeSP& node ) {
                default_handler( node );
            };
        std::function<void( const CloseCircleBracketSyntaxNodeSP& )> close_circle_bracket_syntax_node =
            [this]( const CloseCircleBracketSyntaxNodeSP& node ) {
                default_handler( node );
            };
        std::function<void( const ComputationalExpressionSyntaxNodeSP& )> computational_expression_syntax_node =
            [this]( const ComputationalExpressionSyntaxNodeSP& node ) {
                default_handler( node );
            };
        std::function<void( const ConditionalExpressionSyntaxNodeSP& )> conditional_expression_syntax_node =
            [this]( const ConditionalExpressionSyntaxNodeSP& node ) {
                default_handler( node );
            };
        std::function<void( const PrintExpressionSyntaxNodeSP& )> print_expression_syntax_node =
            [this]( const PrintExpressionSyntaxNodeSP& node ) {
                default_handler( node );
            };
        std::function<void( const VaribleAssigmentSyntaxNodeSP& )> varible_assigment_syntax_node =
            [this]( const VaribleAssigmentSyntaxNodeSP& node ) {
                default_handler( node );
            };
        std::function<void( const NameSyntaxNodeSP& )> name_syntax_node = [this]( const NameSyntaxNodeSP& node ) {
            default_handler( node );
        };
        std::function<void( const PrintSyntaxNodeSP& )> print_syntax_node = [this]( const PrintSyntaxNodeSP& node ) {
            default_handler( node );
        };
        std::function<void( const EqualSyntaxNodeSP& )> equal_syntax_node = [this]( const EqualSyntaxNodeSP& node ) {
            default_handler( node );
        };
        std::function<void( const LessSyntaxNodeSP& )> less_syntax_node = [this]( const LessSyntaxNodeSP& node ) {
            default_handler( node );
        };
        std::function<void( const MoreSyntaxNodeSP& )> more_syntax_node = [this]( const MoreSyntaxNodeSP& node ) {
            default_handler( node );
        };
        std::function<void( const IfSyntaxNodeSP& )> if_syntax_node = [this]( const IfSyntaxNodeSP& node ) {
            default_handler( node );
        };
        std::function<void( const IfExpressionSyntaxNodeSP& )> if_expression_syntax_node =
            [this]( const IfExpressionSyntaxNodeSP& node ) {
                default_handler( node );
            };
    };

    SyntaxNodeEmptyVisitor( const Handlers& handlers ): mHandlers{ handlers } {}

    ~SyntaxNodeEmptyVisitor() = default;

    void visit( const BolSyntaxNodeSP& node ) override { mHandlers.bol_syntax_node( node ); }

    void visit( const EolSyntaxNodeSP& node ) override { mHandlers.eol_syntax_node( node ); }

    void visit( const PlusSyntaxNodeSP& node ) override { mHandlers.plus_syntax_node( node ); }

    void visit( const MinusSyntaxNodeSP& node ) override { mHandlers.minus_syntax_node( node ); }

    void visit( const NumberSyntaxNodeSP& node ) override { mHandlers.number_syntax_node( node ); }

    void visit( const FSyntaxNodeSP& node ) override { mHandlers.f_syntax_node( node ); }

    void visit( const SumSyntaxNodeSP& node ) override { mHandlers.sum_syntax_node( node ); }

    void visit( const DiffSyntaxNodeSP& node ) override { mHandlers.diff_syntax_node( node ); }

    void visit( const ESyntaxNodeSP& node ) override { mHandlers.e_syntax_node( node ); }

    void visit( const SemicolonSyntaxNodeSP& node ) override { mHandlers.semicolon_syntax_node( node ); }

    void visit( const ExpressionSyntaxNodeSP& node ) override { mHandlers.expression_syntax_node( node ); }

    void visit( const ScopeSyntaxNodeSP& node ) override { mHandlers.scope_syntax_node( node ); }

    void visit( const OpenCurlyBracketSyntaxNodeSP& node ) override
    {
        mHandlers.open_curly_bracket_syntax_node( node );
    }

    void visit( const CloseCurlyBracketSyntaxNodeSP& node ) override
    {
        mHandlers.close_curly_bracket_syntax_node( node );
    }

    void visit( const OpenCircleBracketSyntaxNodeSP& node ) override
    {
        mHandlers.open_circle_bracket_syntax_node( node );
    }

    void visit( const CloseCircleBracketSyntaxNodeSP& node ) override
    {
        mHandlers.close_circle_bracket_syntax_node( node );
    }

    void visit( const ComputationalExpressionSyntaxNodeSP& node ) override
    {
        mHandlers.computational_expression_syntax_node( node );
    }

    void visit( const ConditionalExpressionSyntaxNodeSP& node ) override
    {
        mHandlers.conditional_expression_syntax_node( node );
    }

    void visit( const PrintExpressionSyntaxNodeSP& node ) override { mHandlers.print_expression_syntax_node( node ); }

    void visit( const VaribleAssigmentSyntaxNodeSP& node ) override { mHandlers.varible_assigment_syntax_node( node ); }

    void visit( const NameSyntaxNodeSP& node ) override { mHandlers.name_syntax_node( node ); }

    void visit( const PrintSyntaxNodeSP& node ) override { mHandlers.print_syntax_node( node ); }

    void visit( const EqualSyntaxNodeSP& node ) override { mHandlers.equal_syntax_node( node ); }

    void visit( const LessSyntaxNodeSP& node ) override { mHandlers.less_syntax_node( node ); }

    void visit( const MoreSyntaxNodeSP& node ) override { mHandlers.more_syntax_node( node ); }

    void visit( const IfSyntaxNodeSP& node ) override { mHandlers.if_syntax_node( node ); }

    void visit( const IfExpressionSyntaxNodeSP& node ) override { mHandlers.if_expression_syntax_node( node ); }

        private:
    Handlers mHandlers;
};
using SyntaxNodeEmptyVisitorSP = std::shared_ptr<SyntaxNodeEmptyVisitor>;
