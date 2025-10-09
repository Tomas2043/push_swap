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

### Operações _rotate_ (*ra, rb, rr*):

Envia o primeiro node da stack para o último e roda o resto para cima. `ra` faz isto para a stack A, `rb` para a stack B e `rr` para ambas.

### Operações _reverse rotate_ (*rra, rrb, rrr*):

Faz o mesmo que o _rotate_, mas ao contrário. Envia o último node da stack para o topo e roda tudo para baixo. `rra` faz isto para a stack A, `rrb` para a stack B e `rrr` para ambas as stacks.

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

## Deep-dive

### Algoritmo `sort3()`

Com apenas 3 elementos, existem apenas 6 combinações possiveis. Assim, em vez de usar um algoritmo complexo, podemos apenas identificar as combinações possiveis e aplicar movimentos específicos para ordernar as stacks.

O truque é identificar qual é o maior número e a sua posição na stack. Quando sabemos isso, podemos apenas usar duas **rotações** para mover esse valor para o fim da stack. Depois disso, os dois elementos no topo, ou precisam de um **swap**, ou já estão em ordem.

#### Como funciona na realidade

Primeiro temos que contar o caso da stack ter apenas 2 elementos. Nesse caso, temos só que comparar os 2 elementos e ver: se o elemento do topo é maior que o segundo, apenas aplicamos um Swap (**`sa`**), caso contrário não fazemos nada.

Para 3 elementos, primeiro identificamos onde está o maior elemento da stack. Se esse valor estiver no topo, aplicamos um Rotate (**`ra`**) para movê-lo para o final. Se o maior valor estiver no meio da stack, usamos um Reverse Rotate (**`rra`**). E assim temos a certeza de que o maior valor está no final da stack.

Agora apenas temos de ver se os dois primeiros elementos estão em ordem. Se o primeiro elemento for maior que o segundo, apenas fazemos um Swap (**`sa`**), se não, já estão na ordem correta.

### Algoritmo `sort5()`

Com 5 elementos, a ideia é: temporariamente remover 2 elementos da stack A, ordenar os restantes 3 números usando o `sort3()`, e depois trazer os 2 números da stack B para o topo da stack A.

#### Como funciona

A minha função `push_min_to_b()` encontra o menor valor da stack A, aplica rotate (escolhe a opção mais "barata", **rotate** _ou_ **reverse rotate**) até ele estar no topo, e depois manda-o para a stack B. Repetimos isto mais uma vez para ter os dois menores valores na stack B.

Agora que a stack A tem apenas 3 números, podemos usar o `sort3()`.

Agora que a stack A, está ordenada e a stack B tem os 2 menores valores, enviamos os 2 números na stack B usando o `pa` 2 vezes, e tendo em conta que quando mandámos estes valores para a stack B, mandámos primeiro o menor valor e depois o segundo-menor valor, quando voltamos a mandá-los para a stack A, eles já vêm em ordem.

#### Número de movimentos

Encontrar e mandar cada valor para a stack B "custa" no máximo 4 movimentos (**duas rotações** e um **push**), feito 2 vezes são **8** movimentos. O sort `sort3()` faz no máximo **3** movimentos, e os 2 pushes finais são mais **2** movimentos. Trazendo assim o nosso _pior_ cenário para **13** movimentos. **Esté o pior cenário**, na prática, conseguimos atingir os <12 movimentos quase nunca são necessárias os 13 movimentos.

## Turk Algorithm

O "Turk Algorithm" é um algoritmo baseado no "custo" dos movimentos. Basicamente, mandamos todos os nodes para a stack B, deixando apenas alguns na stack A, e movêmos elementos repetidamente de volta para a stack A, escolhendo sempre o elemento mais "barato" para mover a seguir.

### Fase 1 - Setup Inicial

Numa primeira fase, mandamos todos os elementos (não interessa a ordem) para a stack B, deixando apenas 3 elementos na stack A. Depois ordenamos os elementos da stack A usando o `sort3()`, deixando uma "fundação" já ordenada na stack A.

### Fase 2 - O loop

Enquanto a stack B ainda tem elementos, repetimos este processo:

Para cada elemento da stack B, calculamos qual seria o "custo" (de movimentos) para movê-lo para a sua posição correta na stack A. O custo inclui duas coisas: quantas rotações são necessárias na stack B para trazer esse elemento para o topo, e quantas rotações são necessárias na stack A para levá-lo para a sua posição correta.

Depois disto, escolhemos o número com o menor custo, aplicamos as rotações necessárias, e fazemos o push da **B** para a **A**.

#### Como encontramos a posição ideal

Quando temos um elemento na stack B (vamos dizer 5), precisamos de saber onde é que ele deveria ir na stack A. Para isto, vemos qual é o menor elemento na stack A, que ainda é maior que o nosso número na stack B (neste caso 5).

Se este elemento for maior que qualquer elemento da stack A, ele deve vir a seguir ao maior elemento da stack A.

### Fase 3 - Rotação final

