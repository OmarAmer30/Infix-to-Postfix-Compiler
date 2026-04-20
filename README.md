# 🧮 Infix to Postfix Compiler

This project is a simple **compiler front-end** that converts **infix expressions** into **postfix notation (Reverse Polish Notation)** using a **recursive descent parser**.

---

## 📌 Features

* Supports arithmetic expressions with:

  * `+`, `-`, `*`, `/`
  * `div`, `mod`
* Handles:

  * Integers (`NUM`)
  * Identifiers (`ID`)
  * Parentheses `( )`
* Implements:

  * **Lexical Analysis (Scanner)**
  * **Syntax Analysis (Parser)**
  * **Postfix Code Generation**

---

## 🧠 How It Works

The program reads an infix expression from a file, tokenizes it using a **lexer**, then parses it using a **recursive descent parser** based on a context-free grammar.

During parsing, it generates **postfix output** by printing operators after their operands.

---

## 📖 Grammar (Final Form)

The grammar used after eliminating ambiguity and left recursion:

```
start → expr EOF

expr → term moreterms

moreterms → + term { print('+') } moreterms
          | - term { print('-') } moreterms
          | ε

term → factor morefactors

morefactors → * factor { print('*') } morefactors
            | / factor { print('/') } morefactors
            | div factor { print('DIV') } morefactors
            | mod factor { print('MOD') } morefactors
            | ε

factor → (expr)
       | id   { print(id) }
       | num  { print(num) }
```

---

## ⚙️ Components

### 🔹 1. Lexical Analyzer (`lexan`)

* Reads characters from input file
* Converts them into tokens:

  * `NUM`, `ID`, `DIV`, `MOD`
  * Operators like `+`, `-`, `*`, `/`
* Ignores whitespace

---

### 🔹 2. Parser Functions

* `expr()` → handles `+` and `-`
* `term()` → handles `*`, `/`, `div`, `mod`
* `factor()` → handles:

  * numbers
  * identifiers
  * parentheses

---

### 🔹 3. Code Generation (`emit`)

* Outputs postfix notation
* Example:

  ```
  Input:  2 + 3 * x
  Output: NUM(2) NUM(3) ID(x) * +
  ```

---

## ▶️ Example

### Input:

```
2 + 5 * 3
```

### Output:

```
NUM(2) NUM(5) NUM(3) * +
```

---

## 🎯 Key Concepts

* Recursive Descent Parsing
* Operator Precedence
* Left Recursion Elimination
* Lexical Analysis
* Syntax-Directed Translation

---

## 📚 Notes

* Parentheses are used only for parsing and do not appear in postfix output.
* `div` performs integer division.
* `mod` returns remainder.

---

## 👨‍💻 Author

Omar Aamer

---
