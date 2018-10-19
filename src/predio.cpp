#include "predio.h"


bool comparar(const Sala &a, const int b){
	return a.capacidade < b;
}

Predio::Predio(std::string nome){
	this->nome = nome;
}
void Predio::addSala(std::string nomeDaSala, int capacidadeDaSala, std::string tipo){
	Sala nova(nomeDaSala, capacidadeDaSala, tipo);						
	salas.push_back(nova);
}
void Predio::ordenar(){
	std::sort(salas.begin(),salas.end(),
		[](const Sala&  a,const Sala& b){							//porque nao mandou pra uma função
			if(a.capacidade == b.capacidade) a.nome < b.nome;
			return a.capacidade < b.capacidade;
			});
}

void Predio::imprimir(){
	for(int i = 0;i < salas.size();i++){
		//if(salas[i].capacidade < 25) continue;
		std::cout << "Sala: " << salas[i].nome << "\nCapacidade: " << salas[i].capacidade << " " << salas[i].tipo << std::endl;
		salas[i].imprimir();
	}
}

int Predio::capacidadedoPredio(int capacidadePedida){
	int i;
	for(i = 0; i < salas.size(); i++){	
		if(salas[i].capacidade == capacidadePedida){
			if(i == 0){
				//printf("%d: %d\n", i, salas[i].capacidade);
				return 0;
			}
			return salas[i-1].capacidade;
		}
	
	}
		
}
bool Predio::alocarPedido(int capacidadePedida, Pedido pedido, int dia){
	auto vetor = lower_bound(salas.begin(),salas.end(), capacidadePedida, comparar); //aponta pro primeiro e vai ate o ultimo
	for(;vetor != salas.end();++vetor){
		bool salaCheia = false;
		Sala tmp = *vetor;
		if(tmp.tipo != pedido.tipo) continue;
		double numeroreal;
		numeroreal = (1.0*capacidadePedida)/tmp.capacidade*1.0;
		if(numeroreal < 0.5)	{
			return false;
		}
		for(int i = pedido.tempoInicial-1;i < pedido.tempoFinal;i++){
			if(tmp.getHorario(dia, pedido.turno, i) != ""){
				salaCheia = true;
				break;
			}
		}
		if(salaCheia) continue;
		if(tmp.capacidade < capacidadePedida) std::cerr << tmp.capacidade << " " << capacidadePedida << "\n";
		for(int i = pedido.tempoInicial-1;i < pedido.tempoFinal;i++){
			(*vetor).setHorario(dia, pedido.turno, i, pedido.info);
		}
		return true;
	}
	std::cerr << "NAO CONSEGUI ALOCAR\n";
	return false;	
}


