#include "interpreter.h"
// #include "stack_machine.h"

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include <readline/readline.h>
#include <readline/history.h>
#include <cstdlib>   // getenv
#include <sys/stat.h> // mkdir
#include <cstring>   // strerror
#include <cerrno>    // errno
#include <unistd.h>  // access
#include <sstream>

bool ensureDirExists(const std::string& path) {
    struct stat st{};
    if (stat(path.c_str(), &st) != 0) {
        if (mkdir(path.c_str(), 0700) != 0) {
            std::cerr << "Dir creation error " << path << ": " << strerror(errno) << "\n";
            return false;
        }
    } else if (!S_ISDIR(st.st_mode)) {
        std::cerr << path << " exist but is not dir!\n";
        return false;
    }
    return true;
}

bool isInputComplete(const std::string& input) {
    int balance = 0;
    bool in_string = false;
    char string_char = '0';

    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];

        if (in_string) {
            if (c == string_char && input[i - 1] != '\\') {
                in_string = false;
            }
            continue;
        } else {
            if (c == '\'' || c == '"') {
                in_string = true;
                string_char = c;
                continue;
            }
        }

        if (c == '{') balance++;
        else if (c == '}') balance--;
    }

    return balance <= 0;
}

void PointToSyntaxError(const std::string& text, int line, int col)
{
  stringstream ss( text );
  std::string currentLine;
  int currentLineNumber = 0;
  bool markerPlaced = false;
 
  std::cout << "File \"<stdin>\", line " << std::to_string( line ) << std::endl;
  while( getline(ss, currentLine) )
  {
      // Проверяем, нужно ли поставить маркер
      if (currentLineNumber == line && !markerPlaced)
      {
          // Выводим текущую строку
          std::cout << currentLine << std::endl;
          // Проверяем, не выходит ли col за пределы строки
          if (col <= currentLine.size())
          {
              std::cout << string(col, ' ') << "^" << std::endl;
              std::cout << "SyntaxError: invalid syntax" << std::endl;
              markerPlaced = true;
          }
      }
      
      currentLineNumber++;
  }
  
  // Если маркер не был помещен и line существует
  if (!markerPlaced && line < currentLineNumber)
  {
      std::cout << string(col, ' ') << "^" << endl;
      std::cout << "SyntaxError: invalid syntax" << std::endl;
  }
}

int main()
{
   // // Fibonacci number in sequence
   // // 23's number shall be 17711
   // std::string e = R"(
   //  {
   //    a = 1+(2+3)+(4*5)/2;
   //
   //    if( 2 == 2 )
   //    {
   //      1+(2+3)+(4*5)/2;
   //      a = 232 + 2;  
   //    }
   //    function fibonacci(n)
   //    {
   //      a = 0;
   //      b = 1;
   //      i = 2;
   //      while( i < n )
   //      {
   //          // c = a + b;
   //          a = b;
   //          b = c;
   //          // i = i + 1;
   //      }
   //      return b;
   //    }
   //    // number = fibonacci(23);
   //    print(number);
   //    print(number==17711);
   //
   //    // r_fibonacci(n)
   //    // {
   //    //   // print(n*10);
   //    //   // print( n );
   //    //   if( n == 0 )
   //    //   {
   //    //     // print( 0 );
   //    //     return 0;
   //    //   }
   //    //   if( n == 1 )
   //    //   {
   //    //     // print( 1 );
   //    //     return 1;
   //    //   }
   //    //   a = r_fibonacci(n-2);
   //    //   print(a);
   //    //   b = r_fibonacci(n-1);
   //    //   print(b);
   //    //   // print( a + b);
   //    //   return a + b;
   //    // }
   //    // number = r_fibonacci(3);
   //    print(number);
   //    print(number==17711);
   //    // print( r_fibonacci(0) );
   //    // print( r_fibonacci(1) );
   //    // print( r_fibonacci(2) );
   //   // r_fibonacci(3);
   //    // print( r_fibonacci(3) );
   //  })";
   // //
   // //        if(3 < 2)
   // //        {
   // //            print(123);
   // //
   // //            3+5;
   // //        }
   // //        print(456);
   // //
   // //        2 < 3;
   // //        2 > 3;
   // //        -1+3;
   // //        {
   // //            2+2;
   // //        }
   // //    std::string e = "((-1+2)-3)";
   // //    std::string e = "{a=5+5;b=10+17;}";
   //
   // //    int n = 5;
   // //    for (int i=1; i<n; ++i)
   // //    {
   // //        if( i % 2 == 0 )
   // //        {
   // //            e += std::to_string(i)+"+";
   // //        }
   // //        else
   // //        {
   // //            e += std::to_string(i)+"*";
   // //        }
   // //    }
   // //    e += std::to_string(n);
   // std::cout << e << std::endl;
   //
   // Calculator calculator;
   // auto result0 = calculator.solve( e );
   // cout << result0 << std::endl;
   // return 0;

    std::cout << "JavaScript AST REPL. Enter JavaScript code:\n";
    std::cout << "For exit and save history of commands type Ctrl+D.\n";

    const char* home = getenv("HOME");
    if (!home) {
        std::cerr << "Env HOME does not exist\n";
        return 1;
    }

    std::string config_dir = std::string(home) + "/.config/my_programm";
    std::string history_file = config_dir + "/history";

    if (!ensureDirExists(config_dir)) {
        return 1;
    }

    if (access(history_file.c_str(), F_OK) == 0) {
        read_history(history_file.c_str());
    }
    std::string buffer;
    while (true)
    {
        const char* prompt = buffer.empty() ? ">>> " : "... ";
        char* line_cstr = readline(prompt);
        if (!line_cstr) {  // EOF (Ctrl+D)
            std::cout << "\nREPL exit.\n";
            break;
        }

        std::string line(line_cstr);
        free(line_cstr);

        // If enter on empty line - user is finsih input
        if (line.empty())
        {
            if (!buffer.empty())
            {
               add_history(buffer.c_str());
               try 
               {
                 Interpreter naive_stack_machine;
                 auto result0 = naive_stack_machine.eval( buffer.c_str() );
                 std::cout << result0 << std::endl;
               } 
               catch (const SyntaxException& e) 
               {
                  const auto& stack = e.stack();
                  const auto& last_node = *stack.rbegin();
                  const auto last_token = last_node->lexical_tokens().at(0);
                  PointToSyntaxError( buffer, last_token.line, last_token.col ); 
               }

                buffer.clear();
            }
            continue;
        }

        if (!buffer.empty()) buffer += "\n";
        buffer += line;
    }

    if (write_history(history_file.c_str()) != 0)
    {
        std::cerr << "Could not save hostory to file " << history_file << "\n";
    }
    return 0;
}
