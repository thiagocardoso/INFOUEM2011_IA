using namespace std;

class ViagemAbs{
	private:
		int missionarios;
		int canibais;
	public:		
		void setMissionarios(int value);
		void setCanibais(int value);
		int getMissionarios();
		int getCanibais();
		virtual void printViagem()=0;
};

class ViagemIda: public ViagemAbs{
	public:
		ViagemIda(int vMissionarios, int vCanibais);
		void printViagem();
};

class ViagemVolta: public ViagemAbs{
	public:
		ViagemVolta(int vMissionarios, int vCanibais);
		void printViagem();
};

void ViagemAbs::setMissionarios(int value){
	this->missionarios=value;
}
	
void ViagemAbs::setCanibais(int value){
	this->canibais=value;
}

int ViagemAbs::getMissionarios(){
	return this->missionarios;
}

int ViagemAbs::getCanibais(){
	return this->canibais;
}

ViagemIda::ViagemIda(int vMissionarios, int vCanibais){
	this->setMissionarios(vMissionarios);
	this->setCanibais(vCanibais);
}

void ViagemIda::printViagem(){
	cout << "Ida -> M: " << this->getMissionarios() << " C: " << this->getCanibais() <<endl;
}

ViagemVolta::ViagemVolta(int vMissionarios, int vCanibais){
	this->setMissionarios(vMissionarios);
	this->setCanibais(vCanibais);
}

void ViagemVolta::printViagem(){
	cout << "Volta -> M: " << this->getMissionarios() << " C: " << this->getCanibais() <<endl;
}
