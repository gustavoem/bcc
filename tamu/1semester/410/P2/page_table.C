#include "page_table.H"

PageTable::PageTable ()
{
	return;
}


void PageTable::init_paging (FramePool * _kernel_mem_pool, FramePool * _process_mem_pool,
	const unsigned long _shared_size)
{
	kernel_mem_pool = _kernel_mem_pool;
	process_mem_pool = _process_mem_pool;
	shared_size = _shared_size;
	paging_enabled = 0;

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