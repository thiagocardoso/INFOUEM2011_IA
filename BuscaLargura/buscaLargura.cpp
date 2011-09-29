#include "estados.cpp"
#include "arvorebusca.cpp"
#include "fronteira.cpp"
#include <stdio.h>
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
		void Sucess(Node* aResult);
		void ViagemParaEsquerda(Node* Parent, int Missionarios, int Canibais);
		void ViagemParaDireita(Node* Parent, int Missionarios, int Canibais);
		void Viagem(Node* Parent, int Missionarios, int Canibais, int BarcoEsquerda, int BarcoDireita);		
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

void BuscaLargura::Sucess(Node* aResult){
	cout << "ACHOU!!";
}

void BuscaLargura::Execute(){
	bool completed=false;
	Node* actual;	
	int a;
	
	while((!this->getFronteira()->isEmpty())&&(!completed)){
		this->ExpandeFronteira();
		this->getFronteira()->first();
		
		actual = this->getFronteira()->getNode();
		
		actual->getEstado()->printInfo();
		
		//getchar();
		completed = actual->getEstado()->IsSame(this->objetivo);		
	}
	
	if (completed){
		Sucess(actual);
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

void BuscaLargura::Viagem(Node* Parent, int Missionarios, int Canibais, int BarcoEsquerda, int BarcoDireita){
	Node* node;
	bool result=false;
	int missionariosLeft=Missionarios;
	int missionariosRight=Missionarios;
	int canibaisLeft=Canibais;
	int canibaisRight=Canibais;
	
	if (BarcoEsquerda<0){
		missionariosLeft = missionariosLeft * (-1);		
		canibaisLeft = canibaisLeft * (-1);
	}else{		
		missionariosRight = missionariosRight * (-1);
		canibaisRight = canibaisRight * (-1);
	}	
	
	node = new Node(Parent->getEstado()->getMissionaryLeft() + missionariosLeft,
				Parent->getEstado()->getCannibalLeft() + canibaisLeft,
				Parent->getEstado()->getMissionaryRight() + missionariosRight,
				Parent->getEstado()->getCannibalRight() + canibaisRight,
				Parent->getEstado()->getBoatLeft() + BarcoEsquerda,
				Parent->getEstado()->getBoatRight() + BarcoDireita);	
				
	result = (!(node->getEstado()->getCannibalLeft() > node->getEstado()->getMissionaryLeft()))&&(!(node->getEstado()->getCannibalRight() > node->getEstado()->getMissionaryRight()));
	
	if (Parent->getParentNode()!=NULL){
		result = result && (!node->getEstado()->IsSame(Parent->getParentNode()->getEstado()));
	}
	
	if (result){
		node->setParentNode(Parent);		
		Parent->insertChild(node);
		this->fronteira.addNode(node);
	}					
}

void BuscaLargura::ViagemParaEsquerda(Node* Parent, int Missionarios, int Canibais){
	this->Viagem(Parent, Missionarios, Canibais, +1, -1);
}

void BuscaLargura::ViagemParaDireita(Node* Parent, int Missionarios, int Canibais){
	this->Viagem(Parent, Missionarios, Canibais, -1, +1);
}

void BuscaLargura::ExpandirEsquerda(Node* aNode){
	Node * node;
	if(aNode->getEstado()->getMissionaryLeft()>=2){
		this->ViagemParaDireita(aNode,2,0);
		/*
		node = new Node(aNode->getEstado()->getMissionaryLeft()-2,
						aNode->getEstado()->getCannibalLeft(),
						aNode->getEstado()->getMissionaryRight()+2,
						aNode->getEstado()->getCannibalRight(),
						aNode->getEstado()->getBoatLeft()-1,
						aNode->getEstado()->getBoatRight()+1);
						
		if ((!(node->getEstado()->getCannibalLeft() > node->getEstado()->getMissionaryLeft()))&&
			(!(node->getEstado()->getCannibalRight() > node->getEstado()->getMissionaryRight()))&&
			(!node->getEstado()->IsSame(aNode->getParentNode()->getEstado()))
			){
			node->setParentNode(aNode);		
			aNode->insertChild(node);
			this->fronteira.addNode(node);
		}
		*/ 
	}
	
	if(aNode->getEstado()->getCannibalLeft()>=2){
		this->ViagemParaDireita(aNode,0,2);
		/*
		node = new Node(aNode->getEstado()->getMissionaryLeft(),
						aNode->getEstado()->getCannibalLeft()-2,
						aNode->getEstado()->getMissionaryRight(),
						aNode->getEstado()->getCannibalRight()+2,
						aNode->getEstado()->getBoatLeft()-1,
						aNode->getEstado()->getBoatRight()+1);
						
		if ((!(node->getEstado()->getCannibalLeft() > node->getEstado()->getMissionaryLeft()))&&
			(!(node->getEstado()->getCannibalRight() > node->getEstado()->getMissionaryRight()))&&
			(!node->getEstado()->IsSame(aNode->getParentNode()->getEstado()))
			){
			node->setParentNode(aNode);		
			aNode->insertChild(node);
			this->fronteira.addNode(node);
		}
		*/ 
	}		
	
	if(aNode->getEstado()->getMissionaryLeft()>=1){		
		if(aNode->getEstado()->getCannibalLeft()>=1){
			this->ViagemParaDireita(aNode,1,1);
			/*
			node = new Node(aNode->getEstado()->getMissionaryLeft()-1,
							aNode->getEstado()->getCannibalLeft()-1,
							aNode->getEstado()->getMissionaryRight()+1,
							aNode->getEstado()->getCannibalRight()+1,
							aNode->getEstado()->getBoatLeft()-1,
							aNode->getEstado()->getBoatRight()+1);											
			if ((!(node->getEstado()->getCannibalLeft() > node->getEstado()->getMissionaryLeft()))&&
			(!(node->getEstado()->getCannibalRight() > node->getEstado()->getMissionaryRight()))&&
			(!node->getEstado()->IsSame(aNode->getParentNode()->getEstado()))
			){
				node->setParentNode(aNode);		
				aNode->insertChild(node);
				this->fronteira.addNode(node);
			}
			*/ 
		}
		
		this->ViagemParaDireita(aNode,1,0);
		/*
		node = new Node(aNode->getEstado()->getMissionaryLeft()-1,
						aNode->getEstado()->getCannibalLeft(),
						aNode->getEstado()->getMissionaryRight()+1,
						aNode->getEstado()->getCannibalRight(),
						aNode->getEstado()->getBoatLeft()-1,
						aNode->getEstado()->getBoatRight()+1);
		
		if ((!(node->getEstado()->getCannibalLeft() > node->getEstado()->getMissionaryLeft()))&&
			(!(node->getEstado()->getCannibalRight() > node->getEstado()->getMissionaryRight()))&&
			(!node->getEstado()->IsSame(aNode->getParentNode()->getEstado()))
			){
			node->setParentNode(aNode);		
			aNode->insertChild(node);
			this->fronteira.addNode(node);
		}
		*/ 
	}
	
	if(aNode->getEstado()->getCannibalLeft()>=1){
		this->ViagemParaDireita(aNode, 0, 1);
		/*
		node = new Node(aNode->getEstado()->getMissionaryLeft(),
						aNode->getEstado()->getCannibalLeft()-1,
						aNode->getEstado()->getMissionaryRight(),
						aNode->getEstado()->getCannibalRight()+1,
						aNode->getEstado()->getBoatLeft()-1,
						aNode->getEstado()->getBoatRight()+1);											
		if ((!(node->getEstado()->getCannibalLeft() > node->getEstado()->getMissionaryLeft()))&&
			(!(node->getEstado()->getCannibalRight() > node->getEstado()->getMissionaryRight()))&&
			(!node->getEstado()->IsSame(aNode->getParentNode()->getEstado()))
			){
			node->setParentNode(aNode);		
			aNode->insertChild(node);
			this->fronteira.addNode(node);
		}
		*/ 							
	}		
}

void BuscaLargura::ExpandirDireita(Node* aNode){
	Node * node;
	if(aNode->getEstado()->getMissionaryRight()>=2){
		this->ViagemParaEsquerda(aNode,2,0);
		/*
		node = new Node(aNode->getEstado()->getMissionaryLeft()+2,
						aNode->getEstado()->getCannibalLeft(),
						aNode->getEstado()->getMissionaryRight()-2,
						aNode->getEstado()->getCannibalRight(),
						aNode->getEstado()->getBoatLeft()+1,
						aNode->getEstado()->getBoatRight()-1);
		
		if ((!(node->getEstado()->getCannibalLeft() > node->getEstado()->getMissionaryLeft()))&&
			(!(node->getEstado()->getCannibalRight() > node->getEstado()->getMissionaryRight()))&&
			(!node->getEstado()->IsSame(aNode->getParentNode()->getEstado()))
			){
			node->setParentNode(aNode);		
			aNode->insertChild(node);
			this->fronteira.addNode(node);
		}
		*/ 
	}
	
	if(aNode->getEstado()->getCannibalRight()>=2){
		this->ViagemParaEsquerda(aNode,0,2);
		/*
		node = new Node(aNode->getEstado()->getMissionaryLeft(),
						aNode->getEstado()->getCannibalLeft()+2,
						aNode->getEstado()->getMissionaryRight(),
						aNode->getEstado()->getCannibalRight()-2,
						aNode->getEstado()->getBoatLeft()+1,
						aNode->getEstado()->getBoatRight()-1);
						
		if ((!(node->getEstado()->getCannibalLeft() > node->getEstado()->getMissionaryLeft()))&&
			(!(node->getEstado()->getCannibalRight() > node->getEstado()->getMissionaryRight()))&&
			(!node->getEstado()->IsSame(aNode->getParentNode()->getEstado()))
			){
			node->setParentNode(aNode);		
			aNode->insertChild(node);
			this->fronteira.addNode(node);
		}
		*/ 
	}		
	
	if(aNode->getEstado()->getMissionaryRight()>=1){
		if(aNode->getEstado()->getCannibalRight()>=1){
			this->ViagemParaEsquerda(aNode,1,1);
			/*
			node = new Node(aNode->getEstado()->getMissionaryLeft()+1,
							aNode->getEstado()->getCannibalLeft()+1,
							aNode->getEstado()->getMissionaryRight()-1,
							aNode->getEstado()->getCannibalRight()-1,
							aNode->getEstado()->getBoatLeft()+1,
							aNode->getEstado()->getBoatRight()-1);											
			if ((!(node->getEstado()->getCannibalLeft() > node->getEstado()->getMissionaryLeft()))&&
			(!(node->getEstado()->getCannibalRight() > node->getEstado()->getMissionaryRight()))&&
			(!node->getEstado()->IsSame(aNode->getParentNode()->getEstado()))
			){
				node->setParentNode(aNode);		
				aNode->insertChild(node);
				this->fronteira.addNode(node);
			}
			*/
		}
		
		this->ViagemParaEsquerda(aNode,1,0);
		/*
		node = new Node(aNode->getEstado()->getMissionaryLeft()+1,
						aNode->getEstado()->getCannibalLeft(),
						aNode->getEstado()->getMissionaryRight()-1,
						aNode->getEstado()->getCannibalRight(),
						aNode->getEstado()->getBoatLeft()+1,
						aNode->getEstado()->getBoatRight()-1);
		
		if ((!(node->getEstado()->getCannibalLeft() > node->getEstado()->getMissionaryLeft()))&&
			(!(node->getEstado()->getCannibalRight() > node->getEstado()->getMissionaryRight()))&&
			(!node->getEstado()->IsSame(aNode->getParentNode()->getEstado()))
			){
			node->setParentNode(aNode);		
			aNode->insertChild(node);
			this->fronteira.addNode(node);
		}
		*/ 
	}
	
	if(aNode->getEstado()->getCannibalRight()>=1){
		this->ViagemParaEsquerda(aNode,0,1);
		/*
		node = new Node(aNode->getEstado()->getMissionaryLeft(),
						aNode->getEstado()->getCannibalLeft()+1,
						aNode->getEstado()->getMissionaryRight(),
						aNode->getEstado()->getCannibalRight()-1,
						aNode->getEstado()->getBoatLeft()+1,
						aNode->getEstado()->getBoatRight()-1);											
		if ((!(node->getEstado()->getCannibalLeft() > node->getEstado()->getMissionaryLeft()))&&
			(!(node->getEstado()->getCannibalRight() > node->getEstado()->getMissionaryRight()))&&
			(!node->getEstado()->IsSame(aNode->getParentNode()->getEstado()))
			){
			node->setParentNode(aNode);		
			aNode->insertChild(node);
			this->fronteira.addNode(node);
		}
		*/
	}	
}
