#include "lib-header/portio.h"
#include "lib-header/stdtype.h"
#include "lib-header/stdmem.h"
#include "lib-header/gdt.h"
#include "lib-header/framebuffer.h"
#include "lib-header/kernel_loader.h"
#include "lib-header/idt.h"
#include "lib-header/interrupt.h"
#include "lib-header/keyboard.h"
#include "lib-header/pit.h"
#include "lib-header/tss.h"
#include "lib-header/syscall.h"
#include "lib-header/fat32.h"
#include "lib-header/paging.h"
#include "lib-header/memory_manager.h"

#include "lib-header/task.h"

void kernel_setup(void) {
    enter_protected_mode(&_gdt_gdtr);
    pic_remap();
    initialize_idt();
    framebuffer_clear();
    framebuffer_set_cursor(0, 0);

    activate_interrupts();
    
    gdt_install_tss();
    set_tss_register_kernel();
    set_tss_kernel_current_stack();
    initialize_tasking();

    activate_irq(IRQ_TIMER);
    activate_irq(IRQ_KEYBOARD);
    activate_irq(IRQ_PRIMARY_ATA);
    activate_irq(IRQ_SECOND_ATA);

    register_irq_handler(IRQ_KEYBOARD, keyboard_isr);
    register_irq_handler(IRQ_TIMER, pit_isr);

    enable_system_calls();

    initialize_memory();

    // allocate_single_user_page_frame(0);

    keyboard_state_activate();

    // FAT32DriverRequest shell = {
    //     .name                  = "sh",
    //     .ext                   = "\0\0\0",
    //     .parent_cluster_number = ROOT_CLUSTER_NUMBER + 1,
    //     .buffer_size           = 0x100000,
    // };
    // create_task(shell, 1, STACKTYPE_USER, INTERRUPT_FLAG);


    while (TRUE);

}