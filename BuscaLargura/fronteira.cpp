#include <list>
using namespace std;

class Fronteira{
	private:
		std::list<Node*> list;	
		std::list<Node*>::iterator it;
	public:
		Fronteira();
		void addNode(Node *value);
		void nextNode();
		void priorNode();
		void first();
		void last();
		bool eof();
		Node* getNode();
		std::list<Node*>::iterator getIterator();
};

Fronteira::Fronteira(){
	this->first();
}

void Fronteira::first(){
	this->it = this->list.begin();
}

void Fronteira::last(){
	this->it = this->list.end();
	this->it--;
}

void Fronteira::nextNode(){	
	if (!this->eof()){		
		this->it++;
	}
}

void Fronteira::priorNode(){
	if (this->it != this->list.begin()){
		this->it--;
	}	
}

bool Fronteira::eof(){		
	return this->it==this->list.end();
}

void Fronteira::addNode(Node *value){
	this->list.push_back(value);
}

std::list<Node*>::iterator Fronteira::getIterator(){
	return this->it;
}

Node* Fronteira::getNode(){
	std::list<Node*>::iterator elem;
	
	elem = this->it;
	
	return *elem;		
}
