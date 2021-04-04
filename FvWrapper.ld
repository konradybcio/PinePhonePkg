ENTRY(_start);

SECTIONS
{
    _start = 0x41110000;
    . = 0x41110000;
    .data : {
        *(.data)
    }
}
