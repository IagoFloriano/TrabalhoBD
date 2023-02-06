/* arquivo que será reponsável por implementar as funções usadas para
 * verificação de equivalencia por visão
 * além disso fazer o grafo para fazer os testes
*/


#include "util.hpp"
#include "visao.hpp"

using std::set, std::vector, std::pair, std::get;
using ii = pair<int,int>;

namespace visao{
  bool serializavel(vector<variavel_t> &vars, set<int> &tasks, int last_time){
    tasks.insert(tasks.size()+1);   //coloca a TF
    tasks.insert(0);                //coloca a T0

    operacao_t op_0 = operacao_t(0, 0, 'W');
    operacao_t op_F = operacao_t(last_time+1, tasks.size()+1, 'R');

    //passa por todas as variaveis e coloca uma op de escrita em tf e uma de leitura em t0
    for(variavel_t v: vars){
      if(v.id == '-') continue;

      v.ops.push_back(op_0);
      v.ops.push_back(op_F);
    }

    vector<pair<ii,ii>> vetorPares;

    graph_t grafo = makeGraph(vars, tasks, vetorPares);

    return permutaArestasETesta(grafo, vetorPares, 0, vetorPares.size());
  }
}

bool permutaArestasETesta (graph_t &grafo, vector<pair<ii,ii>> &vetorPares, int iAtual, int tamVec){
  //base da recursão, as arestas já foram postas
  if (iAtual == tamVec)
    return topoPossible(grafo);

  int origem_1  = get<0>(get<0>(vetorPares[iAtual]));
  int destino_1 = get<1>(get<0>(vetorPares[iAtual]));
  int origem_2  = get<0>(get<1>(vetorPares[iAtual]));
  int destino_2 = get<1>(get<1>(vetorPares[iAtual]));

  //coloca a primeira aresta possível do par
  addEdge(grafo, origem_1, destino_1);

  if (permutaArestasETesta (grafo, vetorPares, iAtual+1, tamVec))
    return true;

  //cola a primeira pois agr colocaremos a segunda
  rmvEdge(grafo, origem_1, destino_1);

  //coloca a segunda aresta possível do par
  addEdge(grafo, origem_2, destino_2);

  //se não deu certo com a primeira aresta, a resposta será se funciona com a segunda
  return (permutaArestasETesta (grafo, vetorPares, iAtual+1, tamVec));
}

graph_t makeGraph(vector<variavel_t> &vars, set<int> &tasks, vector<pair<ii,ii>> &vetorPares){
  graph_t newg;
  newg.nodes = std::vector<node>();

  // adicionar nodos
  for(std::set<int>::iterator it = tasks.begin(); it != tasks.end(); it++){
    node_t newn;
    newn.incident = 0;
    newn.id = *it;
    newn.edges = std::vector<int>();
    newn.temp = 0;
    newg.nodes.push_back(newn);
  }

  // fazer arestas
  for(variavel_t v: vars){
    if(v.id == '-') continue;

    for(size_t i {0}; i < v.ops.size(); i++){
      for(size_t j {i+1}; j < v.ops.size(); j++){
        // se sao a mesma transacao
        if(get<1>(v.ops[i]) == get<1>(v.ops[j])) continue;

        char opi = get<2>(v.ops[i]);
        char opj = get<2>(v.ops[j]);
        if( (opj == 'R' && opi == 'W') ||// Aresta Ti -> Tj para cada r(x) em Tj depois de w(x) em Ti
            (opj == 'W' && opi == 'R') ||// Aresta Ti -> Tj para cada w(x) em Tj depois de r(x) em Ti
            (opj == 'W' && opi == 'W')  )// Aresta Ti -> Tj para cada w(x) em Tj depois de w(x) em Ti
            {
          addEdge(newg, get<1>(v.ops[i]), get<1>(v.ops[j]));

          //aqui faz a parte da cosntrução do vetor de pares
          for(size_t k {j+1}; k < v.ops.size(); k++){
            // se sao a mesma transacao
            if((get<1>(v.ops[i]) == get<1>(v.ops[k])) ||
               (get<1>(v.ops[j]) == get<1>(v.ops[k]))) continue;

            char opk = get<2>(v.ops[k]);
            if (opk == 'W'){

              //caso Ti == To ou Tj == Tf
              if ((i == 0) || (j == tasks.size()+1)){
                if (i != 0)
                  addEdge(newg, get<1>(v.ops[k]), get<1>(v.ops[i]));
                else //if (j != tasks.size()+1)
                  addEdge(newg, get<1>(v.ops[j]), get<1>(v.ops[k]));
              }
              else{
                ii el1 = pair(k,i);
                ii el2 = pair(j,k);

                pair<ii,ii> par = pair(el1,el2);  //um par de arestas
                vetorPares.push_back(par);        //coloca no vetor
              }
            }
          }
        }
      }
    }
  }

  return newg;
}