# Código do trabalho 1

## Integrantes

- Guilherme Caetano
- Henrique Gomes de Oliveira Sanches
- Leonardo Henrique Cardoso
- Mateus Gomes Flôres
- Thiago Inouye Miyazaki

## Instruções

- Para compilar o programa:
```bash
# compilando o programa
$ make

# limpando o workspace
$ make clean
```

- Para executar o programa:
```bash
# probabilidade de 0.5, produz 50 nós, e produz grafo de Erdos Renyi
$ ./main 0.5 50 er

# probabilidade de 0.3, produz 60 nós, e produz grafo de Barabasi Albert
$ ./main 0.3 60 ba
``` 
- A cada execução as métricas de distância média e distância máxima (**nesta ordem**) são escritas em um arquivo chamado `output.txt`. Além disso, os grafos são printados no console.