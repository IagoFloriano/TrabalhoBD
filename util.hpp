/* arquivo com typedefs e funções para serem usadas por todos os outros arquivos
 */

#ifndef __UTIL__
#define __UTIL__

#include <iostream>
#include <vector>

//            tempo transacao tipo
typedef std::tuple<int,int,char> operacao_t;

typedef struct variavel{
  char id;
  std::vector<operacao_t> ops;
} variavel_t;

typedef struct node{
  int id;
  std::vector<node> edges;
  int visit_id;
} node_t;

typedef struct graph{
  std::vector<node> nodes;
} graph_t;

// adiciona uma aresta a->b no grafo g, se aresta ja exitir nao faz nada
// caso a ou b nao existam nao faz nada
// se a == b nao faz nada
void addEdge(graph_t &g, int a, int b);

#endif
