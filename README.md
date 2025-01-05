# Random Number Generator

A C++17-based modular random number generator with multi-label management, viewing, and deletion features.

## Features

- **Non-repeating Random Numbers**: Manages generated numbers by label so that duplicates are not generated under the same label.
- **Multiple Commands**:
  - `generate`: Generate random numbers
  - `list`: View all labels and their corresponding random numbers
  - `delete`: Delete a specific label and its generated numbers
- **Modular Design**:
  - **`Config`**: Handles argument parsing and configuration
  - **`Storage`**: Manages data reading and writing
  - **`RandomGenerator`**: Handles the random number generation logic
  - **`CommandHandler`**: Executes commands and business logic
- **Easy to Extend**: Facilitates adding more commands or features in the future.

## Requirements

- **Compiler**: A C++17-compatible compiler (e.g., [Clang](https://clang.llvm.org/) or GCC 7.0+)
- **Operating System**: Works on Linux, macOS, Windows, etc.

## Build and Run

1. **Clone the repository** (or download the source code):
   ```bash
   git clone https://github.com/<your-username>/random_generator.git
   cd random_generator

2. **Compile** (using Make):
   ```bash
   make
3. **Run**:
   * Generate random numbers:
   ``` bash
   ./random_generator generate <min_value> <max_value> <count> [label]
   ```
   Example:
   ``` bash
   ./random_generator generate 1 100 5 exampleLabel
   ```
   This generates 5 non-repeating random numbers in the range [1, 100] under the label exampleLabel.
   * List all labels and numbers:
   ``` bash
   ./random_generator list
   ```
   This displays all existing labels (e.g., aaa, bbb) and their corresponding random numbers.
   * Delete a specific label:
   ``` bash
   ./random_generator delete <label>
   ```
   For example:
   ``` bash
   ./random_generator delete aaa
   ```
   Removes all random numbers under label aaa and rewrites the storage file.
4. **Clean up** (optional):
   ``` bash
   make clean
   ```
   Removes the generated executable and intermediate files.
## Todo
  * Custom Storage File: By modifying the Storage module or using environment variables, you can change the default storage file name (currently generated_numbers.txt).
  * Add Commands: For example, implement a reset command to clear all labels, or export data to CSV/JSON.  
  * Logging: Write logs whenever new numbers are generated or labels are deleted, for easier auditing and debugging.
  * Multi-threading: For high-volume random number generation, consider a multi-threading approach with thread-safe data management.
