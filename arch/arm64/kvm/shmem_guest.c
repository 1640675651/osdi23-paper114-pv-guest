#include <kvm/shmem_guest.h>
u64 get_shmem_size()
{
    return kvm_pvops(HVC_GET_SHMEM_SIZE);
}

// allocate memory, register as shared and return the virtual address
void* alloc_shmem_guest(u64 size)
{
	void* base_virt;
	u64 base_phys; 

	printk(KERN_INFO "[SeKVM_Guest] Allocating %llu bytes Shared Memory\n", size);

	// alloc_pages_exact returns a virtual address instead of a page*
	// size in bytes, not pages
	base_virt = alloc_pages_exact(size, GFP_KERNEL);
	
	base_phys = virt_to_phys(base_virt);
	
	kvm_pvops(HVC_GUEST_SHMEM_REGISTER, base_phys);

	//printk(KERN_INFO "[SeKVM_Guest] Writing %d to the first byte of the shared memory\n", 12345);
    //*(int*) base_virt = 12345;

	return base_virt;
}