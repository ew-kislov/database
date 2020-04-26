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

.PHONY: all test