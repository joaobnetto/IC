#ifndef SALA
#define SALA
#include "includes.h"
#define MATUTINO 0
#define TARDE 1
#define NOTURNO 2


/*
*	Declaro a classe sala que representa uma sala de aula.
*	Tem os atributos nome e capacidade, que define uma sala de aula.
*	O atributo capacidade é o mais importante, e é o que define a alocação.
*/
class Sala{
private:
	std::string horario[6][3][5];
public:
	std::string nome;
	int capacidade;
	Sala(std::string nome, int capacidade);
	// Retorna o que há no horário.
	std::string getHorario(int dia, int turno, int digito);
	// Coloca no horário pedido a disciplina que foi alocada.
	void setHorario(int dia, int turno, int digito, std::string detalhesDoPedido);
	// Imprime detalhadamente o que há em cada dia da semana, em cada horário naquela sala.
	void imprimir();
};

#endif