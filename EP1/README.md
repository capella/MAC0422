## Sobre os argumentos

./ep1 1 processos.txt out.txt

## Saída programa

Executando sem um quinto argumento, não haverá nenhuma saída na saída padrão.
Executando com `c` como quinto argumento você verá a saída completa do programa que será da seguinte maneira:

"tempo evento" "numero cpu" > "evento" "nome do processo"

Os tipos de evento existentes são: NEW (apresenta quando um processo chega ao escalonador, não tem numero de CPU); START (quando um processo é executado pela cpu pela primeira vez); IN (qunado um processo retorna a CPU); OUT (qunado um processo sai da cpu); END (qunado um processo acaba de ser executado); OFF (qunado a cpu desliga).

Executando com `c` como quinto argumento você verá a saída completa do programa que será da seguinte maneira:

NEW "nome do processo" ("linha de trace") -> chegada de um processo no sistema, informando a linha do trace daquele processo
"numero da cpu") IN "nome do processo" -> uso da CPU por um processo, informando qual o processo que começou a usar a CPU e qual CPU ele esta usando ´
"numero da cpu") OUT "nome do processo" -> liberação da CPU por um processo, informando qual o processo que deixou de usar a CPU e qual CPU ele esta liberando ´
END "nome do processo" ("linha arquivo de saída") -> finalização da execucção do processo, informando a linha que será escrita no arquivo de sa ´ ´ıda
MC "número de mudanças de contexto" -> quantidade de mudanc¸as de contexto

Note que não será mostrado o processo 'load_process'.

## Como funciona.

Esse escalonador simula um escalonador com x cpus, sendo x o número de cpus reais do usuário. O programa cria uma thread para cada cpu. O escalonador tem 4 funções principais exec (adiciona um novo processo), init (liga o escalonador), run (verifica se o processo atual deve continuar rodando). 

Antes de iniciar o escalonador, ele deve er tum processo que crie os outros processos. Esse processo recebe o nome de 'load_process'.

### Para mais informações, acesse http://github.com/capellaresumo/MAC0422