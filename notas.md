# Push_swap

## Objetivo:

Ordenar uma lista de números em ordem crescente com apenas 2 stacks, um set de movimentos pre-definidos e número limitado de movimentos. Não só é preciso sortear estes números, como é preciso fazê-lo de forma **eficiente**.

## Funcionamento

Começamos com 2 stacks vazias: **A** e **B**, a stack A, vai ser onde vamos pôr todos os nossos números iniciais, e a stack B começa vazia. No final do nosso programa, devemos ter todos os números sorteados na stack A, e devemos conseguir ver todos os movimentos que foram feitos através do output do programa.

## Conceitos básicos

### Estrutura de Dados

Esta é a estrutura das minhas stacks, e de cada um dos seus nodes. Ambas as nossas stacks são listas duplamente "linkadas", o que significa que cada node da lista tem acesso ao node que vem a seguir e ao node que vem antes.

```c
typedef struct   s_node
{
    int             value;
    struct s_node   *prev;
    struct s_node   *next;
}   t_node;
```

Esta é a estrutura dos nossos **nodes**, cada um destes armazena um `value`, e tem acesso aos pointers do node que vem antes (`prev`) e do node que vem a seguir (`next`).

```c
typedef struct   s_stack
{
    t_node  *top;
    t_node  *bottom;
    int     size;
}   t_stack;
```

E esta é a estrutura das **stacks**, que armazenam quantos nodes existem dentro da stack (`size`), e ambos os nodes do topo da stack (`top`) e de baixo da stack (`bottom`).

#### Porquê listas duplamente ligadas?

Todas as operações que temos disponiveis apenas usam os nodes do topo da stack ou do final da stack. E com os pointers que temos para o topo da stack (`top`) e para o final da stack (`bottom`), estas operações tornam-se instantâneas seja qual for o tamanho da stack.

##### Algumas regras:

- O `prev` de cada node no topo da stack é NULL.
- O `next` do node do final da stack é sempre NULL.
- Uma stack vazia tem sempre o `top` e `bottom` como NULL.

## Operações pré-definidas

### Operações _swap_ (*sa, sb, ss*):

Estas operações trocam os 2 primeiros elementos da stack. `sa` faz isto na stack A, `sb` faz na stack B e `ss` faz em ambas as stacks.

### Operações _push_ (*pa, pb*):

Estas operações apenas "enviam" o node do topo de uma stack para o topo da outra. `pa` envia o node no topo da stack B para o topo da stack A, e `pb` envia o node do topo da stack A para o topo da stack B.

### Operações *rotate* (*ra, rb, rr*):

Envia o primeiro node da stack para o último e roda o resto para cima. `ra` faz isto para a stack A, `rb` para a stack B e `rr` para ambas.

### Operações *reverse rotate* (*rra, rrb, rrr*):

Faz o mesmo que o *rotate*, mas ao contrário. Envia o último node da stack para o topo e roda tudo para baixo. `rra` faz isto para a stack A, `rrb` para a stack B e `rrr` para ambas as stacks.

## Parser e Validações

Quando corremos `./push_swap 4 67 3`, o programa precisa de converter esses argumentos em números na stack A. Este "parsing" acontece no meu `parser.c` através da função `parse_args()`.

### Formatos de input diferentes

O meu parser aceita duas formas de input diferentes:

- `./push_swap 4 67 3` (vários argumentos)
- `./push_swap "4 67 3"` (único argumento com espaços)

Isto acontece porque eu uso o `ft_split()` em cada argumento, dividindo-o por espaços. Desta forma, ambos os formatos acabam por ser tratados da mesma maneira.

### A validação

Para cada número, eu faço 3 checks:

Primeiro, uso o `safe_atoi()` para converter a string num _int_. Esta função vê se cada caractér é um digito (exceto um sinal "+" ou um "-" opcional), e vê se existe overflow. Se o número estiver fora do range do INT_MAX ou INT_MIN, é rejeitado.

Segundo, vejo se existem duplicados, usando o `has_dup()`. Esta função "anda" por todos os nodes já na stack A e compara os seus valores ao novo número.

Por último, se ambos os últimos checks passarem, crio um novo node usando o `node_new()` e meto-o no final da stack A. Os elementos vão para o fim da stack para preservar a ordem inicial, fazendo com que o primeiro número que introduzimos fique no topo.

#### Casos de erro:

Se alguma destas validações falhar, retorno `-1`, que ativa o `error_exit()` no main. Esta função printa "Error" no stderr e sai do programa com status 1.

Outros casos de erro são: caractéres não-numéricos, caractéres duplicados, int overflow e falha no malloc.

#### Caso especial:

Se o program receber zero argumentos (apenas `./push_swap` sem mais nada), o main retorna zero imediatamente sem printar nada. Isto não é um error, apenas não tem nada para ordernar.

## Estratégia de ordenação - Dispatch

O meu programa não utiliza apenas um algoritmo para todos os tamanhos de stack. Em vez disso, usa estratégias diferentes consoante o número de elementos na stack.

### Dispatch

Quando o `dispatch()` corre, primeiro vê se há alguma coisa para correr de todo. Se a stack A tiver 0 ou 1 elemento, a stack já está ordenada por definição. Se tiver vários elementos mas eles já estiverem ordenados, também não faz nada - como é pedido no enunciado.

Quando a stack tem 2 ou 3 elementos, usamos a função `sort3()`. Esta função é um algoritmo hard-coded que sabe todas as possiveis combinações de 3 números e aplica a melhor solução para cada caso.

No caso da stack ter 4 ou 5 elementos, usamos a função `sort5()`. Este algoritmo move os 2 menores valores temporariamente para a stack B, ordena os restantes elementos na stack A, e depois move os elementos de volta para a stack A.

Para casos onde a stack tenha 6 ou mais elementos, utilizamos o `turk_sort()`. Este é o algoritmo principal, que funciona para stacks de todos os tamanhos necessários.


