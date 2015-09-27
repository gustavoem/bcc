/*
    File: frame_pool.H

    Author: R. Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 12/09/03

    Description: Management of the Free-Frame Pool.


*/

#ifndef _FRAME_POOL_H_                   // include file only once
#define _FRAME_POOL_H_

/*--------------------------------------------------------------------------*/
/* DEFINES */
#define LONG_SIZE sizeof(long)
#define FRAME_SIZE 4096
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* F r a m e   P o o l  */
/*--------------------------------------------------------------------------*/

class FramePool {

private:

    // Pointer to address of the frame that has the info of the frame pool
    //
    // frame_pool_info[0] contains bitmap for:
    //  frames 0 to frame sizeof(unsigned long) * 8 - 1
    // frame_pool_info[1] contains bitmap for:
    //   frames from sizeof(unsigned long) * 8  - 1 to 2 * (sizeof(unsigned long) * 8 -1)
    //
    // bit mapping: bit 0 = free frame
    //
    unsigned long * free_frames;

    
    // Stores the base address of the frame pool
    //
    unsigned long base_n;


    // Stores the number of frames in the frame pool
    //
    unsigned long frames_n;


    // Stores the address of the frame which contains information about the frame.
    // In our implementation, this is the begining of the free_frames vector
    //
    unsigned long info_frame_n;


    // Stores the location of the head_frame when this frame was instatiated. Then this
    // frame becomes this head and allows us to create a linked list of frames.
    //
    FramePool * previous_frame;


    // Stores the head of a linked list of frames
    //
    static FramePool * head_frame;



public:
  

   FramePool(unsigned long _base_frame_no,
             unsigned long _nframes,
             unsigned long _info_frame_no);
    /* Initializes the data structures needed for the management of this
      frame pool. This function must be called before the paging system
      is initialized.
      
      _base_frame_no is the frame number at the start of the physical memory
      region that this frame pool manages.

      _nframes is the number of frames in the physical memory region that this
      frame pool manages. q

      e.g. If _base_frame_no is 16 and _nframes is 4, this frame pool manages
      physical frames numbered 16, 17, 18 and 19

      _info_frame_no is the frame number (within the directly mapped region) of
      the frame that should be used to store the management information of the
      frame pool. However, if _info_frame_no is 0, the frame pool is free to
      choose any frame from the pool to store management information.
      */


    unsigned long get_frame();
    /* Allocates a frame from the frame pool. If successful, returns the frame
     * number of the frame. If fails, returns 0. */


    void mark_inaccessible (unsigned long _base_frame_no, unsigned long _nframes);
    /* Mark the area of physical memory as inaccessible. The arguments have the
    * same semanticas as in the constructor.
    */


    static void release_frame (unsigned long _frame_no);
    /* Releases frame back to the given frame pool.
      The frame is identified by the frame number. 
      NOTE: This function is static because there may be more than one frame pool
      defined in the system, and it is unclear which one this frame belongs to.
      This function must first identify the correct frame pool and then call the frame
      pool's release_frame function. */



};
#endif
