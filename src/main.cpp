#include "includes.h"
#include "sala.h"
#include "predio.h"
#include "alocar.h"

int main(){
	
	// Redirecionando o cout para um arquivo de texto.
	std::ofstream out("out.txt");
    std::streambuf *coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());

    // Declaro meu vetor de predios, leio e aloco os pedidos.
	std::vector < Predio > predios;

	lerPredios(predios);

	// Faço o mesmo com os pedidos
	std::vector < Pedido > pedidos;
	lerPedidos(predios, pedidos);

	// Termino alocando os pedidos nos predios.
	alocar(predios, pedidos);


	// Resetando o cout.
    std::cout.rdbuf(coutbuf); 


}
