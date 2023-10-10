#ifndef SHMEM_GUEST_H
#define SHMEM_GUEST_H


#include <linux/mman.h>
#include <kvm/pvops.h>

struct guest_shmem_info
{
    u64 size;
    u64 base_phys;
};

u64 get_shmem_size(void);
void* alloc_shmem_guest(u64 size);
//u64 __kvm_call_hyp(void *hypfn, ...);

extern struct guest_shmem_info shmem_info;
extern u64 get_registered_size(void);
extern u64 get_shmem_base(void);

#endif