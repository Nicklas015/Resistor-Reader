// Include necessary header files
#include <iostream>  // For input/output operations

// Using the standard namespace (Note: generally not recommended in larger projects)
using namespace std;

int main() {
    // Demonstrating an if statement with an init-statement (C++17 feature)
    // The init-statement allows you to declare and initialize a variable
    // that is scoped to the if-else block
    if (int a = 5; a < 8) {
        // This block executes if 'a' is less than 8
        cout << "Local variable aAAAAaaa is < 8\n";
    } else {
        // This block executes if 'a' is greater than or equal to 8
        // Note: In this case, this block will never execute because 'a' is always 5
        cout << "Local variable aAAAAAaa is >= 8\n";
    }

    // Return 0 to indicate successful program execution
    return 0;
}