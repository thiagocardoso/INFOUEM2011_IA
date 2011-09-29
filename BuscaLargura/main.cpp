#include <iostream>
#include <string>
#include "buscaLargura.cpp"
#include "buscaGulosa.cpp"
#include <stdio.h>
#include <stdlib.h>
using namespace std;

void ExecuteBuscaLargura(){
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
		cout << "Erro na execução da Busca em Largura.";
	}
}

void ExecuteBuscaGulosa(){
	Estado inicial;
	Estado objetivo;
	BuscaGulosa bG;
	
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
		bG.Initialize(&inicial, &objetivo);
			
		bG.Execute();	
		
	}catch(...){
		cout << "Erro na execução da Busca Gulosa.";
	}
}

int main(){
	//ExecuteBuscaLargura();
	//ExecuteBuscaGulosa();
	char c;
	
	system("clear");
	cout << "============================================================================"<<endl;
	cout << "=              Inteligência Artificial - INFORMATICA 2011                  ="<<endl;
	cout << "=                   BUSCA EM LARGURA E BUSCA GULOSA                        ="<<endl;
	cout << "=                                                                          ="<<endl;  
	cout << "============================================================================"<<endl;
	cout << "= Escolha sua Opção:                                                       ="<<endl;
	cout << "= 1. Busca em Largura                                                      ="<<endl;
	cout << "= 2. Busca Gulosa                                                          ="<<endl;
	cout << "============================================================================"<<endl;
	
	while((c!='1')&&(c!='2')){
		cout << "Digite sua escolha e pressione ENTER:";
		//c=getc();
		gets(&c);
		puts(&c);
		cout << endl;
	}
	
	if (c=='1'){
		ExecuteBuscaLargura();
	}else if(c=='2'){
		ExecuteBuscaGulosa();
	}
}
