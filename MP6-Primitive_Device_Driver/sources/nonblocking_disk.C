/*
     File        : nonblocking_disk.c

     Author      : Rahul Ravi Kadam
     Modified    : 11/12/2024

     Description : 

*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include "assert.H"
#include "utils.H"
#include "console.H"
#include "nonblocking_disk.H"
#include "scheduler.H"
#include "thread.H"
#include "machine.H"

extern Scheduler * SYSTEM_SCHEDULER;

/*--------------------------------------------------------------------------*/
/* CONSTRUCTOR */
/*--------------------------------------------------------------------------*/

NonBlockingDisk::NonBlockingDisk(DISK_ID _disk_id, unsigned int _size) 
  : SimpleDisk(_disk_id, _size) {
  blocked_queue = new Queue();
  blocked_queue_size = 0;
}

/*--------------------------------------------------------------------------*/
/* BLOCKED DISK OPERATIONS */
/*--------------------------------------------------------------------------*/

Thread * NonBlockingDisk::get_top_thread()
{
  // Get the thread at the top of the blocked queue and return
  Thread *top = this->blocked_queue->dequeue();
  this->blocked_queue_size--;
  return top;
}

void NonBlockingDisk::wait_until_ready()
{
  // Add current thread to end of blocked threads queue
  this->blocked_queue->enqueue(Thread::CurrentThread());
  this->blocked_queue_size++;
  SYSTEM_SCHEDULER->yield();
}

bool NonBlockingDisk::check_blocked_thread_in_queue()
{
  // Check if disk is ready to transfer data and threads exist in blocked state
  return ( SimpleDisk::is_ready() && (this->blocked_queue_size > 0) );
}

/*--------------------------------------------------------------------------*/
/* SIMPLE_DISK FUNCTIONS */
/*--------------------------------------------------------------------------*/

void NonBlockingDisk::read(unsigned long _block_no, unsigned char * _buf) {
  // -- REPLACE THIS!!!
  SimpleDisk::read(_block_no, _buf);

}


void NonBlockingDisk::write(unsigned long _block_no, unsigned char * _buf) {
  // -- REPLACE THIS!!!
  SimpleDisk::write(_block_no, _buf);
}
