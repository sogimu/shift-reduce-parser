#include "stack_machine.h"

#include "is_last_nodes.h"
#include "nonterminals/bin_expr_syntax_node.h"
#include "nonterminals/function_statment_syntax_node.h"
#include "nonterminals/if_statment_syntax_node.h"
#include "nonterminals/statment_syntax_node.h"
#include "nonterminals/function_call_syntax_node.h"
#include "nonterminals/return_statment_syntax_node.h"
#include "nonterminals/scope_statment_syntax_node.h"
#include "nonterminals/varible_assigment_statment_syntax_node.h"
#include "nonterminals/varible_syntax_node.h"
#include "nonterminals/while_statment_syntax_node.h"
#include "nonterminals/member_expression_syntax_node.h"
#include "stack_machine.h"
#include "terminals/f_syntax_node.h"
#include "terminals/if_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "syntax_node_empty_visitor.h"
#include "lexical_tokens.h"
#include "abstract_syntax_tree.h"
#include "control_flow_graph.h"
#include "utils.h"
#include "varible_store.h"
#include "function_store.h"
#include "i_syntax_node.h"

#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <variant>

template<typename A>
class CopyOrRef {
public:
    enum class Type
    {
        COPY,
        REFERENCE
    };
    // Конструктор от копии
    CopyOrRef(const A& a) : data(A(a)), mType{ Type::COPY } {}

    // Конструктор от ссылки (явное)
    CopyOrRef(A& a) : data(&a), mType{ Type::REFERENCE } {}

    // Получить доступ к объекту
    A& get() {
        if (std::holds_alternative<A>(data))
            return std::get<A>(data);
        else
            return *std::get<A*>(data);
    }

    const A& get() const {
        if (std::holds_alternative<A>(data))
            return std::get<A>(data);
        else
            return *std::get<A*>(data);
    }

    // Оператор неявного приведения к типу A&
    operator A&() {
        return get();
    }

    operator const A&() const {
        return get();
    }

    Type type() const
    {
        return mType;
    }
private:
    // Вариант с хранением либо копии, либо ссылки через указатель
    std::variant<A, A*> data;
    Type mType;
};

struct FunctionCallMeta
{
   ISyntaxNodeSP function;
   std::vector< ISyntaxNodeSP > arguments;
};

StackMachine::StackMachine( const ControlFlowGraph& cfg )
    : mCfg{ cfg }
{
}

