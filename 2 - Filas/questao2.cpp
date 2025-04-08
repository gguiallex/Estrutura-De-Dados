#include <iostream>

using namespace std;

struct Tarefa {
    char nome[50];
    char premio[50];
    char tipo;
    int tempo;
    Tarefa* prox;
    
    Tarefa(const char* n, const char* p, char t, int tm) : tipo(t), tempo(tm), prox(nullptr) {
        int i = 0;
        while (n[i] != '\0' && i < 49) {
            nome[i] = n[i];
            i++;
        }
        nome[i] = '\0';
        
        i = 0;
        while (p[i] != '\0' && i < 49) {
            premio[i] = p[i];
            i++;
        }
        premio[i] = '\0';
    }
};

class FilaTarefas {
private:
    Tarefa* frente;
    Tarefa* tras;
public:
    FilaTarefas() : frente(nullptr), tras(nullptr) {}
    
    ~FilaTarefas() {
        limpar();
    }
    
    void enfileirar(const char* nome, const char* premio, char tipo, int tempo) {
        Tarefa* nova = new Tarefa(nome, premio, tipo, tempo);
        if (tras) {
            tras->prox = nova;
        } else {
            frente = nova;
        }
        tras = nova;
    }
    
    void desenfileirar() {
        if (!frente) {
            cout << "Erro: Fila vazia!" << endl;
            return;
        }
        Tarefa* temp = frente;
        cout << "Nome: " << temp->nome << " Premio: " << temp->premio 
             << " Tipo: " << temp->tipo << " tempo: " << temp->tempo << endl;
        frente = frente->prox;
        if (!frente) {
            tras = nullptr;
        }
        delete temp;
    }
    
    void espiar() {
        if (!frente) {
            cout << "Erro: Fila vazia!" << endl;
            return;
        }
        cout << "Nome: " << frente->nome << " Premio: " << frente->premio 
             << " Tipo: " << frente->tipo << " tempo: " << frente->tempo << endl;
    }
    
    void limpar() {
        while (frente) {
            desenfileirar();
        }
    }
};

int main() {
    FilaTarefas fila;
    char comando;
    char nome[50], premio[50];
    char tipo;
    int tempo;
    
    while (cin >> comando) {
        if (comando == 'i') {
            cin >> nome >> premio >> tipo >> tempo;
            fila.enfileirar(nome, premio, tipo, tempo);
        } else if (comando == 'r') {
            fila.desenfileirar();
        } else if (comando == 'l') {
            fila.limpar();
        } else if (comando == 'e') {
            fila.espiar();
        } else if (comando == 'f') {
            break;
        }
    }
    return 0;
}