#include "peglib.h"

#include <string>
#include <fstream>
#include <streambuf>

#include <chrono>
#include <iostream>

using namespace std;

// run as ./test grammar input

std::string FileToString(std::string file_name) {
    std::ifstream str(file_name);
    std::string txt((std::istreambuf_iterator<char>(str)),
                     std::istreambuf_iterator<char>());
    return txt;
}

int main(int argc, char** argv)
{    auto base_grammar = FileToString(argv[1]);

    auto start_parser_construct = chrono::system_clock::now();
    peg::parser p(base_grammar);
    p.enable_packrat_parsing();
    //p.enable_ast();
    auto end_parser_construct = chrono::system_clock::now();

    auto construct_ms
            = chrono::duration_cast<chrono::nanoseconds>(
                  end_parser_construct - start_parser_construct)
                  .count();

    if(!(bool)p) {
        printf("parser construction error\n");
        return -1;
    }
    printf("PEG load base grammar %lld\n", construct_ms);
   //  // enable error logging just in case
   // p.set_logger([](size_t line, size_t col, const string& msg) {
   //       printf("Error on line %zu:%zu -> %s\n", line, col, msg.c_str());
   // });

    auto input = FileToString(argv[2]);

    auto start_parser_execute = chrono::system_clock::now();

auto n = atoi(argv[3]);
for (size_t i = 0; i < n; i++) {
   p.parse(input);
}
  auto end_parser_execute = chrono::system_clock::now();

  auto parse_ms
          = chrono::duration_cast<chrono::nanoseconds>(
                end_parser_execute - start_parser_execute)
                .count() / n;

  // Print the result
  printf("PEG parsing time %lld\n", parse_ms);


}