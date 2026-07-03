Projeto-Controlador-de-Viagens

Manual de uso:
Para compilar, você deve ter instalado um compilador c++, no meu caso utilizei o compilador Mingw encontrado no msys2. Você deve instalar todos os arquivos providenciados nesse repositório (a exceção do readme) e colar o seguinte comando no terminal:

g++ maain.cpp Cidade.cpp Passageiro.cpp Trajeto.cpp Transporte.cpp Viagem.cpp ControladorDeTransito.cpp -o sistema_viagens

após isso, cole:

./sistema_viagens para rodar o arquivo.

Imediatamente o sistema pedirá ao usuário as distancias entre cidades, basta digitar o numero em km e apertar enter.

Para os comandos:

CADASTRAR_PASSAGEIRO: digite o comando como escrito e em seguida digite nome e cidade separado por espaços (se o nome for composto, utilize underline entre os nomes) (os nomes das cidades tem que ser digitados dessa forma: Fortaleza, Natal, Joao_Pessoa, Recife, Maceio e Salvador

CADASTRAR_TRANSPORTE: digite o comando como escrito e em seguida digite nome do veículo(com _ se for composto), tipo de transporte (A para aquático ou T para terrestre), número representando a capacidade de passageiros do transporte, número representando velocidade em km/h, distancia em km para que o condutor descanse, tempo em horas do descanso do condutor e cidade de origem do transporte. Tudo separado por espaços.

INICIAR_VIAGEM: Digite o comando como escrito e em seguida digite 
