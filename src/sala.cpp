#include "sala.h"


bool comparar(const Sala &a, const int b){
	return a.capacidade < b;
}

Sala::Sala(std::string nome, int capacidade){
	this->nome = nome;
	this->capacidade = capacidade;
	memset(horario, 0, sizeof(horario));
}

std::string Sala::getHorario(int dia, int turno, int digito){
	return horario[dia][turno][digito];
}

void Sala::setHorario(int dia, int turno, int digito, std::string detalhesDoPedido){
	this->horario[dia][turno][digito] = detalhesDoPedido;
}

void Sala::imprimir(){
	for(int i = 0;i < 5;i++){
		if(i == 0) std::cout << "Segunda\n";
		else if(i == 1) std::cout << "Terça\n";
		else if(i == 2) std::cout << "Quarta\n";
		else if(i == 3) std::cout << "Quinta\n";
		else if(i == 4) std::cout << "Sexta\n";
		else if(i == 5) std::cout << "Sabado\n";
		for(int j = 0;j < 5;j++){
			if(j == 0) std::cout << "07:10-08:00 ";
			else if(j == 1) std::cout << "08:00-08:50 ";
			else if(j == 2) std::cout << "08:50-09:40 ";
			else if(j == 3) std::cout << "10:00-10:50 ";
			else if(j == 4) std::cout << "10:50-11:40 ";
			if(this->horario[i][MATUTINO][j] != "") std::cout << this->horario[i][MATUTINO][j] << "\n";
			else std::cout << "SEM AULA\n";
		}
		for(int j = 0;j < 5;j++){
			if(j == 0) std::cout << "13:10-14:00 ";
			else if(j == 1) std::cout << "14:00-14:50 ";
			else if(j == 2) std::cout << "14:50-15:40 ";
			else if(j == 3) std::cout << "16:00-16:50 ";
			else if(j == 4) std::cout << "16:50-17:40 ";
			if(this->horario[i][TARDE][j] != "") std::cout << this->horario[i][TARDE][j] << "\n";
			else std::cout << "SEM AULA\n";
		}
		// for(int j = 0;j < 5;j++){
		// 	if(j == 0) std::cout << "18:00-18:45 ";
		// 	else if(j == 1) std::cout << "18:50-19:35 ";
		// 	else if(j == 2) std::cout << "19:35-20:20 ";
		// 	else if(j == 3) std::cout << "20:30-21:15 ";
		// 	else if(j == 4) std::cout << "21:15-22:00 ";
		// 	if(this->horario[i][NOTURNO][j] != "") std::cout << this->horario[i][NOTURNO][j] << "\n";
		// 	else std::cout << "SEM AULA\n";
		// }
	}
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