# 📚 Book-Vault

Book-Vault is a console-based Library Management System developed in C. It helps manage a library's book inventory by enabling users to add, view, search, update, and delete book records. The system also supports file-based storage to persist data between sessions.

---

## 📌 Table of Contents

- [📖 Description](#-description)  
- [✨ Features](#-features)  
- [⚙️ Installation](#️-installation)  
- [🚀 Usage](#-usage)

---

## 📖 Description

Book-Vault is designed for small to medium-sized libraries to maintain their book inventory using a simple command-line interface. Each book in the system contains attributes like a unique ID, title, author, quantity, and availability status. The system supports core operations like adding new books, searching by various fields, updating records, and deleting entries.

It also uses file handling to save and load records from a text file (`library_data.txt`) ensuring persistence of data across multiple sessions.

---

## ✨ Features

- ➕ Add new book records with auto-incremented ID  
- 📋 Display all books in a neat table format  
- 🔍 Search books by:
  - ID
  - Title
  - Author  
- ✏️ Update existing book information  
- 🗑️ Delete books from the collection  
- 💾 File-based data persistence (`library_data.txt`)  
- ✅ Input validation for numeric fields

---

## ⚙️ Installation

To run Book-Vault locally, follow these steps:

### 1. **Clone the repository:**
```sh
   git clone https://github.com/your-username/Book-Vault.git
```
### 2. **Navigate to the project directory:**
```sh
cd Book-Vault
```
### 3. **Compile the C source file:**
```sh
gcc -o bookvault main.c
```
### 4. **Run the compiled program:**
```sh
./bookvault
```
⚠️ Ensure you have a C compiler like gcc installed before compiling the code.

---

## Usage

Once the application is running:

Choose from the menu to Add, Display, Search, Update, or Delete books.
Data is stored in a file named library_data.txt and automatically loaded at startup.
Use integer inputs for menu selections and numeric fields.
Exit the program using option 6 to ensure your data is saved.

