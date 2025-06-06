#include <iostream>
#include <cstdlib>

using namespace std;


struct equipe{
    string nomeEquipe;
    string lider;
    string linguagem; 
    int qtdMembros;
};

class noh {
friend class lista;
private:
    equipe elenco; // poderia ser outro tipo de variável
    noh* proximo;
public:
    //noh();
    noh(equipe d);
};

// construindo time chamando seu construtor
noh::noh(equipe d){
    elenco = d;
    proximo = NULL;
}


// lista dinamicamente encadeada
class lista {
private:
    noh* primeiro;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista
     // imprime reverso a partir de um nó -> exemplo de uso de recursão
    void imprimeReversoAux(noh* umNoh);
public:
    // construtores e destrutor
    lista();
    lista(const lista& umaLista);
    ~lista();
    // sobrecarga do operador de atribuição
    lista& operator=(const lista& umaLista);  
    // inserção, remoção e procura
    inline void insere(equipe elenco);
    void insereNoFim(equipe elenco);
    void insereNoInicio(equipe elenco);
    void insereNaPosicao(int posicao, equipe elenco);
    int procura(string valor); // retorna a posição do nó com va
    // métodos adicionais (impressão, vazia)
    void imprime();
    void imprimeReverso();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
};


// constrói uma lista inicialmente vazia
lista::lista() {
   primeiro = NULL;
   tamanho = 0;
}

// construtor de cópia
lista::lista(const lista& umaLista) {
   primeiro = NULL;
   tamanho = 0;
   noh* aux = umaLista.primeiro;
   while (aux != NULL) {
       insereNoFim(aux->elenco);
       aux = aux->proximo;
   }
}

// destrutor da lista (chama função privada auxiliar)
lista::~lista( ) {
   removeTodos();
}    

// remove todos os elementos da lista
void lista::removeTodos( ) {
   while (primeiro != NULL) {
       removeNoInicio();
   }
}    

// sobrecarga do operador de atribuição
lista& lista::operator=(const lista& umaLista){
    // limpa a lista atual
    removeTodos();
     // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaLista.primeiro;
    
    while (aux != NULL) {
        insereNoFim(aux->elenco);
        aux = aux->proximo;  
    }
    
    return *this; 
}  

// insere no final da lista
void lista::insereNoFim(equipe elenco) {
   noh* novo = new noh(elenco);
   if (vazia()) {
       primeiro = novo;
   } else {
    noh* aux = primeiro;
    while (aux->proximo != NULL) {
        aux = aux->proximo;
    }
    aux->proximo = novo;
   }
   tamanho++;
}

// insere no início da lista
void lista::insereNoInicio(equipe elenco) {
 noh* novo = new noh(elenco);
 if (vazia()) {
   primeiro = novo;
   } else {
       novo->proximo = primeiro;
       primeiro = novo;
   }
   tamanho++;
}

// insere em uma determinada posição da lista
void lista::insereNaPosicao(int posicao, equipe elenco){
   if(posicao < 0 || posicao > tamanho) {
       cout << "Posição Inexistente!" << endl;
       return;
   }

   if(posicao == 0){
       insereNoInicio(elenco);
       return;
   }

   if(posicao == tamanho){
       insereNoFim(elenco);
       return;
   }

   noh* novo = new noh(elenco);
   noh* aux = primeiro;
   for(int i = 0; i < posicao - 1; i++){
       aux = aux->proximo;
   }
   novo->proximo = aux->proximo;
   aux->proximo = novo;
   tamanho++;
}

//procura a posição de um determinado elemento
int lista::procura(string valor) {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    } 
    noh* aux = primeiro;
    int pos = 0;
    while (aux != NULL) {
       if (aux->elenco.nomeEquipe == valor) {
           return pos;
       }
       aux = aux->proximo;
       pos++;
    }
    return -1;
}


// método básico que *percorre* uma lista, imprimindo seus elementos
// poderia percorrer fazendo outra ação (multiplicando valores, por exemplo)
void lista::imprime() {
    if (vazia()) {
        cout << "Lista vazia!" << endl;
        return;
    } 

    noh* aux = primeiro;
    while (aux != NULL) {
       cout << "(" << aux->elenco.nomeEquipe << ", "
            << aux->elenco.lider << ", "
            << aux->elenco.linguagem << ", "
            << aux->elenco.qtdMembros << ")" << endl;
       aux = aux->proximo;
    }
}

// verifica se a lista está vazia
inline bool lista::vazia() {
    return (primeiro == NULL);
}
   
void lista::removeNoFim() {
   if (vazia()) {
       cout << "Remoção em lista vazia!" << endl;
       return;
   }

   if (primeiro->proximo == NULL){
    delete primeiro;
       primeiro = NULL;
   } else {
       noh* anterior = primeiro;
       noh* atual = primeiro->proximo;
       while (atual->proximo != NULL) {
            anterior = atual;
           atual = atual->proximo;
       }
       delete atual;
       anterior->proximo = NULL;
   }
   tamanho--;
}
    
void lista::removeNoInicio() {
   if (vazia()) {
       cout << "Remoção em lista vazia!" << endl;
       return;
   }

    noh* aux = primeiro->proximo;
    delete primeiro;
    primeiro = aux; 
   tamanho--;
}

int main() {
    lista minhaLista;
    equipe info;
    char comando;
    int posicao;
    string nomeEquipe;

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir no Inicio
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoInicio(info);
                    break;
                case 'h': // inserir no Fim
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoFim(info);
                    break;             
                case 'm': // inserir Na Posição
                    cin >> posicao;
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNaPosicao(posicao,info);
                    break;             
                case 's': // Busca por equipe
                    cin >> nomeEquipe;
                    if (minhaLista.vazia()) {
                       cout << "Lista vazia!" << endl;
                   } else {
                       int pos = minhaLista.procura(nomeEquipe);
                       if (pos == -1){
                           cout << "Nao encontrado" << endl;
                       } else {
                           cout << pos << endl;
                       }
                   }
                    break;                    
                case 'r': // remover no Inicio
                    minhaLista.removeNoInicio();
                    break;
                case 'a': // remover no Fim
                    minhaLista.removeNoFim();
                    break;                                   
                case 'p': // limpar tudo
                    minhaLista.imprime();
                    break;
                case 'f': // finalizar
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    cout << endl;
    return 0;
}
