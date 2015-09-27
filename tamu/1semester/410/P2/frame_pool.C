#include "frame_pool.H"

FramePool::FramePool (unsigned long _base_frame_no, unsigned long _nframes, 
    unsigned long _info_frame_no)
{
    // Decides the free frame location
    if (_info_frame_no != 0)
        info_frame_n = _info_frame_no;
    else
        info_frame_n = _base_frame_no;

    // Sets the free_frame address
    free_frames = (unsigned long *) 
        ((info_frame_n) * (FRAME_SIZE / LONG_INT_SIZE));

    // Saves parameters
    base_n = _base_frame_no;
    frames_n = _nframes;

    // Makes all frames of this pool available
    for (unsigned long i = 0; i < _nframes; i++)
    {
        free_frames[i] = 0;
    }

    // Makes the info frame unavailable
    unsigned long j = info_frame_n / LONG_INT_SIZE;
    unsigned long mask = 1 << (info_frame_n % LONG_INT_SIZE);
    free_frames[j] = mask;
}


unsigned long FramePool::get_frame ()
{
    for (unsigned long i = 0; i < frames_n; i++)
    {
        unsigned long j = i / LONG_INT_SIZE + 2;
        unsigned long mask = 1 << (i % LONG_INT_SIZE);
        if (!(free_frames[j] & mask))
        {
            // Makes frame unavailable and return frame number
            free_frames[j] = free_frames[j] | mask;
            return i + base_n;
        }
    }
    return 0;
}


void FramePool::mark_inaccessible (unsigned long _base_frame_no, unsigned long _nframes)
{
    for (unsigned long i = _base_frame_no; i < _base_frame_no + _nframes; i++)
    {
        unsigned long j = i / LONG_INT_SIZE + 2;
        unsigned long mask = 1 << (i % LONG_INT_SIZE);
        free_frames[j] = free_frames[j] | mask;
    }
}


void FramePool::release_frame (unsigned long _fram_no)
{
    /*// First identify the currect frame
    unsigned long * frame_pool = 0x0;

    // Now free the frame
    unsigned long j = _fram_no / LONG_INT_SIZE + 2;
    unsigned long mask = ~(1 << (_fram_no % LONG_INT_SIZE));
    free_frames[j] = free_frames[j] & mask;*/
}
