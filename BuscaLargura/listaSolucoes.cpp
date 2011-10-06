using namespace std;

class ListaSolucoes{
	private:
		std::list<Node*> list;	
		std::list<Node*>::iterator it;		
	public:		
		ListaSolucoes();
		void inserirSolucao(Node* solucao);
		void removerSolucao(Node* solucao);		
		void next();
		void prior();
		void first();
		void last();
		bool eof();		
		bool existeSolucao(Node* solucao);		
		bool comparaSolucoes(Node* solucao1, Node* solucao2);
		int size();
		int numeroPassosSolucao(Node* solucao);
		Node* getSolucao();
		void printSolucao();		
};

ListaSolucoes::ListaSolucoes(){
	this->first();
}

void ListaSolucoes::printSolucao(){
	Node* actual = this->getSolucao();
	std::list<Node*> list;
	std::list<Node*>::iterator it;	
	
	it = list.begin();
	
	while(actual!=NULL){		
		//if (actual->getEstado()->getViagemOrigem()!=NULL){
		//	actual->getEstado()->getViagemOrigem()->printViagem();
		//}
		//actual->getEstado()->printInfo();
		list.push_back(actual);
		
		actual = actual->getParentNode();
	}	
	
	it = list.end();
	it--;
	while(it!=list.begin()){
		actual = *it;
		if (actual->getEstado()->getViagemOrigem()!=NULL){
			actual->getEstado()->getViagemOrigem()->printViagem();
		}
		actual->getEstado()->printInfo();
		it--;
		
		if(it==list.begin()){
			actual = *it;
			if (actual->getEstado()->getViagemOrigem()!=NULL){
			actual->getEstado()->getViagemOrigem()->printViagem();
			}
			actual->getEstado()->printInfo();
		}
	}
}

int ListaSolucoes::size(){
	return this->list.size();
}

void ListaSolucoes::inserirSolucao(Node* solucao){
	this->list.push_back(solucao);
}

void ListaSolucoes::removerSolucao(Node* solucao){
	this->list.remove(solucao);
}

int ListaSolucoes::numeroPassosSolucao(Node* solucao){
	int i=0;
	Node* actual;
	
	actual = solucao;
	
	while (actual!=NULL){		
		i++;
		actual= actual->getParentNode();
	}
	return i;
}

bool ListaSolucoes::comparaSolucoes(Node* solucao1, Node* solucao2){
	bool result=false;		
	Node* node1=solucao1;
	Node* node2=solucao2;
	result = this->numeroPassosSolucao(node1)==this->numeroPassosSolucao(node2);
	
	if (result){
		while((node1!=NULL)&&(node2!=NULL)&&(result)){
			result=node1->getEstado()->IsSame(node2->getEstado());
			
			if(result){
				node1=node1->getParentNode();
				node2=node2->getParentNode();
			}
		}
	}	
	return result;
}

bool ListaSolucoes::existeSolucao(Node* solucao){
	bool result=false;
	
	this->first();
	while (!this->eof()&&(!result)){
		result = this->comparaSolucoes(this->getSolucao(), solucao);
		
		if (!result){
			this->next();
		}
	}
	return result;
}

void ListaSolucoes::next(){
	if (!this->eof()){		
		this->it++;
	}	
}

void ListaSolucoes::prior(){
	if (this->it != this->list.begin()){
		this->it--;
	}	
}

void ListaSolucoes::first(){
	this->it = this->list.begin();
}

void ListaSolucoes::last(){
	this->it = this->list.end();
	this->it--;	
}

bool ListaSolucoes::eof(){
	return this->it==this->list.end();
}

Node* ListaSolucoes::getSolucao(){
	std::list<Node*>::iterator elem;
	
	elem = this->it;
	
	return *elem;		
}
