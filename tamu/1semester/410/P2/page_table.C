#include "page_table.H"

PageTable::PageTable ()
{
	return;
}


void PageTable::init_paging (FramePool * _kernel_mem_pool, FramePool * _process_mem_pool,
	const unsigned long _shared_size)
{
	return;
}


void PageTable::load ()
{
	return;
}


void PageTable::enable_paging ()
{
	return;
}

void PageTable::handle_fault (REGS * _r)
{
	return;
}