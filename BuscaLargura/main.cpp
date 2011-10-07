#include <iostream>
#include <string>
#include "buscaLargura.cpp"
#include "buscaGulosa.cpp"
#include "algoritmoGenetico.cpp"
#include <stdio.h>
#include <stdlib.h>
using namespace std;

Estado* getInicial(int CM, int Barcos){
	Estado* inicial = new Estado();;
	inicial->setMissionaryLeft(CM);
	inicial->setCannibalLeft(CM);
	inicial->setMissionaryRight(0);
	inicial->setCannibalRight(0);
	inicial->setBoatLeft(Barcos);
	inicial->setBoatRight(0);
	
	return inicial;	
}

Estado* getObjetivo(int CM, int Barcos){
	Estado* objetivo = new Estado();	

	objetivo->setMissionaryLeft(0);
	objetivo->setCannibalLeft(0);
	objetivo->setMissionaryRight(CM);
	objetivo->setCannibalRight(CM);
	objetivo->setBoatLeft(0);
	objetivo->setBoatRight(Barcos);
	
	return objetivo;	
}

void ExecuteBuscaLargura(int CM, int Barcos){		
	BuscaLargura bL;	
	
	try{		
		bL.setMaxSolucoes(1);
		bL.setListarSolucoes(true);	
		bL.Initialize(getInicial(CM,Barcos), getObjetivo(CM,Barcos));
		bL.Execute();		
		
		bL.getSolucoes()->first();
		cout << "============================================="<<endl;
		cout << "= #Solucao: 1"<<endl;
		cout << "= No. Passos: "<< bL.getSolucoes()->numeroPassosSolucao(bL.getSolucoes()->getSolucao()) <<endl;
		cout << "============================================="<<endl;
		bL.getSolucoes()->printSolucao(NULL);		
	}catch(...){
		cout << "Erro na execução da Busca em Largura.";
	}
}

void ExecuteBuscaGulosa(int CM, int Barcos){
	BuscaGulosa bG;	
	
	try{
		//bG.Initialize(getInicial(), getObjetivo());			
		//bG.Execute();			
		bG.setMaxSolucoes(1);
		bG.setListarSolucoes(true);	
		bG.Initialize(getInicial(CM,Barcos), getObjetivo(CM,Barcos));
		bG.Execute();		
		
		bG.getSolucoes()->first();
		cout << "============================================="<<endl;
		cout << "= #Solucao: 1"<<endl;
		cout << "= No. Passos: "<< bG.getSolucoes()->numeroPassosSolucao(bG.getSolucoes()->getSolucao()) <<endl;		
		cout << "============================================="<<endl;
		bG.getSolucoes()->printSolucao(NULL);			
		
	}catch(...){
		cout << "Erro na execução da Busca Gulosa.";
	}
}

void ExecuteAlgoritmosGeneticos(int CM, int Barcos){
	BuscaLargura bL;	
	AlgoritmoGenetico* aG;	
	int i=0;
	int maxgeracoes=0;
	char s;
	
	cout << "Digite o número inicial de soluções(0 - 100): ";	
	cin >> i;
	cin.clear();
	
	cout << "Informe o numero maximo de geracoes para o algoritmo genetico:";
	cin >> maxgeracoes;
	cin.clear();
	
	if (i<=100){	
		bL.setMaxSolucoes(i);
		bL.setListarSolucoes(true);	
		bL.Initialize(getInicial(CM,Barcos), getObjetivo(CM,Barcos));
		bL.Execute();
		
		aG = new AlgoritmoGenetico(0, maxgeracoes);
		aG->setPopulacao(bL.getSolucoes());
		aG->Execute();
		
		cout << "============================================="<<endl;
		cout << "= Melhor Solucao Encontrada"<<endl;
		cout << "= No. Passos: "<< aG->getPopulacao()->numeroPassosSolucao(aG->getMelhorSolucao()) <<endl;
		cout << "============================================="<<endl;		
		aG->getPopulacao()->printSolucao(aG->getMelhorSolucao());
/*
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
				cout << "= No. Passos: "<< bL.getSolucoes()->numeroPassosSolucao(bL.getSolucoes()->getSolucao()) <<endl;				
				cout << "============================================="<<endl;
				bL.getSolucoes()->printSolucao();
				bL.getSolucoes()->next();
			}
		}
*/
	}	
}

int main(){
	char c;
	int CM=3;
	int Barcos=1;
	
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
		gets(&c);
		puts(&c);
		cout << endl;
	}
	
	if (c!='4'){
		cout << "Digite a quantidade de Canibais e Missionarios do problema(Padrão=3):";
		cin >> CM;
		cin.clear();
		if (CM<=0){
			CM=3;
		}
		
		cout << "Digite a quantidade de Barcos do problema(Padrão=1):";
		cin >> Barcos;
		cin.clear();
		if (Barcos<=0){
			Barcos=1;
		}		
	}
	
	switch(c){
		case '1':{
			ExecuteBuscaLargura(CM,Barcos);
			break;
		}
		case '2':{
			ExecuteBuscaGulosa(CM,Barcos);
			break;
		}
		case '3':{
			ExecuteAlgoritmosGeneticos(CM,Barcos);
			break;
		}
		case '4':{
			break;
		}
	}
}
