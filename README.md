Projeto-Controlador-de-Viagens

Manual de uso:
Para compilar, você deve ter instalado um compilador c++, no meu caso utilizei o compilador Mingw encontrado no msys2. Você deve instalar todos os arquivos providenciados nesse repositório (a exceção do readme) e colar o seguinte comando no terminal:

g++ maain.cpp Cidade.cpp Passageiro.cpp Trajeto.cpp Transporte.cpp Viagem.cpp ControladorDeTransito.cpp -o sistema_viagens

após isso, cole:
./sistema_viagens para rodar o arquivo.

Para os comandos:
CADASTRAR_PASSAGEIRO: digite o comando como escrito e em seguida digite nome e cidade separado por espaços (se o nome for composto, utilize underline entre os nomes) (os nomes das cidades tem que ser digitados dessa forma: Fortaleza, Natal, Joao_Pessoa, Recife, Maceio e Salvador

CADASTRAR_TRANSPORTE: digite o comando como escrito e em seguida digite 
