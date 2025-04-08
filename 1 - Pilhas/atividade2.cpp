#include <iostream>
using namespace std;

const int PilhaVAZIA = -1;
const int TamPilhaMAX = 6;

struct tarefa {
    string nome;
    char tipo;
    int valor;
};

class robo {
private:
    struct Noh {
        tarefa item;
        Noh* proximo;
    };
    Noh* topo;
    int tamanho;

public:
    robo();
    ~robo();
    void empilhar(string nome, char tipo, int valor);
    tarefa desempilhar();
    tarefa espia();
    bool vazia();
    void limparTarefas();
};

robo::robo() {
    topo = nullptr;
    tamanho = PilhaVAZIA;
}

robo::~robo() {
    limparTarefas();
}

void robo::empilhar(string nome, char tipo, int valor) {
    if(tamanho < TamPilhaMAX){
        Noh* novo = new Noh;
        novo->item = {nome, tipo, valor};
        novo->proximo = topo;
        topo = novo;
        tamanho++;
    } else {
        cout << "Erro: pilha cheia!" << endl;
    }
}

tarefa robo::desempilhar() {
    if (vazia()) {
        cout << "Erro: pilha vazia!" << endl;
        return {"", ' ', -1}; 
    }
    Noh* auxiliar = topo;
    tarefa removido = auxiliar->item;
    topo = topo->proximo;
    delete auxiliar;
    tamanho--;
    return removido;
}

tarefa robo::espia() {
    if (vazia()) {
        cout << "Erro: pilha vazia!" << endl;
        return {"", ' ', -1}; 
    }
    return topo->item;
}

bool robo::vazia() {
    return topo == nullptr;
}

void robo::limparTarefas() {
    while (!vazia()) {
        desempilhar();
    }
}

int main() {
    robo tarefas;
    char opcao;

    while (cin >> opcao) {
        if (opcao == 'i') {
            string nome;
            char tipo;
            int valor;
            cin >> nome >> tipo >> valor;
            tarefas.empilhar(nome, tipo, valor);
        } 
        else if (opcao == 'r') {
            tarefa removido = tarefas.desempilhar();
            if (removido.valor != -1) {
                cout << "Nome: " << removido.nome << " Tipo: " << removido.tipo << " Valor: " << removido.valor << endl;
            }
        } 
        else if (opcao == 'e') {
            tarefa topo = tarefas.espia();
            if (topo.valor != -1) {
                cout << "Nome: " << topo.nome << " Tipo: " << topo.tipo << " Valor: " << topo.valor << endl;
            }
        } 
        else if (opcao == 'l') {
            tarefas.limparTarefas();
        } 
        else if (opcao == 'f') {
            while (!tarefas.vazia()) {
                tarefa removido = tarefas.desempilhar();
                cout << "Nome: " << removido.nome << " Tipo: " << removido.tipo << " Valor: " << removido.valor << endl;
            }
            break;
        }
    }

    return 0;
}
