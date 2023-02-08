/* arquivo que será reponsável por definir as funções usadas para
 * verificação de seriabilidade por conflito
 * além disso fazer o grafo para fazer os testes
*/

#ifndef __CONFLITO__
#define __CONFLITO__

#include <bits/stdc++.h>
#include <vector>
#include "util.hpp"

namespace conflito{
  bool serializavel(std::vector<variavel_t> &vars, std::set<int> &tasks);
}

graph_t makeGraph(std::vector<variavel_t> &vars, std::set<int> &tasks);

#endif
