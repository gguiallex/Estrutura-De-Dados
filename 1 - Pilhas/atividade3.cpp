#include <iostream>
using namespace std;

struct jogo
{
    string nome;
    char tipo;
    int valor;
};

class inventario
{
private:
    struct Noh
    {
        jogo item;
        Noh *proximo;
    };
    Noh *topo;
    int tamanho;

public:
    inventario();
    ~inventario();
    void empilhar(string nome, char tipo, int valor);
    jogo desempilhar();
    jogo espia();
    bool vazia();
    void limparInventario();
    void removerInferiores(int limite);
};

inventario::inventario()
{
    topo = nullptr;
    tamanho = 0;
}

inventario::~inventario()
{
    limparInventario();
}

void inventario::empilhar(string nome, char tipo, int valor)
{
    Noh *novo = new Noh;
    novo->item = {nome, tipo, valor};
    novo->proximo = topo;
    topo = novo;
    tamanho++;
}

jogo inventario::desempilhar()
{
    if (vazia())
    {
        cout << "Erro: pilha vazia!" << endl;
        return {"", ' ', -1};
    }
    Noh *auxiliar = topo;
    jogo removido = auxiliar->item;
    topo = topo->proximo;
    delete auxiliar;
    tamanho--;
    return removido;
}

void inventario::removerInferiores(int limite)
{
    inventario aux;

    while (!vazia())
    {
        jogo atual = desempilhar();
        if(atual.valor >= limite){
            aux.empilhar(atual.nome, atual.tipo, atual.valor);
        } else {
            cout << "Nome: " << atual.nome << " Tipo: " << atual.tipo << " Valor: " << atual.valor << endl;
        }
    }

    while (!aux.vazia()){
        jogo atual = aux.desempilhar();
        empilhar(atual.nome, atual.tipo, atual.valor);
    };
}

jogo inventario::espia()
{
    if (vazia())
    {
        cout << "Erro: pilha vazia!" << endl;
        return {"", ' ', -1};
    }
    return topo->item;
}

bool inventario::vazia()
{
    return topo == nullptr;
}

void inventario::limparInventario()
{
    while (!vazia()) {
        desempilhar();
    }
}

int main()
{
    inventario pilha;
    char opcao;

    while (cin >> opcao)
    {
        if (opcao == 'i')
        {
            string nome;
            char tipo;
            int valor;
            cin >> nome >> tipo >> valor;
            pilha.empilhar(nome, tipo, valor);
        }
        else if (opcao == 'r')
        {
            jogo removido = pilha.desempilhar();
            cout << "Nome: " << removido.nome << " Tipo: " << removido.tipo << " Valor: " << removido.valor << endl;
        }
        else if (opcao == 'e')
        {
            jogo topo = pilha.espia();
            if (topo.valor != -1)
            {
                cout << "Nome: " << topo.nome << " Tipo: " << topo.tipo << " Valor: " << topo.valor << endl;
            }
        }
        else if (opcao == 'l')
        {
            pilha.limparInventario();
        }
        else if(opcao == 'x'){
            int valorLimite;
            cin >> valorLimite;
            pilha.removerInferiores(valorLimite);
        }
        else if (opcao == 'f')
        {
            while (!pilha.vazia())
            {
                jogo removido = pilha.desempilhar();
                cout << "Nome: " << removido.nome << " Tipo: " << removido.tipo << " Valor: " << removido.valor << endl;
            }
            break;
        }
    }

    return 0;
}
