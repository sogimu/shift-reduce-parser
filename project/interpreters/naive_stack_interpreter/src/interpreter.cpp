#include "interpreter.h"

#include "stack_machine.h"
#include "lexical_tokens.h"
#include "abstract_syntax_tree.h"
#include "control_flow_graph.h"
#include <iostream>
#include <string>

double Interpreter::eval( const std::string& expression ) const
{
    std::cout << "== Lexemes ==" << std::endl;
    LexicalTokens lexical_tokens( expression );
    std::cout << lexical_tokens << std::endl;

    std::cout << "== AST ==" << std::endl;
    AbstractSyntaxTree ast( lexical_tokens );
    std::cout << ast << std::endl;

    std::cout << "== CFG ==" << std::endl;
    ControlFlowGraph cfg{ ast };
    std::cout << cfg << std::endl;

    std::cout << "== Executioning ==" << std::endl;
    StackMachine stack_machine{ cfg };
    double result = 0;
    result = stack_machine.exec();

    return result;
}
