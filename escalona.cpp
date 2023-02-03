#include <bits/stdc++.h>
#include "conflito.hpp"
#include "visao.hpp"
#include "util.hpp"

using std::cout, std::endl, std::cin, std::string;

int main(){
  int time, task;
  char type, var;
  int counter {1};
  std::vector<tarefa_t> tasks {};
  std::set<int> activeTasks {};
  std::map<int, int> taskIndex {};
  while(cin >> time >> task >> type >> var) {
    cin.ignore();
    operacao_t op = operacao_t(time, type, var);
    activeTasks.insert(task);

    // if first operation add to map
    if(!taskIndex.count(task)){
      tarefa_t newtask {};
      newtask.id = task;
      newtask.ops = std::vector<operacao_t>(); 
      tasks.push_back(newtask);
      taskIndex[task] = tasks.size() - 1;
    }
    if(type == 'C') activeTasks.erase(task);

    tasks[taskIndex[task]].ops.push_back(op);

    if(activeTasks.empty()){
      cout << counter++ << " " << tasks[0].id;
      for(int i {1}; i < tasks.size(); i++){
        cout << "," << tasks[i].id;
      }
      // do tests
      cout << " " << (conflito::serializavel(tasks)?"SS":"NS");
      cout << " " << (visao::serializavel(tasks)   ?"SV":"NV") << endl;

      // reset variables
      activeTasks.clear();
      taskIndex.clear();
      tasks.clear();
    }
  }
}
