/* arquivo que será reponsável por implementar as funções usadas para
 * verificação de seriabilidade por conflito
 * além disso fazer o grafo para fazer os testes
*/

#include "util.hpp"
#include "conflito.hpp"

namespace conflito{

  bool serializavel(std::vector<variavel_t> &vars, std::set<int> &tasks) {

    graph_t grafo = makeGraph(vars, tasks);
    // printGraph(grafo);
    return topoPossible(grafo);
  }

};

graph_t makeGraph(std::vector<variavel_t> &vars, std::set<int> &tasks) {
  graph_t newg;
  newg.nodes = std::vector<node>();

  // adicionar nodos
  for(std::set<int>::iterator it = tasks.begin(); it != tasks.end(); it++){
    node_t newn;
    newn.incident = 0;
    newn.id = *it;
    newn.edges = std::vector<int>();
    newn.temp = 0;
    newg.nodes.push_back(newn);
  }

  using std::get;
  // fazer arestas
  for(variavel_t v: vars){
    if(v.id == '-') continue;

    for(size_t i {0}; i < v.ops.size(); i++){
      for(size_t j {i+1}; j < v.ops.size(); j++){
        // se sao a mesma transacao
        if(get<1>(v.ops[i]) == get<1>(v.ops[j])) continue;

        char opi = get<2>(v.ops[i]);
        char opj = get<2>(v.ops[j]);
        if( (opj == 'R' && opi == 'W') ||// Aresta Ti -> Tj para cada r(x) em Tj depois de w(x) em Ti
            (opj == 'W' && opi == 'R') ||// Aresta Ti -> Tj para cada w(x) em Tj depois de r(x) em Ti
            (opj == 'W' && opi == 'W')  )// Aresta Ti -> Tj para cada w(x) em Tj depois de w(x) em Ti
            {
          addEdge(newg, get<1>(v.ops[i]), get<1>(v.ops[j]));
        }
      }
    }
  }

  return newg;
}

void printGraph(graph_t g){
  using std::cout, std::endl;
  for(node_t n: g.nodes){
    cout << n.id << "(" << n.incident << ") :";
    for(int nn: n.edges){
      cout << " " << nn;
    }
    cout << endl;
  }
}
