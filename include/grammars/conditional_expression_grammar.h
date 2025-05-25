#pragma once

#include "terminals/name_syntax_node.h"
#include "nonterminals/conditional_expression_syntax_node.h"
#include "i_grammar.h"

#include <memory>
#include <vector>
#include "utils.h"

class ISyntaxNodeVisitor;

class ConditionalExpression : public IGrammar
{
public:
   ConditionalExpression()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         EQUAL_EXPRESSION0,
         EQUAL_EXPRESSION1,
         FIRST_COMPUTATIONAL_EXPRESSION,
         SECOND_COMPUTATIONAL_EXPRESSION,
         VALUE,
         MORE,
         LESS,
         EQUAL,
         NAME
      };

      // COMPUTATIONAL_EXPRESSION EQUAL EQUAL COMPUTATIONAL_EXPRESSION
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            ComputationalExpressionSyntaxNodeSP computational_expression0;
            EqualSyntaxNodeSP equal0;
            EqualSyntaxNodeSP equal1;
            ComputationalExpressionSyntaxNodeSP computational_expression1;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.computational_expression_syntax_node =
               [ &computational_expression0, &computational_expression1, &state ]( const ComputationalExpressionSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  state = State::FIRST_COMPUTATIONAL_EXPRESSION;
                  computational_expression0 = node;
               }
               else if( state == State::EQUAL_EXPRESSION1 )
               {
                  state = State::SECOND_COMPUTATIONAL_EXPRESSION;
                  computational_expression1 = node;
                  state = State::FINISH;
               }
            };
            handlers.equal_syntax_node = [ &equal0, &equal1, &state ]( const EqualSyntaxNodeSP& node )
            {
               if( state == State::FIRST_COMPUTATIONAL_EXPRESSION )
               {
                  equal0 = node;
                  state = State::EQUAL_EXPRESSION0;
               }
               else if( state == State::EQUAL_EXPRESSION0 )
               {
                  equal1 = node;
                  state = State::EQUAL_EXPRESSION1;
               }
            };

            iterate_over_last_n_nodes( stack, 4, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( computational_expression0 );
            plan.to_remove.nodes.push_back( equal0 );
            plan.to_remove.nodes.push_back( equal1 );
            plan.to_remove.nodes.push_back( computational_expression1 );

            const auto& conditional_expression_node =
               std::make_shared< ConditionalExpressionSyntaxNode >( computational_expression0, computational_expression1, ConditionalExpressionSyntaxNode::Type::EQUAL );
            plan.to_add.nodes.push_back( conditional_expression_node );
            return plan;
         } );

      // NAME EQUAL EQUAL COMPUTATIONAL_EXPRESSION
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            NameSyntaxNodeSP name;
            EqualSyntaxNodeSP equal0;
            EqualSyntaxNodeSP equal1;
            ComputationalExpressionSyntaxNodeSP computational_expression1;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.name_syntax_node = [ &name, &state ]( const NameSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  state = State::NAME;
                  name = node;
               }
            };
            handlers.equal_syntax_node = [ &equal0, &equal1, &state ]( const EqualSyntaxNodeSP& node )
            {
               if( state == State::NAME )
               {
                  equal0 = node;
                  state = State::EQUAL_EXPRESSION0;
               }
               else if( state == State::EQUAL_EXPRESSION0 )
               {
                  equal1 = node;
                  state = State::EQUAL_EXPRESSION1;
               }
            };
            handlers.computational_expression_syntax_node = [ &computational_expression1, &state ]( const ComputationalExpressionSyntaxNodeSP& node )
            {
               if( state == State::EQUAL_EXPRESSION1 )
               {
                  state = State::SECOND_COMPUTATIONAL_EXPRESSION;
                  computational_expression1 = node;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 4, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( name );
            plan.to_remove.nodes.push_back( equal0 );
            plan.to_remove.nodes.push_back( equal1 );
            plan.to_remove.nodes.push_back( computational_expression1 );

            const auto& conditional_expression_node =
               std::make_shared< ConditionalExpressionSyntaxNode >( name, computational_expression1, ConditionalExpressionSyntaxNode::Type::EQUAL );
            plan.to_add.nodes.push_back( conditional_expression_node );
            return plan;
         } );

      // COMPUTATIONAL_EXPRESSION LESS COMPUTATIONAL_EXPRESSION
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            ComputationalExpressionSyntaxNodeSP computational_expression0;
            LessSyntaxNodeSP less;
            ComputationalExpressionSyntaxNodeSP computational_expression1;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.computational_expression_syntax_node =
               [ &computational_expression0, &computational_expression1, &state ]( const ComputationalExpressionSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  state = State::FIRST_COMPUTATIONAL_EXPRESSION;
                  computational_expression0 = node;
               }
               else if( state == State::LESS )
               {
                  state = State::SECOND_COMPUTATIONAL_EXPRESSION;
                  computational_expression1 = node;
                  state = State::FINISH;
               }
            };
            handlers.less_syntax_node = [ &less, &state ]( const LessSyntaxNodeSP& node )
            {
               if( state == State::FIRST_COMPUTATIONAL_EXPRESSION )
               {
                  less = node;
                  state = State::LESS;
               }
            };

            iterate_over_last_n_nodes( stack, 3, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( computational_expression0 );
            plan.to_remove.nodes.push_back( less );
            plan.to_remove.nodes.push_back( computational_expression1 );

            const auto& conditional_expression_node =
               std::make_shared< ConditionalExpressionSyntaxNode >( computational_expression0, computational_expression1, ConditionalExpressionSyntaxNode::Type::LESS );
            plan.to_add.nodes.push_back( conditional_expression_node );
            return plan;
         } );

      // COMPUTATIONAL_EXPRESSION LESS EQUAL COMPUTATIONAL_EXPRESSION
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            ComputationalExpressionSyntaxNodeSP computational_expression0;
            LessSyntaxNodeSP less;
            EqualSyntaxNodeSP equal;
            ComputationalExpressionSyntaxNodeSP computational_expression1;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.computational_expression_syntax_node =
               [ &computational_expression0, &computational_expression1, &state ]( const ComputationalExpressionSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  state = State::FIRST_COMPUTATIONAL_EXPRESSION;
                  computational_expression0 = node;
               }
               else if( state == State::EQUAL )
               {
                  state = State::SECOND_COMPUTATIONAL_EXPRESSION;
                  computational_expression1 = node;
                  state = State::FINISH;
               }
            };
            handlers.less_syntax_node = [ &less, &state ]( const LessSyntaxNodeSP& node )
            {
               if( state == State::FIRST_COMPUTATIONAL_EXPRESSION )
               {
                  less = node;
                  state = State::LESS;
               }
            };
            handlers.equal_syntax_node = [ &equal, &state ]( const EqualSyntaxNodeSP& node )
            {
               if( state == State::LESS )
               {
                  equal = node;
                  state = State::EQUAL;
               }
            };

            iterate_over_last_n_nodes( stack, 4, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( computational_expression0 );
            plan.to_remove.nodes.push_back( less );
            plan.to_remove.nodes.push_back( equal );
            plan.to_remove.nodes.push_back( computational_expression1 );

            const auto& conditional_expression_node = std::make_shared< ConditionalExpressionSyntaxNode >( computational_expression0, computational_expression1,
                                                                                                           ConditionalExpressionSyntaxNode::Type::LESS_OR_EQUAL );
            plan.to_add.nodes.push_back( conditional_expression_node );
            return plan;
         } );

      // COMPUTATIONAL_EXPRESSION MORE EQUAL COMPUTATIONAL_EXPRESSION
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            ComputationalExpressionSyntaxNodeSP computational_expression0;
            MoreSyntaxNodeSP more;
            EqualSyntaxNodeSP equal;
            ComputationalExpressionSyntaxNodeSP computational_expression1;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.computational_expression_syntax_node =
               [ &computational_expression0, &computational_expression1, &state ]( const ComputationalExpressionSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  state = State::FIRST_COMPUTATIONAL_EXPRESSION;
                  computational_expression0 = node;
               }
               else if( state == State::EQUAL )
               {
                  state = State::SECOND_COMPUTATIONAL_EXPRESSION;
                  computational_expression1 = node;
                  state = State::FINISH;
               }
            };
            handlers.more_syntax_node = [ &more, &state ]( const MoreSyntaxNodeSP& node )
            {
               if( state == State::FIRST_COMPUTATIONAL_EXPRESSION )
               {
                  more = node;
                  state = State::MORE;
               }
            };
            handlers.equal_syntax_node = [ &equal, &state ]( const EqualSyntaxNodeSP& node )
            {
               if( state == State::MORE )
               {
                  equal = node;
                  state = State::EQUAL;
               }
            };

            iterate_over_last_n_nodes( stack, 4, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( computational_expression0 );
            plan.to_remove.nodes.push_back( more );
            plan.to_remove.nodes.push_back( equal );
            plan.to_remove.nodes.push_back( computational_expression1 );

            const auto& conditional_expression_node = std::make_shared< ConditionalExpressionSyntaxNode >( computational_expression0, computational_expression1,
                                                                                                           ConditionalExpressionSyntaxNode::Type::MORE_OR_EQUAL );
            plan.to_add.nodes.push_back( conditional_expression_node );
            return plan;
         } );

      // NAME LESS COMPUTATIONAL_EXPRESSION
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            NameSyntaxNodeSP name;
            LessSyntaxNodeSP less;
            ComputationalExpressionSyntaxNodeSP computational_expression1;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.name_syntax_node = [ &name, &state ]( const NameSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  state = State::NAME;
                  name = node;
               }
            };
            handlers.less_syntax_node = [ &less, &state ]( const LessSyntaxNodeSP& node )
            {
               if( state == State::NAME )
               {
                  less = node;
                  state = State::LESS;
               }
            };
            handlers.computational_expression_syntax_node = [ &computational_expression1, &state ]( const ComputationalExpressionSyntaxNodeSP& node )
            {
               if( state == State::LESS )
               {
                  state = State::SECOND_COMPUTATIONAL_EXPRESSION;
                  computational_expression1 = node;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 3, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( name );
            plan.to_remove.nodes.push_back( less );
            plan.to_remove.nodes.push_back( computational_expression1 );

            const auto& conditional_expression_node =
               std::make_shared< ConditionalExpressionSyntaxNode >( name, computational_expression1, ConditionalExpressionSyntaxNode::Type::LESS );
            plan.to_add.nodes.push_back( conditional_expression_node );
            return plan;
         } );

      // NAME LESS NAME
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            NameSyntaxNodeSP name;
            LessSyntaxNodeSP less;
            NameSyntaxNodeSP value;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.name_syntax_node = [ &name, &value, &state ]( const NameSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  state = State::NAME;
                  name = node;
               }
               else if( state == State::LESS )
               {
                  state = State::VALUE;
                  state = State::FINISH;
                  value = node;
               }
            };
            handlers.less_syntax_node = [ &less, &state ]( const LessSyntaxNodeSP& node )
            {
               if( state == State::NAME )
               {
                  less = node;
                  state = State::LESS;
               }
            };

            iterate_over_last_n_nodes( stack, 3, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( name );
            plan.to_remove.nodes.push_back( less );
            plan.to_remove.nodes.push_back( value );

            const auto& conditional_expression_node = std::make_shared< ConditionalExpressionSyntaxNode >( name, value, ConditionalExpressionSyntaxNode::Type::LESS );
            plan.to_add.nodes.push_back( conditional_expression_node );
            return plan;
         } );

      // NAME LESS EQUAL COMPUTATIONAL_EXPRESSION
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            NameSyntaxNodeSP name;
            LessSyntaxNodeSP less;
            EqualSyntaxNodeSP equal;
            ComputationalExpressionSyntaxNodeSP computational_expression1;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.name_syntax_node = [ &name, &state ]( const NameSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  state = State::NAME;
                  name = node;
               }
            };
            handlers.less_syntax_node = [ &less, &state ]( const LessSyntaxNodeSP& node )
            {
               if( state == State::NAME )
               {
                  less = node;
                  state = State::LESS;
               }
            };
            handlers.equal_syntax_node = [ &equal, &state ]( const EqualSyntaxNodeSP& node )
            {
               if( state == State::LESS )
               {
                  equal = node;
                  state = State::EQUAL;
               }
            };
            handlers.computational_expression_syntax_node = [ &computational_expression1, &state ]( const ComputationalExpressionSyntaxNodeSP& node )
            {
               if( state == State::EQUAL )
               {
                  state = State::SECOND_COMPUTATIONAL_EXPRESSION;
                  computational_expression1 = node;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 4, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( name );
            plan.to_remove.nodes.push_back( less );
            plan.to_remove.nodes.push_back( equal );
            plan.to_remove.nodes.push_back( computational_expression1 );

            const auto& conditional_expression_node =
               std::make_shared< ConditionalExpressionSyntaxNode >( name, computational_expression1, ConditionalExpressionSyntaxNode::Type::LESS_OR_EQUAL );
            plan.to_add.nodes.push_back( conditional_expression_node );
            return plan;
         } );

      // NAME MORE COMPUTATIONAL_EXPRESSION
      mProductions.emplace_back(
         []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            NameSyntaxNodeSP name;
            MoreSyntaxNodeSP more;
            ComputationalExpressionSyntaxNodeSP computational_expression1;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.name_syntax_node = [ &name, &state ]( const NameSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  state = State::NAME;
                  name = node;
               }
            };
            handlers.more_syntax_node = [ &more, &state ]( const MoreSyntaxNodeSP& node )
            {
               if( state == State::NAME )
               {
                  more = node;
                  state = State::MORE;
               }
            };
            handlers.computational_expression_syntax_node = [ &computational_expression1, &state ]( const ComputationalExpressionSyntaxNodeSP& node )
            {
               if( state == State::MORE )
               {
                  state = State::SECOND_COMPUTATIONAL_EXPRESSION;
                  computational_expression1 = node;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 3, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( name );
            plan.to_remove.nodes.push_back( more );
            plan.to_remove.nodes.push_back( computational_expression1 );

            const auto& conditional_expression_node =
               std::make_shared< ConditionalExpressionSyntaxNode >( name, computational_expression1, ConditionalExpressionSyntaxNode::Type::MORE );
            plan.to_add.nodes.push_back( conditional_expression_node );
            return plan;
         } );

      // COMPUTATIONAL_EXPRESSION MORE COMPUTATIONAL_EXPRESSION
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            ComputationalExpressionSyntaxNodeSP computational_expression0;
            MoreSyntaxNodeSP more;
            ComputationalExpressionSyntaxNodeSP computational_expression1;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.computational_expression_syntax_node =
               [ &computational_expression0, &computational_expression1, &state ]( const ComputationalExpressionSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  state = State::FIRST_COMPUTATIONAL_EXPRESSION;
                  computational_expression0 = node;
               }
               else if( state == State::MORE )
               {
                  state = State::SECOND_COMPUTATIONAL_EXPRESSION;
                  computational_expression1 = node;
                  state = State::FINISH;
               }
            };
            handlers.more_syntax_node = [ &more, &state ]( const MoreSyntaxNodeSP& node )
            {
               if( state == State::FIRST_COMPUTATIONAL_EXPRESSION )
               {
                  more = node;
                  state = State::MORE;
               }
            };

            iterate_over_last_n_nodes( stack, 3, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( computational_expression0 );
            plan.to_remove.nodes.push_back( more );
            plan.to_remove.nodes.push_back( computational_expression1 );

            const auto& conditional_expression_node =
               std::make_shared< ConditionalExpressionSyntaxNode >( computational_expression0, computational_expression1, ConditionalExpressionSyntaxNode::Type::MORE );
            plan.to_add.nodes.push_back( conditional_expression_node );
            return plan;
         } );
   }
};
