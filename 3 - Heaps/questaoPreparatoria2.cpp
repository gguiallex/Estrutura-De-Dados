#include <iostream>
#include <cstring>
#include <algorithm> 
using namespace std;

const int INVALIDO = -1;

class torneio{
private:
	int *heap;
	int tamanho;
	int capacidade;
    int inicioDados;
	inline int pai(int filho);
	inline int esquerda(int getPai);
	inline int direita(int getPai);
	void arruma();
	void compete(int i);
    void verBaseMaior();

public:
	torneio(int vet[], int tam);
	~torneio();
};

//Construtor da classe
torneio::torneio(int vet[], int tam){ 
    tamanho = tam;
    capacidade = 1;

    while(capacidade < tam){
        capacidade *= 2;
    }

    capacidade = capacidade * 2 - 1;

    heap = new int[capacidade];

    int inicioFolhas = capacidade / 2;
    for (int i=0; i<tam; i++){
        heap[inicioFolhas+i]=vet[i];
    }

    for (int i= inicioFolhas + tam; i<capacidade; i++){
        heap[i] = INVALIDO;
    }

    for(int i=inicioFolhas-1; i>=0; i--){
        compete(i);
    }

    cout<<heap[0]<<endl;
}

// Destrutor da classe
torneio::~torneio(){
    delete[] heap;
}

// Retorno a posição do nó pai de um determinado elemento
int torneio::pai(int filho){  
    return (filho-1) / 2;
}

// Retorna o filho à esquerda de um determinado nó
int torneio::esquerda(int pai){ 
    return pai*2+1;
}

// Retorna o filho à direita do nó pai
int torneio::direita(int pai){ 
    return pai*2+2;
}

// Faz a competição por cada posição vencedora no vetor e imprime o vencedor
void torneio::arruma(){
}

// Faz a competição entre os elementos
void torneio::compete(int i){ 
    int esq = esquerda(i);
    int dir = direita(i);
    int maior;

    if(esq <= tamanho){
        if((dir <= tamanho) && (heap[dir] > heap[esq])){
            maior = dir;
        } else {
            maior = esq;
        }

        heap[i] = heap[maior];
    } else {
        heap[i] = INVALIDO;
    }
}

int main(){
    int tam;

    cin >> tam;

    int* vet = new int[tam];

    for(int i = 0; i < tam; i++){
        cin >> vet[i];
    }

    torneio participantes(vet, tam);

    delete[] vet;
    return 0;
}