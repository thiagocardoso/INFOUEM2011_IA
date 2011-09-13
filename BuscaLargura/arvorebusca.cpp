#include <list>
using namespace std;

class Node{
	private:
		std::list<Node*> nodeList;
		std::list<Node*>::iterator it;
		Estado state;
		Node* parentNode;
	public:
		Node(int missionaryLeft, int cannibalLeft, int missionaryRight, 
			int cannibalRight, int boatLeft, int boatRight);
		void insertChild(Node* aNode);
		void firstChild();
		void nextChild();
		void lastChild();
		void priorChild();
		Node* getParentNode();
		Node* getChild();
		void setParentNode(Node* parent);
};

Node::Node(int missionaryLeft, int cannibalLeft, int missionaryRight, 
	int cannibalRight, int boatLeft, int boatRight){
	
	this->firstChild();
	this->state.setCannibalLeft(cannibalLeft);
	this->state.setCannibalRight(cannibalRight);
	this->state.setMissionaryLeft(missionaryLeft);
	this->state.setMissionaryRight(missionaryLeft);
	this->state.setBoatLeft(boatLeft);
	this->state.setBoatRight(boatRight);
}

void Node::insertChild(Node* aNode){
	this->nodeList.push_back(aNode);
}

void Node::firstChild(){
	this->it = this->nodeList.begin();
}

void Node::nextChild(){
	this->it++;
}

void Node::lastChild(){
	this->it = this->nodeList.end();
}

void Node::priorChild(){
	this->it--;
}

Node* Node::getParentNode(){
	return this->parentNode;
}

void Node::setParentNode(Node* parent){
	this->parentNode = parent;
}

Node* Node::getChild(){
	std::list<Node*>::iterator elem;

	elem = this->it;

	return *elem;		
}
