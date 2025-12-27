<div align="center">
    <h2>&#9888; WARNING: THIS PROJECT IS UNDER DEVELOPMENT</h2>
    <h1>CaveLang</h1>
    <h3>A middle-ground between C and C++</h3>
</div>

#
### Overview
CaveLang is a lightweight language designed to find that perfect 'sweet spot' between C and C++.

CaveLang is not a C++ dialect and does not aim for source compatibility with C++.

It is intentionally non-modular, favoring static compilation and a minimal import model over dynamic modules.

It focuses on simplicity and performance while providing the necessary tooling for basic development needs.
#
### Features:
- Maintains C-compatible ABI for interoperability.
- Minimal runtime with ahead-of-time compilation
- Deterministic compilation model
- No mandatory runtime dependencies
#
### Requirements
- OS: [Linux](https://www.kernel.org) / [BSD](https://www.bsd.org) based operating systems
- Compiler: C version >= C17
- Build utils: Make
#
### Installation
#### From source
```bash
git clone https://www.github.com/dhrxvxd-arch/cave-lang.git
cd cave-lang
make build
```
#
### Usage
- Basic usage:
```bash
cave -i main.cav
./a.out
```
- Advanced usage:
```bash
cave -i main.cav -o main -v
./main
```
#
### Project Status
CaveLang is in active development. The language is not yet stable, and breaking changes are expected.
#
### Target Audience
- C developers seeking safer or more structured abstractions
- Systems programmers who want deterministic builds
- Developers who prefer static, minimal toolchains
#
### CaveLang Example
> The example below demonstrates CaveLang’s object model and constructor semantics.
> Object allocation and construction are explicit and under programmer control.
```cpp
#include <stdio.cav>        // Although c headers are fully supported, we recommend using cav modules
#include <stdlib.cav>

class MyClass {
public:
    this->__constructor(int x, int y) {
        this->x = x;
        this->y = y;
    }
private:
    int x, y;
};

int main(int argc, char** argv)
{
    MyClass *obj = malloc(sizeof(*obj));
    printf("Hello World!\n");
    return 0;
};
```
#
### Source Structure
```text
.
├── build
├── docs
│   └── c_grammar.md
├── include
│   ├── ast.h
│   ├── lexer.h
│   ├── opts.h
│   ├── parser.h
│   └── tokens.h
├── LICENCE
├── README.md
├── refr
│   └── sources.md
└── src
    ├── ast.c
    ├── lexer.c
    ├── opts.c
    ├── parser.c
    └── tokens.c
```
#
### Links
- [Sources](https://github.com/dhrxvxd-arch/cave-lang/blob/devel/refr/sources.md)
- [C Grammar](https://github.com/dhrxvxd-arch/cave-lang/blob/devel/docs/c_grammar.md)
#
### Roadmap
#### C section
- [x] Main source file
- [x] Lexer
- [ ] Parser
- [ ] AST
- [ ] Optimization
- [ ] Visitor

#### Cave section
- [ ] Language specification
- [ ] Standard library
- [ ] Error diagnostics
- [ ] Tooling (formatter, linter)

#
### Design Goals
- Predictable compilation and runtime behavior
- Close-to-metal performance
- Familiarity for C developers
- Minimal abstraction overhead
#
### Non-Goals
- Runtime polymorphism
- Garbage collection
- Cross-platform support beyond UNIX-like systems
#
### License
This project is licensed under the MIT License.
#
#
