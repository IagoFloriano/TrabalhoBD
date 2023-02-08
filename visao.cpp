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
    int tf = -1; //(int)(tasks.size()+1);
    tasks.insert(tf); //coloca a TF
    tasks.insert(0);  //coloca a T0

    operacao_t op_0 = operacao_t(0, 0, 'W');
    operacao_t op_F = operacao_t(last_time+1, tf, 'R');

    //passa por todas as variaveis e coloca uma op de escrita em tf e uma de leitura em t0
    for(variavel_t &v: vars){
      if(v.id == '-') continue;

      v.ops.push_back(op_0);
      v.ops.push_back(op_F);
      std::sort(v.ops.begin(), v.ops.end());
    }

    vector<pair<ii,ii>> vetorPares;

    graph_t grafo = makeGraph(vars, tasks, vetorPares);

    return permutaArestasETesta(grafo, vetorPares, 0, vetorPares.size());
  }
}

bool permutaArestasETesta (graph_t &grafo, vector<pair<ii,ii>> &vetorPares, int iAtual, int tamVec){
  //base da recursão, as arestas já foram postas
  if (iAtual == tamVec){
    return topoPossible(grafo);
  }

  int origem_1  = get<0>(get<0>(vetorPares[iAtual]));
  int destino_1 = get<1>(get<0>(vetorPares[iAtual]));
  int origem_2  = get<0>(get<1>(vetorPares[iAtual]));
  int destino_2 = get<1>(get<1>(vetorPares[iAtual]));

  //coloca a primeira aresta possível do par
  bool existia_1 = hasEdge(grafo, origem_1, destino_1);
  addEdge(grafo, origem_1, destino_1);

  if (permutaArestasETesta (grafo, vetorPares, iAtual+1, tamVec))
    return true;

  //cola a primeira pois agr colocaremos a segunda
  if(!existia_1) rmvEdge(grafo, origem_1, destino_1);

  //coloca a segunda aresta possível do par
  bool existia_2 = hasEdge(grafo, origem_2, destino_2);
  addEdge(grafo, origem_2, destino_2);

  //se não deu certo com a primeira aresta, a resposta será se funciona com a segunda
  bool result = permutaArestasETesta(grafo, vetorPares, iAtual+1, tamVec);
  if(!existia_2) rmvEdge(grafo, origem_2, destino_2);
  return result;
}

graph_t makeGraph(vector<variavel_t> &vars, set<int> &tasks, vector<pair<ii,ii>> &vetorPares){
  graph_t newg;
  newg.nodes = std::vector<node>();

  // adicionar nodos
  for(std::set<int>::iterator it = tasks.begin(); it != tasks.end(); ++it){
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
      char opi = get<2>(v.ops[i]);
      if( opi != 'W') continue;
      // testar apenas transacoes que leram de i
      for(size_t j {i+1}; j < v.ops.size(); j++){
        // se sao a mesma transacao
        if(get<1>(v.ops[i]) == get<1>(v.ops[j])) continue;

        char opj = get<2>(v.ops[j]);
        if (opj == 'W') break;
        // j leu de i
        if(opj == 'R'){
          addEdge(newg, get<1>(v.ops[i]), get<1>(v.ops[j]));
          makePair(newg, vetorPares, tasks, v, i, j);
        }
      }
    }
  }

  return newg;
}

void makePair(graph_t &g, std::vector<pair<ii,ii>> &vetorPares, std::set<int> &tasks, variavel_t v, size_t i, size_t j){

  //aqui faz a parte da cosntrução do vetor de pares
  for(size_t k {0}; k < v.ops.size(); k++){
    // se sao a mesma transacao ou se k == i ou k == j
    if( (k == i || j == k) ||
        (get<1>(v.ops[i]) == get<1>(v.ops[k])) ||
        (get<1>(v.ops[j]) == get<1>(v.ops[k]))) continue;

    char opk = get<2>(v.ops[k]);
    if (opk == 'W'){

      int ti = get<1>(v.ops[i]);
      int tj = get<1>(v.ops[j]);
      int tk = get<1>(v.ops[k]);
      //caso Ti == To ou Tj == Tf
      if ((ti == 0) || (tj == -1)){
        if (ti != 0){
          addEdge(g, tk, ti);
        }
        else if (tj != (int)(tasks.size()+1)){
          addEdge(g, tj, tk);
        }
      }
      else if (tk != 0 && tk != -1){
        ii el1 = pair(tk,ti);
        ii el2 = pair(tj,tk);

        pair<ii,ii> par = pair(el1,el2);  //um par de arestas
        vetorPares.push_back(par);        //coloca no vetor
      }
    }
  }
}
