*This project has been created as part of the 42 curriculum by moatieh*

# push_swap


## Description

push_swap is a sorting algorithm project that sorts a stack of integers using a limited set of operations in the minimum number of moves.

The project includes:
- **push_swap**: Outputs the optimal sequence of operations to sort a list of integers
- **checker**: Verifies if a sequence of operations correctly sorts the stack

Available operations:
- `sa`, `sb`, `ss`: swap first two elements
- `pa`, `pb`: push top element between stacks
- `ra`, `rb`, `rr`: rotate stack up
- `rra`, `rrb`, `rrr`: rotate stack down

This implementation uses a **chunking sort algorithm** that divides the stack into chunks, pushes them to stack B by value ranges, then pushes them back to stack A in sorted order.

**Indexing:** Maps input values to their sorted positions (0 to n-1)

## Instructions

### Compilation
```bash
make        # creates push_swap
make bonus  # creates checker
```

### Usage
```bash
./push_swap 3 2 5 1 4
./push_swap 3 2 5 1 4 | ./checker 3 2 5 1 4  # outputs OK or KO
```

## Resources

**Algorithm & Sorting:**
- [Sorting Algorithms - Wikipedia](https://en.wikipedia.org/wiki/Sorting_algorithm)
- [Chunk Algorithm Guide](https://github.com/anyaschukin/push_swap)
