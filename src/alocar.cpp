#include "alocar.h"

void lerPedidos(std::vector < Predio > &predios, std::vector < Pedido > &pedidos){

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
		Pedido tmp;
		i = j = 0;

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
		
		tmp.tempoInicial = horario[j] - '0';
		tmp.tempoFinal = horario[horario.size()-1]-'0';
		tmp.npredio = i;
		
		pedidos.push_back(tmp);
	}
	
	sort(pedidos.begin(),pedidos.end(), customCompare);
	fclose(fp);
}

void alocar(std::vector < Predio > &predios, std::vector < Pedido > &pedidos){
		std::queue < Pedido > nao_alocados;

		for(int i = 0;i < pedidos.size();++i){
		
			// E aloco o pedido no predio
			int capacidadedpp = pedidos[i].capacidade;
			int capa = pedidos[i].capacidade;\

			for(int j = 0;j < pedidos[i].dias.size();j++){
				
				bool situacao = predios[pedidos[i].npredio].alocarPedido(capa, pedidos[i], pedidos[i].dias[j]);
				
				if(situacao == false){
					
					capa = predios[pedidos[i].npredio].capacidadedoPredio(capa);
					double numeroreal = (capa*1.0)/capacidadedpp*1.0; 
					
					if(numeroreal >= 0.5){
						j = -1;
					}
					else if(numeroreal < 0.5){	
						printf("NAO FOI POSSIVEL ALOCAR NO PREDIO\n");
						// nao_alocados.push(pedidos[i]);
						break;
					}
				}
			
			}
		}

		for(auto i : predios){
			i.imprimir();
		}

		if(!nao_alocados.empty()) std::cout << "Falta alocar\n";

		while(!nao_alocados.empty()){
			
			Pedido tmp = nao_alocados.front();
			nao_alocados.pop();

			std::cout << "Predio: " << tmp.predio << "\nInfo: " << tmp.info << "\nTipo: " 
				<< tmp.tipo << "\nPrioridade: " << tmp.prioridade <<  "\nCapacidade: " << tmp.capacidade;
		}
}
