#include <stdio.h>

int main() {
    int a = 42;
    int b = 58;
    int result;

    // Inline ARM assembly to add a and b
    __asm__
    (
        "ADD %0, %1, %2\n"   // result = a + b
        : "=r" (result)      // output operand
        : "r" (a), "r" (b)   // input operands
    );

    // Print the result
    printf("The result of %d + %d is: %d\n", a, b, result);

    return 0;
}
