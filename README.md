# Arena Allocator & Simple Parser
A basic C++ expression parser using a custom memory arena  
**by: Matthew Stoklosinski**

---

## Overview
This project implements a simple expression parser in C++ that can:

- Tokenize a string input into numbers, identifiers, operators, and parentheses.
- Parse `let` statements, arithmetic expressions, and parentheses.
- Build an Abstract Syntax Tree (AST) using custom nodes: `NumberNode`, `IdentifierNode`, `OperatorNode`, `AssignmentNode`.
- Use a custom arena allocator to efficiently allocate memory for AST nodes.

This project is designed as an educational exercise in memory management, parsing, and AST construction.

---

## Features
- Tokenizes input expressions into a structured `Token` vector.
- Supports arithmetic operations: `+`, `-`, `*`, `/`.
- Handles `let` statements and variable assignment.
- Respects operator precedence using separate `parseExpression` and `parseTerm` functions.
- Memory-efficient allocation using a custom arena allocator.
- Simple command-line testing.

---

## Directory Structure
/src → C++ source files (.cpp)
/include → Header files (.h)
/bin → Compiled executables (created after build)
Makefile → Build script
README.md → Project description


---

## Requirements
- C++17 or newer
- Standard Template Library (STL)
- C++ compiler such as:
  - `g++`
  - `clang++`

---

## Building With Make
This project uses a Makefile to compile the code.

From the project root:

1. Open a terminal in the project directory.
2. To clean up object files and the executable: make clean
3. Run the command: make
4. After building, you can run the program from the terminal: ./bin/parser
