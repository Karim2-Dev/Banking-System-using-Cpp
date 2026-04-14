# 🏦 Bank Management System (C++)

A comprehensive **CLI-based Bank Management System** built with C++. This project focuses on core programming concepts, data persistence, and a robust permission-based security system.

## 🚀 Key Features

* **User Authentication & Authorization**: Secure login system with a unique **Bitwise Permission** logic.
* **Permission Management**: Granular control over user actions (Show List, Add, Delete, Update, Find, and Transactions).
* **Client Management**: Full CRUD operations for bank clients (Create, Read, Update, Delete).
* **Transactions Engine**: Handles deposits and withdrawals with real-time balance validation.
* **Data Persistence**: All data is stored and retrieved from flat files (`.txt`), ensuring data is saved between sessions.
* **Modular Design**: Organized using Namespaces, Structs, and Enums for high readability and maintainability.

## 🛠️ Tech Stack

* **Language**: C++
* **OS**: Developed and tested on **Fedora Linux**.
* **Concepts**: File Handling, Bitwise Operations, Vectors, String Manipulation.

## 📂 Project Structure

* `BankSystem.h`: Contains the core logic, data structures, and UI functions.
* `ClientsData.txt`: Storage for client records.
* `UsersData.txt`: Storage for user credentials and permission flags.

## 📖 How it Works (Permission Logic)

The system uses a **Flag-based system** to manage permissions:

* Each action has a specific power-of-two value (e.g., `enAddNewClientAccess = 2`).
* Permissions are checked using the Bitwise `&` operator to ensure the current user has the right to perform an action.
