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
	wget -P $(DOWNLOAD_PATH) http://www.land.ufrj.br/~daniel/grafos/data/grafo_1.txt
	wget -P $(DOWNLOAD_PATH) http://www.land.ufrj.br/~daniel/grafos/data/grafo_2.txt
	wget -P $(DOWNLOAD_PATH) http://www.land.ufrj.br/~daniel/grafos/data/grafo_3.txt
	wget -P $(DOWNLOAD_PATH) http://www.land.ufrj.br/~daniel/grafos/data/grafo_4.txt
	wget -P $(DOWNLOAD_PATH) http://www.land.ufrj.br/~daniel/grafos/data/grafo_5.txt
	wget -P $(DOWNLOAD_PATH) http://www.land.ufrj.br/~daniel/grafos/data/rede_colaboracao.txt
	wget -P $(DOWNLOAD_PATH) http://www.land.ufrj.br/~daniel/grafos/data/rede_colaboracao_vertices.txt
	
clean:
	rm a.out || true
	rm bfs.txt || true
	rm dfs.txt || true
	rm graph_info.txt || true
	rm cc.txt || true
	rm dijkstra.txt || true
	rm mst.txt || true
