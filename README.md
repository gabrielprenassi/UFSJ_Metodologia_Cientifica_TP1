# Comparação de Algoritmos de Ordenação  

Este programa executa experimentos de desempenho para diferentes algoritmos de ordenação, medindo **tempo de execução** e **uso de memória**, em cenários variados de entrada. Os resultados são salvos em arquivos `.csv` para posterior análise.  

## Algoritmos suportados
- Bubble Sort  
- Insertion Sort  
- Selection Sort  
- Radix Sort  

## Estrutura
O projeto está organizado em múltiplos arquivos:

- `main.c` → ponto de entrada do programa, responsável por gerar os vetores, rodar os testes e salvar os resultados em `.csv`.  
- `codigo/algoritmos.c` → implementações dos algoritmos de ordenação (Bubble, Insertion, Selection e Radix).  
- `codigo/algoritmos.h` → cabeçalho com os protótipos das funções de ordenação.  
- `codigo/monitor_memoria.c` → implementação do monitor de memória, que rastreia alocações e liberações.  
- `codigo/monitor_memoria.h` → cabeçalho do monitor de memória (`my_malloc`, `my_free`, `current_mem`, `peak_mem`).  
- `Makefile` → script de compilação que gera o executável `main` e permite limpeza com `make clean`.  


## Cenários de teste
São gerados vetores de inteiros de acordo com três padrões:  
- **sorted** → vetor já ordenado crescente  
- **reverse** → vetor ordenado decrescente  
- **random** → vetor com valores aleatórios  

Os números podem ter **1, 3 ou 5 dígitos**.  

## Configurações principais
- `min_size = 1000` → tamanho inicial do vetor  
- `step = 1000` → incremento no tamanho do vetor a cada teste  
- O comportamento muda conforme o cenário:

    - **random** → para cada tamanho de vetor, são gerados **3 vetores diferentes** e cada um é executado 1 vez.  
    - **sorted** e **reverse** → para cada tamanho de vetor, é gerado **1 vetor fixo**, mas ele é executado 3 vezes.  

Cada algoritmo tem um limite de tamanho máximo por cenário, definido em `max_size_for_algo_scenario`:  
- Bubble Sort → até **100.000 elementos**  
- Insertion/Selection Sort → até **250.000 elementos**  
- Radix Sort → até **1.000.000 elementos**  

## Saída dos experimentos
Para cada cenário (`sorted.csv`, `reverse.csv`, `random.csv`), o programa gera arquivos CSV contendo as seguintes colunas: 

```
algorithm,scenario,size,digits,repetition,execution_time,memory_used_bytes
```

Exemplo de linha:  

```
bubble_sort,random,5000,3,1,0.125432,20000
```

Também imprime no terminal um resumo de cada execução:  
```
bubble_sort | random | n=5000 | d=3 | rep=1 | time=0.125432 s
```

## Como compilar e executar
O projeto já possui um **Makefile** configurado. Basta rodar:  

```bash
make
```

Isso vai compilar o programa e gerar o executável main.

Para executar:
```
./main
```

Isso vai gerar os arquivos:

- `sorted.csv`  
- `reverse.csv`  
- `random.csv`  

Para limpar os binários compilados:
```
make clean
```