*This project has been created as part of the 42 curriculum by **toandrad***

# Push_swap

## Description

Push_swap is a sorting algorithm project that challenges you to sort a stack of integers using a limited set of operations, while minimizing the number of moves required. The goal is to implement an efficient sorting algorithm that can handle various input sizes with optimal performance.

The project consists of two stacks (**A** and **B**) and a set of allowed operations: 

| Operation | Description |
|-----------|-------------|
| `sa` | Swap the first two elements of stack A |
| `sb` | Swap the first two elements of stack B |
| `ss` | Execute `sa` and `sb` simultaneously |
| `pa` | Push the top element of B onto A |
| `pb` | Push the top element of A onto B |
| `ra` | Rotate A upward (first element becomes last) |
| `rb` | Rotate B upward |
| `rr` | Execute `ra` and `rb` simultaneously |
| `rra` | Reverse rotate A (last element becomes first) |
| `rrb` | Reverse rotate B |
| `rrr` | Execute `rra` and `rrb` simultaneously |

### Algorithm

My implementation includes different sorting strategies for stacks of different sizes:

- **2-3 elements**: Simple comparison-based sorting
- **4-5 elements**: Push smallest elements to B, sort remaining, push back
- **6+ elements**: Turkish algorithm - a cost-based approach that calculates the cheapest element to move at each step, minimizing total operations

### Performance requirements

- **3 numbers**: 2-3 operations
- **5 numbers**: <12 operations
- **100 numbers**: <700 operations (for **100%** validation)
- **500 numbers**: <5500 operations (for **100%** validation)

## Instructions

### Compilation

`make`

Other rules (made by me):

- `make tests` - Asks the user how many numbers to sort and how many times to sort, thus making it easier to test the program without running it multiple times.
- `make edge` - Tests edge cases in the program (leaks, empty inputs, wrong inputs, etc)

Default rules:

- `make clean` - Remove object files
- `make fclean` - Remove all generated files
- `make re` - Rebuild from scratch

### Execution

```bash
./push_swap <integers>
```

Examples:

```bash
./push_swap 3 2 1 5 4
./push_swap "3 2 1 5 4"
./push_swap $(shuf -i 1-100 -n 100 | tr '\n' ' ')
```

### Verification

Use the checker to verify the output:

```bash
ARG="3 2 1 5 4"; ./push_swap $ARG | ./checker_linux $ARG
ARG=$(shuf -i 1-100 -n 100 | tr '\n' ' '); ./push_swap $ARG | ./checker_linux $ARG
```

Count operations:

```bash
./push_swap 3 2 1 5 4 | wc -l
./push_swap $(shuf -i 1-100 -n 100 | tr '\n' ' ') | wc -l
```

## Resources

### Documentation and References

- [42 push_swap subject](https://cdn.intra.42.fr/pdf/pdf/189080/en.subject.pdf)
- [Turkish Algorithm explanation](https://medium.com/@ayogun/push-swap-c1f5d2d41e97)
- [push_swap TUTORIAL!](https://www.youtube.com/watch?v=wRvipSG4Mmk&t=123s)

### AI Usage

AI tools were used during this project for:

- Project studying
- Explaining algorithm concepts and optimization strategies
- Code review (finding errors or optimization possibilities)
- Testing
