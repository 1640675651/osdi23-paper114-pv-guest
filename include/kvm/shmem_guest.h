#ifndef SHMEM_GUEST_H
#define SHMEM_GUEST_H


#include <linux/mman.h>
#include <kvm/pvops.h>

u64 get_shmem_size(void);
void* alloc_shmem_guest(u64 size);

#endif