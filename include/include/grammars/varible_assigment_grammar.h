#pragma once

#include "terminals/name_syntax_node.h"
#include "terminals/semicolon_syntax_node.h"
#include "nonterminals/computational_expression_syntax_node.h"
#include "i_grammar.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"
#include "nonterminals/varible_assigment_syntax_node.h"

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
         ADDITION,
         SUBTRACTION,
         MULTIPLY,
         DIVISION,
         VALUE,
         EXPRESSION,
         SEMICOLON,
         NAME
      };

      // NAME EQUAL COMPUTATIONAL_EXPRESSION|ADDITION|SUBTRACTION|MULTIPLY|DIVISION SEMICOLON
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            NameSyntaxNodeSP name;
            EqualSyntaxNodeSP equal;
            ISyntaxNodeSP expression;
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
            handlers.computational_expression_syntax_node = [ &expression, &state ]( const ComputationalExpressionSyntaxNodeSP& node )
            {
               if( state == State::EQUAL )
               {
                  expression = node;
                  state = State::COMPUTATIONAL_EXPRESSION;
               }
            };
            // handlers.addition_syntax_node = [ &expression, &state ]( const AdditionSyntaxNodeSP& node )
            // {
            //    if( state == State::EQUAL )
            //    {
            //       expression = node;
            //       state = State::ADDITION;
            //    }
            // };
            // handlers.subtraction_syntax_node = [ &expression, &state ]( const SubtractionSyntaxNodeSP& node )
            // {
            //    if( state == State::EQUAL )
            //    {
            //       expression = node;
            //       state = State::SUBTRACTION;
            //    }
            // };
            // handlers.multiply_syntax_node = [ &expression, &state ]( const MultiplySyntaxNodeSP& node )
            // {
            //    if( state == State::EQUAL )
            //    {
            //       expression = node;
            //       state = State::MULTIPLY;
            //    }
            // };
            // handlers.division_syntax_node = [ &expression, &state ]( const DivisionSyntaxNodeSP& node )
            // {
            //    if( state == State::EQUAL )
            //    {
            //       expression = node;
            //       state = State::DIVISION;
            //    }
            // };
            handlers.semicolon_syntax_node = [ &semicolon, &state ]( const SemicolonSyntaxNodeSP& node )
            {
               if( state == State::COMPUTATIONAL_EXPRESSION || state == State::ADDITION || state == State::MULTIPLY || state == State::SUBTRACTION ||
                   state == State::DIVISION )
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
            plan.to_remove.nodes.push_back( expression );
            plan.to_remove.nodes.push_back( semicolon );

            // const auto& computational_expression = std::make_shared< ComputationalExpressionSyntaxNode >();
            // computational_expression->Add( expression );

            const auto& varible_assigment_syntax_node = std::make_shared< VaribleAssigmentSyntaxNode >( /* name, expression */ );
            varible_assigment_syntax_node->Add( name );
            varible_assigment_syntax_node->Add( expression );
            plan.to_add.nodes.push_back( varible_assigment_syntax_node );
            return plan;
         } );

      // NAME EQUAL NAME SEMICOLON
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            NameSyntaxNodeSP target_name;
            EqualSyntaxNodeSP equal;
            NameSyntaxNodeSP source_name;
            SemicolonSyntaxNodeSP semicolon;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.name_syntax_node = [ &target_name, &source_name, &state ]( const NameSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  state = State::NAME;
                  target_name = node;
               }
               else if( state == State::EQUAL )
               {
                  state = State::VALUE;
                  source_name = node;
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
            handlers.semicolon_syntax_node = [ &semicolon, &state ]( const SemicolonSyntaxNodeSP& node )
            {
               if( state == State::VALUE )
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
            plan.to_remove.nodes.push_back( target_name );
            plan.to_remove.nodes.push_back( equal );
            plan.to_remove.nodes.push_back( source_name );
            plan.to_remove.nodes.push_back( semicolon );

            const auto& varible_assigment_syntax_node = std::make_shared< VaribleAssigmentSyntaxNode >( target_name, source_name );
            // varible_assigment_syntax_node->Add( name );
            // varible_assigment_syntax_node->Add( value );
            plan.to_add.nodes.push_back( varible_assigment_syntax_node );
            return plan;
         } );
   }
};
