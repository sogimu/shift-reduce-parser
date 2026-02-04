#include "varible_assigment_grammar.h"

#include "nonterminals/function_call_syntax_node.h"
#include "nonterminals/member_expression_syntax_node.h"
#include "nonterminals/object_pair_syntax_node.h"
#include "nonterminals/varible_syntax_node.h"
#include "terminals/close_curly_bracket_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "terminals/open_curly_bracket_syntax_node.h"
#include "terminals/semicolon_syntax_node.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"
#include "nonterminals/varible_assigment_statment_syntax_node.h"
#include <memory>
#include <vector>

VaribleAssigment::VaribleAssigment()
{
  enum class State
  {
     START,
     FINISH,
     ERROR,
     VAR,
     EQUAL,
     VALUE,
     SEMICOLON,
     NAME,
     VARIBLE_ASSIGMENT,
     OPEN_CURLY_BRACKET
  };

  // VAR NAME|MEMBER_EXPRESSION EQUAL F|BIN_EXPR|UN_EXPR|NAME|FUNCTION_CALL|MEMBER_EXPRESSION [SEMICOLON|CLOSE_CURLY_BRACKET]
  mProductions.emplace_back(
     []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
     {
        const size_t minimal_size = 4;
        const size_t minimal_steps_number = 4;
        return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_steps_number, &lookahead]( size_t n )->PlanOrProgress
                                                        {
                                                        VarSyntaxNodeSP var;
                                                        ISyntaxNodeSP target;
                                                        EqualSyntaxNodeSP equal;
                                                        ISyntaxNodeSP value;

                                                        const Stack& s = stack;
                                                        SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_steps_number, State::START};
                                                        using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
                                                        using HandlerReturn = Handlers::HandlerReturn;
                                                        using Impact = Handlers::Impact;

                                                        handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn
                                                        { 
                                                           return { State::ERROR, Impact::ERROR };
                                                        };

                                                        handlers.var_syntax_node = [ &var, &lookahead ]( const State& state, const VarSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::START )
                                                           {
                                                               var = node;
                                                               return { State::VAR, Impact::MOVE };
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.name_syntax_node = [ &target, &value, &lookahead ]( const State& state, const NameSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::VAR )
                                                           {
                                                               target = node;
                                                               return { State::NAME, Impact::MOVE };
                                                           }
                                                           else if( state == State::EQUAL )
                                                           {
                                                               if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                               {
                                                                   std::vector< LexicalTokens::LexicalToken > lexical_tokens {};
                                                                   value = std::make_shared<VaribleSyntaxNode>( node, node->lexical_tokens() );
                                                                   return { State::FINISH, Impact::MOVE };
                                                               }
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.member_expression_syntax_node = [ &target, &value, &lookahead ]( const State& state, const MemberExpressionSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::VAR )
                                                           {
                                                               target = node;
                                                               return { State::NAME, Impact::MOVE };
                                                           }
                                                           else if( state == State::EQUAL )
                                                           {
                                                               if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                               {
                                                                   value = node;
                                                                   return { State::FINISH, Impact::MOVE };
                                                               }
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.equal_syntax_node = [ &equal ]( const State& state, const EqualSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::NAME )
                                                           {
                                                               equal = node;
                                                               return { State::EQUAL, Impact::MOVE };
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.f_syntax_node = [ &value, &lookahead ]( const State& state, const FSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::EQUAL )
                                                           {
                                                               if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                               {
                                                                   value = node;
                                                                   return { State::FINISH, Impact::MOVE };
                                                               }
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.bin_expr_syntax_node = [ &value, &lookahead ]( const State& state, const BinExprSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::EQUAL )
                                                           {
                                                               if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                               {
                                                                   value = node;
                                                                   return { State::FINISH, Impact::MOVE };
                                                               }
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.un_expr_syntax_node = [ &value, &lookahead ]( const State& state, const UnExprSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::EQUAL )
                                                           {
                                                               if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                               {
                                                                   value = node;
                                                                   return { State::FINISH, Impact::MOVE };
                                                               }
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.function_call_syntax_node = [ &value, &lookahead ]( const State& state, const FunctionCallSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::EQUAL )
                                                           {
                                                               if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                               {
                                                                   value = node;
                                                                   return { State::FINISH, Impact::MOVE };
                                                               }
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.member_expression_syntax_node = [ &value, &lookahead ]( const State& state, const MemberExpressionSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::EQUAL )
                                                           {
                                                               if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                               {
                                                                   value = node;
                                                                   return { State::FINISH, Impact::MOVE };
                                                               }
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.array_syntax_node = [ &value, &lookahead ]( const State& state, const ArraySyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::EQUAL )
                                                           {
                                                               if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                               {
                                                                   value = node;
                                                                   return { State::FINISH, Impact::MOVE };
                                                               }
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.object_syntax_node = [ &value, &lookahead ]( const State& state, const ObjectSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::EQUAL )
                                                           {
                                                               if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                               {
                                                                   value = node;
                                                                   return { State::FINISH, Impact::MOVE };
                                                               }
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
                                                            plan.to_remove.nodes.push_back( var );
                                                            plan.to_remove.nodes.push_back( target );
                                                            plan.to_remove.nodes.push_back( equal );
                                                            plan.to_remove.nodes.push_back( value );

                                                            std::vector< LexicalTokens::LexicalToken > lexical_tokens {};
                                                            const auto& varible_assigment_statment_syntax_node = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( target, value, equal->lexical_tokens().at(0), VaribleAssigmentStatmentSyntaxNode::Context::LOCAL );
                                                            plan.to_add.nodes.push_back( varible_assigment_statment_syntax_node );
                                                            plan_or_progress = plan;
                                                        }
                                                        else
                                                        {
                                                            plan_or_progress = Progress{ .readiness = iteration_result.readiness };
                                                        }
                                                        return plan_or_progress;
                                                        });
     } );
  
  // VAR NAME EQUAL OPEN_CURLY_BRACKET CLOSE_CURLY_BRACKET [SEMICOLON|CLOSE_CURLY_BRACKET]
  mProductions.emplace_back(
     []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
     {
        const size_t minimal_size = 5;
        const size_t minimal_steps_number = 5;
        return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_steps_number, &lookahead]( size_t n )->PlanOrProgress
                                                        {
                                                        VarSyntaxNodeSP var;
                                                        NameSyntaxNodeSP name;
                                                        EqualSyntaxNodeSP equal;
                                                        OpenCurlyBracketSyntaxNodeSP open_curly_bracket;
                                                        CloseCurlyBracketSyntaxNodeSP close_curly_bracket;

                                                        const Stack& s = stack;
                                                        SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_steps_number, State::START};
                                                        using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
                                                        using HandlerReturn = Handlers::HandlerReturn;
                                                        using Impact = Handlers::Impact;

                                                        handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn
                                                        { 
                                                           return { State::ERROR, Impact::ERROR };
                                                        };

                                                        handlers.var_syntax_node = [ &var, &lookahead ]( const State& state, const VarSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::START )
                                                           {
                                                               var = node;
                                                               return { State::VAR, Impact::MOVE };
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.name_syntax_node = [ &name, &lookahead ]( const State& state, const NameSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::VAR )
                                                           {
                                                               name = node;
                                                               return { State::NAME, Impact::MOVE };
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.equal_syntax_node = [ &equal ]( const State& state, const EqualSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::NAME )
                                                           {
                                                               equal = node;
                                                               return { State::EQUAL, Impact::MOVE };
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.open_curly_bracket_syntax_node = [ &open_curly_bracket, &lookahead ]( const State& state, const OpenCurlyBracketSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::EQUAL )
                                                           {
                                                               open_curly_bracket = node;
                                                               return { State::OPEN_CURLY_BRACKET, Impact::MOVE };
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.close_curly_bracket_syntax_node = [ &close_curly_bracket, &lookahead ]( const State& state, const CloseCurlyBracketSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::OPEN_CURLY_BRACKET )
                                                           {
                                                               if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                               {
                                                                   close_curly_bracket = node;
                                                                   return { State::FINISH, Impact::MOVE };
                                                               }
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
                                                            plan.to_remove.nodes.push_back( var );
                                                            plan.to_remove.nodes.push_back( name );
                                                            plan.to_remove.nodes.push_back( equal );
                                                            plan.to_remove.nodes.push_back( open_curly_bracket );
                                                            plan.to_remove.nodes.push_back( close_curly_bracket );

                                                            std::vector< LexicalTokens::LexicalToken > lexical_tokens { 
                                                                                          open_curly_bracket->lexical_tokens().at(0),
                                                                                          close_curly_bracket->lexical_tokens().at(0)
                                                                                          };
                                                            const auto& object = std::make_shared< ObjectSyntaxNode >( std::vector<ObjectPairSyntaxNodeSP>{}, lexical_tokens );
                                                            const auto& varible_assigment_statment_syntax_node = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( name, object, equal->lexical_tokens().at(0), VaribleAssigmentStatmentSyntaxNode::Context::LOCAL );
                                                            plan.to_add.nodes.push_back( varible_assigment_statment_syntax_node );
                                                            plan_or_progress = plan;
                                                        }
                                                        else
                                                        {
                                                            plan_or_progress = Progress{ .readiness = iteration_result.readiness };
                                                        }
                                                        return plan_or_progress;
                                                        });
     } );

  // NAME EQUAL F|BIN_EXPR|UN_EXPR|NAME|FUNCTION_CALL|MEMBER_EXPRESSION [SEMICOLON|CLOSE_CURLY_BRACKET]
  mProductions.emplace_back(
     []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
     {
        const size_t minimal_size = 3;
        const size_t minimal_steps_number = 3;
        return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_steps_number, &lookahead]( size_t n )->PlanOrProgress
                                                        {
                                                        ISyntaxNodeSP target;
                                                        EqualSyntaxNodeSP equal;
                                                        ISyntaxNodeSP source;

                                                        const Stack& s = stack;
                                                        SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_steps_number, State::START};
                                                        using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
                                                        using HandlerReturn = Handlers::HandlerReturn;
                                                        using Impact = Handlers::Impact;

                                                        handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn
                                                        { 
                                                           return { State::ERROR, Impact::ERROR };
                                                        };

                                                        handlers.name_syntax_node = [ &target, &source, &lookahead ]( const State& state, const NameSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::START )
                                                           {
                                                               target = node;
                                                               return { State::NAME, Impact::MOVE };
                                                           }
                                                           else if( state == State::EQUAL )
                                                           {
                                                               if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                               {
                                                                   std::vector< LexicalTokens::LexicalToken > lexical_tokens {};
                                                                   source = std::make_shared<VaribleSyntaxNode>( node, node->lexical_tokens() );
                                                                   return { State::FINISH, Impact::MOVE };
                                                               }
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.equal_syntax_node = [ &equal ]( const State& state, const EqualSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::NAME )
                                                           {
                                                               equal = node;
                                                               return { State::EQUAL, Impact::MOVE };
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.f_syntax_node = [ &source, &lookahead ]( const State& state, const FSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::EQUAL )
                                                           {
                                                               if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                               {
                                                                   source = node;
                                                                   return { State::FINISH, Impact::MOVE };
                                                               }
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.bin_expr_syntax_node = [ &source, &lookahead ]( const State& state, const BinExprSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::EQUAL )
                                                           {
                                                               if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                               {
                                                                   source = node;
                                                                   return { State::FINISH, Impact::MOVE };
                                                               }
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.un_expr_syntax_node = [ &source, &lookahead ]( const State& state, const UnExprSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::EQUAL )
                                                           {
                                                               if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                               {
                                                                   source = node;
                                                                   return { State::FINISH, Impact::MOVE };
                                                               }
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.function_call_syntax_node = [ &source, &lookahead ]( const State& state, const FunctionCallSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::EQUAL )
                                                           {
                                                               if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                               {
                                                                   source = node;
                                                                   return { State::FINISH, Impact::MOVE };
                                                               }
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.member_expression_syntax_node = [ &source, &target, &lookahead ]( const State& state, const MemberExpressionSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::START )
                                                           {
                                                               target = node;
                                                               return { State::NAME, Impact::MOVE };
                                                           }
                                                           else if( state == State::EQUAL )
                                                           {
                                                               if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                               {
                                                                   source = node;
                                                                   return { State::FINISH, Impact::MOVE };
                                                               }
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };

                                                        handlers.array_syntax_node = [ &source, &lookahead ]( const State& state, const ArraySyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::EQUAL )
                                                           {
                                                               if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                               {
                                                                   source = node;
                                                                   return { State::FINISH, Impact::MOVE };
                                                               }
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        
                                                        handlers.object_syntax_node = [ &source, &lookahead ]( const State& state, const ObjectSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::EQUAL )
                                                           {
                                                               if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                               {
                                                                   source = node;
                                                                   return { State::FINISH, Impact::MOVE };
                                                               }
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
                                                            plan.to_remove.nodes.push_back( target );
                                                            plan.to_remove.nodes.push_back( equal );
                                                            plan.to_remove.nodes.push_back( source );

                                                            const auto& varible_assigment_statment_syntax_node = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( target, source, equal->lexical_tokens().at(0) );
                                                            plan.to_add.nodes.push_back( varible_assigment_statment_syntax_node );
                                                            plan_or_progress = plan;
                                                        }
                                                        else
                                                        {
                                                            plan_or_progress = Progress{ .readiness = iteration_result.readiness };
                                                        }
                                                        return plan_or_progress;
                                                        });
  } ); 
  
  // NAME EQUAL OPEN_CURLY_BRACKET CLOSE_CURLY_BRACKET [SEMICOLON|CLOSE_CURLY_BRACKET]
  mProductions.emplace_back(
     []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
     {
        const size_t minimal_size = 4;
        const size_t minimal_steps_number = 4;
        return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_steps_number, &lookahead]( size_t n )->PlanOrProgress
                                                        {
                                                        NameSyntaxNodeSP name;
                                                        EqualSyntaxNodeSP equal;
                                                        OpenCurlyBracketSyntaxNodeSP open_curly_bracket;
                                                        CloseCurlyBracketSyntaxNodeSP close_curly_bracket;

                                                        const Stack& s = stack;
                                                        SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_steps_number, State::START};
                                                        using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
                                                        using HandlerReturn = Handlers::HandlerReturn;
                                                        using Impact = Handlers::Impact;

                                                        handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn
                                                        { 
                                                           return { State::ERROR, Impact::ERROR };
                                                        };
                                                        handlers.name_syntax_node = [ &name, &lookahead ]( const State& state, const NameSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::START )
                                                           {
                                                               name = node;
                                                               return { State::NAME, Impact::MOVE };
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.equal_syntax_node = [ &equal ]( const State& state, const EqualSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::NAME )
                                                           {
                                                               equal = node;
                                                               return { State::EQUAL, Impact::MOVE };
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.open_curly_bracket_syntax_node = [ &open_curly_bracket, &lookahead ]( const State& state, const OpenCurlyBracketSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::EQUAL )
                                                           {
                                                               open_curly_bracket = node;
                                                               return { State::OPEN_CURLY_BRACKET, Impact::MOVE };
                                                           }
                                                           return { state, Impact::ERROR };
                                                        };
                                                        handlers.close_curly_bracket_syntax_node = [ &close_curly_bracket, &lookahead ]( const State& state, const CloseCurlyBracketSyntaxNodeSP& node ) -> HandlerReturn
                                                        {
                                                           if( state == State::OPEN_CURLY_BRACKET )
                                                           {
                                                               if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                               {
                                                                   close_curly_bracket = node;
                                                                   return { State::FINISH, Impact::MOVE };
                                                               }
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
                                                            plan.to_remove.nodes.push_back( name );
                                                            plan.to_remove.nodes.push_back( equal );
                                                            plan.to_remove.nodes.push_back( open_curly_bracket );
                                                            plan.to_remove.nodes.push_back( close_curly_bracket );

                                                            std::vector< LexicalTokens::LexicalToken > lexical_tokens { 
                                                                                          open_curly_bracket->lexical_tokens().at(0),
                                                                                          close_curly_bracket->lexical_tokens().at(0)
                                                                                          };
                                                            const auto& object = std::make_shared< ObjectSyntaxNode >( std::vector<ObjectPairSyntaxNodeSP>{}, lexical_tokens );
                                                            const auto& varible_assigment_statment_syntax_node = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( name, object, equal->lexical_tokens().at(0), VaribleAssigmentStatmentSyntaxNode::Context::GLOBAL );
                                                            plan.to_add.nodes.push_back( varible_assigment_statment_syntax_node );
                                                            plan_or_progress = plan;
                                                        }
                                                        else
                                                        {
                                                            plan_or_progress = Progress{ .readiness = iteration_result.readiness };
                                                        }
                                                        return plan_or_progress;
                                                        });
     } );
  // VARIBLE_ASSIGMENT SEMICOLON
  mProductions.emplace_back(
     []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
     {
        const size_t minimal_size = 2;
        size_t minimal_steps_number = 2;
        return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_steps_number, &lookahead]( size_t n )->PlanOrProgress
                                                        
        {
          VaribleAssigmentStatmentSyntaxNodeSP varible_assigment;
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
          handlers.varible_assigment_statment_syntax_node = [ &varible_assigment ]( const State& state, const VaribleAssigmentStatmentSyntaxNodeSP& node ) -> HandlerReturn
          {
             if( state == State::START )
             {
                varible_assigment = node;
                return { State::VARIBLE_ASSIGMENT, Impact::MOVE };
             }
             return { state, Impact::ERROR };
          };
          handlers.semicolon_syntax_node = [ &semicolon ]( const State& state, const SemicolonSyntaxNodeSP& node ) -> HandlerReturn
          {
             if( state == State::VARIBLE_ASSIGMENT )
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
              plan.to_remove.nodes.push_back( varible_assigment );
              plan.to_remove.nodes.push_back( semicolon );

              plan.to_add.nodes.push_back( varible_assigment );
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
