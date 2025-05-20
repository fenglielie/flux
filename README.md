# Flux

## Build requirements

Testing environment and versions

| Family | version | Required flags |
| ------ | ------- | -------------- |
| clang  | 18.1.8  | -std=c++23     |
| gcc    | 14.2.0  | -std=c++23     |
| MSVC   | 2022    | /std:c++23     |


build (cmake version >= 3.15)
```
cmake -S . -B build
cmake --build ./build -j8
```

run examples
```
./bin/xxx
```
