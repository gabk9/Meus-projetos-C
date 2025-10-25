int main(void) {
    const char hello[] = "Hello, World!";

    asm volatile (
        "mov $1, %%rax;"
        "mov $1, %%rdi;"
        "lea %0, %%rsi;"
        "mov $14, %%rdx;"
        "syscall"
        :
        :"m"(hello)
        :"%rax", "%rdi", "%rsi", "%rdx"
        
    );

    return 0;
}