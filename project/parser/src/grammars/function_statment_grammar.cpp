#include "function_statment_grammar.h"

#include "i_grammar.h"
#include "nonterminals/function_statment_syntax_node.h"
#include "terminals/function_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "terminals/comma_syntax_node.h"
#include "nonterminals/scope_statment_syntax_node.h"
#include "terminals/open_circle_bracket_syntax_node.h"
#include "terminals/close_circle_bracket_syntax_node.h"
#include "utils.h"

#include <memory>
#include <vector>

FunctionStatment::FunctionStatment()
{
  enum class State
  {
     START,
     FINISH,
     ERROR,
     FUNCTION,
     NAME,
     ARGUMENT,
     OPEN_CIRCLE_BRACKET,
     CONDITION,
     CLOSE_CIRCLE_BRACKET,
     COMMA,
     SCOPE_STATMENT,
     FUNCTION_CALL,
     FUNCTION_STATMENT
  };

  // FUNCTION NAME OPEN_CIRCLE_BRACKET (NAME|F|BIN_EXPR|UN_EXPR|FUNC_CALL COMMA?)+ CLOSE_CIRCLE_BRACKET SCOPE
  mProductions.emplace_back(
     []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
     {
        bool is_function_syntax_node_found = false;

        auto reversed_it = stack.rbegin();
        
        SyntaxNodeEmptyVisitor::Handlers function_handler;
        function_handler.function_syntax_node = [ &is_function_syntax_node_found ]( const FunctionSyntaxNodeSP& /* node */ )
        { 
            is_function_syntax_node_found = true;
        };
        const auto& function_visitor = std::make_shared< SyntaxNodeEmptyVisitor >( function_handler );
        for( ; reversed_it != stack.rend(); ++reversed_it )
        {
            ( *reversed_it )->accept( function_visitor );
            if( is_function_syntax_node_found )
                break;
        }
        if( !is_function_syntax_node_found )
            return Progress{ .readiness = 0.0 };
        
        bool is_open_circle_bracket_found = false;
        bool is_close_circle_bracket_found = false;
        size_t distance_between_open_close_circle_bracket = 0;
        
        auto it = reversed_it.base();
        SyntaxNodeEmptyVisitor::Handlers open_circle_bracket_handler;
        auto open_circle_bracket_syntax_node_it = it;
        open_circle_bracket_handler.open_circle_bracket_syntax_node = [ &is_open_circle_bracket_found ]( const OpenCircleBracketSyntaxNodeSP& /* node */ )
        { 
            is_open_circle_bracket_found = true;
        };
        const auto& open_circle_bracket_visitor = std::make_shared< SyntaxNodeEmptyVisitor >( open_circle_bracket_handler );
        for( ; it != stack.end(); ++it )
        {
           ( *it )->accept( open_circle_bracket_visitor );
           if( is_open_circle_bracket_found )
           {
              open_circle_bracket_syntax_node_it = it;
              break;
           }
        }
        
        if( !is_open_circle_bracket_found )
            return Progress{ .readiness = 0.1 };


        SyntaxNodeEmptyVisitor::Handlers close_circle_bracket_handler;
        auto close_circle_bracket_syntax_node_it = it;
        close_circle_bracket_handler.close_circle_bracket_syntax_node = [ &is_close_circle_bracket_found ]( const CloseCircleBracketSyntaxNodeSP& /* node */ )
        { 
            is_close_circle_bracket_found = true;
        };
        const auto& close_circle_bracket_visitor = std::make_shared< SyntaxNodeEmptyVisitor >( close_circle_bracket_handler );
        for( ; it != stack.end(); ++it )
        {
           ( *it )->accept( close_circle_bracket_visitor );
           if( is_close_circle_bracket_found )
           {
              close_circle_bracket_syntax_node_it = it;
              distance_between_open_close_circle_bracket = std::distance( open_circle_bracket_syntax_node_it, close_circle_bracket_syntax_node_it ) + 1;
              break;
           }
        }
        
        if( !is_close_circle_bracket_found )
            return Progress{ .readiness = 0.2 };
        
        const size_t minimal_size = distance_between_open_close_circle_bracket + 3;
        size_t minimal_steps_number = minimal_size + 1;
        return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_steps_number, &lookahead]( size_t n )->PlanOrProgress
                                                        
        {

            FunctionSyntaxNodeSP function;
            NameSyntaxNodeSP name;
            OpenCircleBracketSyntaxNodeSP open_circle_bracket;
            std::vector< ISyntaxNodeSP > arguments;
            std::vector< ISyntaxNodeSP > commas;
            CloseCircleBracketSyntaxNodeSP close_circle_bracket;
            ScopeSyntaxNodeSP scope_statment;
            
            const Stack& s = stack;
            SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_steps_number, State::START};
            using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
            using HandlerReturn = Handlers::HandlerReturn;
            using Impact = Handlers::Impact;

            handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn
            { 
               return { State::ERROR, Impact::ERROR };
            };
            handlers.function_syntax_node = [ &function, &arguments ]( const State& state, const FunctionSyntaxNodeSP& node ) -> HandlerReturn
            {
               if( state == State::START )
               {
                  function = node;
                   return { State::FUNCTION, Impact::MOVE };
               }
               return { state, Impact::ERROR };
            };
            handlers.name_syntax_node = [ &name, &arguments ]( const State& state, const NameSyntaxNodeSP& node ) -> HandlerReturn
            {
               if( state == State::FUNCTION )
               {
                  name = node;
                   return { State::NAME, Impact::MOVE };
               }
               else if( state == State::OPEN_CIRCLE_BRACKET || state == State::COMMA )
               {
                  arguments.emplace_back( node );
                   return { State::ARGUMENT, Impact::MOVE };
               }
               return { state, Impact::ERROR };
            };
            handlers.comma_syntax_node = [ &commas ]( const State& state, const CommaSyntaxNodeSP& node ) -> HandlerReturn
            {
               if( state == State::ARGUMENT )
               {
                  commas.emplace_back( node );
                   return { State::COMMA, Impact::MOVE };
               }
               return { state, Impact::ERROR };
            };
            handlers.open_circle_bracket_syntax_node = [ &open_circle_bracket ]( const State& state, const OpenCircleBracketSyntaxNodeSP& node ) -> HandlerReturn
            {
               if( state == State::NAME )
               {
                  open_circle_bracket = node;
                   return { State::OPEN_CIRCLE_BRACKET, Impact::MOVE };
               }
               return { state, Impact::ERROR };
            };
            handlers.close_circle_bracket_syntax_node = [ &close_circle_bracket ]( const State& state, const CloseCircleBracketSyntaxNodeSP& node ) -> HandlerReturn
            {
               if( state == State::ARGUMENT || state == State::OPEN_CIRCLE_BRACKET )
               {
                  close_circle_bracket = node;
                   return { State::CLOSE_CIRCLE_BRACKET, Impact::MOVE };
               }
               return { state, Impact::ERROR };
            };
            handlers.scope_statment_syntax_node = [ &scope_statment ]( const State& state, const ScopeSyntaxNodeSP& node ) -> HandlerReturn
            {
               if( state == State::CLOSE_CIRCLE_BRACKET )
               {
                  scope_statment = node;
                   return { State::FINISH, Impact::MOVE };
               }
               return { state, Impact::ERROR };
            };

            auto iteration_result = iterate_over_last_n_nodesv2< State >( stack, n, handlers );

            PlanOrProgress plan_or_progress;
            if( iteration_result.state == State::ERROR )
            {
                plan_or_progress = Progress{ .readiness = 0 };
            }  
            else if( iteration_result.state == State::FINISH )
            {
                Plan plan;
                plan.to_remove.nodes.push_back( function );
                plan.to_remove.nodes.push_back( name );
                plan.to_remove.nodes.push_back( open_circle_bracket );
                for( const auto& argument : arguments )
                   plan.to_remove.nodes.push_back( argument );
                for( const auto& comma : commas )
                   plan.to_remove.nodes.push_back( comma );
                plan.to_remove.nodes.push_back( close_circle_bracket );
                plan.to_remove.nodes.push_back( scope_statment );
                std::vector< LexicalTokens::LexicalToken > lexical_tokens { 
                                              function->lexical_tokens().at(0),
                                              open_circle_bracket->lexical_tokens().at(0),
                                              close_circle_bracket->lexical_tokens().at(0)
                                              };
                const auto& function_node = std::make_shared< FunctionStatmentSyntaxNode >( name, arguments, scope_statment, lexical_tokens );
                plan.to_add.nodes.push_back( function_node );
                plan_or_progress = plan;
            }
            else
            {
                plan_or_progress = Progress{ .readiness = iteration_result.readiness };
            }
            return plan_or_progress;
         });
    });
  
  // FUNCTION_STATMENT SEMICOLON
  mProductions.emplace_back(
     []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
     {
        const size_t minimal_size = 2;
        size_t minimal_steps_number = 2;
        return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_steps_number, &lookahead]( size_t n )->PlanOrProgress
                                                        
        {
          FunctionStatmentSyntaxNodeSP function_statment;
          SemicolonSyntaxNodeSP semicolon;

          const Stack& s = stack;
          SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_steps_number, State::START};
          using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
          using HandlerReturn = Handlers::HandlerReturn;
          using Impact = Handlers::Impact;

          handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn
          { 
             return { State::ERROR, Impact::ERROR };
          };
          handlers.function_statment_syntax_node = [ &function_statment ]( const State& state, const FunctionStatmentSyntaxNodeSP& node ) -> HandlerReturn
          {
             if( state == State::START )
             {
                function_statment = node;
                return { State::FUNCTION_STATMENT, Impact::MOVE };
             }
             return { state, Impact::ERROR };
          };
          handlers.semicolon_syntax_node = [ &semicolon ]( const State& state, const SemicolonSyntaxNodeSP& node ) -> HandlerReturn
          {
             if( state == State::FUNCTION_STATMENT )
             {
                semicolon = node;
                return { State::FINISH, Impact::MOVE };
             }
             return { state, Impact::ERROR };
          };
          auto iteration_result = iterate_over_last_n_nodesv2< State >( stack, n, handlers );

          PlanOrProgress plan_or_progress;
          if( iteration_result.state == State::ERROR )
          {
              plan_or_progress = Progress{ .readiness = 0 };
          }  
          else if( iteration_result.state == State::FINISH )
          {
              Plan plan;
              plan.to_remove.nodes.push_back( function_statment );
              plan.to_remove.nodes.push_back( semicolon );

              plan.to_add.nodes.push_back( function_statment );
              plan_or_progress = plan;
          }
          else
          {
              plan_or_progress = Progress{ .readiness = iteration_result.readiness };
          }
          return plan_or_progress;
        });
     } );
  }
