all: build

# run `make` there before
DUCKDB_PREFIX=/Users/hannes/source/duckdb/


build: test_yacc.cpp test_peg.cpp peglib.h #${DUCKDB_PREFIX}/libpg_query/build/libduckdb_pg_query.a
	g++ test_peg.cpp -I. -std=c++17 -o test_peg -O3 -Wall
	g++ -I${DUCKDB_PREFIX}third_party/libpg_query/include/ -I${DUCKDB_PREFIX}src/include/  test_yacc.cpp ${DUCKDB_PREFIX}build/release/third_party/libpg_query/libduckdb_pg_query.a -I. -std=c++17 -o test_yacc -O3 -Wall

test: build
	./test_peg sql.gram all.sql 10
	./test_yacc all.sql 10

clean:
	rm -rf test_peg test_yacc