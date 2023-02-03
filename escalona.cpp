#include <bits/stdc++.h>

using std::cout, std::endl, std::cin, std::string;

//              tempo, tipo, variável
typedef std::tuple<int,char,char> operacao_t;

typedef struct tarefa{
  int id;
  std::vector<operacao_t> ops;
} tarefa_t;

int main(){
  int time, task;
  char type, var;
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
      // do tests
      for(tarefa_t t: tasks){
        cout << t.id << ":" << endl;
        for(operacao_t o: t.ops){
          cout << std::get<0>(o) << " " << std::get<1>(o) << " " << std::get<2>(o) << endl;
        }
      }

      // reset variables
      activeTasks.clear();
      taskIndex.clear();
      tasks.clear();
      cout << "Clearing active tasks\n";
    }
  }
}
