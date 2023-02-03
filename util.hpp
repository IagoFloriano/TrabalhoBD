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

#endif
