/* arquivo que será reponsável por definir as funções usadas para
 * verificação de equivalencia por visão
 * além disso fazer o grafo para fazer os testes
*/

#ifndef __VISAO__
#define __VISAO__

#include <bits/stdc++.h>
#include <vector>
#include "util.hpp"

using std::vector, std::pair;
using ii = std::pair<int,int>;

namespace visao{
  bool serializavel(std::vector<variavel_t> &vars, std::set<int> &tasks, int last_time);
}

graph_t makeGraph(std::vector<variavel_t> &vars, std::set<int> &tasks, vector<pair<ii,ii>> &vetorPares);

#endif
