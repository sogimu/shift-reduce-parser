#pragma once

#include "nlohmann_json/json.hpp"
#include "syntax_tree.h"

#include <cstddef>
#include <iterator>
#include <linux/limits.h>
#include <vector>
#include <variant>
#include <string>
#include <functional>

inline SyntaxTree CreateSyntaxNodeTree( const std::string& description )
{
   using json = nlohmann::json;
   const auto& description_as_json = json::parse( description );

   class DfsHandler
   {
   public:
      struct Item
      {
         struct NoKeyOrIndex
         {
         };
         using KeyOrIndex = std::variant< ptrdiff_t, std::string, NoKeyOrIndex >;
         const KeyOrIndex keyOrIndex;
         const json& value;
      };
      using SearchPath = std::vector< Item >;

      using Func = const std::function< void( const SearchPath& ) >&;
      void handle( const json& json, Func pre_func, Func post_func )
      {
         mSearchPath.emplace_back( Item{ Item::NoKeyOrIndex{}, json } );
         pre_func( mSearchPath );
         if( json.is_array() )
            handle_array( json, pre_func, post_func );
         else if( json.is_object() )
            handle_object( json, pre_func, post_func );
         post_func( mSearchPath );
         mSearchPath.pop_back();
      }

   private:
      void handle_array( const json& array, Func pre_func, Func post_func )
      {
         ptrdiff_t index = 0;
         for( const auto& element : array )
         {
            mSearchPath.emplace_back( Item{ index, element } );
            pre_func( mSearchPath );
            if( element.is_array() )
               handle_array( element, pre_func, post_func );
            else if( element.is_object() )
               handle_object( element, pre_func, post_func );
            post_func( mSearchPath );
            mSearchPath.pop_back();
            ++index;
         }
      };
      void handle_object( const json& object, Func pre_func, Func post_func )
      {
         for( const auto& [ key, element ] : object.items() )
         {
            mSearchPath.emplace_back( Item{ key, element } );
            pre_func( mSearchPath );
            if( element.is_array() )
               handle_array( element, pre_func, post_func );
            else if( element.is_object() )
               handle_object( element, pre_func, post_func );
            post_func( mSearchPath );
            mSearchPath.pop_back();
         }
      };

   private:
      SearchPath mSearchPath;
   };

   ISyntaxNodeSP root;

   std::vector< std::variant< json, ISyntaxNodeSP > > arguments;
   DfsHandler handler;
   handler.handle(
      description_as_json, [ /* &root */ ]( const DfsHandler::SearchPath& /* search_path */ ) {},
      [ &arguments ]( const DfsHandler::SearchPath& search_path )
      {
         std::visit(
            [ &arguments, &search_path ]( auto&& key )
            {
               using T = std::decay_t< decltype( key ) >;
               if constexpr( std::is_same_v< T, DfsHandler::Item::NoKeyOrIndex > )
               {
               }
               else if constexpr( std::is_same_v< T, ptrdiff_t > )
               {
                  const auto& value = search_path.back().value;
                  if( value.is_string() || value.is_number() )
                  {
                     arguments.emplace_back( value );
                  }
               }
               else if constexpr( std::is_same_v< T, std::string > )
               {
                  if( key == "NameSyntaxNode" )
                  {
                     std::string argument0 = std::get< json >( arguments.back() );
                     arguments.pop_back();
                     arguments.push_back( std::make_shared< NameSyntaxNode >( argument0 ) );
                  }
                  else if( key == "VaribleSyntaxNode" )
                  {
                     std::string argument0 = std::get< json >( arguments.back() );
                     arguments.pop_back();
                     arguments.push_back( std::make_shared< VaribleSyntaxNode >( argument0 ) );
                  }
                  else if( key == "FSyntaxNode" )
                  {
                     int argument0 = std::get< json >( arguments.back() );
                     arguments.pop_back();
                     arguments.push_back( std::make_shared< FSyntaxNode >( argument0 ) );
                  }
                  else if( key == "PrintStatmentSyntaxNode" )
                  {
                     ISyntaxNodeSP argument0 = std::get< ISyntaxNodeSP >( arguments.back() );
                     arguments.pop_back();
                     const auto& print_expression_syntax_node = std::make_shared< PrintStatmentSyntaxNode >();
                     print_expression_syntax_node->add_back( argument0 );
                     arguments.push_back( print_expression_syntax_node );
                  }
                  else if( key == "IfStatmentSyntaxNode" )
                  {
                     const auto& if_statment_syntax_node = std::make_shared< IfStatmentSyntaxNode >();
                     auto it = arguments.begin();
                     std::advance( it, arguments.size() - 2 );
                     if( !arguments.empty() )
                     {
                        ISyntaxNodeSP argument0 = std::get< ISyntaxNodeSP >( *it );
                        if_statment_syntax_node->add_back( argument0 );
                     }
                     if( !arguments.empty() )
                     {
                        ++it;
                        ISyntaxNodeSP argument1 = std::get< ISyntaxNodeSP >( *it );
                        if_statment_syntax_node->add_back( argument1 );
                     }
                     arguments.pop_back();
                     arguments.pop_back();
                     arguments.push_back( if_statment_syntax_node );
                  }
                  else if( key == "BinExprSyntaxNode" )
                  {
                     ISyntaxNodeSP argument0 = std::get< ISyntaxNodeSP >( arguments.back() );
                     arguments.pop_back();
                     ISyntaxNodeSP argument1 = std::get< ISyntaxNodeSP >( arguments.back() );
                     arguments.pop_back();
                     BinExprSyntaxNode::Type type = std::get< json >( arguments.back() );
                     arguments.pop_back();
                     const auto& bin_expr_syntax_node = std::make_shared< BinExprSyntaxNode >( type, argument0, argument1 );
                     arguments.push_back( bin_expr_syntax_node );
                  }
                  else if( key == "UnExprSyntaxNode" )
                  {
                     ISyntaxNodeSP argument0 = std::get< ISyntaxNodeSP >( arguments.back() );
                     arguments.pop_back();
                     UnExprSyntaxNode::Type type = std::get< json >( arguments.back() );
                     arguments.pop_back();
                     const auto& un_expr_syntax_node = std::make_shared< UnExprSyntaxNode >( type, argument0 );
                     arguments.push_back( un_expr_syntax_node );
                  }
                  // else if( key == "AdditionSyntaxNode" )
                  // {
                  //    ISyntaxNodeSP argument0 = std::get< ISyntaxNodeSP >( arguments.back() );
                  //    arguments.pop_back();
                  //    ISyntaxNodeSP argument1 = std::get< ISyntaxNodeSP >( arguments.back() );
                  //    arguments.pop_back();
                  //    const auto& addition_syntax_node = std::make_shared< AdditionSyntaxNode >();
                  //    addition_syntax_node->add_back( argument1 );
                  //    addition_syntax_node->add_back( argument0 );
                  //    arguments.push_back( addition_syntax_node );
                  // }
                  // else if( key == "SubtractionSyntaxNode" )
                  // {
                  //    ISyntaxNodeSP argument0 = std::get< ISyntaxNodeSP >( arguments.back() );
                  //    arguments.pop_back();
                  //    ISyntaxNodeSP argument1 = std::get< ISyntaxNodeSP >( arguments.back() );
                  //    arguments.pop_back();
                  //    const auto& addition_syntax_node = std::make_shared< SubtractionSyntaxNode >();
                  //    addition_syntax_node->add_back( argument1 );
                  //    addition_syntax_node->add_back( argument0 );
                  //    arguments.push_back( addition_syntax_node );
                  // }
                  // else if( key == "MultiplySyntaxNode" )
                  // {
                  //    ISyntaxNodeSP argument0 = std::get< ISyntaxNodeSP >( arguments.back() );
                  //    arguments.pop_back();
                  //    ISyntaxNodeSP argument1 = std::get< ISyntaxNodeSP >( arguments.back() );
                  //    arguments.pop_back();
                  //    const auto& multiple_syntax_node = std::make_shared< MultiplySyntaxNode >();
                  //    multiple_syntax_node->add_back( argument1 );
                  //    multiple_syntax_node->add_back( argument0 );
                  //    arguments.push_back( multiple_syntax_node );
                  // }
                  // else if( key == "DivisionSyntaxNode" )
                  // {
                  //    ISyntaxNodeSP argument0 = std::get< ISyntaxNodeSP >( arguments.back() );
                  //    arguments.pop_back();
                  //    ISyntaxNodeSP argument1 = std::get< ISyntaxNodeSP >( arguments.back() );
                  //    arguments.pop_back();
                  //    const auto& division_syntax_node = std::make_shared< DivisionSyntaxNode >();
                  //    division_syntax_node->add_back( argument1 );
                  //    division_syntax_node->add_back( argument0 );
                  //    arguments.push_back( division_syntax_node );
                  // }
                  else if( key == "VaribleAssigmentStatmentSyntaxNode" )
                  {
                     ISyntaxNodeSP argument0 = std::get< ISyntaxNodeSP >( arguments.back() );
                     arguments.pop_back();
                     ISyntaxNodeSP argument1 = std::get< ISyntaxNodeSP >( arguments.back() );
                     arguments.pop_back();
                     const auto& varible_assignment_syntax_node = std::make_shared< VaribleAssigmentStatmentSyntaxNode >();
                     varible_assignment_syntax_node->add_back( argument1 );
                     varible_assignment_syntax_node->add_back( argument0 );
                     arguments.push_back( varible_assignment_syntax_node );
                  }
                  else if( key == "ConditionalExpressionSyntaxNode" )
                  {
                     ISyntaxNodeSP argument0 = std::get< ISyntaxNodeSP >( arguments.back() );
                     arguments.pop_back();
                     ISyntaxNodeSP argument1 = std::get< ISyntaxNodeSP >( arguments.back() );
                     arguments.pop_back();
                     const auto& conditinal_expression_syntax_node = std::make_shared< ConditionalExpressionSyntaxNode >();
                     conditinal_expression_syntax_node->add_back( argument1 );
                     conditinal_expression_syntax_node->add_back( argument0 );
                     arguments.push_back( conditinal_expression_syntax_node );
                  }
                  else if( key == "ComputationalExpressionSyntaxNode" )
                  {
                     ISyntaxNodeSP argument0 = std::get< ISyntaxNodeSP >( arguments.back() );
                     arguments.pop_back();
                     const auto& e = std::make_shared< ComputationalExpressionSyntaxNode >();
                     e->add_back( argument0 );
                     arguments.push_back( e );
                  }
                  else if( key == "VaribleAssigmentStatmentSyntaxNode" )
                  {
                     ISyntaxNodeSP argument0 = std::get< ISyntaxNodeSP >( arguments.back() );
                     arguments.pop_back();
                     ISyntaxNodeSP argument1 = std::get< ISyntaxNodeSP >( arguments.back() );
                     arguments.pop_back();
                     const auto& e = std::make_shared< VaribleAssigmentStatmentSyntaxNode >();
                     e->add_back( argument1 );
                     e->add_back( argument0 );
                     arguments.push_back( e );
                  }
                  else if( key == "StatmentSyntaxNode" )
                  {
                     const auto& e = std::make_shared< StatmentSyntaxNode >();
                     if( !arguments.empty() )
                     {
                        ISyntaxNodeSP argument0 = std::get< ISyntaxNodeSP >( arguments.back() );
                        arguments.pop_back();
                        e->add_back( argument0 );
                     }
                     arguments.push_back( e );
                  }
                  else if( key == "ScopeSyntaxNode" )
                  {
                     const auto& scope_statment_syntax_node = std::make_shared< ScopeSyntaxNode >();
                     const auto& value = search_path.back().value;
                     if( arguments.size() >= value.size() )
                     {
                        for( size_t i = arguments.size() - value.size(); i < arguments.size(); ++i )
                        {
                           ISyntaxNodeSP argument = std::get< ISyntaxNodeSP >( arguments[ i ] );
                           scope_statment_syntax_node->add_back( argument );
                        }
                        for( size_t i = 0; i < value.size(); ++i )
                        {
                           arguments.pop_back();
                        }
                     }
                     arguments.push_back( scope_statment_syntax_node );
                  }
               }
            },
            search_path.back().keyOrIndex );
      } );

   root = std::get< ISyntaxNodeSP >( arguments.back() );

   return SyntaxTree{ root };
}
