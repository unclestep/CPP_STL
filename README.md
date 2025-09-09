# STL Associative Containers

Own implementation of STL associative containers: `set`, `map` and `multiset`. The goal was to mimic the behavior of original library and get familiar with the main principles of OOP. The repository includes unit-tests written with GTest Framework. 

This project is part of project-based learning series.

# Project Features

- ✅ Red-Black Tree inside — effective self-balancing binary search tree;
- ✅ Don't repeat yourself (DRY) — one base class `s21_rbt` inherited by containers with necessary adjustments; 
- ✅ Base class methods encapsulated by using `protected` — methods are available only for children;
- ✅ Templates are used — containers can handle any data type;
- ✅ Unit-tests to check if everything's alright — Google Test Framework is used to catch nasty bugs;
- ✅ Build Automation — project is built with Makefile;
- ✅ Clang-formatted with Google Code Style.

# STL UML

![[STL_UML.png]]

# Code Samples
# General

Using the parent class `s21_rbt` and inheritance helps to avoid code duplication. All associative containers are quite similar and most of their methods look like this:
![[associative_functions.png]]
The key difference between `s21_set`/`s21_multiset` and `s21_map` is the data type stored in RBT. For `map`, it's `std::pair`:
![[rbt_map_templ_param.png]]
And for `s21_set`/`s21_multiset`, it's just a value:
![[rbt_set_templt_param.png]]

And knowing this, we should only get parent class know how to extract key from our nodes.

## Using lambda-functions to adjust base class methods

Lambda-function:
![[map_lambda.png]]
`s21_map` functions insert a value into Red-Black Tree:
![[map_inserts.png]]
Lambda-function:
![[set_lambda.png]]
`s21_set` function inserts a value into Red-Black Tree:
![[set_insert.png]]

Thus, despite exclusive functions in some containers (e.g. `s21_multiset` has `count`) the common functions share the same behavior.

# How to Run Tests (MacOS/Ubuntu)

_Before cloning, make sure you have `googletest` installed_. If not, see the link for [googletest](https://github.com/google/googletest)

1. Clone the repo;
2. `cd CPP_STL/src/`;
3. `make`.
