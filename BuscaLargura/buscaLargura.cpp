#include "viagem.cpp"
#include "estados.cpp"
#include "arvorebusca.cpp"
#include "fronteira.cpp"
#include <stdio.h>
#include "listaSolucoes.cpp"
using namespace std;

class BuscaLargura{
	private:
		Node* raizArvore;
		Fronteira fronteira;
		ListaSolucoes listaSolucoes;
		bool listarSolucoes;
		int maxSolucoes;
	protected:
		Estado* inicial;
		Estado* objetivo;	
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
		bool getListarSolucoes();
		void setListarSolucoes(bool value);
		void Initialize(Estado* aEstadoInicial,  Estado* aEstadoObjetivo);
		virtual void Execute();
		virtual void ExpandeFronteira();		
		Fronteira* getFronteira();	
		ListaSolucoes* getSolucoes();		
		int getMaxSolucoes();
		void setMaxSolucoes(int value);
};

BuscaLargura::BuscaLargura(){
	this->raizArvore = NULL;
	this->listarSolucoes = false;
}

ListaSolucoes* BuscaLargura::getSolucoes(){
	return &this->listaSolucoes;
}

int BuscaLargura::getMaxSolucoes(){
	return this->maxSolucoes;
}

void BuscaLargura::setMaxSolucoes(int value){
	this->maxSolucoes=value;
}

bool BuscaLargura::getListarSolucoes(){
	return this->listarSolucoes;
}

void BuscaLargura::setListarSolucoes(bool value){
	this->listarSolucoes = value;
}

void BuscaLargura::Sucess(Node* aResult){
	//cout << "ACHOU!!";
	Node* actual = aResult;
	
	
	while(actual!=NULL){
		actual->getEstado()->printInfo();
	
		actual = actual->getParentNode();
	}	
}

void BuscaLargura::Execute(){
	bool completed=false;
	Node* actual;	
	int a;
	
	while((!this->getFronteira()->isEmpty())&&(!completed)){
		this->ExpandeFronteira();
		this->getFronteira()->first();
		
		actual = this->getFronteira()->getNode();
		
		//actual->getEstado()->printInfo();
		
		//getchar();
		//completed = actual->getEstado()->IsSame(this->objetivo);		
		if (actual->getEstado()->IsSame(this->objetivo)){
			if (this->listarSolucoes){
				if(!this->listaSolucoes.existeSolucao(actual)){
					this->listaSolucoes.inserirSolucao(actual);
				}				
				
				this->getFronteira()->RemoveNode(actual);
				
				completed = this->listaSolucoes.size()==this->getMaxSolucoes();
			}else{
				completed=true;
			}
		}		
	}
	
	if ((completed)&&(!this->listarSolucoes)){
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
	bool result=true;
	ViagemAbs* viagemOrigem;
	int missionariosLeft=Missionarios;
	int missionariosRight=Missionarios;
	int canibaisLeft=Canibais;
	int canibaisRight=Canibais;
	
	if (BarcoEsquerda<0){
		missionariosLeft = missionariosLeft * (-1);		
		canibaisLeft = canibaisLeft * (-1);
		viagemOrigem = new ViagemIda(Missionarios, Canibais);
	}else{		
		missionariosRight = missionariosRight * (-1);
		canibaisRight = canibaisRight * (-1);
		viagemOrigem = new ViagemVolta(Missionarios, Canibais);
	}	
	
	node = new Node(Parent->getEstado()->getMissionaryLeft() + missionariosLeft,
				Parent->getEstado()->getCannibalLeft() + canibaisLeft,
				Parent->getEstado()->getMissionaryRight() + missionariosRight,
				Parent->getEstado()->getCannibalRight() + canibaisRight,
				Parent->getEstado()->getBoatLeft() + BarcoEsquerda,
				Parent->getEstado()->getBoatRight() + BarcoDireita);	
				
	if (node->getEstado()->getMissionaryLeft()>0){
		result = result && (!(node->getEstado()->getCannibalLeft() > node->getEstado()->getMissionaryLeft()));
	}
	
	if (node->getEstado()->getMissionaryRight()>0){
		result = result && (!(node->getEstado()->getCannibalRight() > node->getEstado()->getMissionaryRight()));	
	}	
	
	if (Parent->getParentNode()!=NULL){
		result = result && (!node->getEstado()->IsSame(Parent->getParentNode()->getEstado()));
	}
	
	if (result){
		node->getEstado()->setViagemOrigem(viagemOrigem);
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
