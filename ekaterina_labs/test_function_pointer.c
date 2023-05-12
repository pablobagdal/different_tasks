#include<stdio.h>

void foo() {
    printf("Hello world\n");
    return;
}

int main(int argc, char const *argv[]) 
{
    void (*func_ptr)();

    func_ptr = foo;

    func_ptr();

    printf("%s", argv[1]);
    
    return 0;
}
