#include "lib-header/stdtype.h"
#include "lib-header/syscall.h"
#include "lib-header/fat32.h"

int main(void) {
    __asm__ volatile("mov %0, %%eax" : /* <Empty> */ : "r"(0xDEADBEEF));
    // __asm__ volatile("int $0x1");
    while (TRUE){
        syscall(SYSCALL_NULL, 0, 0, 0);
        // __asm__ volatile("int $0x1");
    }

    return 0;
}
