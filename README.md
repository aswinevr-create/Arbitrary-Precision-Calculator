# Arbitrary Precision Calculator (APC)

A calculator written in C that handles integers and decimals of any length. Numbers are stored as doubly linked lists of 9-digit boxes, with manual memory management.

## Features

- Addition, subtraction, multiplication, division, modulus, and exponents
- Negative numbers and decimals
- Parentheses with standard operator precedence
- Text mode (`apc`) and graphical mode (`apc_gui`, built with raylib)

## Build

Requires GCC and Make. The GUI also needs raylib.

On Windows, use the MSYS2 UCRT64 terminal. Install the tools with:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc make mingw-w64-ucrt-x86_64-raylib
```

Then build:

```bash
make            # builds apc and apc_gui
make apc        # text calculator only
make apc_gui    # graphical calculator only
make clean      # removes build files and programs
```

## Run

```bash
./apc        # type expressions, or q to quit
./apc_gui    # click or type in the window
```

## Examples

```
(1.5 + 2.25) * 2     ->  7.5
2 ^ 100              ->  1267650600228229401496703205376
2 ^ -2               ->  0.25
-2 ^ 2               ->  -4
1 / 3                ->  0.3333333333
10 % 3 * 2           ->  2
```

Division shows 10 decimal places by default. Change `APC_DIV_EXTRA` in `include/apc.h` to adjust it.

## How it works

Each number is a doubly linked list. Every node (a "box") holds 9 decimal digits, and the list runs from the most significant box (`head`) to the least significant box (`tail`).

- **Addition and subtraction** walk the lists from the tail, carrying or borrowing between boxes.
- **Multiplication** uses schoolbook multiplication.
- **Division** uses long division, finding each quotient box by binary search.
- **Exponents** use repeated squaring. Negative exponents compute the reciprocal.
- **Expressions** are parsed with recursive descent, with precedence from lowest to highest: `+ -`, then `* / %`, then unary `-`, then `^`.

## Project layout

```
apc/
├── Makefile
├── include/
│   └── apc.h          Types and function declarations
└── src/
    ├── arithmetic.c   Add, subtract, multiply, divide, power
    ├── convert.c      String to number and number to string
    ├── gui_main.c     Graphical calculator (raylib)
    ├── list.c         Create, push, trim, and free box lists
    ├── main.c         Text-mode calculator
    └── parser.c       Expression parser
```

## Limits

- Decimal division is truncated, not rounded (`2 / 3` gives `0.6666666666`).
- `%` works on whole numbers only.
- Very large exponents and very long divisions can be slow.

## Roadmap

- Rounding for decimal results
- Choosing the number of decimal places at runtime
- Calculation history in the GUI

## License

MIT. See [LICENSE](LICENSE).
