#include "../lib-header/syscall.h"
#include "../lib-header/stdtype.h"


void syscall(uint32_t eax, uint32_t ebx, uint32_t ecx, uint32_t edx) {
    __asm__ volatile("mov %0, %%ebx" : /* <Empty> */ : "r"(ebx));
    __asm__ volatile("mov %0, %%ecx" : /* <Empty> */ : "r"(ecx));
    __asm__ volatile("mov %0, %%edx" : /* <Empty> */ : "r"(edx));
    __asm__ volatile("mov %0, %%eax" : /* <Empty> */ : "r"(eax));
    // Note : gcc usually use %eax as intermediate register,
    //        so it need to be the last one to mov
    __asm__ volatile("int $0x30");
}

void delay(uint32_t tick){
    uint32_t currentTick = 0;
    uint32_t cachedTick = 0;
    syscall(SYSCALL_GET_TICK, (uint32_t) &currentTick, 0, 0);
    cachedTick = currentTick + tick;

    while (currentTick < cachedTick){
        syscall(SYSCALL_GET_TICK, (uint32_t) &currentTick, 0, 0);
    }
}