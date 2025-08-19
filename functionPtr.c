#include <stdio.h>

void say_hello(unsigned char var)
{
    printf("Hello from the function handler! Passed value: %d\n", var);
}

void secondFoo(void (*foo)(unsigned char))
{
    foo(7);
}

int main() {

    // Create function pointer
    void (*func_ptr)(unsigned char);

    // Assign function pointer to say_hello function
    func_ptr = &say_hello;

    // Call out say_hello functon with function pointer
    func_ptr(5);

    // Call out say_hello function with secondFoo function by passing say_hello as an argument
    secondFoo(&say_hello);

    return 0;
}
