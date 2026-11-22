# OOPS Lab Code

Object Oriented Programming lab assignments (C++17), one program per experiment.
Every program is compiled with `-Wall -Wextra -Wpedantic` (zero warnings) and
exercised with the scripted inputs in `tests/`.

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
g++ -std=c++17 -Wall -Wextra -Wpedantic -o a1_music src/a1_music.cpp
./a1_music
```

## Experiments

| File | Program | Concepts demonstrated |
|------|---------|-----------------------|
| [src/a1_music.cpp](src/a1_music.cpp) | Music library manager | Class, encapsulation, constructors, copy constructor, destructor with a live-object counter, `static` data member, `std::vector` of objects |
| [src/a2_bank.cpp](src/a2_bank.cpp) | Bank account operations | Parameterised input through a member function, `this` pointer, chained calls returning `Account&`, `static` member function, `friend` function, `inline` function |
| [src/a3_biodata.cpp](src/a3_biodata.cpp) | Employee bio-data | Inheritance, **virtual base class** (diamond), multiple inheritance, protected access |
| [src/a4_vehicle.cpp](src/a4_vehicle.cpp) | Vehicle rental fleet | Abstract base class, pure virtual functions, runtime polymorphism through base pointers, virtual destructor |
| [src/a5_complex.cpp](src/a5_complex.cpp) | Complex number arithmetic | Operator overloading (`+`, `*`), `friend` stream operators `<<` and `>>`, default arguments via constructors |
| [src/a6_file.cpp](src/a6_file.cpp) | Student records file I/O | `ofstream` / `ifstream`, stream state checks, formatted output with `iomanip` |
| [src/a7_exception.cpp](src/a7_exception.cpp) | Eligibility criteria check | User-defined exception class derived from `std::exception`, `what()` override, `throw` / `catch` |
| [src/a8_template_sort.cpp](src/a8_template_sort.cpp) | Generic sort | Function templates, template argument deduction, sorting across `int` and `float` |
| [src/a9_item_vector.cpp](src/a9_item_vector.cpp) | Item inventory | `std::vector` of class objects, STL `sort` with lambdas, `find_if`, formatted tabular output |

## Sample output

`a5_complex` — operator overloading:

```
Default complex number: 0 + 0i
First: 3 + 4i
Second: 1 - 2i
Sum: 4 + 2i
Product: 11 - 2i
```

`a6_file` — written to and read back from `students.txt`:

```
Name                Age   Roll
------------------------------------
Alice               20    101
Bob                 21    102
```

`a7_exception` — a rejected applicant:

```
Criteria not met: Age must be between 18 and 55.
```

`a9_item_vector` — sorted inventory:

```
Code      Name           Cost        Quantity
-----------------------------------------------
101       Pen            10.50       50
102       Book           250.00      20
103       Bag            899.99      5
```

## Test inputs

`tests/aN_*.in` holds one scripted session per program, so `make test` runs
non-interactively. Text fields that may contain spaces (song playlist names,
employee names and addresses, item names) are read with `getline`, so each
such field occupies its own line in the input files.

## Fixes applied during the build check

- **a3_biodata** — a name containing a space (`Ravi Kumar`) made `cin >> empID`
  fail; the failed stream state then silently blanked every later field, so the
  program printed garbage. The name is now read with `getline(cin >> ws, name)`,
  `accept()` stops at the first failed read, and `main` reports bad numeric
  input instead of printing an empty record.
- **a1_music** — the live-object counter was printed while the `vector<Song>`
  was still in scope, so a correct program reported `Song objects alive: 1`.
  The library is now scoped so the counter shows `0` after destruction; the
  playlist name also accepts spaces.
- **a9_item_vector** — item names were read with `cin >> name`, so a name with a
  space broke the following numeric reads; both entry and search now use
  `getline`.
- **a8_template_sort** — a non-positive or non-numeric count is rejected before
  `new T[n]` instead of throwing `bad_array_new_length`.

## License

MIT — see [LICENSE](LICENSE).
