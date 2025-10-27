#include "GIE_interface.h"
#include "GIE_reg.h"

void GIE_voidEnableGlobal(void) {
    __asm volatile("SEI");
}

void GIE_voidDisableGlobal(void) {
    __asm volatile("CLI");
}