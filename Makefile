FLAGS="-std=c++11"
study_case:
	g++ $(FLAGS) case_study.cpp
	./a.out || true
	rm a.out
test_bench:
	g++ $(FLAGS) test.cpp
	./a.out || true
	rm a.out

test:
	g++ $(FLAGS) unit_tests.cpp
	./a.out || true
	rm a.out
clean:
	rm a.out || true
	rm bfs.txt || true
	rm dfs.txt || true
	rm graph_info.txt || true
	rm cc.txt || true
