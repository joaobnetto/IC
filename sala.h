#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <iostream>
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