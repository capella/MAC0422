# Coisas para fazer:

## Parte I - Shell

### Rodar os comandos:
- [x] /bin/ls -l
- [x] /bin/date
- [x] ./ep1 <argumentos do EP1>
- [x] chmod <modo numérico> <arquivo no diretório atual>
- [x] id -u

- [x] Nome do diretório antes do comando

## Parte II - Simulador de processos

- [ ] Ler um arquivo txt no formato
    `t0 nome dt deadline`

### Implementar:
- [ ] FCFS
- [ ] SRTN
- [ ] Múltiplas filas

### Caso haja o parâmetro `d`, imprimir:
- [ ] Chegada de um processo no sistema, informando a linha do trace daquele processo
- [ ] Uso da CPU por um processo, informando qual o processo que começou a usar a CPU e qual CPU ele está usando.
- [ ] Liberação da CPU por um processo, informando qual o processo que deixou de usar a CPU e qual CPU ele está liberando.
- [ ] Finalização da execução do processo, informando a linha que será escrita no arquivo de saída.
- [ ] Quantidade de mudanças de contexto.

## Compilação
- [ ] Gerar dois binários: um referente à parte I e outro referente à parte II.

## Entrega:
- [ ] Códigos em C.
- [ ] LEIAME.txt
- [ ] Makefile
- [ ] Apresentação .pdf

## Apresentação:
- [ ] Resumo dos resultados.
- [ ] Explicar a arquitetura do shell.
- [ ] Mostrar a implementação dos escalonadores.

## Experimentos (gráficos):

### Impacto dos escalonadores:
- [ ] Muitos processos.
- [ ] Poucos processos.
- [ ] Valor intermediário.

### Quantidade das mudanças de contexto:
- [ ] Muitos processos.
- [ ] Poucos processos.
- [ ] Valor intermediário.

- Fazer os gráficos em barra.
- Fazer as soluções com n = 30 e intervalo de confiança de 95%.

- [ ] Nome no EP:
    `ep1-gabriel-luis`
