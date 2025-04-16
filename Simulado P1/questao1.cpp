#include <iostream>
using namespace std;

struct dado {
    string nome = "vazio";
    string tipo;
    dado *proximo;
};

class fila {
private:
    dado *inicio;
    dado *fim;
public:
    fila() {
        inicio = NULL;
        fim = NULL;
    }

    void enfileirar(dado entrada) {
        dado *novo = new dado;
        *novo = entrada;
        novo->proximo = NULL;
        if (fim != NULL)
            fim->proximo = novo;
        else
            inicio = novo;
        fim = novo;
    }

    dado desenfileirar() {
        if (inicio == NULL) throw runtime_error("Fila vazia!");
        dado *retornado = new dado;
        dado *removido = inicio;
        if (inicio == fim)
            fim = NULL;
        retornado->nome = inicio->nome;
        retornado->tipo = inicio->tipo;
        inicio = inicio->proximo;
        removido->proximo = NULL;
        delete removido;
        return *retornado;
    }

    bool vazia() {
        return inicio == NULL;
    }

    ~fila() {
        while (inicio != NULL)
            desenfileirar();
    }
};

int main() {
    fila prioridades, normais;
    string comando;
    dado entrada, atendido;
    int cont_prioridade = 0;

    cin >> comando;
    while (comando != "fim") {
        if (comando == "normal") {
            cin >> entrada.nome;
            entrada.tipo = "normal";
            normais.enfileirar(entrada);
        } else if (comando == "prioridade") {
            cin >> entrada.nome;
            entrada.tipo = "prioridade";
            prioridades.enfileirar(entrada);
        } else if (comando == "atender") {
            if (cont_prioridade < 3 && !prioridades.vazia()) {
                atendido = prioridades.desenfileirar();
                cout << atendido.nome << endl;
                cont_prioridade++;
            } else if (!normais.vazia()) {
                atendido = normais.desenfileirar();
                cout << atendido.nome << endl;
                cont_prioridade = 0;
            } else if (!prioridades.vazia()) {
                atendido = prioridades.desenfileirar();
                cout << atendido.nome << endl;
                cont_prioridade++;
            } else {
                cout << "AGUARDE" << endl;
            }
        }
        cin >> comando;
    }

    return 0;
}
