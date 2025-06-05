/*
     File        : nonblocking_disk.H

     Author      : Rahul Ravi Kadam

     Date        : 11/12/2024
     Description : 

*/

#ifndef _NONBLOCKING_DISK_H_
#define _NONBLOCKING_DISK_H_

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include "simple_disk.H"
#include "thread.H"
#include "queue.H"

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* N o n B l o c k i n g D i s k  */
/*--------------------------------------------------------------------------*/

class NonBlockingDisk : public SimpleDisk {

   Queue * blocked_queue;
   int blocked_queue_size;

public:

   Thread * get_top_thread();
   /* Return the thread at the top of the blocked threads queue. */
   
   void wait_until_ready();
   /* Add current thread to end of blocked threads queue and yield
      CPU to next thread */

   NonBlockingDisk(DISK_ID _disk_id, unsigned int _size); 
   /* Creates a NonBlockingDisk device with the given size connected to the 
      MASTER or DEPENDENT slot of the primary ATA controller.
      NOTE: We are passing the _size argument out of laziness. 
      In a real system, we would infer this information from the 
      disk controller. */

   /* DISK OPERATIONS */

   virtual void read(unsigned long _block_no, unsigned char * _buf);
   /* Reads 512 Bytes from the given block of the disk and copies them 
      to the given buffer. No error check! */

   virtual void write(unsigned long _block_no, unsigned char * _buf);
   /* Writes 512 Bytes from the buffer to the given block on the disk. */

   bool check_blocked_thread_in_queue();
   /* Checks if the disk is ready to transfer data and threads in blocked
      state exist in the blocked queue. */

};

#endif
