#include "frame_pool.H"

FramePool * FramePool::head_frame = 0;

FramePool::FramePool (unsigned long _base_frame_no, unsigned long _nframes, 
    unsigned long _info_frame_no)
{
	Console::puts ("\n\nentered framepool() to create this guy: ");
	Console::putui (_base_frame_no);
	Console::putui (_nframes);
	Console::putui (_info_frame_no);

    // Decides the free frame location
    if (_info_frame_no != 0)
        info_frame_n =  _info_frame_no; // I'm assuming that if you're doing this,
					// this frame number is already unavailable
					// inside its frame pool creator 
    else
        info_frame_n = _base_frame_no;
		

    // Sets the free_frame address
    free_frames = (unsigned long *) ((info_frame_n) * (FRAME_SIZE));

    // Saves parameters
    base_n = _base_frame_no;
    frames_n = _nframes;

    // Makes all frames available
    for (unsigned long i = 0; i < _nframes; i++)
    {
        free_frames[i] = 0;
    }
    // And if the info frame is inside the frame pool, make it unavailable
    if (_info_frame_no == 0)
	free_frames[0] = 0x1;
    
    Console::puts ("free_frames[0]: ");
    Console::putui (free_frames[0]);

    // List of frames update
    FramePool * prev = FramePool::head_frame;
    FramePool::head_frame = this;
    previous_frame = prev;
}


unsigned long FramePool::get_frame ()
{
	Console::puts ("\n\nEntered get_frame. Info frame no: ");
	Console::putui (info_frame_n);
	Console::puts (" From frame: ");
	Console::putui ((unsigned int)this);
    for (unsigned long i = 0; i < frames_n; i++)
    {
        unsigned long j = i / LONG_SIZE;
        unsigned long mask = 0x1 << (i % (unsigned long)LONG_SIZE);
	
	//Console::puts ("\nSeeing frame: ");
	//Console::putui (i);
//	Console::puts ("\nfree_frame[j] = ");
//	Console::putui (free_frames[j]);
        if (!(free_frames[j] & mask))
        {
            // Makes frame unavailable and return frame number
//		Console::puts ("\nThis is free, lets use it");
            free_frames[j] = free_frames[j] | mask;
//		Console::puts ("\n(after use) free_frame[j] = ");
//		Console::putui (free_frames[j]);
		//Console::puts (" i =");
//		Console::putui (i);
//		Console::puts (" j =");
//		Console::putui (j);
//		Console::puts (" mask = ");
//		Console::putui (mask);
//		Console::puts ("\n");
		//showFramesStates ();
            return i + base_n;
        }
//	if(i>0)	while (true);

    }
	Console::puts ("\nCouldn't find a free frame");
	while(true); 
    return 0;
}


void FramePool::mark_inaccessible (unsigned long _base_frame_no, unsigned long _nframes)
{
    for (unsigned long i = _base_frame_no; i < _base_frame_no + _nframes; i++)
    {
        unsigned long j = i / LONG_SIZE;
        unsigned long mask = 1 << (i % LONG_SIZE);

        // Console::puts ("\nBefore | After making unaccessible: ");
        // Console::putui (free_frames[j]);

        free_frames[j] = free_frames[j] | mask;

        // Console::puts (" | ");
        // Console::putui (free_frames[j]);
    }
}


void FramePool::release_frame (unsigned long _fram_no)
{
    // First identify the currect frame
    FramePool * frame_pool = FramePool::head_frame;
    while (frame_pool != 0 && 
        (frame_pool->base_n > _fram_no || 
        ((frame_pool->base_n + frame_pool->frames_n) < _fram_no)))
        frame_pool = frame_pool->previous_frame;


    // This happens when someone tries to release a frame with an index out of the 
    // possible range
    if (frame_pool == 0) 
    {
        Console::puts ("Frame number out of rage... doing nothing\n");
        return; 
    }

    // Now, assuming that we found the frame_pool, free the frame
    unsigned long info_n = frame_pool->info_frame_n;
    unsigned long * free_frames = (unsigned long *) (info_n * (FRAME_SIZE));
    unsigned long j = _fram_no / LONG_SIZE;
    unsigned long mask = ~(1 << (_fram_no % LONG_SIZE));
    free_frames[j] = free_frames[j] & mask;
}


void FramePool::showFramesStates ()
{
        Console::puts ("Frames states from frame pool ");
        Console::putui ((unsigned int) this);
    for (unsigned long i = 0; i < frames_n; i++)
    {
        unsigned long j = i / LONG_SIZE;
        unsigned long mask = 1 << (i % LONG_SIZE);
        Console::putui (!(!(free_frames[j] & mask)));
    }
}