Json StackMachine::exec()
{
   VaribleStore varible_store;
   varible_store.pushScope();

   FunctionStore function_store;
   std::deque< CopyOrRef<Json> > argument_stack;
   std::deque< FunctionCallSyntaxNodeSP > function_call_stack;
    
   std::function<Json(const ISyntaxNodeSP&)> get_value;
   get_value = [&argument_stack, &varible_store, &get_value](const ISyntaxNodeSP& value_syntax_node ) -> Json
    {   auto& s = argument_stack;
        (void) s;
        if( check_type<MemberExpressionSyntaxNode>( value_syntax_node ) )
        {
            auto key_or_index = get_value( value_syntax_node->operator[](1) );
            // if( !argument_stack.empty() )
               // argument_stack.pop_back();
            auto container = get_value( value_syntax_node->operator[](0) ); 
            // if( !argument_stack.empty() )
               // argument_stack.pop_back();
            // varible.get() = value;
             // auto& container = varible_store[ varible_name.get_string() ];
             if( container.is_array() )
             {
                if( key_or_index.is_int() )
                {
                   return container.get_array()[key_or_index.get_int()];
                }
                else
                {
                    throw std::runtime_error("Element of array can not be accesed not by index!");
                }
             }
             else if( container.is_object() )
             {
                if( key_or_index.is_string() )
                {
                   return container.get_object()[key_or_index.get_string()];
                }
                else
                {
                    throw std::runtime_error("Element of object can not be accesed not by key!");
                }
             }
        }
        else
        {
            auto value = argument_stack.back();
            if( !argument_stack.empty() )
               argument_stack.pop_back();
            return value.get();
        }
       return {};
    };

   std::vector< ISyntaxNodeSP > stack;
   iterative_managed_dfs(
      mCfg.root(),
      [ &varible_store, &function_store, &function_call_stack, &argument_stack, &stack, &get_value ]( const ISyntaxNodeSP& node, StackDFS< ISyntaxNodeSP >& stack_dfs )
      {
          stack.emplace_back( node );
         auto children = node->Children();
         SyntaxNodeEmptyVisitor::Handlers handlers;
         handlers.scope_statment_syntax_node =
            [ &varible_store, &function_store ]( const ScopeSyntaxNodeSP& /* scope */ )

         {
            // create scope in a VaribleStore
            varible_store.pushScope();
            function_store.pushScope();
            // std::cout << "Scope begin" << std::endl;
         },
         handlers.if_statment_syntax_node = [ &children, &argument_stack, &get_value ]( const IfStatmentSyntaxNodeSP& if_statment )
         {
            // CopyOrRef<Json> condition_result;
            if( !argument_stack.empty() )
            {
                auto& s = argument_stack;
                (void) s;
                const auto& condition = get_value( if_statment->conditional_expression() );
                if( !condition.is_null() )
                {
                   if( ( condition.is_double() && condition.get_double() > 0.0 ) || 
                       ( condition.is_int()    && condition.get_int() > 0 )      || 
                       ( condition.is_bool()   && condition.get_bool() == true ) )
                   {
                       const auto& true_scope = if_statment->true_scope();
                       children = std::list< ISyntaxNodeSP >{ true_scope };
                       return;
                   }    
                   children = {};
                }
                // argument_stack.pop_back();
            }
            else
            {
               children = {};
            }
         };
         handlers.function_statment_syntax_node = [ &function_store, &children ]( const FunctionStatmentSyntaxNodeSP& function )
         {
            const auto& function_name = function->name();
            const auto& arguments_number = function->Children().size() - 2;
            function_store.insert( { function_name, arguments_number }, function );
            children = {};
         };
         handlers.function_call_syntax_node = [ &function_call_stack ]( const FunctionCallSyntaxNodeSP& function_call )
         { 
             function_call_stack.emplace_back( function_call );
         };
         // handlers.varible_assigment_statment_syntax_node = [ &children ]( const VaribleAssigmentStatmentSyntaxNodeSP& varible_assigment )
         // {
         //    const auto& source = varible_assigment->source();
         //    children = {source};
         // };
         handlers.return_statment_syntax_node = [ &stack_dfs, &function_call_stack, &argument_stack ]( const ReturnStatmentSyntaxNodeSP& /* return_statment */ )
         {
             if( !stack_dfs.empty() )
             {
               auto& d = function_call_stack ;
               (void) d;
                stack_dfs.popUntil( !function_call_stack.empty() ? function_call_stack.back() : nullptr );
             }
             // if( !argument_stack.empty() )
             // {
             //    auto result = argument_stack.back();
             //    // argument_stack.pop_back();
             //
             //    std::cout << "return: " << std::to_string( result ) << std::endl;
             // }
         };
         const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
         node->accept( visitor );
         
         if( IsLastNodesIs<FunctionCallSyntaxNode, ScopeSyntaxNode>( stack ) )
         {
             auto& s = stack;
             (void) s;
             auto scope_it = stack.rbegin();
             auto function_call_it = std::next(scope_it);
             const auto& function_call = std::dynamic_pointer_cast< FunctionCallSyntaxNode >( *function_call_it );
             const auto& function_statment = function_store[ function_call->signature() ];
             children.push_back( function_statment->scope() ); 
         }
         
         stack_dfs.push( children );
         return children;
      },
      [ &varible_store, &function_store, &argument_stack, &function_call_stack, &stack, &get_value ]( const ISyntaxNodeSP& node )
      {
         SyntaxNodeEmptyVisitor::Handlers handlers;
         handlers.string_syntax_node = [ &argument_stack ]( const StringSyntaxNodeSP& node )
         {
             auto& s = argument_stack;
             (void) s;
             argument_stack.push_back( CopyOrRef<Json>{ node->value() } );
            // std::cout << "f = " << node->value() << std::endl;
         };
         handlers.int_syntax_node = [ &argument_stack ]( const IntSyntaxNodeSP& node )
         {
             auto& s = argument_stack;
             (void) s;
             argument_stack.push_back( CopyOrRef<Json>{ node->value() } );
            // std::cout << "f = " << node->value() << std::endl;
         };
         handlers.double_syntax_node = [ &argument_stack ]( const DoubleSyntaxNodeSP& node )
         {
             auto& s = argument_stack;
             (void) s;
             argument_stack.push_back( CopyOrRef<Json>{ node->value() } );
            // std::cout << "f = " << node->value() << std::endl;
         };
         handlers.name_syntax_node = [ &argument_stack, &varible_store ]( const NameSyntaxNodeSP& name )
         {
            argument_stack.push_back( CopyOrRef<Json>( name->value() ) );
         };
         handlers.varible_syntax_node = [ &argument_stack, &varible_store ]( const VaribleSyntaxNodeSP& varible )
         {
            auto& varible_value_ref = varible_store[ varible->name() ];
            argument_stack.push_back( CopyOrRef<Json>( varible_value_ref ) );
         };
         handlers.array_syntax_node = [ &argument_stack, &get_value ]( const ArraySyntaxNodeSP& node )
         {
            auto& s = argument_stack;
            (void) s;
            // std::cout << "f = " << node->value() << std::endl;
            std::vector<Json> arrays_elements;
            for( auto it=node->rbegin(); it!= node->rend(); ++it )
            {
               const auto& child = *it;
               auto value = argument_stack.back();
               if( !argument_stack.empty() )
                  argument_stack.pop_back();
               // const auto& value = get_value( child );
               arrays_elements.insert( arrays_elements.begin(), value );
            }
            argument_stack.push_back( CopyOrRef<Json>{ arrays_elements } );
         };
         handlers.object_syntax_node = [ &argument_stack, &get_value ]( const ObjectSyntaxNodeSP& node )
         {
             auto& s = argument_stack;
             (void) s;
            // std::cout << "f = " << node->value() << std::endl;
            std::map<std::string, Json> object_elements;
            for( auto it=node->rbegin(); it!= node->rend(); ++it )
            {
               const auto& child = *it;
               auto value = argument_stack.back();
               if( !argument_stack.empty() )
                  argument_stack.pop_back();
               // const auto& value = get_value( child->operator[](1) );
               auto key = argument_stack.back();
               if( !argument_stack.empty() )
                  argument_stack.pop_back();
               // const auto& key = get_value( child->operator[](0) );
               object_elements.emplace( key.get().get_string(), value );
            }
            argument_stack.push_back( CopyOrRef<Json>{ object_elements } );
         };
         handlers.bin_expr_syntax_node = [ &argument_stack, &get_value ]( const BinExprSyntaxNodeSP& node )
         {
             auto& s = argument_stack;
             (void) s;
             // std::cout << "<<<STACK>>>>";
             // for (const auto& j : argument_stack )
             // {
             //     std::cout << j << ", ";
             // }
             // std::cout << "<<<STACK>>>>" << std::endl;
            // auto rhs = argument_stack.back().get();
            // if( !argument_stack.empty() )
            //    argument_stack.pop_back();
            // auto lhs = argument_stack.back().get();
            // if( !argument_stack.empty() )
            //    argument_stack.pop_back();
            // const auto& rhs = get_value( node->operator[](1) );
             auto rhs = argument_stack.back();
             if( !argument_stack.empty() )
                argument_stack.pop_back();
            // const auto& lhs = get_value( node->operator[](0) );
             auto lhs = argument_stack.back();
             if( !argument_stack.empty() )
                argument_stack.pop_back();
            if( node->type() == BinExprSyntaxNode::Type::Addition )
            {
              const auto& result = lhs + rhs;
              // std::cout << std::to_string( lhs ) << " + " << std::to_string( rhs ) << " = " << std::to_string( result ) << std::endl;
              argument_stack.push_back( result );
            }
            else if( node->type() == BinExprSyntaxNode::Type::Substruction )
            {
              const auto& result = lhs - rhs;
              // std::cout << std::to_string( lhs ) << " - " << std::to_string( rhs ) << " = " << std::to_string( result ) << std::endl;
              argument_stack.push_back( result );
            }
            else if( node->type() == BinExprSyntaxNode::Type::Multiply )
            {
              const auto& result = lhs * rhs;
              // std::cout << std::to_string( lhs ) << " * " << std::to_string( rhs ) << " = " << std::to_string( result ) << std::endl;
              argument_stack.push_back( result );
            }
            else if( node->type() == BinExprSyntaxNode::Type::Division )
            {
              const auto& result = lhs / rhs;
              // std::cout << std::to_string( lhs ) << " / " << std::to_string( rhs ) << " = " << std::to_string( result ) << std::endl;
              argument_stack.push_back( result );
            }
            else if( node->type() == BinExprSyntaxNode::Type::Equal )
            {
              const auto& result = lhs.get() == rhs.get();
              // std::cout << std::to_string( lhs ) << " == " << std::to_string( rhs ) << " = " << std::to_string( result ) << std::endl;
              argument_stack.push_back( CopyOrRef<Json>{ result } );
            }
            else if( node->type() == BinExprSyntaxNode::Type::Less )
            {
              const auto& result = lhs < rhs;
              // std::cout << std::to_string( lhs ) << " < " << std::to_string( rhs ) << " = " << std::to_string( result ) << std::endl;
              argument_stack.push_back( CopyOrRef<Json>{ result } );
            }
            else if( node->type() == BinExprSyntaxNode::Type::LessEqual )
            {
              const auto& result = lhs <= rhs;
              // std::cout << std::to_string( lhs ) << " <= " << std::to_string( rhs ) << " = " << std::to_string( result ) << std::endl;
              argument_stack.push_back( CopyOrRef<Json>{ result } );
            }
            else if( node->type() == BinExprSyntaxNode::Type::More )
            {
              const auto& result = lhs > rhs;
              // std::cout << std::to_string( lhs ) << " > " << std::to_string( rhs ) << " = " << std::to_string( result ) << std::endl;
              argument_stack.push_back( CopyOrRef<Json>{ result } );
            }
            else if( node->type() == BinExprSyntaxNode::Type::MoreEqual )
            {
              const auto& result = lhs >= rhs;
              // std::cout << std::to_string( lhs ) << " >= " << std::to_string( rhs ) << " = " << std::to_string( result ) << std::endl;
              argument_stack.push_back( CopyOrRef<Json>{ result } );
            }
         };
         handlers.scope_statment_syntax_node = [ &varible_store, &function_store ]( const ScopeSyntaxNodeSP& /*  scope */ )
         {
            // delete scope in a VaribleStore
            varible_store.popScope();
            function_store.popScope();
            // argument_stack.clear();
            // std::cout << "Scope end" << std::endl;
         };
         handlers.return_statment_syntax_node = [ &function_call_stack, &argument_stack, &varible_store, &get_value ]( const ReturnStatmentSyntaxNodeSP& return_statment )
         {
             auto& s = argument_stack;
             (void) s;
             // const auto& value = get_value( return_statment->operator[](0) );
             auto value = argument_stack.back();
             if( !argument_stack.empty() )
                argument_stack.pop_back();
             const auto& v = value.get();
             argument_stack.push_back( v );
         };
         handlers.print_statment_syntax_node = [ &argument_stack, &varible_store, &get_value ]( const PrintStatmentSyntaxNodeSP& print_statment )
         {
             auto value = argument_stack.back();
             if( !argument_stack.empty() )
                argument_stack.pop_back();
             // return varible_name.get().get_int();
             // const auto& value = get_value( print_statment->operator[](0) );
             std::cout << "print: " << value.get() << std::endl;
         };
         handlers.member_expression_syntax_node = [ &argument_stack, &varible_store, &get_value ]( const MemberExpressionSyntaxNodeSP& member_expression )
         {
             auto& s = argument_stack;
             (void) s;
             const auto& value = get_value( member_expression );
             argument_stack.push_back( CopyOrRef<Json>{ value } );
             std::cout << "member_expression value: " << value << std::endl;
         };
         handlers.varible_assigment_statment_syntax_node = [ &varible_store, &argument_stack, &get_value ]( const VaribleAssigmentStatmentSyntaxNodeSP& varible_assigment )
         {
            // const auto& source = varible_assigment->source();
            auto& s = argument_stack;
            (void) s;
            
            if( check_type<NameSyntaxNode>( varible_assigment->operator[]( 0 ) ) )
            {
                // const auto& varible_value = get_value( varible_assigment->operator[](1) );
                auto varible_value = argument_stack.back();
                if( !argument_stack.empty() )
                   argument_stack.pop_back();
                auto varible_name = argument_stack.back();
                if( !argument_stack.empty() )
                   argument_stack.pop_back();
                // varible.get() = value;
                std::string context;
                if( varible_assigment->context() == VaribleAssigmentStatmentSyntaxNode::Context::GLOBAL )
                {
                   varible_store[ varible_name.get().get_string() ] = varible_value;
                   context = "Global";
                }
                else if( varible_assigment->context() == VaribleAssigmentStatmentSyntaxNode::Context::LOCAL )
                {
                   varible_store.writeValueToLocalVarible( varible_name.get().get_string(), varible_value );
                   context = "Local";
                }
                // std::cout << "Write " << target_name << " .Value is " << value << ". Context: " << context << std::endl;
            }
            else if( check_type<MemberExpressionSyntaxNode>( varible_assigment->operator[]( 0 ) ) )
            {
                const auto& member_value = get_value( varible_assigment->operator[](1) );
                auto key_or_index = argument_stack.back();
                if( !argument_stack.empty() )
                   argument_stack.pop_back();
                auto varible_name = argument_stack.back();
                if( !argument_stack.empty() )
                   argument_stack.pop_back();
                if( varible_assigment->context() == VaribleAssigmentStatmentSyntaxNode::Context::GLOBAL )
                {
                   auto& container = varible_store[ varible_name.get().get_string() ];
                   if( container.is_array() )
                   {
                      if( key_or_index.get().is_int() )
                      {
                         container.get_array()[key_or_index.get().get_int()] = member_value;
                      }
                      else
                      {
                          throw std::runtime_error("Element of array can not be accesed not by index!");
                      }
                   }
                   else if( container.is_object() )
                   {
                      if( key_or_index.get().is_string() )
                      {
                         container.get_object()[key_or_index.get().get_string()] = member_value;
                      }
                      else
                      {
                          throw std::runtime_error("Element of object can not be accesed not by key!");
                      }
                   }
                }
            }
            varible_store.print();
         };
         handlers.function_call_syntax_node = [ &function_call_stack ]( const FunctionCallSyntaxNodeSP& function_call )
         { 
             function_call_stack.pop_back();
         };
         const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
         node->accept( visitor );

       
         stack.pop_back();
} );
    
    Json result;
    if( !argument_stack.empty() )
    {
        result = argument_stack.back().get();
        argument_stack.pop_back();
    }
    return result;
}
