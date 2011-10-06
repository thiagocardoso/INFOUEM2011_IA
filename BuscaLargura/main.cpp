#include <iostream>
#include <string>
#include "buscaLargura.cpp"
#include "buscaGulosa.cpp"
#include <stdio.h>
#include <stdlib.h>
using namespace std;

Estado* getInicial(){
	Estado* inicial = new Estado();;
	inicial->setMissionaryLeft(3);
	inicial->setCannibalLeft(3);
	inicial->setMissionaryRight(0);
	inicial->setCannibalRight(0);
	inicial->setBoatLeft(1);
	inicial->setBoatRight(0);
	
	return inicial;	
}

Estado* getObjetivo(){
	Estado* objetivo = new Estado();	

	objetivo->setMissionaryLeft(0);
	objetivo->setCannibalLeft(0);
	objetivo->setMissionaryRight(3);
	objetivo->setCannibalRight(3);
	objetivo->setBoatLeft(0);
	objetivo->setBoatRight(1);
	
	return objetivo;	
}

void ExecuteBuscaLargura(){		
	BuscaLargura bL;	
	
	try{		
		bL.setMaxSolucoes(1);
		bL.setListarSolucoes(true);	
		bL.Initialize(getInicial(), getObjetivo());
		bL.Execute();		
		
		bL.getSolucoes()->first();
		cout << "============================================="<<endl;
		cout << "= #Solucao: 1"<<endl;
		cout << "============================================="<<endl;
		bL.getSolucoes()->printSolucao();		
	}catch(...){
		cout << "Erro na execução da Busca em Largura.";
	}
}

void ExecuteBuscaGulosa(){
	BuscaGulosa bG;	
	
	try{
		//bG.Initialize(getInicial(), getObjetivo());			
		//bG.Execute();			
		bG.setMaxSolucoes(1);
		bG.setListarSolucoes(true);	
		bG.Initialize(getInicial(), getObjetivo());
		bG.Execute();		
		
		bG.getSolucoes()->first();
		cout << "============================================="<<endl;
		cout << "= #Solucao: 1"<<endl;
		cout << "============================================="<<endl;
		bG.getSolucoes()->printSolucao();			
		
	}catch(...){
		cout << "Erro na execução da Busca Gulosa.";
	}
}

void ExecuteAlgoritmosGeneticos(){
	BuscaLargura bL;		
	int i;
	char s;
	
	cout << "Digite o número inicial de soluções(0 - 100): ";	
	cin >> i;
	cin.clear();
	
	if (i<=100){	
		bL.setMaxSolucoes(i);
		bL.setListarSolucoes(true);	
		bL.Initialize(getInicial(), getObjetivo());
		bL.Execute();
		
		cout << "Existem " << bL.getSolucoes()->size() << " soluções possíveis." <<endl;
		cout << "Deseja imprimir as solucoes? (S/N): ";
		
		cin >> s;
		cin.clear();
		i = 0;
		if (s=='S'){
			bL.getSolucoes()->first();
			while(!bL.getSolucoes()->eof()){
				i++;
				cout << "============================================="<<endl;
				cout << "= #Solucao: " << i <<endl;
				cout << "============================================="<<endl;
				bL.getSolucoes()->printSolucao();
				bL.getSolucoes()->next();
			}
		}
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
	cout << "= 3. Algoritmos Geneticos                                                  ="<<endl;
	cout << "= 4. Sair                                                                  ="<<endl;
	cout << "============================================================================"<<endl;
	
	while((c!='1')&&(c!='2')&&(c!='3')&&(c!='4')){
		cout << "Digite sua escolha e pressione ENTER:";
		//c=getc();
		gets(&c);
		puts(&c);
		cout << endl;
	}
	
	switch(c){
		case '1':{
			ExecuteBuscaLargura();
			break;
		}
		case '2':{
			ExecuteBuscaGulosa();
			break;
		}
		case '3':{
			ExecuteAlgoritmosGeneticos();
			break;
		}
		case '4':{
			break;
		}
	}
/*
	if (c=='1'){
		ExecuteBuscaLargura();
	}else if(c=='2'){
		ExecuteBuscaGulosa();
	}
*/ 
}
