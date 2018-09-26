#include "predio.h"

bool comparar(const Sala &a, const int b){
	return a.capacidade < b;
}

Predio::Predio(std::string nome){
	this->nome = nome;
}
void Predio::addSala(std::string nomeDaSala, int capacidadeDaSala){
	Sala nova(nomeDaSala, capacidadeDaSala);
	salas.push_back(nova);
}
void Predio::ordenar(){
	std::sort(salas.begin(),salas.end(),
		[](const Sala&  a,const Sala& b){
			if(a.capacidade == b.capacidade) a.nome < b.nome;
			return a.capacidade < b.capacidade;
			});
}

void Predio::imprimir(){
	for(int i = 0;i < salas.size();i++){
		if(salas[i].capacidade < 50) continue;
		std::cout << "Sala: " << salas[i].nome << "\nCapacidade: " << salas[i].capacidade << std::endl;
		salas[i].imprimir();
	}
}
bool Predio::alocarPedido(int capacidadePedida, int dia, int turno, int tempoInicial, int tempoFinal, std::string detalhesDoPedido){
	auto vetor = lower_bound(salas.begin(),salas.end(), capacidadePedida, comparar);
	for(;vetor != salas.end();++vetor){
		bool salaCheia = false;
		Sala tmp = *vetor;
		for(int i = tempoInicial-1;i < tempoFinal;i++){
			if(tmp.getHorario(dia, turno, i) != ""){
				salaCheia = true;
				break;
			}
		}
		if(salaCheia) continue;
		for(int i = tempoInicial-1;i < tempoFinal;i++){
			(*vetor).setHorario(dia, turno, i, detalhesDoPedido);
		}
		return true;
	}
	std::cout << "NAO CONSEGUI ALOCAR\n";
	return false;	
}