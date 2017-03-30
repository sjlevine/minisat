This version of Minisat is the same as the original, forking repo, with one 
notable exception: it builds a shared object (.so) file that can easily be
used to interoperate with other languages.

Specifically, the .so file provides several useful for functions for building
up CNF problems and checking satisfiability -- without doing any memory 
management. Makes integrating with CFFI systems easier by just having a purely
functional interface.

Build instructions:
```
make config prefix=build  # will create a build folder
make
```

Once done, there will be a `libminisat_bindings.so` file in the `build/dynamic/bindings/` folder.

You can also run
```
make clean
```
to clean up.
