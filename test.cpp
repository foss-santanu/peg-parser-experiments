#include "peglib.h"

#include <string>
#include <fstream>
#include <streambuf>

#include <chrono>
#include <iostream>

using namespace std;

// run as ./test grammar input

int main(int argc, char** argv)
{ 

    std::ifstream t1(argv[1]);
    std::string grammar((std::istreambuf_iterator<char>(t1)),
                     std::istreambuf_iterator<char>());


    auto start_parser_construct = chrono::system_clock::now();


    peg::parser p(grammar);

    auto end_parser_construct = chrono::system_clock::now();

    auto construct_ms
            = chrono::duration_cast<chrono::milliseconds>(
                  end_parser_construct - start_parser_construct)
                  .count();

    // Print the result
    printf("construct %lld\n", construct_ms);


//rules["name"] = "..."

  if(!(bool)p) {
    printf("parser construction error\n");
    return -1;
  }

   p.set_logger([](size_t line, size_t col, const string& msg) {
         printf("Error on line %zu:%zu -> %s\n", line, col, msg.c_str());
   });



    std::ifstream t2(argv[2]);
    std::string input((std::istreambuf_iterator<char>(t2)),
                     std::istreambuf_iterator<char>());

    auto start_parser_execute = chrono::system_clock::now();

auto n = 100;
auto ok = 0;
for (size_t i = 0; i < n; i++) {
    vector<double> result;
   ok += p.parse(input, result);
}
  auto end_parser_execute = chrono::system_clock::now();

  auto parse_ms
          = chrono::duration_cast<chrono::milliseconds>(
                end_parser_execute - start_parser_execute)
                .count() / n;

  // Print the result
  printf("parse %lld\n", parse_ms);
}