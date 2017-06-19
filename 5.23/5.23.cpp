#include "vector"
#include "algorithm"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define pii pair<int, int>
#define pip pair<int, pii>
#define F first
#define S second

const int MAX = 10010;

class Union_Find
{
  public:

    int id[MAX], sz[MAX];
    Union_Find(int n)
    {
        for (int i = 0; i < n; ++i)
        {
            id[i] = i;
            sz[i] = 1;
        }
    }
    
    int root(int i)
    {
        while(i != id[i])
        {
            id[i] = id[id[i]];
            i = id[i];
        }
        return i;
    }
    int find(int p, int q)
    {
        return root(p)==root(q);
    }
    void unite(int p, int q)
    {
        int i = root(p);
        int j = root(q);

        if(sz[i] < sz[j])
        {
            id[i] = j;
            sz[j] += sz[i];
        }
        else
        {
            id[j] = i;
            sz[i] += sz[j];
        }
    }
};


vector < pip > graph;
vector < pip > v_new_vector;
vector < pip > u_new_vector;
vector < pip > final_vector;

int n, e;
long long int T = 0;
int v_i = 0;
int u_i = 0;
int fv_i = 0;

void Kruskal_MST()
{
    Union_Find UF(n);
    int u, v, c;

    for (int i = 0; i < v_i; ++i)
    {
        u = v_new_vector[i].S.F;
        v = v_new_vector[i].S.S;
        c = v_new_vector[i].F;
        if (!UF.find(u, v))
        {
            UF.unite(u, v);
            T += c;
            
            fv_i++;
            final_vector.resize(fv_i);
            final_vector[fv_i-1] = pip(c, pii(u,v));
        }
    }
}

int main()
{
    int u, v, c, r;
    int u_vector[r];
    
    ifstream file;
    file.open("input/input.txt", ifstream::in);
    if (!file.is_open()) {
        cout << "Arquivo vazio!";
        return 1;
    }
    
    // Carregar número de Vértices, Número de Arestas e Número de Nós do conjunto U
    file >> n;
    file >> e;
    file >> r;
    
    graph.resize(e);

    // Carregar Arestas que ligam Vértices (u, v) e Adiciona seu custo (c)
    for (int i = 0; i < e; ++i)
    {
        file >> u;
        file >> v;
        file >> c;
        
        u--;
        v--;
        graph[i] = pip(c, pii(u,v));
    }
    
    // Carregar valores do arquivo
    for (int i = 0; i < r; i++)
    {
        file >> u_vector[i];
        u_vector[i] = u_vector[i]-1;
    }
    
    // Remover nós de U
    int p = 0;
    for (int i = 0; i < e; i++)
    {
        for (int j = 0; j < r; j++)
        {
            if ((graph[i].S.F == u_vector[j]) || (graph[i].S.S == u_vector[j]))
            {
                u_i++;
                u_new_vector.resize(u_i);
                u_new_vector[u_i - 1] = graph[i];
                p = 1;
                break;
            }
        }
        if(p == 0)
        {
            v_i++;
            v_new_vector.resize(v_i);
            v_new_vector[v_i - 1] = graph[i];
        }
        p = 0;
    }
    
    // Ordena o conjunto de arestas V-U
    sort(v_new_vector.begin(), v_new_vector.end());
    
    // Aplica Kruskal para obter a MST no conjunto V-U
    Kruskal_MST();
    
    printf("MST\n");
    
    // Exibe a MST do conjunto V-U
    for (int i = 0; i < fv_i; i++)
    {
        printf("Vertices %d e %d. Peso: %d\n", (final_vector[i].S.F)+1, (final_vector[i].S.S)+1, final_vector[i].F);
    }
    printf("Custo da MST: %lld\n", T);
    
    // Ordena as arestas de U
    sort(u_new_vector.begin(), u_new_vector.end());
    
    printf("\nVertices Adicionados\n");
    
    // Adicionar as menores arestas de U de cada nó na MST, gerando a LST
    for (int j = 0; j < r; j++)
    {
        for (int i = 0; i < (int)u_new_vector.size(); i++)
        {
            if ((u_new_vector[i].S.F == u_vector[j]) || (u_new_vector[i].S.S == u_vector[j]))
            {
                fv_i++;
                final_vector.resize(fv_i);
                final_vector[fv_i-1] = pip(u_new_vector[i].F, pii(u_new_vector[i].S.F, u_new_vector[i].S.S));
                printf("Vertices %d e %d. Peso: %d\n", (u_new_vector[i].S.F)+1, (u_new_vector[i].S.S)+1, u_new_vector[i].F);
                break;
            }
        }
    }
    
    // Exibe a LST
    printf("\nLST\n");
    T = 0;
    for (int i = 0; i < (int)final_vector.size(); i++)
    {
        printf("Vertices %d e %d. Peso: %d\n", (final_vector[i].S.F)+1, (final_vector[i].S.S)+1, final_vector[i].F);
        T += final_vector[i].F;
    }
    printf("Custo da LST: %lld\n", T);
    
    
    file.close();
    return 0;
}
