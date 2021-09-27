#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <asm/io.h>

#define IOAPIC_BASE 0xFEC00000

void* ioapic_ptr;

int init_module(void)
{
	void* ioapic_sel = NULL;
	void* ioapic_win = NULL;
	int ident = 0;
	int ver = 0;

	/*remaps phy address space to kernels virtual address space*/
	/*thus phy address made available to kernel*/

	ioapic_ptr = ioremap(IOAPIC_BASE, PAGE_SIZE);
	ioapic_sel = (void*)((long)(ioapic_ptr + 0x00));
	ioapic_win = (void*)((long)(ioapic_ptr + 0x10));

	/*even though they are phy address mapped virtually*/
	/*direct pointer referencing no possible, use appropriate machine inst func*/
	iowrite32(0,ioapic_sel);
	ident = ioread32(ioapic_win);
	printk("\nIdentification : %08X\n",ident);

	iowrite32(1,ioapic_sel);
	ver = ioread32(ioapic_win);
	printk("\nVersion : %08X\n",ver);

	return(0);

}

void cleanup_module(void)
{
	iounmap(ioapic_ptr);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("chai.bpt@gmail.com");
MODULE_DESCRIPTION("STUDY:memory mapped address space");


