all: create_directory main test
create_directory:
	mkdir -p out
	mkdir -p out/main
	mkdir -p out/test
main:
	g++ src/client.cpp -w -o out/main/client.out
	g++ src/server.cpp -w -o out/main/server.out
test:
	g++ test/query_parser/CreateQuery.test.cpp -w -o out/test/create.test.out
	g++ test/query_parser/DeleteQuery.test.cpp -w -o out/test/delete.test.out
	g++ test/query_parser/UpdateQuery.test.cpp -w -o out/test/update.test.out
	g++ test/query_parser/SelectQuery.test.cpp -w -o out/test/select.test.out
	g++ test/query_parser/DropQuery.test.cpp -w -o out/test/drop.test.out
	g++ test/query_parser/InsertQuery.test.cpp -w -o out/test/insert.test.out
	g++ test/query_parser/LexicParser.test.cpp -w -o out/test/lexic.test.out
	g++ test/query_processor/conditionTree.test.cpp -w -o out/test/tree.test.out

.PHONY: all test