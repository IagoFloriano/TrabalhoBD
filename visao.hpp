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

bool permutaArestasETesta (graph_t &grafo, vector<pair<ii,ii>> &vetorPares, int iAtual, int tamVec);

graph_t makeGraph(std::vector<variavel_t> &vars, std::set<int> &tasks, vector<pair<ii,ii>> &vetorPares);

void makePair(graph_t &g, std::vector<pair<ii,ii>> &vetorPares, std::set<int> &tasks, variavel_t v, size_t i, size_t j);

#endif
