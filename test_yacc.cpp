#include "peglib.h"

#include <string>
#include <fstream>
#include <streambuf>

#include <chrono>
#include <iostream>

#include "postgres_parser.hpp"

using namespace std;

// run as ./test grammar input

std::string FileToString(std::string file_name) {
    std::ifstream str(file_name);
    std::string txt((std::istreambuf_iterator<char>(str)),
                     std::istreambuf_iterator<char>());
    return txt;
}

int main(int argc, char** argv)
{
    auto input = FileToString(argv[1]);
    auto n = atoi(argv[2]);

    duckdb::PostgresParser pg;

    auto start_pg_parser_execute = chrono::system_clock::now();

    for (size_t i = 0; i < n; i++) {
        vector<double> result;
        pg.Parse(input);
    }

    auto end_pg_parser_execute = chrono::system_clock::now();

    auto parse_pg_ms
          = chrono::duration_cast<chrono::nanoseconds>(
                end_pg_parser_execute - start_pg_parser_execute)
                .count() / n;

    // Print the result
    printf("Postgres parsing time %lld\n", parse_pg_ms);
   }