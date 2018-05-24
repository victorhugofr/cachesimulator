# cachesimulator
Simulador de hierarquia de memória cache utilizando mapeamento, politica de substituição e política de escrita.
Simulador de Hierarquia de Memória
1. Descrição
Implementar uma ferramenta que simule o comportamento interno de uma cache L1 e da memória
principal. O simulador recebe como entrada uma sequencia de comandos que podem ser de leitura ou
escrita e o endereço solicitado. A cache simulada deve verificar a presença ou não do bloco contendo o
dado solicitado (acarretando em um Hit ou Miss). O simulador deve ser configurável no que diz respeito
aos aspectos de projeto de cache discutidos em sala: Mapeamento, Politica de Substituição e Política de
Escrita.
1.1. Mapeamento:
O mapeamento escolhido pode ser de 3 tipos: Direto, Totalmente Associativo e Parcialmente
associativo. Dependendo do mapeamento escolhido e após receber o comando de leitura ou escrita o
simulador deve informar o resultado da operação (hit ou miss) e a linha da cache que contém o bloco
solicitado.
1.2. Política de Substituição:
O algoritmo de substituição de blocos podem ser de 4: Aleatório, FIFO, LFU e LRU. Dependendo da
política de substituição escolhida e após receber o comando de leitura ou escrita o simulador deve
adicionalmente informar se houve substituição e qual bloco foi retirado de que linha da cache.
2. Comandos
O simulador aceita como entrada 3 comandos: read, write e show. O comando read recebe como parâmetro
o endereço a ser lido. Como resposta o simulador deve informar o resultado (hit ou miss) e a linha da cache
que contém o bloco solicitado. O comando write funciona de maneira similar, entretanto além do endereço
do dado a ser escrito ele tem como parâmetro o novo valor a ser escrito. Por fim, o comando show mostra o
conteúdo de toda a cache e de toda a memória principal.
3. Arquivo de Configuração
O simulador precisa gerenciar uma memória cache com características pré-definidas. Em um arquivo de
configuração (config.txt) devem ficar armazenadas as escolhas do usuário para as seguintes características
(nesta ordem). No início da simulação este arquivo é lido e suas configurações entram em vigor durante a
execução.
Tamanho do bloco (em número de palavras)
Numero de linhas da cache
Numero de blocos da memória principal
Mapeamento (1 – Direto; 2 – Totalmente Associativo; 3 – Parcialmente Associativo)
Numero de conjuntos (caso não seja Parcialmente Associativo, ler o valor normalmente mas desconsidere-o)
Política de substituição (1 – Aleatório; 2 – FIFO; 3 – LFU; 4 – LRU)4.
Exemplo de arquivo de configuração
Arquivo config.txt: O que significa:
4 - Cada bloco contém 4 palavras
8 - A cache tem 8 linhas (ou seja, comportam até 8 blocos vindos da memória)
16 - A memória principal tem 16 blocos
1 - Mapeamento Direto
2 - Não significa NADA pois o mapeamento não é parcialmente associativo
4 - Política de substituição LRU5.
## Exemplo de funcionamento:
Entrada: Saída:
Command> Read 25

Command> Read 28

Command>Write 25 41

Command> Show Read 25 -> HIT linha 2

Read 28 -> MISS -> alocado na linha 3 -> bloco 7 substituido

Write 25 -> HIT linha 2 -> novo valor do endereço 25=41

Show ->

CACHE L1

Linha –Bloco-Endereço -Conteúdo

0 – 4– 16 – 23
0 – 4 – 17 - 32
0 – 4 – 18 – 0
0 – 4 – 19 – 12
1 – 1 – 4 - 7
1 – 1 – 5 - 12
1 – 1 – 6 – 12
1 – 1 – 7 - 7
2 – 6 – 24 – 0
2 – 6 – 25 - 41
2 – 6 – 26 - 0
2 – 6 – 27 – 0
3 – 7 – 28 - 3
3 – 7 – 29 - 99
3 – 7 – 30 - 0
3 – 7 – 31 - 1
MEMORIA PRINCIPAL
Bloco-Endereço -Conteúdo
0 – 0 – 7
0 – 1 - 2
0 – 2 – 0
0 – 3 – 0
1 – 4 – 7
1 – 5 – 12
1 – 6 – 12
1 – 7 – 7
2 – 8 – 0
2 – 9 – 0
2 – 10 – 0
2 – 11 – 0
3 – 12 – 0
3 – 13 – 0
3 – 14– 0
3 – 15 –1
