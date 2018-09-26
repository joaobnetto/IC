/*
	O arquivo de entrada precisa estar no formato:
	08:00-08:50	
	2 Economia Brasileira 1, Ciências Econômicas
	3 Macroeconomia 1, Ciências Econômicas
	4 Economia Brasileira 1, Ciências Econômicas
	5 Microeconomia 2, Ciências Econômicas
	6 Econometria 1, Ciências Econômicas
	7 Pesquisa EM Administração, Administração

	O horario precisa estar em cima de todas as disciplinas. 
	A numeração com o dia precisa estar antes da materia.
	Precisa ter virgula separando a materia do curso.

*/



#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <set>

// Defino essas três váriaveis porque eu sei qual irei utilizar antes de executar o programa.
// Posso mudar depois pra leitura, mas como é programa de conversão interno, ainda estou indeciso.

#define PREDIO "CAB"
#define CAPACIDADE 50
#define ABRIR "101.txt"

// Separo a string original em duas partes
// A parte final contem a materia e a parte do resto contem o curso.

void separar(std::string original, std::string &final, std::string &resto){
	
	final = resto = "";
	int j = 2;

	while(original[j] != ','){
		final += original[j++];
	}

	j += 2;

	while(j < original.size()){
		resto += original[j++];
	}

}

// Imprimo os dados que obti das outras funções em formato JSON.

void imprimir_json(std::string hr, std::string nome, std::string curso, int &contador){

	std::string pedido = "pedido";
	std::string cont = std::to_string(contador++);
	pedido += cont;

	std::cout << "	\"" << pedido << "\":{\n";
	std::cout << "		\"horario\": \"" << hr << "\",\n";
	std::cout << "		\"info\": \"" << nome << "\",\n";
	std::cout << "		\"curso\": \"" << curso << "\",\n";
	std::cout << "		\"capacidade\": \"" << CAPACIDADE << "\",\n";
	std::cout << "		\"predio\": \"" << PREDIO << "\",\n";
	std::cout << "		\"prioridade\": \"" << 0 << "\",\n";
	std::cout << "	},\n";
}

void concatenar(std::map < std::string , std::set < int > > &horarios, std::map < std::string , std::set < int > > &dias, int h,int &contador,
	std::map <std::string , std::string > &curso){
	// Itero pelo meu mapa de dias, pois nele há as matérias e os dias que elas estão.
	for(auto j = dias.begin();j != dias.end();++j){

		// Pego o nome pelo nome da materia e tmp são os dias que há essa matéria
		std::string hr = "";
		std::string nome = j->first;
		std::set < int > tmp = j->second;

		// Pego todos os dias que há a matéria
		for(auto k = tmp.begin();k != tmp.end();++k){
			 hr += (*k+'0');
		}

		// Dependendo do turno que tou, coloco M, T ou N
		if(h == 0) hr += 'M';
		else if(h == 1) hr += 'T';
		else hr += 'N';

		// Coloco os horarios na minha string horario, iterando novamente.
		for(auto k = horarios[nome].begin();k != horarios[nome].end();++k){
			hr += (*k+'0');
		}

		// Mando imprimir os dados que obti
		imprimir_json(hr, nome, curso[nome], contador);
	}
}

void alocar(int h, int &contador){
	// Declaro variaveis que irei utilizar.
	std::string str;
	int i = 1;
	std::map < std::string , std::set < int >> horarios, dias;
	std::map < std::string , std::string > curso;

	while(getline(std::cin, str)){
		// Se for um horario, preciso incrementar i, pois ele define qual horario aquela materia esta.
		if(str[0] <= '9' && str[0] >= '0' && str[1] <= '9' && str[1] >= '0'){
			i++;
			if(i == 5){
				break;
			}
			continue;
		}
		// Separo a string em 2
		std::string final, resto;
		separar(str, final, resto);

		// Insiro o horario, dia e curso da materia que obti na string da materia.
		dias[final].insert(str[0]-'0');
		horarios[final].insert(i);
		curso[final] = resto;

	}
	concatenar(horarios, dias, h, contador, curso);
}

// Abro o contador que salvo num arquivo txt pras proximas iterações do programa.

int set_contador(){

	std::ifstream in("contador.txt");
	std::streambuf *cinbuf = std::cin.rdbuf();
	std::cin.rdbuf(in.rdbuf());

	int contador = -1;

	while(std::cin >> contador);

	std::cin.rdbuf(cinbuf);

	if(contador == -1) return 1;
	else return contador;
}

// Salvo o contador pras proximas iterações do programa.

void save_contador(int contador){
	std::ofstream off("contador.txt");
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(off.rdbuf());

	std::cout << contador << "\n";

	std::cout.rdbuf(coutbuf);

}

// Função main que auxilia na execução do programa.

int main(){
	int contador = set_contador();

	// Abro pra ler do arquivo de entrada, definido na constante pra facilidade de conversão.
	std::ifstream in(ABRIR);
	std::streambuf *cinbuf = std::cin.rdbuf();
	std::cin.rdbuf(in.rdbuf());

	// Abro pra escrever no json.
	std::ofstream off("novo.json", std::ofstream::app);
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(off.rdbuf());


	// Leio a primeira linha, por conta de bugs que ocorrem.
	std::string lixo;
	getline(std::cin, lixo);

	// Leio os 3 turnos, para alocar eles diferentemente.
	for(int i = 0;i < 3;i++){
		alocar(i, contador);
	}

	// Fecho as pendencias para finalizar o programa;
	in.close();
	off.close();

	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);


	save_contador(contador);
	return 0;
}