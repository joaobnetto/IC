#include <iostream>
#include "sala.h"
#include "predio.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <cstdio>
#include <vector>
#include <time.h>

struct Pedido{
	std::string info, predio, tipo;
	int capacidade, turno, primeiroHorario, ultimoHorario, prioridade, npredio;
	std::vector < int > dias;
};

bool customCompare(const Pedido &a, const Pedido &b){
	if(a.prioridade > b.prioridade) return true;
	else if(a.prioridade == b.prioridade) return a.capacidade > b.capacidade;
	return false;
}

void lerPredios(std::vector < Predio > &predios){
	// Variaveis que serão utilizadas depois
	int i = 0, capacidade = 0;

	// Abro o arquivo Json e coloco ele num documento pra ser utilizado depois
	FILE *fp = fopen("salas.json", "r");
	char readBuffer[1000010];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	rapidjson::Document d;
	d.ParseStream(is);

	// Declaro uma variavel para iterar pelo meu documento.	
	const rapidjson::Value& predio = d;

	// Começo iterar por FEFDa predio.
	for(rapidjson::Value::ConstMemberIterator iter = predio.MemberBegin();iter != predio.MemberEnd();++iter){
		const rapidjson::Value& tipo = iter->value;
		for(rapidjson::Value::ConstMemberIterator tipos = tipo.MemberBegin();tipos != tipo.MemberEnd();++tipos){
			// Crio um novo predio, com o nome dado no arquivo json.
			Predio tmp(iter->name.GetString());
			// Coloco esse predio na minha lista de predios.
			predios.push_back(tmp);

			// Comeco iterar pelas salas dentro desse predio.
			const rapidjson::Value& sala = tipos->value;
			// std::cout << 


			for(rapidjson::Value::ConstMemberIterator itr = sala.MemberBegin();itr != sala.MemberEnd();++itr){

				// Pego a capacidade das salas, e a lista de salas com aquela capacidade.
				capacidade = std::stoi(itr->name.GetString());
				for(auto& array : itr->value.GetArray()){
					// E coloco essa sala no meu predio.
					predios[i].addSala(array.GetString(),capacidade, tipos->name.GetString());
				}
			}
		}
		// Por fim ordeno as salas do meu prédio por capacidade, pois precisarei disso depois.
		predios[i++].ordenar();

	}

	// Ordeno meus predios por nome, caso não tenham sido ordenados na entrada.
	std::sort(predios.begin(),predios.end(),
		[](const Predio& a,const Predio& b){
			return a.nome < b.nome;
			});
	fclose(fp);
}

void lerPedidos(std::vector < Predio > &predios){

	// Abro o arquivo Json e coloco ele num documento pra ser utilizado depois
	int j = 0, i = 0;
	FILE *fp = fopen("pedidos.json", "r");
	char readBuffer[1000010];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	rapidjson::Document d;
	d.ParseStream(is);

	// Coloco ele numa variavel pra ser iterada.
	const rapidjson::Value& pedido = d;
	std::vector < Pedido > pedidos;
	for(rapidjson::Value::ConstMemberIterator itr = pedido.MemberBegin();itr != pedido.MemberEnd();++itr){
		const rapidjson::Value& membro = itr->value;
		Pedido tmp;
		i = 0, j = 0;

		// Pego as variaveis necessarias do pedido.
		std::string horario = membro["horario"].GetString();
		tmp.info = membro["info"].GetString();
		tmp.predio = membro["predio"].GetString();
		tmp.tipo = membro["tipo"].GetString();
		tmp.capacidade = std::stoi(membro["capacidade"].GetString());
		tmp.prioridade = membro["prioridade"].GetInt();

		// Procuro o predio que o pedido se esta referindo
		bool achei = false;
		for(;i < predios.size();++i){
			if(tmp.predio.compare(predios[i].nome) == 0){
				achei = true;
				break;
			}
		}

		// Se eu não encontrar, passo pro proximo pedido
		if(!achei){
			std::cout << "Predio nao existe\n";
			continue;
		}

		// Se não pego os dias que tem a aula, quando comeca, termina e o turno
		j = 0;
		while(horario[j] <= '9' && horario[j] >= '0'){
			tmp.dias.push_back((int)(horario[j]-'0')-2);
			j++;
		}
		if(horario[j] == 'M') tmp.turno = 0;						
		else if(horario[j] == 'T') tmp.turno = 1;
		else tmp.turno = 2;
		j++;
		tmp.primeiroHorario = horario[j] - '0';
		tmp.ultimoHorario = horario[horario.size()-1]-'0';
		tmp.npredio = i;
		pedidos.push_back(tmp);
	}
	sort(pedidos.begin(),pedidos.end(), customCompare);
	// std::cout << pedidos.size() << std::endl;
	// for(auto it : pedidos){
	// 	std::cout << it.prioridade << " " << it.capacidade << " " << it.turno << " " << it.info << std::endl;
	// }
	// return;
	for(int i = 0;i < pedidos.size();++i){
		// E aloco o pedido no predio
		int capacidadedpp = pedidos[i].capacidade;
		int capa = pedidos[i].capacidade;
		for(int k = 0;k < pedidos[i].dias.size();k++){
			
			bool situacao = predios[pedidos[i].npredio].alocarPedido(capa, pedidos[i].dias[k], pedidos[i].turno, pedidos[i].primeiroHorario, pedidos[i].ultimoHorario, pedidos[i].info);
			if(situacao == false){
				capa = predios[i].capacidadedoPredio(capa);
				double numeroreal = (capa*1.0)/capacidadedpp*1.0; 
				if(numeroreal >= 0.5)
				{
					k = -1;
				}
				else if(numeroreal < 0.5)
				{	
					printf("NAO FOI POSSIVEL ALOCAR NO PREDIO\n");
					break;
				}
			}
		
		}
		
	} 

	fclose(fp);
}

int main(){
	
	//clock_t T = clock();
	std::vector < Predio > predios;
	lerPredios(predios);
	lerPedidos(predios);
	for(int i = 0; i < predios.size(); i++){
		predios[i].imprimir();	
	}

	//T = clock() - T;

	//printf("%f\n", ((float)T)/CLOCKS_PER_SEC);



}
