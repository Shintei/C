#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>


#include "bits.h"
#include "memory.h"


Memory M;
int fd;

void __attribute__ ((constructor)) init_mallocator(void);
void __attribute__ ((constructor)) finalize_mallocator(void);

// allocate for sizes > 1024
void * allocate_region(unsigned int size) {
  
  void *mapped_addr = mmap(NULL, size + sizeof(Region), PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  
  if(mapped_addr==MAP_FAILED) {
    perror("Mapping failed during allocate_region");
    exit(0);
  }

  Region * tmp = M.R;

  M.R = (Region *)mapped_addr;
  M.R->addr = mapped_addr + sizeof(Region);
  M.R->size = size;
  M.R->next = tmp;
  
  return M.R->addr;

}


  // do this next time
int getset_freeSlot(Slab *S, int max_slots) {

  // compute a conservative bm_size
  int bm_size = max_slots/8 + 1; 

  int i;
  int bi, si = -1;

  for(i=0; i< bm_size; i++) {
    if((bi=getset_freeBit(S->bitmap+i))!=-1) {
      // make sure that value returned
      // is smaller than max_slots
      si = i*8+bi;
      if(si>=max_slots) si = -1;
      break;
    }
  }

  // no free slot
  return si;
}


// allocate for sizes <= 1024
void * allocate_cache(unsigned int size) {

  // The algorithm

  // 1. Find the cache index to allocate from

  int ci = 0;

  while(size > M.C[ci].slot_size) ci++;
  
  int slot_size = M.C[ci].slot_size;

  // 2. Find or create a slab with an empty slot 
  // from that cache

  // iterate through the slabs finding one with an 
  // empty slot
  Slab *head = M.C[ci].S;
  Slab *iterator = head;
  Slab *prev = head;
  Slab *slab;

  while(iterator != NULL) {
    if(iterator->used!=M.C[ci].max_slots) break;
    prev = iterator;
    iterator = iterator->next;
  } 
  
  if(iterator==NULL) {

    printf("Could not find a slab with a free slot ... Creating a new one!\n");

    void *mapped_addr;

    // No slab with free slot 
    // Need to create a slab
    mapped_addr = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  
    if(mapped_addr==MAP_FAILED) {
      errno = ENOMEM;
      perror("Mapping failed during allocate_region");
      exit(0);
    }

    // initialize mapped page (including bitmap) to zero
    bzero(mapped_addr, PAGE_SIZE);

    if(head == NULL) {
      M.C[ci].S = (Slab *)mapped_addr;
      slab = M.C[ci].S;
    } else { 
      prev->next = (Slab *)mapped_addr;
      slab = prev->next;
    }

    slab->next = NULL;
    slab->bitmap = (char *) (mapped_addr + sizeof(Slab)); 
    slab->addr = (void *) (slab->bitmap + M.C[ci].bm_size);
       
  } else {
    slab = iterator;
  }
    
  // 3. Find a free slot
  // create a placeholder for the slot index within the 
  // slab that has an empty slot
  int si;

  // I have a slab and a free slot in it

  // 4. Update the bitmap for the specific slot

  si = getset_freeSlot(slab, M.C[ci].max_slots);
  
  // update number of used slots
  slab->used++;
  
  // 5. Compute the memory address of the slot

  void *retaddr = slab->addr + si*slot_size;

  // 6. return this memory address
  return retaddr;

}



// Allocates memory of size bytes and returns a pointer to it. Other details are set up so that it functions similar to malloc (see the man page).

void *allocate(unsigned int size) {

  if(size>1024) 
    return allocate_region(size);
  else
    return allocate_cache(size);

}

int deallocate_region(void *addr) {

  Region *iterator = M.R;
  Region *prev = M.R;

  while(iterator!=NULL) {

    if(addr == iterator->addr) {  
    // region is found!    
    // remove region from the list
    // unmap region 
    
      printf("Found region allocation of size = %d\n", iterator->size);

      if(iterator==M.R) {      
	// head of the region list matched
	M.R = M.R->next;
      } else {
	prev->next = iterator->next;	
      }
 
      munmap(iterator, iterator->size + sizeof(Region));
      return 0;
    }

    prev = iterator;
    iterator = iterator->next;    
  }

  printf("Unable to Find region allocation at addr = %p\n", addr);

  return -1;

}


int deallocate_cache(void *addr) {
int ci = 0;
  // Iterate through each cache

  //    Iterate through each slab
  Slab *head = M.C[ci].S;
  Slab *iterator = head;
  Slab *prev = head;
  Slab *slab = head;
  void * temp = addr;

  int thisByte, thisBit, si = 0;
  while(iterator != NULL) {
    if(iterator == head){ 
    prev = iterator;
    iterator = iterator->next;}
  else{ 
if(((char *)slab->addr <= (char *)addr) && ((char *)addr <= (char *)(slab + sizeof(slab))))
{
//       check if addr falls within the allocated range
  // if so, you have found the cache
  	while ((char *)temp < (char *)((char *)slab + sizeof(slab))){
	if((char *)temp == (char *)addr){break;}
	else si++;
	temp = temp + M.C[ci].slot_size;
	} 
	thisByte = si/8;
	thisBit = si%8;
	char *del = slab->bitmap + thisByte;
	if (((addr - slab->addr)%M.C[ci].slot_size)==0){
	resetbit(del, thisBit);
	slab->used--;
	if(slab->used == 0){munmap(slab, sizeof(slab));
return 0;}
	}
	else goto OUT;
}
  // if not,
else goto OUT;
}}

  // 2. Find the slot
  // How?
  // Check Is it a valid slot addr?
  // If not, goto OUT
  // If yes, go to next step

  
  // 3. Check bit corresponding to
  // above slot in bitmap
  // IF bit is zero, then goto OUT


  // 4. We have found a valid bit
  // Reset/clear the bit

  // 5. Decrease slots used

  // 6. If (slots_used == 0)
  // Remove slab from list of slabs
  // And unmap slab using slab starting address

  // 7. return 0

 OUT: 
  return -1;

}

/*
int deallocate_cache(void * addy){
int ci = 0, counter, done;
 Slab *slab;
 for(; ci < 9; ci++){
         void *last_addr = slab + SLAB_SIZE;
         counter = 1;
         slab = (Slab *)&M.C[ci].S;
         while(slab->next != NULL){
             if( (char *)addy > (char *)slab->addr && (char *)addy > (char *)last_addr){ 
                 slab = slab->next;
                 last_addr += SLAB_SIZE; 
                 counter++; 
             }
             else {
                     done = 1;
                     break;
             }
         }
         if(done == 1) break;

 }
return 0;
}
*/
// Frees the allocated memory, checking for appropriate error conditions. Other details are set up so that it functions similarly to free (see the man page)

void deallocate(void * addr) {

  if(deallocate_region(addr)==-1) {
    if(deallocate_cache(addr)==-1) {
      printf("Deallocation failed: %p\n", addr);
    }
  }

  return;

}




void init_mallocator() {

  fd = open("/dev/zero", O_RDWR);

  if(fd<0) {
    perror("opening the ZEROES file failed!");
    exit(0);
  }

  // initialize the region list
  M.R = NULL;

  // initilizalize the caches
  int i;
  for(i=0; i<NUM_CACHES; i++) {
    M.C[i].slot_size = MIN_SLOT_SIZE << i;
    M.C[i].max_slots = 8*(PAGE_SIZE - SLAB_SIZE - 1) / (M.C[i].slot_size*8 + 1);
    M.C[i].bm_size = M.C[i].max_slots/8 + 1; // a conservative bm_size
    M.C[i].S = NULL;
  }

  return;

}

void finalize_mallocator() {
int ci = 0;

  // Steps:

  // 1. Iterate through region list 
  //    unmap each region

  Region *iterator = M.R;
  Region *prev = M.R;

  while(iterator!=NULL) {
 
    prev = iterator;
    iterator = iterator->next;    
    munmap(prev, iterator->size + sizeof(Region));
    
}
  // 2. Iterate through each cache
  //      Iterate through each slab
  //         Unmap each slab

 Slab *head2 = M.C[ci].S;
  Slab *iterator2 = head2;
  Slab *prev2 = head2;
  //Slab *slab;

  while(iterator2 != NULL) {
    prev2 = iterator2;
    iterator2 = iterator2->next;
    munmap(prev2, sizeof(Slab));}
 

}

void test_region_allocator() {


  void *p;
  
  p = allocate(2000);

  printf("Allocated 2000 bytes at %p\n",p);

  strcpy((char *)(p+1900), "hello, world!");
  
  printf("@ (p+1900): %s\n", (char *)(p+1900));

  // Test deallocate
  deallocate(p);

  deallocate(p);

  // Cannot do this since p just got deallocated
  // printf("@ (p+1900): %s\n", (char *)(p+1900));

  p = allocate(1500);

  printf("Allocated 1500 bytes at %p\n",p);

  // this doesn't work
  // strcpy((char *)(p+10000), "hello, world!");
  
  strcpy((char *)(p+1400), "hello, world!");
  
  printf("@ (p+1400): %s\n", (char *)(p+1400));


  p = allocate(3600);

  printf("Allocated 3600 bytes at %p\n", p);

  strcpy((char *)(p+3500), "hello, world!");

  printf("@ (p+3500): %s\n", (char *)(p+3500));

  return;
}



void test_slab_allocator() {

  void *p1;
  int i;

  p1 = allocate(19);


  printf("Allocated 19 bytes at %p\n",p1);

  for(i =0; i<1000; i++) {

    p1 = allocate(23);
    printf("Allocated 23 bytes at %p\n",p1);

  }

  for(i =0; i<50; i++) {

    p1 = allocate(231);
    printf("Allocated 231 bytes at %p\n",p1);

  }

  for(i =0; i<10; i++) {

    p1 = allocate(1024);
    printf("Allocated 1024 bytes at %p\n",p1);

  }

  return;

}

