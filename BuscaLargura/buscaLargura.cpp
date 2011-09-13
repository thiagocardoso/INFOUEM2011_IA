#include "estados.cpp"
#include "arvorebusca.cpp"
#include "fronteira.cpp"
using namespace std;

class BuscaLargura{
	private:
		Node* raizArvore;
		Fronteira fronteira;
		Estado* inicial;
		Estado* objetivo;
	protected:
		void Expandir(Node* aNode);		
		void criaNoInicial();
	public:
		BuscaLargura();	
		void Execute(Estado* aEstadoInicial,  Estado* aEstadoObjetivo);
		Fronteira getFronteira();	
};

BuscaLargura::BuscaLargura(){
	this->raizArvore = NULL;
}

void BuscaLargura::criaNoInicial(){
	Node* node;	
	
	node = new Node(
		this->inicial->getMissionaryLeft(), 
		this->inicial->getCannibalLeft(), 
		this->inicial->getMissionaryRight(),
		this->inicial->getCannibalRight(),
		this->inicial->getBoatLeft(),
		this->inicial->getBoatRight()
	);
	this->raizArvore = node;
}

void BuscaLargura::Execute(Estado* aEstadoInicial,  Estado* aEstadoObjetivo){
	this->inicial = aEstadoInicial;
	this->objetivo = aEstadoObjetivo;	
	this->criaNoInicial();	
	
	this->fronteira.addNode(this->raizArvore);	
}

void BuscaLargura::Expandir(Node* aNode){
}

Fronteira BuscaLargura::getFronteira(){
	return this->fronteira;
}
