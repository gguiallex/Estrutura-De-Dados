#include <iostream>

using namespace std;

const int CAPACIDADE_FILA = 6;

struct Dado {
    string nome;
    string assunto;
    char tipo;
    int nProcesso;
};

// Imprime informações de um dado qualquer.
void imprimir_dado(const Dado& umDado){
    cout << "Nome: " << umDado.nome 
         << " Assunto: " << umDado.assunto 
         << " Tipo: " << umDado.tipo
         << " Processo: " << umDado.nProcesso
         <<endl;
}

class Fila {
    private:
        Dado mFila[CAPACIDADE_FILA];
        int posPrimeiro, posUltimo, tamanho;
    public:
        // Constrói fila vazia.
        Fila();
        // Destrutor que desaloca memória.
        ~Fila();
        // Retira e retorna o elemento que estiver na primeira posição.
        Dado Desenfileirar(); 
        // Insere um elemento na fila.
        void Enfileirar(const Dado& d);
        // Apagar todos os dados da fila.
        void LimparTudo();
        // Imprime os valores do elemento que está na frente da fila, sem Desenfileirar.
        inline void PrimeiroDaFila();
        // Informa se a fila está Vazia.
        inline bool Vazia();
        // Informa se a fila está Cheia.
        inline bool Cheia();
};

Fila::Fila(){
    posPrimeiro = 0;
    posUltimo = -1;
    tamanho = 0;
}

Fila::~Fila() {
    LimparTudo();
}

Dado Fila::Desenfileirar() {
    if (this->Vazia()) throw runtime_error("Erro: fila vazia!");
    
   Dado removido = mFila[posPrimeiro];
   posPrimeiro = (posPrimeiro + 1) % CAPACIDADE_FILA;
   tamanho--;
   return removido;
}

void Fila::Enfileirar(const Dado& d) {
    if (this->Cheia()) throw runtime_error("Erro: fila cheia!");
    // completar com código necessário caso fila não esteja vazia

    posUltimo = (posUltimo + 1) % CAPACIDADE_FILA;
    mFila[posUltimo] = d;
    tamanho++;
}

void Fila::LimparTudo() {
    bool estaVazia = Vazia();
    while(!estaVazia){
        Desenfileirar();
        estaVazia = Vazia();
    };
}

void Fila::PrimeiroDaFila() {
    if (this->Vazia()) throw runtime_error("Erro: fila vazia!");
    imprimir_dado(mFila[posPrimeiro]);      
}

bool Fila::Vazia() {
    return(tamanho == 0);
}

bool Fila::Cheia() {
    return(tamanho == CAPACIDADE_FILA);
}


int main() {
    Fila fila;
    Dado info;
    char comando;
    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nome >> info.assunto >> info.tipo >> info.nProcesso;
                    fila.Enfileirar(info);
                    break;
                case 'r': // remover
                    imprimir_dado(fila.Desenfileirar());
                    break;
                case 'l': // limpar tudo
                    fila.LimparTudo();
                    break;
                case 'e': // espiar 
                    if(!fila.Vazia())               
                        fila.PrimeiroDaFila();
                    else
                        cout << "Erro: fila vazia!"<< endl;
                    break;
                case 'f': // finalizar
                    // checado no do-while
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    while (!fila.Vazia()) {
        imprimir_dado(fila.Desenfileirar());
    }
    cout << endl;
    return 0;
}