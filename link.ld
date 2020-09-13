SECTIONS 
{
    . = 0x7c00;

    /*-----------------------*/
    /*        LOADER         */
    /*-----------------------*/

    _loader_start = .;
    .loader : {
        boot.asm.o(.text)
    }
    _loader_end = .;

    /*-----------------------*/
    /*      END LOADER       */
    /*-----------------------*/


    /*-----------------------*/
    /*        KERNEL         */
    /*-----------------------*/

    . = 0x100000;
    
    kernel_start = .;
    .text : {
        kernel.c.o(.text)
        *(.text)
        *(.rdata)
    }

    .rodata : {
        *(.rodata)
    }

    .eh_frame : {
        *(.eh_frame)
    }

    .bss : {
        *(.bss)   
    }

    .data : {
        *(.data)
        . = ALIGN(512);
    } = 0

    kernel_end = .;

    kernel_stack = 0x1000;

    /*_kernel_size = _kernel_end - _kernel_start;*/
    /*kernel_address = _kernel_start;
    kernel_sectecots = _kernel_size / 512;*/

    /*-----------------------*/
    /*      END KERNEL       */
    /*-----------------------*/
}