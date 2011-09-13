#include <list>
using namespace std;

class Fronteira{
	private:
		std::list<Node*> fronteira;
		std::list<Node*>::iterator it;
	public:
		bool eof();
		void insertNode(Node* aNode);		
		void deleteNode();
		void first();
		void next();
		void last();
		void prior();		
		Node* getNode();
};

bool Fronteira::eof(){
	return this->it==this->fronteira.end();
}

void Fronteira::insertNode(Node* aNode){
	this->fronteira.push_back(aNode);
}

void Fronteira::deleteNode(){
	this->fronteira.remove(this->getNode());
}

void Fronteira::first(){
	this->it = this->fronteira.begin();
}

void Fronteira::next(){
	this->it++;
}
	
void Fronteira::last(){
	this->it = this->fronteira.end();
}

void Fronteira::prior(){
	this->it--;
}

Node* Fronteira::getNode(){
	std::list<Node*>::iterator elem;

	elem = this->it;

	return *elem;		
}
