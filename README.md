# 🧮 Infix to Postfix Compiler (Recursive Descent + Symbol Table)

This project implements a simple **compiler front-end** that converts **infix expressions** into **postfix notation (Reverse Polish Notation)** using a **recursive descent parser**.

It also includes a **symbol table** to manage identifiers and reserved keywords (`div`, `mod`).

---

## 📌 Features

* Supports arithmetic operators:

  * `+`, `-`, `*`, `/`
  * `div`, `mod`
* Handles:

  * Integers (`NUM`)
  * Identifiers (`ID`)
  * Parentheses `( )`
* Supports **multiple expressions** separated by `;`
* Uses:

  * File input/output (`input.txt` → `output.txt`)
  * Symbol table for identifiers and keywords

---

## 🧠 Grammar (Final Form)

```plaintext
start → parse EOF

parse → expr ; parse
      | ε

expr → term moreterms

moreterms → + term { emit('+') } moreterms
          | - term { emit('-') } moreterms
          | ε

term → factor morefactors

morefactors → * factor { emit('*') } morefactors
            | / factor { emit('/') } morefactors
            | div factor { emit('DIV') } morefactors
            | mod factor { emit('MOD') } morefactors
            | ε

factor → (expr)
       | id   { emit(ID) }
       | num  { emit(NUM) }
```

---

## ⚙️ How It Works

### 🔹 1. Lexical Analyzer (`lexan`)

* Reads characters from `input.txt`
* Converts them into tokens:

  * `NUM`, `ID`, `DIV`, `MOD`
* Uses the **symbol table** to:

  * Store identifiers
  * Recognize keywords (`div`, `mod`)

---

### 🔹 2. Symbol Table

Stores all identifiers and keywords.

#### Structure:

```plaintext
index → (lexeme, token)
```

#### Example:

```plaintext
1 → ("x", ID)
2 → ("y", ID)
3 → ("div", DIV)
4 → ("mod", MOD)
```

#### Functions:

* `lookup(s)` → search for identifier
* `insert(s, token)` → add new identifier
* `init()` → preload keywords (`div`, `mod`)

---

### 🔹 3. Parser (Recursive Descent)

Functions correspond to grammar rules:

* `parse()` → handles multiple expressions
* `expr()` → handles `+`, `-`
* `term()` → handles `*`, `/`, `div`, `mod`
* `factor()` → handles:

  * numbers
  * identifiers
  * parentheses

---

### 🔹 4. Code Generation (`emit`)

Outputs postfix notation to `output.txt`.

---

## ▶️ Example

### Input (`input.txt`)

```plaintext
2 + 3 * x;
a mod 5;
```

### Output (`output.txt`)

```plaintext
NUM(2) NUM(3) ID(x) * +
ID(a) NUM(5) MOD
```

---

## 🎯 Key Concepts

* Recursive Descent Parsing
* Operator Precedence
* Left Recursion Elimination
* Lexical Analysis
* Symbol Table Design
* Syntax-Directed Translation

---

## 📚 Notes

* Each expression must end with `;`
* Parentheses are used only for parsing (not printed in output)
* `div` → integer division
* `mod` → remainder
* Keywords (`div`, `mod`) are reserved (not treated as identifiers)

---

## 👨‍💻 Author

Omar Aamer

---
