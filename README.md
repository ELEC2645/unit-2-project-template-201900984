[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=22019818)
# ELEC2645 Unit 2 Project 201900984


This is my command line calculator.

The code has separated the menu handling code in `main.c` and the alculation and unit-conversion functions implementations in `funcs.c`. 

You can build the code with
`gcc main.c funcs.c -o main.out -lm` (the `-lm` is required to link the math library). You can also use `make -B` to force a rebuild using the provided `Makefile`.

Then run the code with `./main.out`.