# Vectors-c

The **Vectors-c** project implements generalized vectors for working with various data types (integer, real, complex). The main emphasis is on the console interface, which allows performing arithmetic operations on vectors (addition, scalar product), as well as changing, adding and deleting vectors.

## Description of functionality

**Main functionality:**
- **Vectors:** Creating vectors, changing their dimensions, arithmetic operations (addition, scalar product).
- **Console interface:** The user selects an operation from the menu, enters the required data, and the result is displayed on the screen.

**Error Handling:**
- Errors are handled using return codes (`VectorError`) and the `errorsHandler()` function, which prints an error message and allows the operation to be completed gracefully.

## Build and run

### Prerequisites
- gcc compiler (MinGW or similar for Windows)
- Make

## How to Run

1. Clone the repository:
    ```bash
    git clone https://github.com/AlexanderTaran73/vectors-c.git
    cd vectors-c
    ```

2. Running the main program
    Run:
    ```bash
    make run
    ```

    or run directly:
    ```bash
    ./bin/main.exe
    ```

3. Building and running tests
    To build and run the tests:
    ```bash
    make test
    ```
    The tests are located in the test/src folder and are compiled into test/bin/test.exe. After the tests are completed, a message about passing all tests will be displayed in the console.

## Usage Documentation
After starting the program, a menu will be displayed, for example:

    Choose operation:
    1 - Addition
    2 - Scalar Product
    3 - Show all vectors
    4 - Change a vector
    5 - Add a vector
    6 - Remove a vector
    7 - Exit

Depending on the selected operation, the user enters the necessary data (vector indices, type, size, coordinates, etc.), and the program performs the corresponding operation and outputs the result.

## Project structure
```
    vectors-c/ 
    ├── bin/ # Compiled files of the main program
    ├── include/ # Header files
    ├── src/ # Program source code
    │
    ├── test/ # Project tests
    | ├── bin/ #Compiled test executables
    │ ├── include/ # Header files for tests
    │ └── src/ # Test source code
    │
    └── makefile # Script for building a project
```


## Author
[AlexanderTaran73](https://github.com/AlexanderTaran73)