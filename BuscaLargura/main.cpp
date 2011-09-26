#include <iostream>
#include <string>
#include "buscaLargura.cpp"
using namespace std;

int main(){
	Estado inicial;
	Estado objetivo;
	BuscaLargura bL;
	
	inicial.setMissionaryLeft(3);
	inicial.setCannibalLeft(3);
	inicial.setMissionaryRight(0);
	inicial.setCannibalRight(0);
	inicial.setBoatLeft(1);
	inicial.setBoatRight(0);
	
	objetivo.setMissionaryLeft(0);
	objetivo.setCannibalLeft(0);
	objetivo.setMissionaryRight(3);
	objetivo.setCannibalRight(3);
	objetivo.setBoatLeft(0);
	objetivo.setBoatRight(1);
	
	try{
		bL.Initialize(&inicial, &objetivo);
			
		bL.Execute();	
		
	}catch(...){
		cout << "Erro na execução do aplicativo.";
	}
}
