FLAGS="-std=c++11"
DOWNLOAD_PATH="src/graphs/"
study_case:
	g++ $(FLAGS) src/case_study.cpp
	./a.out || true
	rm a.out
test_bench:
	g++ $(FLAGS) test.cpp
	./a.out || true
	rm a.out

test:
	g++ $(FLAGS) src/tests/unit_tests.cpp
	./a.out || true
	rm a.out

download_graphs:
	rm $(DOWNLOAD_PATH)* || true
	for i in 5 10 20 50 100 200 500 1000 2000 5000 7500 10000 ; do \
		wget -P $(DOWNLOAD_PATH) http://www.land.ufrj.br/~daniel/grafos/data/points-$$i.txt; \
	done

convert_graphs:
	g++ $(FLAGS) src/graph_converter.cpp
	find src/graphs/ -name "*[0-9]\.txt" -exec ./a.out {} \;
	rm a.out
	
clean:
	rm a.out || true
	rm bfs.txt || true
	rm dfs.txt || true
	rm graph_info.txt || true
	rm cc.txt || true
	rm dijkstra.txt || true
	rm mst.txt || true
