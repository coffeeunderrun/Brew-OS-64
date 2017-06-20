#include <cpu.h>

/* External function headers */
extern uint8_t in_port(uint16_t port);
extern void out_port(uint16_t port, uint8_t val);

extern void load_idt(void *p);
extern void load_tss(uint16_t sel);

extern bool get_int_flag();

extern void flush_page(void *p);
extern void flush_all_pages();

extern uint64_t read_cr0();
extern uint64_t read_cr1();
extern uint64_t read_cr2();
extern uint64_t read_cr3();
extern uint64_t read_cr4();

extern void write_cr0(uint64_t val);
extern void write_cr1(uint64_t val);
extern void write_cr2(uint64_t val);
extern void write_cr3(uint64_t val);
extern void write_cr4(uint64_t val);
