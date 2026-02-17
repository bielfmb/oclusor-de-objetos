# Oclusor de objetos em 2D (C++)

Sistema que resolve o problema de oclusão de segmentos (objetos) em uma cena 2D e imprime os trechos visíveis por objeto em um dado instante de tempo.

# Visão geral

O programa recebe comandos da entrada padrão que descrevem:
- a criação de objetos (segmentos horizontais com centro, largura e profundidade y),
- movimentações de objetos em instantes de tempo,
- e pedidos de geração/impressão da cena num determinado instante.

Ao gerar a cena (C tempo) o motor:
- ordena os objetos por profundidade (eixo y),
- insere o objeto mais próximo primeiro (não pode ser ocluído),
- para cada objeto, calcula a parte do seu segmento que permanece visível após considerar os objetos já colocados na cena (operações de subtração de intervalos),
- armazena os intervalos visíveis e, por fim, imprime-os ordenados por id (com duas casas decimais).

O algoritmo principal usa um [QuickSort](https://www.geeksforgeeks.org/dsa/quick-sort-algorithm/) para ordenação e um procedimento recursivo que divide intervalos quando um oclusor se encontra totalmente dentro do intervalo ocluído.

# Execução

Programa principal:
```
make
./bin/oclusor.out < input.txt > output.txt
```
    
Testes:
```
make tests
```

# Entrada/Saída

**Comandos da entrada** (cada comando começa com um caractere):

- `O` `id x y largura` — adiciona um objeto com:
id (inteiro)
    - x (double) — centro no eixo X
    - y (double) — profundidade (quanto maior, aparece primeiro/mais à frente conforme ordenação - usada)
    - largura (double) — extensão total do segmento (de ponta a ponta)
- `M` `tempo id x y` — movimenta o objeto id para novo centro x e y no instante tempo. (O programa - apenas atualiza a posição do objeto na lista.)
- `C` `tempo` — ordena os objetos por profundidade, calcula as oclusões considerando as posições atuais e imprime a cena para o tempo informado

**Saída**: para cada C tempo o programa imprime linhas com um indicador de saída de cena, um inteiro representando o instante de geração (o mesmo tempo passado no comando C), o identificador do objeto cujo trecho é visível e os limites do trecho visível no eixo X, com duas casas decimais.

> [!NOTE] 
> Exemplos completos de entrada/saída podem ser encontrados em `tests/exemplos`
