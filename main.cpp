#include <iostream>
#include "sala.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <cstdio>
#include <vector>

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

	// Começo iterar por cada predio.
	for(rapidjson::Value::ConstMemberIterator iter = predio.MemberBegin();iter != predio.MemberEnd();++iter){
		// Crio um novo predio, com o nome dado no arquivo json.
		Predio tmp(iter->name.GetString());
		// Coloco esse predio na minha lista de predios.
		predios.push_back(tmp);

		// Comeco iterar pelas salas dentro desse predio.
		const rapidjson::Value& sala = iter->value;
		for(rapidjson::Value::ConstMemberIterator itr = sala.MemberBegin();itr != sala.MemberEnd();++itr){

			// Pego a capacidade das salas, e a lista de salas com aquela capacidade.
			capacidade = std::stoi(itr->name.GetString());
			for(auto& array : itr->value.GetArray()){
				// E coloco essa sala no meu predio.
				predios[i].addSala(array.GetString(),capacidade);
			}
		}
		// Por fim ordeno as salas do meu prédio por capacidade, pois precisarei disso depois.
		predios[i].ordenar();
		i++;

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
	for(rapidjson::Value::ConstMemberIterator itr = pedido.MemberBegin();itr != pedido.MemberEnd();++itr){
		const rapidjson::Value& membro = itr->value;
		i = 0, j = 0;

		// Pego as variaveis necessarias do pedido.
		std::string horario = membro["horario"].GetString();
		std::string info = membro["info"].GetString();
		std::string predio = membro["predio"].GetString();
		int capacidade = std::stoi(membro["capacidade"].GetString());

		// Procuro o predio que o pedido se esta referindo
		bool achei = false;
		for(;i < predios.size();++i){
			if(predio.compare(predios[i].nome) == 0){
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
		std::vector < int > dias;
		int primeiroHorario, ultimoHorario, turno;
		j = 0;
		while(horario[j] <= '9' && horario[j] >= '0'){
			dias.push_back((int)(horario[j]-'0')-2);
			j++;
		}
		if(horario[j] == 'M') turno = 0;
		else if(horario[j] == 'T') turno = 1;
		else turno = 2;
		j++;
		primeiroHorario = horario[j] - '0';
		ultimoHorario = horario[horario.size()-1]-'0';

		// E aloco o pedido no predio
		for(int k = 0;k < dias.size();k++){
			predios[i].alocarPedido(capacidade, dias[k], turno, primeiroHorario, ultimoHorario, info);
		}

	} 

	fclose(fp);
}

int main(){
	std::vector < Predio > predios;
	lerPredios(predios);
	lerPedidos(predios);
	predios[0].imprimir();
}