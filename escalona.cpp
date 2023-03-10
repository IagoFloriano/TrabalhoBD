#include <bits/stdc++.h>
#include "conflito.hpp"
#include "visao.hpp"
#include "util.hpp"

using std::cout, std::endl, std::cin, std::string, std::vector, std::set, std::map;

int main(){
  int time, task;
  char type, var;
  int counter {1};
  vector<variavel_t> vars {};   // salvar operacoes feitas em uma variavel p/ fazer arestas
  set<int> activeTasks {};      // salvar transacoes que nao deram commit p/ saber quando verifica serializacao
  set<int> currTasks {};        // salvar transacoes p/ saber os nodos
  map<char, int> varsIndex {};  // saber onde cada variavel esta em vara p/ poder atualizar

  while(cin >> time >> task >> type >> var) {
    cin.ignore();
    operacao_t op = operacao_t(time, task, type);
    activeTasks.insert(task);
    currTasks.insert(task);

    // se primeira vez q variavel foi usada em operacao salvar em varsIndex
    if(!varsIndex.count(var)){
      variavel_t newvar {};
      newvar.id = var;
      newvar.ops = vector<operacao_t>(); 
      vars.push_back(newvar);
      varsIndex[var] = vars.size() - 1;
    }
    // removes de transacoes ativas caso tenha dado commit
    if(type == 'C') activeTasks.erase(task);

    // salvar operacao p/ variavel
    vars[varsIndex[var]].ops.push_back(op);

    if(activeTasks.empty()){
      // imprimir qual numero da serializacao e transacoes
      set<int>::iterator tasksIt = currTasks.begin();
      cout << counter++ << " " << *tasksIt;
      for(tasksIt++; tasksIt != currTasks.end(); tasksIt++){
        cout << "," << *tasksIt;
      }

      // imprimir saida baseada nos testes
      cout << " " << (conflito::serializavel(vars, currTasks)?"SS":"NS");
      cout << " " << (visao::serializavel(vars, currTasks, time)   ?"SV":"NV") << endl;

      // resetar variaveis para poder fazer proximas transacoes
      activeTasks.clear();
      currTasks.clear();
      varsIndex.clear();
      vars.clear();
    }
  }
}
