/* arquivo com typedefs e funções para serem usadas por todos os outros arquivos
 */

#ifndef __UTIL__
#define __UTIL__

#include <iostream>
#include <vector>

typedef std::tuple<int,char,char> operacao_t;

typedef struct tarefa{
  int id;
  std::vector<operacao_t> ops;
} tarefa_t;

typedef struct node{
  int id;
  std::vector<node> edges;
  int visit_id;
} node_t;

typedef struct graph{
  std::vector<node> nodes;
} graph_t;

#endif
