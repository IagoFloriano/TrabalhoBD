/* arquivo que será reponsável por definir as funções usadas para
 * verificação de seriabilidade por conflito
 * além disso fazer o grafo para fazer os testes
*/

#ifndef __CONFLITO__
#define __CONFLITO__

#include <iostream>
#include <vector>
#include "util.hpp"

namespace conflito{
  bool serializavel(std::vector<tarefa_t> &tasks);
}

graph_t makeGraph(std::vector<tarefa_t> &tasks);
void printGraph(graph_t g);

#endif
