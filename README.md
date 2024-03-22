# Personal Finance Management System

This command-line Personal Finance Management System, implemented in C, provides a robust set of tools for efficiently managing personal finances. This task was assigned by our college professor, Dr. Parul Patel, for learning purposes, aiming to demonstrate how similar results to MySQL (DBMS) can be achieved using C. The project serves as a practical platform for honing C programming skills while exploring fundamental principles of financial data management.

## Overview

The Personal Finance Management System is designed to help individuals track their income, expenses, and financial goals. It offers a user-friendly command-line interface for easy navigation and management of financial records.

## Contains

This repository contains two files:
1. `mainFile.c`, which utilizes ANSI codes for color formatting (which may not be supported on all systems), and
2. `plain.c`, which offers similar functionalities without the ANSI color formatting.

## Features

- **Record Management**: Add, display, search, modify, and delete financial records seamlessly.
- **Data Sorting**: Arrange records based on amount, facilitating better organization and analysis.
- **Categorization**: Classify income sources and expenses for a clearer financial overview.
- **Loan Interest Calculation**: Calculate loan interests effortlessly, aiding in informed financial decisions.
- **Report Generation**: Produce a financial report displaying income, expenses, remaining income, and recommendations for financial distribution based on the predefined standard ratio of 50 : 30 : 20 for need, want, and investment respectively.

## How It Works

1. Upon launching the application, users are presented with a main menu displaying available options.
2. Users can select an option from the menu to perform specific tasks such as inserting records, displaying records, etc.
3. The application interacts with the file system to read, write, and manipulate financial records.
4. Users can input data such as record name, amount, and type using the command-line interface.
5. The application processes the user input and performs the requested operation, providing feedback to the user upon completion.

## How to Use

1. Compile the c program
    ```bash
    gcc mainFile.c -o finance_management
2. Run the executable

    ```bash
    ./finance_management
3. Follow the on-screen menu to perform various tasks related to personal finance management.

## How to Contribute

- If you'd like to contribute to the project or report issues, feel free to fork the repository and submit pull requests.
  - Clone the repository to your local machine.
  - Run the program into your local system to test.
- To clone the repository:

   ```bash
   https://github.com/Rucha-Ambaliya/Personal_Finance_Management.git
- Feel free to fork this project and make your own improvements! If you have any questions or suggestions, don't hesitate to reach out.

## Acknowledgements

Special thanks to Our Professor Dr. Parul Patel for their guidance and encouragement in challenging us to develop a project on file management system in C. Their support has been invaluable in shaping this project.

## Feedback

- If you have any feedback, suggestions, or questions, please feel free to reach out. I appreciate your interest in this project!
