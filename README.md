# Marble-Rolling-Toy

## Input File Format

Filename: description.dat
    
    (Number of states)
    (List of states, separated by space)
    (List of symbols, not separated)
    (Initial state)
    (Final state amount)
    (List of final states, separated by spaces)
    (Table-shaped transition function)

For the transition function, the conditions are as follows:
- The state order is according to the description.dat
- Sequence of symbols according to writing in description.dat
- Transition tables consist of a number of state rows, each row containing a number of state symbols
- For each i and j with 1 <= i <= number of states and 1 <= j <= number of symbols, the j-symbol will direct state i to the j-state in the i-th row
