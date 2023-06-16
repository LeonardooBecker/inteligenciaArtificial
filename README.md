# Trabalho 1 - Floodit  

*Implementar um programa em C que recebe como entrada uma instância do
jogo Floodit e que gera como saída uma sequência de ações que pinta o
tabuleiro todo com uma única cor.*

---
Para preencher o tabuleiro, foi adotado uma busca em profundidade limitada (valor variando para cada especificação de tabuleiro), onde todos os nós são expandidos.
O estado objetivo dessa busca, ou seja, a sequência de passos que ela irá retornar, se baseia em uma busca gulosa de melhor escolha.
Portanto, para cada folha presente na busca de profundidade limitada, ele verifica se ela possui o melhor h(n).

Como heurística foi utilizado a definição de uma matriz valoração, onde cada conjunto (i,j) presente no mapa possui um determinado valor.
Quanto mais próximo das diagonais principais, maior é esse valor.

Com isso, o algoritmo tende a andar pelas diagonais principais, dado que esses valores foram superestimados em relação aos demais, mas não desprezando-os.

## Foram desenvolvidas duas estrturas de dados:

###  -Verificar: int *verificar*, int *valor*, int *camadaExterna*
  **- valor:** corresponde ao valor atual presente na posição (i,j).  
  **- verificar:** caso a posição (i,) já tenha sido definida alguma vez, nas próximas é preciso apenas trocar o valor conforme o escolhido.  
  **- camadaExterna:** Trata das bordas do mapa, ou seja, todas as posições (i,j) que estão suscetíveis a trocar de cor, conforme o canto muda.  

### -Parametros: int *num_cores*, int *num_linhas*, int *num_colunas*
  Apenas guarda as informações de cada mapa nas respectivas variáveis.  

## Funcionamento do código

### progride()
A função *progride*, é reponsável por realizar a expansão de todos os nós possíveis.

Para cada nó expandido existe um mapa do tipo *Verificar*, mas com valores distintos.

### verificaMapa()
A função *verificaMapa*, é responsáivel por realizar o backtracking do mapa atual nas quatro direções, visando mudar o valor das posições (i,j), assim como expandir o mapa através da variável *verificar* e definir as novas posições de *camadaExterna*.  


