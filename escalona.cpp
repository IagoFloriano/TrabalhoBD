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
    activeTasks.inset(task);

    // if first operation add to map
    if(!taskIndex.count(task)){
    }

    if(activeTasks.empty()){
      // do tests

      // reset variables
      activeTasks.clear();
      taskIndex.clear();
      tasks.clear();
      cout << "Clearing active tasks\n";
    }
  }
}
