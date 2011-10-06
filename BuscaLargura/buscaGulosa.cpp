using namespace std;

class BuscaGulosa: public BuscaLargura{
	protected:
		Node* getBestNode();
	public:
		virtual void Execute();
		virtual void ExpandeFronteira();	
};

void BuscaGulosa::Execute(){
	bool completed=false;
	Node* actual;	
	int a;
	
	while((!this->getFronteira()->isEmpty())&&(!completed)){		
		actual = this->getBestNode();						
		
		completed = actual->getEstado()->IsSame(this->objetivo);		
		
		if(!completed){
			this->getFronteira()->RemoveNode(actual);
			this->Expandir(actual);			
			//actual->getEstado()->printInfo();
			
		}
	}
	
	if (completed){
	//	Sucess(actual);
		this->getSolucoes()->inserirSolucao(actual);
	}	
}

void BuscaGulosa::ExpandeFronteira(){
	this->Expandir(this->getBestNode());	
}

Node* BuscaGulosa::getBestNode(){
	Node* node;
	
	this->getFronteira()->first();	
	node = this->getFronteira()->getNode();
	
	while (!this->getFronteira()->eof()){
		if (this->getFronteira()->getNode()->getEstado()->getMissionaryLeft() < node->getEstado()->getMissionaryLeft()){
			node = this->getFronteira()->getNode();
		}
		
		this->getFronteira()->nextNode();
	}	
	return node;
}
