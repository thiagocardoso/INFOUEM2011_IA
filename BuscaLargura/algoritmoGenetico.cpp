#include <stdlib.h>
#include <time.h>
using namespace std;

class AlgoritmoGenetico{
	private:
		ListaSolucoes* populacao;
		Node* melhorSolucao;
		int taxaMutacao;
		int maxGeracoes;
	protected:
		void Mutacao(Node* node);
		Node* Reproduz(Node* parent1, Node* parent2);
		Node* Selecao(); 
		void buscaMelhorSolucao();
		bool sofreMutacao();		
	public:
		AlgoritmoGenetico(int TaxaMutacao, int MaxGeracoes);
		void Execute();
		void setPopulacao(ListaSolucoes* lista);
		ListaSolucoes* getPopulacao();
		int getMaxGeracoes();
		int getTaxaMutacao();
		Node* getMelhorSolucao();
};

AlgoritmoGenetico::AlgoritmoGenetico(int TaxaMutacao, int MaxGeracoes){
	this->taxaMutacao=TaxaMutacao;
	this->maxGeracoes=MaxGeracoes;
	this->melhorSolucao=NULL;
}

void AlgoritmoGenetico::buscaMelhorSolucao(){	
	this->populacao->first();
	this->melhorSolucao = this->populacao->getSolucao();
	this->populacao->next();
	while(!(this->populacao->eof())){
		if((this->populacao->numeroPassosSolucao(this->melhorSolucao))
			>(this->populacao->numeroPassosSolucao(this->populacao->getSolucao()))){
			this->melhorSolucao = this->populacao->getSolucao();
		}
		this->populacao->next();		
	}
}

Node* AlgoritmoGenetico::getMelhorSolucao(){
	return this->melhorSolucao;
}

void AlgoritmoGenetico::Execute(){
	Node* x = NULL;
	Node* y = NULL;
	Node* filho = NULL;
	int i=0;
	
	this->buscaMelhorSolucao();
	
	while(i<this->maxGeracoes){
		x = this->Selecao();
		y = this->Selecao();
		
		filho = Reproduz(x, y);
		
		if (this->sofreMutacao()){
			this->Mutacao(filho);
		}
		
		if (filho!=NULL){
			if(!(this->populacao->existeSolucao(filho))){
				this->populacao->inserirSolucao(filho);
			
				if ((this->populacao->numeroPassosSolucao(filho))
					<(this->populacao->numeroPassosSolucao(this->melhorSolucao))){
						this->melhorSolucao = filho;
				}			
			}
		}		
		i++;
	}
}

bool AlgoritmoGenetico::sofreMutacao(){
	return false;
}

void AlgoritmoGenetico::setPopulacao(ListaSolucoes* lista){
	this->populacao = lista;
}

ListaSolucoes* AlgoritmoGenetico::getPopulacao(){
	return this->populacao;
}

void AlgoritmoGenetico::Mutacao(Node* node){	
	node = NULL;
}

Node* AlgoritmoGenetico::Reproduz(Node* parent1, Node* parent2){
}

Node* AlgoritmoGenetico::Selecao(){
	int i;
	srand(this->populacao->size());
	
	i = rand() % this->populacao->size();
	
	return this->populacao->getSolucaoByIndex(i);
}

int AlgoritmoGenetico::getMaxGeracoes(){
	return this->maxGeracoes;
}

int AlgoritmoGenetico::getTaxaMutacao(){
	return this->taxaMutacao;
}
