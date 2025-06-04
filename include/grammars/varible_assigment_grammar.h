#pragma once

#include "nonterminals/function_call_syntax_node.h"
#include "terminals/close_curly_bracket_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "terminals/semicolon_syntax_node.h"
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

      // NAME EQUAL F|BIN_EXPR|UN_EXPR|NAME|FUNCTION_CALL [SEMICOLON|CLOSE_CURLY_BRACKET]
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            NameSyntaxNodeSP name;
            EqualSyntaxNodeSP equal;
            ISyntaxNodeSP value;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& /* node */ ) { state = State::ERROR; };
            handlers.name_syntax_node = [ &name, &value, &state, &lookahead ]( const NameSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  state = State::NAME;
                  name = node;
               }
               else if( state == State::EQUAL )
               {
                   if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                    check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                   {
                        value = node;
                        state = State::VALUE;
                        state = State::FINISH;
                    }
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
            handlers.f_syntax_node = [ &value, &state, &lookahead ]( const FSyntaxNodeSP& node )
            {
               if( state == State::EQUAL )
               {
                   if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                    check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                   {
                        value = node;
                        state = State::VALUE;
                        state = State::FINISH;
                    }
               }
            };
            handlers.bin_expr_syntax_node = [ &value, &state, &lookahead ]( const BinExprSyntaxNodeSP& node )
            {
               if( state == State::EQUAL )
               {
                   if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                    check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                   {
                        value = node;
                        state = State::VALUE;
                        state = State::FINISH;
                    }
               }
            };
            handlers.un_expr_syntax_node = [ &value, &state, &lookahead ]( const UnExprSyntaxNodeSP& node )
            {
               if( state == State::EQUAL )
               {
                   if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                    check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                   {
                        value = node;
                        state = State::VALUE;
                        state = State::FINISH;
                    }
               }
            };
            handlers.function_call_syntax_node = [ &value, &state, &lookahead ]( const FunctionCallSyntaxNodeSP& node )
            {
               if( state == State::EQUAL )
               {
                   if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                    check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                   {
                        value = node;
                        state = State::VALUE;
                        state = State::FINISH;
                    }
               }
            };

            iterate_over_last_n_nodes( stack, 3, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( name );
            plan.to_remove.nodes.push_back( equal );
            plan.to_remove.nodes.push_back( value );

            const auto& varible_assigment_statment_syntax_node = std::make_shared< VaribleAssigmentStatmentSyntaxNode >();
            varible_assigment_statment_syntax_node->add_back( name );
            varible_assigment_statment_syntax_node->add_back( value );
            plan.to_add.nodes.push_back( varible_assigment_statment_syntax_node );
            return plan;
         } );

   }
};
