#ifndef PREDIO
#define PREDIO
#include "sala.h"
#include "extras.h"
/*
*	Declaro a classe predio, que tem todo o conjunto de salas naquele predio.
*	A função adicionar sala cria uma nova sala e adiciona aquele predio.
*	A função alocar pedido encontra a primeira sala disponivel naquele horario e coloca o pedido lá.
*/



class Predio{
private:
	std::vector < Sala > salas;
public:
	std::string nome;
	Predio(std::string nome);
	void addSala(std::string nomeDaSala, int capacidadeDaSala);
	// Ordena as salas por capacidade.
	void ordenar();
	// Imprime toda as salas daquele edificio.
	void imprimir();
	bool alocarPedido(int capacidadePedida, int dia, int turno, int tempoInicial, int tempoFinal, std::string detalhesDoPedido);
};

// Comparo duas salas por ordem de capacidade. Retornando falso se a é maior que b.

bool comparar(const Sala &a, const int b);

#endif