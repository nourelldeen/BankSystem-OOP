\# 🏦 Bank System - Object-Oriented Banking Application



A comprehensive C++ banking system with client management, transaction processing, user authentication, permissions management, and real-time currency exchange functionality. Built with modern C++ principles and a clean object-oriented architecture.



\## ✨ Features



\### 🔐 Authentication \& Security

\- \*\*Secure Login System\*\* with username/password authentication

\- \*\*Permissions-based access control\*\* (Create, Read, Update, Delete, List, Find)

\- \*\*Login activity logging\*\* to track user access

\- \*\*Session management\*\* with role-based permissions



\### 👥 User Management

\- \*\*Add, Update, Delete, and Find\*\* users

\- \*\*List all registered users\*\* with their permissions

\- \*\*Permission flags\*\* for granular access control



\### 💳 Client Management

\- \*\*Full CRUD operations\*\* for bank clients

\- \*\*Account number, PIN, and balance tracking\*\*

\- \*\*Client search\*\* by account number

\- \*\*View client list\*\* with complete details



\### 💰 Transactions

\- \*\*Deposits\*\* to client accounts

\- \*\*Withdrawals\*\* with balance validation

\- \*\*Transfers\*\* between clients with automatic balance updates

\- \*\*Transfer logs\*\* for audit trail

\- \*\*Total balance summary\*\* across all clients



\### 💱 Currency Exchange

\- \*\*Currency management\*\* with exchange rates

\- \*\*Real-time currency conversion\*\*

\- \*\*Update exchange rates\*\*

\- \*\*Currency list\*\* with current rates

\- \*\*Currency calculator\*\* for conversions



\### 📊 Logging

\- \*\*Transfer logs\*\* with timestamps

\- \*\*Login logs\*\* for security auditing

\- \*\*Transaction history\*\* tracking



\## 🏗️ Architecture

BankSystem-OOP/

├── include/ # Header files

│ ├── clsBankClient.h # Client class with CRUD operations

│ ├── clsUser.h # User class with permission management

│ ├── clsCurrency.h # Currency class with exchange rates

│ ├── clsPerson.h # Base person class

│ ├── clsDate.h # Date handling utilities

│ ├── clsScreen.h # Base screen class

│ ├── clsInputValidate.h # Input validation utilities

│ ├── clsString.h # String manipulation utilities

│ ├── clsUtil.h # General utilities

│ └── \*Screen.h # All UI screen classes

├── src/ # Source files

│ ├── main.cpp # Application entry point

│ └── CMakeLists.txt # CMake build configuration

├── data/ # Data storage (JSON-like text files)

│ ├── Clients.txt # Client data

│ ├── Users.txt # User accounts

│ ├── Currencies.txt # Currency exchange rates

│ ├── TransferLog.txt # Transfer history

│ └── LoginRegister.txt # Login activity log

├── CMakeLists.txt # Root CMake configuration

├── LICENSE # MIT License

├── CONTRIBUTING.md # Contribution guidelines

└── README.md # This file



text



\## 🚀 Getting Started



\### Prerequisites

\- \*\*C++17\*\* or higher

\- \*\*CMake\*\* 3.10 or higher

\- \*\*Visual Studio\*\* (Windows) or \*\*GCC/Clang\*\* (Linux/macOS)



\### Installation



\*\*1. Clone the repository\*\*

```bash

git clone https://github.com/nourelldeen/BankSystem-OOP.git

cd BankSystem-OOP

2\. Build with CMake



bash

mkdir build \&\& cd build

cmake ..

cmake --build .

3\. Run the application



bash

\# Windows

./build/BankSystem.exe



\# Linux/macOS

./build/BankSystem

Default Login Credentials

Username	Password	Role

admin	admin123	Full Admin Access

💻 Usage Examples

Login Screen

After launching the application, you'll be presented with the login screen. Enter your credentials to access the main menu.



Main Menu

text

===========================================

&#x20;        Bank System Main Menu

===========================================

\[1] Manage Clients

\[2] Manage Users

\[3] Transactions

\[4] Currency Exchange

\[5] Transfer Log

\[6] Total Balance

\[7] Login Register

\[8] Logout

===========================================

Client Management

Add new clients with account number, PIN, and balance



Update client information



Delete clients from the system



Find clients by account number



List all clients with their details



Transactions

Deposit: Add funds to a client's account



Withdraw: Remove funds (with balance validation)



Transfer: Move funds between clients



All transactions are logged for audit purposes



🛠️ Technologies Used

C++17 - Core language



Object-Oriented Programming - Classes, inheritance, polymorphism



File I/O - Persistent data storage



STL - Vectors, strings, algorithms, maps



CMake - Cross-platform build system



📸 Screenshots

Coming soon - Screenshots of the application in action



🤝 Contributing

Contributions are welcome! Please see CONTRIBUTING.md for guidelines.



📄 License

This project is licensed under the MIT License - see the LICENSE file for details.



👨‍💻 Author

Nour Eldeen



GitHub: @nourelldeen



🧠 Development Notes

This project was originally developed by me. AI tools were used to assist with documentation, repository organization, code review, and development workflow improvements.



🎯 Key Learning Outcomes

OOP Principles: Encapsulation, inheritance, polymorphism in action



File Handling: Persistent data storage with CRUD operations



User Authentication: Secure login with permission-based access



Transaction Processing: Financial operations with validation



Clean Architecture: Separation of concerns with screen/controller pattern



Modern C++: const correctness, pass-by-reference, STL usage

