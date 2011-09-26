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
		void ExpandirEsquerda(Node* aNode);
		void ExpandirDireita(Node* aNode);
		void Expandir(Node* aNode);		
		void criaNoInicial();
	public:
		BuscaLargura();	
		void Initialize(Estado* aEstadoInicial,  Estado* aEstadoObjetivo);
		void Execute();
		Fronteira* getFronteira();	
		void ExpandeFronteira();
};

BuscaLargura::BuscaLargura(){
	this->raizArvore = NULL;
}

void BuscaLargura::Execute(){
	bool completed=false;
	Estado* actual;	
	
	while((!this->getFronteira()->isEmpty())&&(!completed)){
		this->ExpandeFronteira();
		this->getFronteira()->first();
		
		actual = this->getFronteira()->getNode()->getEstado();
		
		completed = actual->IsSame(this->objetivo);		
	}
	
	if (completed){
		cout << "ACHOU!!";
	}
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
	
	node->setParentNode(NULL);	
	
	this->raizArvore = node;		
}

void BuscaLargura::Initialize(Estado* aEstadoInicial,  Estado* aEstadoObjetivo){
	this->inicial = aEstadoInicial;
	this->objetivo = aEstadoObjetivo;	
	this->criaNoInicial();	
	
	this->fronteira.addNode(this->raizArvore);	
	
	
}

void BuscaLargura::Expandir(Node* aNode){	
	if(aNode->getEstado()->HasBoatLeft()){
		this->ExpandirEsquerda(aNode);
	}
	
	if(aNode->getEstado()->HasBoatRight()){
		this->ExpandirDireita(aNode);
	}
}

Fronteira* BuscaLargura::getFronteira(){
	return &this->fronteira;
}

void BuscaLargura::ExpandeFronteira(){		
	this->Expandir(this->getFronteira()->RemovePrimeiro());
}

void BuscaLargura::ExpandirEsquerda(Node* aNode){
	Node * node;
	if(aNode->getEstado()->getMissionaryLeft()>=2){
		node = new Node(aNode->getEstado()->getMissionaryLeft()-2,
						aNode->getEstado()->getCannibalLeft(),
						aNode->getEstado()->getMissionaryRight()+2,
						aNode->getEstado()->getCannibalRight(),
						aNode->getEstado()->getBoatLeft()-1,
						aNode->getEstado()->getBoatRight()+1);
						
		node->setParentNode(aNode);
		aNode->insertChild(node);
		this->fronteira.addNode(node);
	}
	
	if(aNode->getEstado()->getCannibalLeft()>=2){
		node = new Node(aNode->getEstado()->getMissionaryLeft(),
						aNode->getEstado()->getCannibalLeft()-2,
						aNode->getEstado()->getMissionaryRight(),
						aNode->getEstado()->getCannibalRight()+2,
						aNode->getEstado()->getBoatLeft()-1,
						aNode->getEstado()->getBoatRight()+1);
						
		node->setParentNode(aNode);
		aNode->insertChild(node);
		this->fronteira.addNode(node);
	}		
	
	if(aNode->getEstado()->getMissionaryLeft()>=1){
		if(aNode->getEstado()->getCannibalLeft()>=1){
			node = new Node(aNode->getEstado()->getMissionaryLeft()-1,
							aNode->getEstado()->getCannibalLeft()-1,
							aNode->getEstado()->getMissionaryRight()+1,
							aNode->getEstado()->getCannibalRight()+1,
							aNode->getEstado()->getBoatLeft()-1,
							aNode->getEstado()->getBoatRight()+1);											
			node->setParentNode(aNode);
			aNode->insertChild(node);
			this->fronteira.addNode(node);								
		}
		
		node = new Node(aNode->getEstado()->getMissionaryLeft()-1,
						aNode->getEstado()->getCannibalLeft(),
						aNode->getEstado()->getMissionaryRight()+1,
						aNode->getEstado()->getCannibalRight(),
						aNode->getEstado()->getBoatLeft()-1,
						aNode->getEstado()->getBoatRight()+1);
		
		node->setParentNode(aNode);
		aNode->insertChild(node);
		this->fronteira.addNode(node);
	}
	
	if(aNode->getEstado()->getCannibalLeft()>=1){
		node = new Node(aNode->getEstado()->getMissionaryLeft(),
						aNode->getEstado()->getCannibalLeft()-1,
						aNode->getEstado()->getMissionaryRight(),
						aNode->getEstado()->getCannibalRight()+1,
						aNode->getEstado()->getBoatLeft()-1,
						aNode->getEstado()->getBoatRight()+1);											
		node->setParentNode(aNode);
		aNode->insertChild(node);		
		this->fronteira.addNode(node);								
	}		
}

void BuscaLargura::ExpandirDireita(Node* aNode){
	Node * node;
	if(aNode->getEstado()->getMissionaryRight()>=2){
		node = new Node(aNode->getEstado()->getMissionaryLeft()+2,
						aNode->getEstado()->getCannibalLeft(),
						aNode->getEstado()->getMissionaryRight()-2,
						aNode->getEstado()->getCannibalRight(),
						aNode->getEstado()->getBoatLeft()+1,
						aNode->getEstado()->getBoatRight()-1);
						
		node->setParentNode(aNode);
		aNode->insertChild(node);
		this->fronteira.addNode(node);
	}
	
	if(aNode->getEstado()->getCannibalRight()>=2){
		node = new Node(aNode->getEstado()->getMissionaryLeft(),
						aNode->getEstado()->getCannibalLeft()+2,
						aNode->getEstado()->getMissionaryRight(),
						aNode->getEstado()->getCannibalRight()-2,
						aNode->getEstado()->getBoatLeft()+1,
						aNode->getEstado()->getBoatRight()-1);
						
		node->setParentNode(aNode);
		aNode->insertChild(node);
		this->fronteira.addNode(node);
	}		
	
	if(aNode->getEstado()->getMissionaryRight()>=1){
		if(aNode->getEstado()->getCannibalRight()>=1){
			node = new Node(aNode->getEstado()->getMissionaryLeft()+1,
							aNode->getEstado()->getCannibalLeft()+1,
							aNode->getEstado()->getMissionaryRight()-1,
							aNode->getEstado()->getCannibalRight()-1,
							aNode->getEstado()->getBoatLeft()+1,
							aNode->getEstado()->getBoatRight()-1);											
			node->setParentNode(aNode);
			aNode->insertChild(node);
			this->fronteira.addNode(node);								
		}
		
		node = new Node(aNode->getEstado()->getMissionaryLeft()+1,
						aNode->getEstado()->getCannibalLeft(),
						aNode->getEstado()->getMissionaryRight()-1,
						aNode->getEstado()->getCannibalRight(),
						aNode->getEstado()->getBoatLeft()+1,
						aNode->getEstado()->getBoatRight()-1);
		
		node->setParentNode(aNode);
		aNode->insertChild(node);
		this->fronteira.addNode(node);
	}
	
	if(aNode->getEstado()->getCannibalRight()>=1){
		node = new Node(aNode->getEstado()->getMissionaryLeft(),
						aNode->getEstado()->getCannibalLeft()+1,
						aNode->getEstado()->getMissionaryRight(),
						aNode->getEstado()->getCannibalRight()-1,
						aNode->getEstado()->getBoatLeft()+1,
						aNode->getEstado()->getBoatRight()-1);											
		node->setParentNode(aNode);
		aNode->insertChild(node);		
		this->fronteira.addNode(node);								
	}	
}
