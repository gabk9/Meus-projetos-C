int main(void) {
    const char str[] = "Hello, World!\n";

    asm volatile (
        "mov $1, %%rax\n\t"
        "mov $1, %%rdi\n\t"
        "mov %0, %%rsi\n\t"
        "mov $14, %%rdx\n\t"
        "syscall\n\t"
        :
        : "m"(str)
        : "rax", "rdi", "rsi", "rdx", "rcx", "r11", "memory"
    );

    asm volatile (
        "mov $60, %%rax\n\t"
        "xor %%rdi, %%rdi\n\t"
        "syscall\n"
        "ret"
        :
        :
        : "rax", "rdi", "rcx", "r11"
    );

    return 0;
}