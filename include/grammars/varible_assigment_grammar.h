#pragma once

#include "nonterminals/function_call_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "terminals/semicolon_syntax_node.h"
#include "nonterminals/computational_expression_syntax_node.h"
#include "i_grammar.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"
#include "nonterminals/varible_assigment_statment_syntax_node.h"

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
         VALUE,
         SEMICOLON,
         NAME
      };

      // NAME EQUAL COMPUTATIONAL_EXPRESSION SEMICOLON
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack ) -> std::optional< Plan >
         {
            NameSyntaxNodeSP name;
            EqualSyntaxNodeSP equal;
            ISyntaxNodeSP value;
            SemicolonSyntaxNodeSP semicolon;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& /* node */ ) { state = State::ERROR; };
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
            handlers.computational_expression_syntax_node = [ &value, &state ]( const ComputationalExpressionSyntaxNodeSP& node )
            {
               if( state == State::EQUAL )
               {
                  value = node;
                  state = State::VALUE;
               }
            };
            handlers.function_call_syntax_node = [ &value, &state ]( const FunctionCallSyntaxNodeSP& node )
            {
               if( state == State::EQUAL )
               {
                  const auto& function_call = std::make_shared< FunctionCallSyntaxNode >( node->name() );
                  for( const auto& argument : *node )
                     function_call->add_back( argument );
                  value = function_call;
                  state = State::VALUE;
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
            plan.to_remove.nodes.push_back( name );
            plan.to_remove.nodes.push_back( equal );
            plan.to_remove.nodes.push_back( value );
            plan.to_remove.nodes.push_back( semicolon );

            // const auto& computational_expression = std::make_shared< ComputationalExpressionSyntaxNode >();
            // computational_expression->add_back( expression );

            const auto& varible_assigment_statment_syntax_node = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( /* name, expression */ );
            varible_assigment_statment_syntax_node->add_back( name );
            varible_assigment_statment_syntax_node->add_back( value );
            plan.to_add.nodes.push_back( varible_assigment_statment_syntax_node );
            return plan;
         } );

      // NAME EQUAL NAME SEMICOLON
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack ) -> std::optional< Plan >
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

            const auto& varible_assigment_statment_syntax_node = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( target_name, source_name );
            // varible_assigment_statment_syntax_node->add_back( name );
            // varible_assigment_statment_syntax_node->add_back( value );
            plan.to_add.nodes.push_back( varible_assigment_statment_syntax_node );
            return plan;
         } );
   }
};
