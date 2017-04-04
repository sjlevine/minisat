This version of Minisat is the same as the original, forking repo, with one
notable exception: it builds a shared object (.so) file that can easily be
used to interoperate with other languages. Thanks to the Minisat team for their excellent work on the core of this solver!

Specifically, the .so file provides several useful for functions for building
up CNF problems and checking satisfiability -- without doing any memory
management. Makes integrating with CFFI systems easier by just having a purely
functional interface.

Build instructions:
```bash
make config prefix=build  # will create a build folder
make
```

Once done, there will be a `libminisat_bindings.so` file in the `build/dynamic/bindings/` folder. To use it, copy it somewhere like `/usr/local/lib`, then run `ldconfig`.

You can also run
```bash
make clean
```
to clean up.


## Using the API

Once built, the `libminisat_bindings.so` library contains the following functions (with C calling conventions, not C++, for simpler interoperability):


- `void minisat_initialize_new_solver()`

- `void minisat_shutdown_solver()`

- `void minisat_begin_new_clause()`

- `void minisat_add_literal_to_current_clause(int var, bool positive)`

- `void minisat_add_current_clause()`

- `bool minisat_solve()`


To use the solver with a CFFI of your choosing, first call `minisat_initialize_new_solver()`.

Then, build a CNF problem by continually adding new clauses. For each clause, call `minisat_begin_new_clause()` once. Then, for each literal in that clause, call `minisat_add_literal_to_current_clause(int var, bool positive)` with the variable index (starting from 0), and the positivity of that literal (true means positive, false means negative). Once you've added all the literals forming this disjunctive clause, call `void minisat_add_current_clause()` to actually add it to the problem.

Repeat the above for each clause you want to add to the problem. Once you're done, call `minisat_solve()`, which will return true if the problem is satisfiable, and false otherwise. And voila!

Currently, there is no API for reading back the actual solution assignment, but that wouldn't be hard to add.

Enjoy!
