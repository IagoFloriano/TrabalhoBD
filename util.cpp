/* arquivo com implmentação de funções para serem usadas por todos os outros arquivos
 */

#include "util.hpp"

void addEdge(graph_t &g, int a, int b){
  if(a==b) return;
  //std::cout << "Fazendo aresta " << a << "->" << b << std::endl;
  node_t *nodeb {NULL};
  node_t *nodea {NULL};
  // achar ambos os nodos
  for(size_t i = 0; i < g.nodes.size(); i++){
    if(g.nodes[i].id == a) nodea = &g.nodes[i];
    if(g.nodes[i].id == b) nodeb = &g.nodes[i];
  }

  // se nao achou algum
  if (!nodea || !nodeb) return;

  // verificar se ja existe a aresta
  bool exists {false};
  for(node_t n: nodea->edges){
    if(n.id == nodeb->id) exists = true;
  }

  if(!exists){
    nodea->edges.push_back(*nodeb);
  }
}
