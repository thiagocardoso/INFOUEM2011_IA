#include <list>
#include <string>
using namespace std;

class Estado{
	private:
		int cannibalLeft;
		int missionaryLeft;
		int cannibalRight;
		int missionaryRight;
		int boatLeft;
		int boatRight;	
	public:
		bool HasBoatLeft();
		bool HasBoatRight();		
		bool IsSame(Estado * aEstado);
		int getCannibalLeft();	
		int getMissionaryLeft();
		int getCannibalRight();
		int getMissionaryRight();	
		int getBoatLeft();
		int getBoatRight();	
		string AsString();
		void setCannibalLeft(int count);
		void setMissionaryLeft(int count);
		void setCannibalRight(int count);
		void setMissionaryRight(int count);			
		void setBoatLeft(int count);
		void setBoatRight(int count);	
		void printInfo();	
};

class ListaEstado{
	private:
		std::list<Estado*> stateList;
		std::list<Estado*>::iterator it;
	protected:
		bool existeEstado(Estado* aEstado);
	public:
		bool eof();
		void insertEstado(Estado* aEstado);		
		void first();
		void next();
		void last();
		void prior();	
		Estado* getEstado();
};

bool Estado::HasBoatLeft(){
	return this->boatLeft>0;
}

bool Estado::HasBoatRight(){
	return this->boatRight>0;
}

void Estado::setCannibalLeft(int count){
	this->cannibalLeft = count;
}

void Estado::setMissionaryLeft(int count){
	this->missionaryLeft = count;
}

void Estado::setCannibalRight(int count){
	this->cannibalRight = count;
}
	
void Estado::setMissionaryRight(int count){
	this->missionaryRight = count;
}

int Estado::getCannibalLeft(){
	return this->cannibalLeft;
}

int Estado::getMissionaryLeft(){
	return this->missionaryRight;
}

int Estado::getCannibalRight(){
	return this->cannibalRight;
}

int Estado::getMissionaryRight(){
	return this->missionaryRight;
}

int Estado::getBoatLeft(){
	return this->boatLeft;
}

int Estado::getBoatRight(){
	return this->boatRight;
}

void Estado::setBoatLeft(int count){
	this->boatLeft = count;
}

void Estado::setBoatRight(int count){
	this->boatRight = count;
}

bool Estado::IsSame(Estado * aEstado){
	return
	(aEstado->getCannibalLeft()==this->getCannibalLeft())&&
	(aEstado->getCannibalRight()==this->getCannibalRight())&&
	(aEstado->getMissionaryLeft()==this->getMissionaryLeft())&&
	(aEstado->getMissionaryRight()==this->getMissionaryRight())&&
	(aEstado->getBoatLeft()==this->getBoatLeft());
}

string Estado::AsString(){
	//
}

void Estado::printInfo(){
	cout << "ML:" << this->getMissionaryLeft();
	cout << "CL:" << this->getCannibalLeft();
	cout << "MR:" << this->getMissionaryRight();
	cout << "CR:" << this->getCannibalRight();
	if (this->HasBoatLeft()){		
		cout << "BP: ESQ";
	}else{
		if (this->HasBoatRight()){
			cout << "BP: DIR";
		}
	}
	cout << endl;	
}

Estado* ListaEstado::getEstado(){
	std::list<Estado*>::iterator elem;

	elem = this->it;

	return *elem;	
}

void ListaEstado::insertEstado(Estado* aEstado){
	if (!this->existeEstado(aEstado)){
		this->stateList.push_back(aEstado);
	}
}

bool ListaEstado::eof(){
	return this->it == this->stateList.begin();
}

bool ListaEstado::existeEstado(Estado* aEstado){
	bool result=false;
	Estado* actual;
	this->first();
	while((!this->eof())&&(!result)){
		actual = this->getEstado();
		result = actual->IsSame(aEstado);
		
		if (!result){
			this->next();
		}
	}
	return result;
}

void ListaEstado::first(){
	this->it = this->stateList.begin();
}

void ListaEstado::next(){
	this->it++;
}

void ListaEstado::last(){
	this->it = this->stateList.end();
}

void ListaEstado::prior(){
	this->it--;
}
