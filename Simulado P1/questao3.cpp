#include <iostream>

using namespace std;

struct dado {
	int elemento;
	dado *proximo;
};

class pilha{
	private:
		dado *topo;
	public:
		pilha(){
			topo = NULL;
		}
		void empilha (dado entrada){
			dado *novo = new dado;
			*novo = entrada;
			novo->proximo = topo;
			topo = novo;
		}
		int desempilha(){
			if (topo == nullptr) throw runtime_error("Pilha vazia!");
			int removido;
			dado *apagado = topo;
			removido = topo->elemento;
			topo = topo->proximo;
			apagado->proximo = nullptr;
			delete apagado;
			return removido;
		}
		~pilha(){
			while (topo != nullptr)
				desempilha();
		}		
		void inverte(){
            pilha aux1, aux2;
	
            while (topo != nullptr){
                dado temp;
                temp.elemento = desempilha();
                aux1.empilha(temp);
            }
            
            while (aux1.topo != nullptr){
                dado temp;
                temp.elemento = aux1.desempilha();
                aux2.empilha(temp);
            }
            
            while (aux2.topo != nullptr){
                dado temp;
                temp.elemento = aux2.desempilha();
                empilha(temp);
            }
		}
		void imprime(){
            pilha aux;

	while (topo != nullptr){
		dado temp;
		temp.elemento = desempilha();
		cout << temp.elemento << " ";
		aux.empilha(temp);
	}
	    cout << endl;

	while (aux.topo != nullptr){
		dado temp;
		temp.elemento = aux.desempilha();
		empilha(temp);
	}
		}		
	};
int main(){
	int tamanho;
	cin >> tamanho;
	dado entrada;
	pilha mp;
	for (int i=0; i<tamanho; i++){
		cin>>entrada.elemento;
		mp.empilha(entrada);
	}
	mp.inverte();
	mp.imprime();
	return 0;
}