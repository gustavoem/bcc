#include "page_table.H"

// Static variables
//
PageTable * PageTable::current_page_table = NULL;
unsigned int PageTable::paging_enabled = FALSE;
FramePool * PageTable::kernel_mem_pool = NULL;
FramePool * PageTable::process_mem_pool = NULL;
unsigned long PageTable::shared_size = 0;





PageTable::PageTable ()
{
    Console::puts ("Entered PageTable ()\n");
    // Initializes page_directory. Gives it a frame to store entries
    // what if kenerl_mem_pool == NULL?
    if (kernel_mem_pool == NULL)
    {
        Console::puts ("Unable to create a PageTabel. First you need to initialize class members\n");
        return;
    }

    page_directory = (unsigned long *) (kernel_mem_pool->get_frame () * FRAME_SIZE); 
    Console::puts ("Created Page Directory at ");
    Console::putui ((unsigned long) page_directory);
    Console::puts ("\n");

    // Creates a frame for the first page table in the page_directory, which maps memory
    // from 0MB to 4MB
    unsigned long * first_page_table = (unsigned long *) 
        (kernel_mem_pool->get_frame () * FRAME_SIZE);
    Console::puts ("Created first Page Directory at ");
    Console::putui ((unsigned long) first_page_table);
    Console::puts ("\n");

    // Now we map addresses from 0MB to 4MB
    // Holds the physical address of where a page is
    unsigned long address = 0;

    // Maps the first 4MB of memory (i is the frame number)
    unsigned int i;
    for (i = 0; i < 1024; i++)
    {
        // Masks page_table entry to: superv. level, read/write present (011 in binary)
        first_page_table[i] = address | 3;    // <- direct addressing
        address = address + FRAME_SIZE;
    }

    // Sets the first page table as the first entry in the page_directory
    page_directory[0] = ((unsigned long) first_page_table) | 3; 


    // Sets the rest of the page_directory as supervisor level,
    // read/write, not present(010 in binary)
    for (i = 1; i < 1024; i++)
        page_directory[i] = 0 | 2;

    Console::puts ("Leaving  PageTable ()\n");
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
    paging_enabled = TRUE;
    write_cr0(read_cr0() | 0x80000000); // set the paging bit in CR0 to 1
}

void PageTable::handle_fault (REGS * _r)
{
    return;
}