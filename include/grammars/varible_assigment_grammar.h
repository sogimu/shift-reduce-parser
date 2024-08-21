#pragma once

#include "base/name_syntax_node.h"
#include "base/semicolon_syntax_node.h"
#include "computational_expression_syntax_node.h"
#include "i_grammar.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"
#include "varible_assigment_syntax_node.h"

#include <vector>

class VaribleAssigment : public IGrammar
{
public:
   VaribleAssigment()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         EQUAL,
         COMPUTATIONAL_EXPRESSION,
         EXPRESSION,
         SEMICOLON,
         NAME
      };

      // NAME EQUAL COMPUTATIONAL_EXPRESSION
      // mProductions.emplace_back(
      //    [ this ]( const Stack& stack ) -> std::optional< Plan >
      //    {
      //       NameSyntaxNodeSP name;
      //       EqualSyntaxNodeSP equal;
      //       ComputationalExpressionSyntaxNodeSP computational_expression;
      //
      //       State state = State::START;
      //
      //       SyntaxNodeEmptyVisitor::Handlers handlers;
      //       handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
      //       handlers.name_syntax_node = [ &name, &state ]( const NameSyntaxNodeSP& node )
      //       {
      //          if( state == State::START )
      //          {
      //             state = State::NAME;
      //             name = node;
      //          }
      //       };
      //       handlers.equal_syntax_node = [ &equal, &state ]( const EqualSyntaxNodeSP& node )
      //       {
      //          if( state == State::NAME )
      //          {
      //             state = State::EQUAL;
      //             equal = node;
      //          }
      //       };
      //       handlers.computational_expression_syntax_node = [ &computational_expression, &state ]( const ComputationalExpressionSyntaxNodeSP& node )
      //       {
      //          if( state == State::EQUAL )
      //          {
      //             computational_expression = node;
      //             state = State::COMPUTATIONAL_EXPRESSION;
      //             state = State::FINISH;
      //          }
      //       };
      //
      //       iterate_over_last_n_nodes( stack, 3, handlers );
      //
      //       if( state != State::FINISH )
      //          return {};
      //
      //       Plan plan;
      //       plan.to_remove.nodes.push_back( name );
      //       plan.to_remove.nodes.push_back( equal );
      //       plan.to_remove.nodes.push_back( computational_expression );
      //
      //       const auto& name_syntax_node = std::make_shared< VaribleAssigmentSyntaxNode >( name, computational_expression );
      //       plan.to_add.nodes.push_back( name_syntax_node );
      //       return plan;
      //    } );

      // NAME EQUAL COMPUTATIONAL_EXPRESSION SEMICOLON
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            NameSyntaxNodeSP name;
            EqualSyntaxNodeSP equal;
            ComputationalExpressionSyntaxNodeSP computational_expression;
            SemicolonSyntaxNodeSP semicolon;

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
            handlers.equal_syntax_node = [ &equal, &state ]( const EqualSyntaxNodeSP& node )
            {
               if( state == State::NAME )
               {
                  state = State::EQUAL;
                  equal = node;
               }
            };
            handlers.computational_expression_syntax_node = [ &computational_expression, &state ]( const ComputationalExpressionSyntaxNodeSP& node )
            {
               if( state == State::EQUAL )
               {
                  computational_expression = node;
                  state = State::COMPUTATIONAL_EXPRESSION;
               }
            };
            handlers.semicolon_syntax_node = [ &semicolon, &state ]( const SemicolonSyntaxNodeSP& node )
            {
               if( state == State::COMPUTATIONAL_EXPRESSION )
               {
                  semicolon = node;
                  state = State::SEMICOLON;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 4, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( name );
            plan.to_remove.nodes.push_back( equal );
            plan.to_remove.nodes.push_back( computational_expression );
            plan.to_remove.nodes.push_back( semicolon );

            const auto& varible_assigment_syntax_node = std::make_shared< VaribleAssigmentSyntaxNode >( name, computational_expression );
            plan.to_add.nodes.push_back( varible_assigment_syntax_node );
            return plan;
         } );
   }
};
