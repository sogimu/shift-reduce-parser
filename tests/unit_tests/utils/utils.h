#pragma once

#include "enums.h"
#include "lexical_tokens.h"
#include "nlohmann_json/json.hpp"
#include "syntax_tree.h"
#include "utils.h"

#include <vector>

inline SyntaxTree CreateSyntaxNodeTree( const std::string& description )
{
    using json = nlohmann::json;
    const auto& description_as_json = json::parse( description );

    // using Handler = std::function<void(const json&)>;

    class DfsHandler
    {
            public:
        struct Item
        {
            struct NoKeyOrIndex
            {
            };
            using KeyOrIndex = std::variant<ptrdiff_t, std::string, NoKeyOrIndex>;
            const KeyOrIndex keyOrIndex;
            const json& value;
        };
        using SearchPath = std::vector<Item>;

        using Func = const std::function<void( const SearchPath& )>&;
        void handle( const json& json, Func pre_func, Func post_func )
        {
            mSearchPath.emplace_back( Item::NoKeyOrIndex{}, json );
            pre_func( mSearchPath );
            if ( json.is_array() )
                handle_array( json, pre_func, post_func );
            else if ( json.is_object() )
                handle_object( json, pre_func, post_func );
            post_func( mSearchPath );
            mSearchPath.pop_back();
        }

            private:
        void handle_array( const json& array, Func pre_func, Func post_func )
        {
            ptrdiff_t index = 0;
            for ( const auto& element : array )
            {
                mSearchPath.emplace_back( index, element );
                pre_func( mSearchPath );
                if ( element.is_array() )
                    handle_array( element, pre_func, post_func );
                else if ( element.is_object() )
                    handle_object( element, pre_func, post_func );
                post_func( mSearchPath );
                mSearchPath.pop_back();
                ++index;
            }
        };
        void handle_object( const json& object, Func pre_func, Func post_func )
        {
            for ( const auto& [key, element] : object.items() )
            {
                mSearchPath.emplace_back( key, element );
                pre_func( mSearchPath );
                if ( element.is_array() )
                    handle_array( element, pre_func, post_func );
                else if ( element.is_object() )
                    handle_object( element, pre_func, post_func );
                post_func( mSearchPath );
                mSearchPath.pop_back();
            }
        };

            private:
        SearchPath mSearchPath;
    };

    ISyntaxNodeSP root;

    std::vector<std::variant<json, ISyntaxNodeSP>> arguments;
    DfsHandler handler;
    handler.handle(
        description_as_json,
        [&root]( const DfsHandler::SearchPath& search_path ) {},
        [&arguments]( const DfsHandler::SearchPath& search_path ) {
            std::visit(
                [&arguments, &search_path]( auto&& arg ) {
                    using T = std::decay_t<decltype( arg )>;
                    if constexpr ( std::is_same_v<T, DfsHandler::Item::NoKeyOrIndex> )
                    {
                    }
                    else if constexpr ( std::is_same_v<T, ptrdiff_t> )
                    {
                        const auto& value = search_path.back().value;
                        if ( value.is_string() || value.is_number() )
                        {
                            arguments.emplace_back( value );
                        }
                    }
                    else if constexpr ( std::is_same_v<T, std::string> )
                    {
                        if ( arg == "NameSyntaxNode" )
                        {
                            std::string argument0 = std::get<json>( arguments.back() );
                            arguments.pop_back();
                            arguments.push_back( std::make_shared<NameSyntaxNode>( argument0 ) );
                        }
                        else if ( arg == "FSyntaxNode" )
                        {
                            size_t s = arguments.size();
                            auto aa = arguments;
                            int argument0 = std::get<json>( arguments.back() );
                            arguments.pop_back();
                            arguments.push_back( std::make_shared<FSyntaxNode>( argument0 ) );
                        }
                        else if ( arg == "ComputationalExpressionSyntaxNode" )
                        {

                            size_t s = arguments.size();
                            auto aa = arguments;
                            ISyntaxNodeSP argument0 = std::get<ISyntaxNodeSP>( arguments.back() );
                            arguments.pop_back();
                            const auto& e = std::make_shared<ComputationalExpressionSyntaxNode>();
                            e->Add( argument0 );
                            arguments.push_back( e );
                        }
                        else if ( arg == "VaribleAssigmentSyntaxNode" )
                        {
                            size_t s = arguments.size();
                            auto aa = arguments;
                            ISyntaxNodeSP argument0 = std::get<ISyntaxNodeSP>( arguments.back() );
                            arguments.pop_back();
                            ISyntaxNodeSP argument1 = std::get<ISyntaxNodeSP>( arguments.back() );
                            arguments.pop_back();
                            const auto& e = std::make_shared<VaribleAssigmentSyntaxNode>();
                            e->Add( argument0 );
                            e->Add( argument1 );
                            arguments.push_back( e );
                        }
                        else if ( arg == "ExpressionSyntaxNode" )
                        {
                            size_t s = arguments.size();
                            auto aa = arguments;
                            ISyntaxNodeSP argument0 = std::get<ISyntaxNodeSP>( arguments.back() );
                            arguments.pop_back();
                            const auto& e = std::make_shared<ExpressionSyntaxNode>();
                            e->Add( argument0 );
                            arguments.push_back( e );
                        }
                        else if ( arg == "ScopeSyntaxNode" )
                        {
                            ISyntaxNodeSP argument0 = std::get<ISyntaxNodeSP>( arguments.back() );
                            arguments.pop_back();
                            const auto& e = std::make_shared<ScopeSyntaxNode>();
                            e->Add( argument0 );
                            arguments.push_back( e );
                        }
                    }
                },
                search_path.back().keyOrIndex );
        } );

    root = std::get<ISyntaxNodeSP>( arguments.back() );

    return SyntaxTree{ root };
}
