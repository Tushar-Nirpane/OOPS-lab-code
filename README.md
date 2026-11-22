# OOPS Lab Code

Object Oriented Programming lab assignments (C++17), one program per experiment,
flat in the repository root. Every program compiles with `-Wall -Wextra
-Wpedantic` (zero warnings) and is exercised with the scripted inputs in `tests/`.

## Build and run

```bash
make              # compile every program into build/
make test         # run all programs against tests/*.in
make run PROG=a1_music
make sanitize     # rebuild and run under ASan + UBSan
make clean
```

Compiling a single file by hand:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -o a1_music a1_music.cpp
./a1_music
```

## Experiments

| File | Program | Concepts demonstrated |
|------|---------|-----------------------|
| [a1_music.cpp](a1_music.cpp) | Online music management system | Class with default, parameterised and copy constructors, destructor, dynamic array of `Song*` with capacity doubling, deep copy of the database, play counts and availability |
| [a2_bank.cpp](a2_bank.cpp) | Bank account operations | `this` pointer, `static` data member and `static` member function, `inline` member function, `friend` function |
| [a3_biodata.cpp](a3_biodata.cpp) | Employee bio-data | Inheritance, **virtual base class** (diamond), multiple inheritance, protected access |
| [a4_vehicle.cpp](a4_vehicle.cpp) | Vehicle rental fleet | Abstract base class, pure virtual functions, runtime polymorphism through base pointers, virtual destructor |
| [a5_complex.cpp](a5_complex.cpp) | Complex number arithmetic | Operator overloading (`+`, `*`), `friend` stream operators `<<` and `>>` |
| [a6_file.cpp](a6_file.cpp) | Student record file I/O | `ofstream` / `ifstream`, `getline` from a file, closing streams |
| [a7_exception.cpp](a7_exception.cpp) | Eligibility criteria check | User-defined exception class derived from `std::exception`, `what()` override, `throw` / `catch` |
| [a8_template_sort.cpp](a8_template_sort.cpp) | Generic sort | Function templates, template argument deduction, sorting across `int` and `float` |
| [a9_item_vector.cpp](a9_item_vector.cpp) | Item inventory | `std::vector` of class objects, STL `sort` with lambdas, `find_if`, tabular output |

## Sample output

`a5_complex` — operator overloading:

```
First Complex Number = 3 + 4i
Second Complex Number = 1 - 2i
Addition = 4 + 2i
Multiplication = 11 - 2i
```

`a6_file` — written to and read back from `student.txt`:

```
Student Details from File:
Student Name: Ravi
Age: 21
Roll Number: 101
```

`a7_exception` — a rejected applicant:

```
Criteria not met: Age must be between 18 and 55.
```

`a9_item_vector` — sorted inventory:

```
Code	Name	Cost	Quantity
103	Bag	899.99	5
102	Book	250	20
101	Pen	10.5	50
```

## Test inputs

`tests/aN_*.in` holds one scripted session per program, so `make test` runs
non-interactively. Each program reads names and other text fields as single
tokens (`cin >> name`), so entries such as `Ravi` work but `Ravi Kumar` does
not — keep one word per field in the input files.

## Notes on the current sources

- **a4_vehicle** — the fleet array holds 20 pointers; adding the 21st vehicle
  used to write past the array (a stack buffer overflow, caught with
  AddressSanitizer). The add path now checks `count >= 20` and reports that the
  fleet is full.
- **a5_complex** — `operator<<` printed a negative imaginary part as
  `1 + -2i`; it now prints `1 - 2i`. The operator takes a `const Complex&`, so a
  temporary result can be streamed directly.
- **a8_template_sort** — a non-positive or non-numeric element count is rejected
  before `new T[n]` instead of throwing `bad_array_new_length`.

## License

MIT — see [LICENSE](LICENSE).
