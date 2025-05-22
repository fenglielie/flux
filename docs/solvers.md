# Time Integration Framework

This project implements five C++ time integration frameworks, all supporting Forward Euler, SSP-RK3, as well as optional pre- and post-processing.
Each framework offers different trade-offs in flexibility, complexity, and performance, so all are retained:

- Runtime Polymorphism:
  - `solver_virtual.hpp`: virtual functions
  - `solver_stdfunc.hpp`: `std::function` (type erasure)

- Compile-time Polymorphism:
  - `solver_crtp.hpp`: CRTP
  - `solver_deducing.hpp`: deducing this (C++23)
  - `solver_template.hpp`: template parameters

Runtime approaches are simpler but slower; compile-time approaches are faster but more complex.
