/* arquivo que será reponsável por implementar as funções usadas para
 * verificação de seriabilidade por conflito
 * além disso fazer o grafo para fazer os testes
*/

#include "util.hpp"
#include "conflito.hpp"

using std::cout, std::endl;
namespace conflito{

  bool serializavel(std::vector<variavel_t> &vars, std::set<int> &tasks) {
    graph_t grafo = makeGraph(vars, tasks);
    return true;
  }

};

graph_t makeGraph(std::vector<variavel_t> &vars, std::set<int> &tasks) {
  graph_t newg;
  //newg.nodes = std::vector<node>();

  //// adicionar nodos
  //for(size_t i {0}; i < tasks.size(); i++){
  //  node_t newn;
  //  newn.id = tasks[i].id;
  //  newn.edges = std::vector<node_t>();
  //  newn.visit_id = 0;
  //  newg.nodes.push_back(newn);
  //}

  //// fazer arestas

  printGraph(newg);

  return newg;
}

void printGraph(graph_t g){
  for(node_t n: g.nodes){
    cout << n.id << " :";
    for(node_t nn: n.edges){
      cout << " " << nn.id;
    }
    cout << endl;
  }
}
