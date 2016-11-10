# GraphProject
Biblioteca em c++ de grafos.

A biblioteca principal encontra-se no arquivo graph.h e utiliza as classes encontradas no arquivo linked_list.h como lista de adjacências.

Para utilizá-la basta importar graph.h no seu código e inicializar a classe do tipo de grafo desejado (AdjacencyMatrixGraph ou AdjacencyListGraph).

Existem duas classes auxiliares utilizadas para as funções dos grafos na biblioteca:
    - Linked_List
    - Priority_Queue

funções de Linked_List:
    push(edge, weight=1) // Adiciona um novo elemento à cabeça da lista.
    push_ordered(edge, weight=1) // Adiciona um novo elemento respeitando a ordem na lista.
    push_back(edge, weight=1) // Adicione um novo elemento ao final da lista.
    pop() // Retira um elemento da cabeça da lista.

funções de Priority_Queue:
    Priority_Queue(max_size) // Constrói a classe e determina o tamanho máximo que o heap pode ter.
    push(id, weight) // Adiciona um novo elemento à fila na posição adequada.
    pop() // Retira a cabeça da fila e a reorganiza.
    update(id, weight) // Atualiza o peso de um elemento da fila.
