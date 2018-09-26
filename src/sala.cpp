#include "sala.h"

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
