# Trabalho 1 - Floodit  

*Implementar um programa em C que recebe como entrada uma instância do
jogo Floodit e que gera como saída uma sequência de ações que pinta o
tabuleiro todo com uma única cor.*

---
Para preencher o tabuleiro, foi adotado uma busca em profundidade limitada (limite variando para cada especificação de tabuleiro), onde todos os nós são expandidos.
O estado objetivo dessa busca, ou seja, a sequência de passos que ela irá retornar, se baseia em uma busca gulosa de melhor escolha.
Portanto, para cada folha presente na busca de profundidade limitada, ele verifica se ela possui o melhor h(n).

Como heurística foi utilizado a definição de uma matriz valoração, onde cada conjunto (i,j) presente no mapa possui um determinado valor.
Quanto mais próximo das diagonais principais, maior é esse valor.

Com isso, o algoritmo tende a andar pelas diagonais principais, dado que esses valores foram superestimados em relação aos demais, mas não desprezando-os.

## Estrturas de dados:

###  -Verificar: int *verificar*, int *valor*, int *camadaExterna*
  **- valor:** corresponde ao valor atual presente na posição (i,j).  
  **- verificar:** caso a posição (i,j) já tenha sido definida alguma vez, nas próximas é preciso apenas trocar o valor conforme o escolhido.  
  **- camadaExterna:** Trata das bordas do mapa, ou seja, todas as posições (i,j) que estão suscetíveis a trocar de cor, conforme o canto muda.  

### -Parametros: int *num_cores*, int *num_linhas*, int *num_colunas*
  Apenas guarda as informações de cada mapa nas respectivas variáveis.  

## Funcionamento do código

### defineLimite()
A função *defineLimite()* é resposável por retornar um valor que será a profundidade máxima expandida para cada busca em profundidade realizada.  
O cálculo desse valor é feito através dos parâmetros específicos de cada mapa.

### setaMapa()

A função *setaMapa()* atribui uma valoração a cada posição (i,j) do tabuleiro, considerando a distância em que essa posição se encontra das diagonais principais.

### progride()
A função *progride()* é reponsável por realizar a expansão de todos os nós possíveis.

Para cada nó expandido existe um mapa do tipo *Verificar*, mas com valores distintos.

### verificaMapa()
A função *verificaMapa()* é responsáivel por realizar o backtracking do mapa atual nas quatro direções, com isso mudando o valor das posições (i,j), assim como expandindo o mapa através da variável *verificar* e definindo as novas posições de *camadaExterna*.  

### main

O arquivo principal coordena o chamado das funções anteriormente descritas.  
Para cada resultado de busca gerado pela *progride()*, seu retorno é tratado pela função *main*, emendando próximas chamadas que persiste enquanto todas as posições do mapa não tiverem sido pintadas.  
Esse processo se repete para os 4 cantos do mapa. O canto que gerar a menor quantidade de passos será o escolhido como resultado final.

## Utilização

### Compilação

Primeiro é necessário compilar o código através do comando:

```bash
make
```
Com isso será gerado o código fonte *main*.

### Execução

Como foi proposto receber o mapa através da entrada padrão do sistema, tendo o mapa salvo as características necessárias, basta executar:

```c
./main < nome_arquivo.txt
```



