#include <iostream>
#include <fstream>
#include "Graph.h"
#include "LinkedList.h"

using namespace std;

/**
 * As funções comentadas abaixo forma utilizadas para realizar experimentos
 */
/*
#include <chrono>

long getTime(){
    using namespace std::chrono;
    return duration_cast< milliseconds >(
        high_resolution_clock::now().time_since_epoch()
    ).count();
}

void testInstances(){
    LinkedList<char>* filenames = new LinkedList<char>();
    filenames->add("grafo_1000_1.txt");
    filenames->add("grafo_1000_2.txt");
    filenames->add("grafo_1000_3.txt");
    filenames->add("grafo_1000_4.txt");
    filenames->add("grafo_1000_5.txt");
    filenames->add("grafo_1000_6.txt");
    filenames->add("grafo_1000_7.txt");
    filenames->add("grafo_1000_8.txt");
    filenames->add("grafo_10000_1.txt");
    filenames->add("grafo_10000_2.txt");
    filenames->add("grafo_10000_3.txt");
    filenames->add("grafo_10000_4.txt");
    filenames->add("grafo_10000_5.txt");
    filenames->add("grafo_10000_6.txt");
    filenames->add("grafo_10000_7.txt");
    filenames->add("grafo_10000_8.txt");

    cout << "Processando..." << endl;

    ofstream file;
    file.open("test.txt");

    int i = 1;
    filenames->goFirst();
    while(filenames->get() != NULL){
        long end, start;

        file << "----------------------------" << endl;
        file << i++ << "ª instância: " << filenames->get() << endl;
        file << "----------------------------" << endl;
        start = getTime();
        Graph* graph = new Graph(filenames->get());
        end = getTime();

        file << "Tempo de leitura do arquivo: " << end-start << " ms" << endl;
        file << "|V| = " << graph->getVertexCount() << endl;
        file << "|E| = " << graph->getEdgesCount() << endl;

        start = getTime();
        int componentsCount = graph->getComponentsCount();
        end = getTime();
        file << "Tempo gasto para identificar as componentes conexas: " << end-start << " ms" << endl;
        file << "Número de componentes encontradas: " << componentsCount << endl;
        file << "Número de vértices na maior componente: " << graph->getBiggestComponentSize() << endl;
        file << "Número de vértices na menor componente: " << graph->getSmallestComponentSize() << endl;
        file << endl << endl << endl;

        filenames->next();
    }

    file.close();
}*/

int main(){
    /// Obtém nome do arquivo
    string filename;
    cout << "Digite o nome do arquivo: " << endl;
    getline(cin, filename);

    /// Faz a leitura do grafo
    Graph* graph = new Graph(filename);
    cout << "Processando..." << endl;

    /// Prepara arquivo de saída
    ofstream file;
    file.open("results.txt");

    /// Escreve informações relevantes no arquivo
    int k = graph->isKRegular();
    if(k != -1)
        file << "O grafo é k-regular, com k = " << k << endl;
    else
        file << "O grafo não é k-regular" << endl;

    file << "Número de vértices: " << graph->getVertexCount() << endl;
    file << "Número de arestas: " << graph->getEdgesCount() << endl;
    file << "Grau médio: " << graph->getAverageDegree() << endl;
    file << "Número de componentes encontradas: " << graph->getComponentsCount() << endl;
    file << "Número de vértices na maior componente: " << graph->getBiggestComponentSize() << endl;
    file << "Número de vértices na menor componente: " << graph->getSmallestComponentSize() << endl;

    float* dist = graph->getDegreeDistribution();
    file << endl << "Distribuição empírica do grau dos vértices:" << endl;

    for(int i = 0; i < graph->getVertexCount(); i++)
        file << "Grau " << i << ": " << dist[i] << endl;

    /// Fecha arquivo
    file.close();
    delete graph;
    cout << "Resultado no arquivo results.txt" << endl;
    return 0;
}
