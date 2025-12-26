# WARNING: THIS PROJECT IS UNDER DEVELOPMENT

<div align="center">
    <h1>Cave-Lang</h1>
    <h4>A middle-ground between c and c++ for sane dev</h4>
</div>

#
### Overview
CaveLang is a light-weight and non-modular language designed to find that perfect 'sweet spot' between c and c++.

It focuses on simplicity, performance while giving necessary tooling for basic development needs.
#
### Features:
- Fast and lightweight
- Optimized 
- Gentle learning curve
- Only x86_64 linux support because who uses anything other than that
- Well documented API
#
### Requirements
- OS: [Linux](https://www.kernel.org) / [BSD](https://www.bsd.org) based operating systems
- Compiler: C
- Build utils: Make and [Cmake](https://www.cmake.org/)
#
### Installation
#### From source
```bash
git clone https://www.github.com/dhrxvxd-arch/cave-lang.git
cd cave-lang
mkdir -p
cmake -S . -B build/
```
#
### Usage
- Basic usage:
```bash
cave main.cav -o main
./main
```
- Advanced usage:
```bash
cave -i main.cav -o main -v
./main
```
#
### Source Structure
```bash
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
### Licence
<h4>This project is licenced under MIT Licence</h4>

#
#