Depois de todos os elementos estarem na stack A, o menor elemento pode não estar no topo. Se for esse o caso, encontramos onde o menor número está posicionado na stack, e fazemos as rotações necessárias para levá-lo ao topo.


## Código

### Fase 1

```c
void  push_initial_to_b(t_stack *a, t_stack *b)
{
  int push_count;

  if (a->size <= 5)
    return ;
  push_count = a->size - 3;
  while (push_count-- && a->size > 3)
    pb(a, b);
  sort3(a);
}
```

Esta função é a que manda todos os números para a stack B, deixando apenas 3 na stack A. Nesta função, definimos uma variável `push_count`, que dizemos que é igual ao número total de elementos na stack A, menos 3. E depois enquanto o `size` da stack A for maior que 3, aplicamos o `pb`. Depois de tudo aplicamos a nossa função `sort3()`.

### Fase 2

```c
int find_target_pos_in_a(t_stack *a, t_stack *b)
{
  int target_pos;
  int max_value;
  int max_pos;

  if (a->size == 0)
    return (0);
  target_pos = find_bigger_target(a, b_value);
  if (target_pos != -1)
    return (target_pos);
  max_value = find_max_value(a);
  max_pos = find_position(a);
  return ((max_pos + 1) % a->size);
}
```

Esta é a função que resolve a pergunta: "Para onde é que este elemento da stack B deve ir?"

Primeiro, usamos a função `find_bigger_target()`, que procura pelo menor elemento na stack A que é maior do que o nosso elemento da stack B.

Se o meu valor de B for maior que todos os elementos da stack A, não há alvo maior. Portanto temos que pô-lo depois do número máximo. Primeiro encontra-mos o máximo, vemos a sua posição e retornamos a posição a seguir.

### Fase 3

```c
int calculate_cost(t_stack *a, t_stack *b, int b_index)
{
  int b_value;
  int target_pos_a;
  int cost_b;
  int cost_a;

  b_value = get_b_value_at_index(b, b_index);
  if (b_value == INT_MAX)
    return (INT_MAX);
  target_pos_a = find_target_pos_in_a(a, b_value);
  cost_b = calculate_rotation_cost(b_index, b->size);
  cost_a = calculate_rotation_cost(target_pos_a, a->size);
  return (cost_a + cost_b);
}
```

Para cada elemento de B, esta função calcula o custo total para movê-lo.

`get_b_value_at_index(b, b_index)` obtem o valor da posição `b_index()` na stack B.

`find_target_pos_in_a()` diz-nos onde é este elemento deve ir na stack A.

`calculate_rotation_cost()` calcula o número de rotações necessárias.

```c
static int  calculate_rotation_cost(int pos, int size)
{
  if (pos <= size / 2)
    return (pos);        // Rotate forward
  else
    return (size - pos); // Rotate backward
}
```

Se o elemento estiver na posição 2 numa stack com tamanho 10, uma rotação para a frente (`ra`) custa 2 movimentos. Mas se estiver na posição 8, uma rotação para trás (`rra`) custa menos (10 - 8 = 2).

### Fase 4

```c
int  find_cheapest_index(t_stack *a, t_stack *b)
{
  int  cheapest_cost;
  int  cheapest_index;
  int  current_cost;
  int  i;

  cheapest_cost = INT_MAX;
  cheapest_index = 1;
  i = 0;
  while (i < b->size)
  {
    current_cost = calculate_cost(a, b, i);
    if (current_cost < cheapest_cost)
    {
      cheapest_cost = current_cost;
      cheapest_index = i;
    }
    i++;
  }
  return (cheapest_index);
}
```

Esta função faz um loop por todos os elementos da stack B, calcula o custo de os mover para a stack A, e retorna o index do elemento mais barato.

Depois o `push_cheapest_to_a()` é que executa:

```c
void  push_cheapest_to_a(t_stack *a, t_stack *b)
{
  int  cheapest_index;
  int  b_value;
  int  target_pos;

  cheapest_index = find_cheapest_index(a, b);
  b_value = get_b_value_at_index(b, cheapest_index);
  target_pos = find_target_pos_in_a(a, b_value);
  rotate_to_position_b(b, cheapest_index);
  rotate_to_position_a(a, target_pos);
  pa(a, b);
}
```

Esta função encontra o elemento mais barato, faz as rotações na stack B para levá-lo ao topo, prepara a stack A para o receber (ou seja, faz as rotações necessárias para recebê-lo na posição correta) e depois aplica o push (`pa`).

### Fase 5

Loop principal:

```c
void  turk_sort(t_stack *a, t_stack *b)
{
  int  min_pos;

  push_initial_to_b(a, b);
  while (b->size > 0)
    push_cheapest_to_a(a, b);
  min_pos = find_position(a, find_min_value(a));
  rotate_to_position_a(a, min_pos);
}
```

Primeiro fazemos o setup, depois mandamos todos os números da stack B e depois disso fazemos a rotação final.
