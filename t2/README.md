# Trabalho 2
## Integrantes
- Guilherme Caetano
- Henrique Gomes de Oliveira Sanches
- Leonardo Henrique Cardoso
- Mateus Gomes Flôres
- Thiago Inouye Miyazaki

## Como executar o programa

- Para compilar o código rode `make`
- Para limpar os executáveis `make clean`
- Para invocar o programa alguns parâmetros devem ser passados:

```
# Para criar grafos de Erdos-Renyi:
./main prob qtNodes graphType
./main 0.5 1000 er

# Para criar grafos de Watts-Stogratz:
./main prob qtNodes graphType qtNeighbors
./main 0.5 1000 ws 16
```

- A cada execução um arquivo chamado `output.txt` será gerado, onde o primeiro valor representa o **Limite Inferior** para o **Número Cromático**, e o segundo valor representa o **Limite Superior**.