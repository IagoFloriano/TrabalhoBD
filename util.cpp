/* arquivo com implmentação de funções para serem usadas por todos os outros arquivos
 */

#include "util.hpp"

// função interna para achar indice de um vertice no grafo
// retorna o indice se exite e -1 caso contrário
int findNode(graph_t &g, int id){
  for(size_t i {0}; i < g.nodes.size(); i++){
    if(g.nodes[i].id == id) return i;
  }
  return -1;
}

void addEdge(graph_t &g, int a, int b){
  //se os nodos forem iguais
  if(a==b) return;
  //std::cout << "Fazendo aresta " << a << "->" << b << std::endl;
  node_t *nodeb {NULL};
  node_t *nodea {NULL};
  // achar ambos os nodos
  /*for(size_t i = 0; i < g.nodes.size(); i++){
    if(g.nodes[i].id == a) nodea = &g.nodes[i];
    if(g.nodes[i].id == b) nodeb = &g.nodes[i];
  }*/

  int i_a = findNode(g, a);
  int i_b = findNode(g, b);

  nodea = &g.nodes[i_a];
  nodeb = &g.nodes[i_b];

  // se nao achou algum
  if (!nodea || !nodeb) return;

  // verificar se ja existe a aresta
  bool exists {false};
  for(int n: nodea->edges){
    if(n == nodeb->id) exists = true;
  }

  if(!exists){
    nodea->edges.push_back(nodeb->id);
    nodeb->incident++;
  }
}

void rmvEdge(graph_t &g, int a, int b){
  //se os nodos forem iguais
  if(a==b) return;
  
  //std::cout << "Removendo aresta " << a << "->" << b << std::endl;

  node_t *nodeb {NULL};
  node_t *nodea {NULL};
  // achar ambos os nodos
  /*for(size_t i = 0; i < g.nodes.size(); i++){
    if(g.nodes[i].id == a) nodea = &g.nodes[i];
    if(g.nodes[i].id == b) nodeb = &g.nodes[i];
  }*/

  int i_a = findNode(g, a);
  int i_b = findNode(g, b);

  nodea = &g.nodes[i_a];
  nodeb = &g.nodes[i_b];

  // se nao achou algum
  if (!nodea || !nodeb) return;

  // verificar se ja existe a aresta
  for(auto i = nodea->edges.begin() ; i != nodea->edges.end() ; i++){
    if(*i == nodeb->id){
      nodea->edges.erase(i);
      nodeb->incident++;
      return;
    }
  }

  //passando daqui, sabemos que a aresta n existe
  //std::cout << "Não existe aresta de "  << a << " para " << b << std::endl;
}

bool topoPossible(graph_t &g){
  std::vector<int> S;
  std::vector<int> L;

  for(size_t i {0}; i < g.nodes.size(); i++){
    g.nodes[i].temp = g.nodes[i].incident;
    if(g.nodes[i].incident == 0) S.push_back(g.nodes[i].id);
  }

  while(S.size() > 0){
    int n = S[S.size()-1];
    S.pop_back();
    L.push_back(n);
    for(int m: g.nodes[findNode(g, n)].edges){
      int mIndex = findNode(g,m);
      g.nodes[mIndex].temp--;
      if(g.nodes[mIndex].temp == 0){
        S.push_back(m);
      }
    }
  }

  return L.size() == g.nodes.size();
}
