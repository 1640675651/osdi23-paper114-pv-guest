#include <kvm/shmem_guest.h>
struct guest_shmem_info shmem_info;

u64 get_shmem_size(void)
{
    return kvm_pvops(HVC_GET_SHMEM_SIZE);
}

u64 get_registered_size(void)
{
	return shmem_info.size;
}

u64 get_shmem_base(void)
{
	return shmem_info.base_phys;
}

// allocate memory, register as shared and return the virtual address
void* alloc_shmem_guest(u64 size)
{
	void* base_virt;
	u64 base_phys; 
	shmem_info.size = 0;
	shmem_info.base_phys = 0;

	printk(KERN_INFO "[SeKVM_Guest] Allocating %llu bytes Shared Memory\n", size);

	// alloc_pages_exact returns a virtual address instead of a page*
	// size in bytes, not pages
	base_virt = alloc_pages_exact(size, GFP_KERNEL);
	
	base_phys = virt_to_phys(base_virt);
	
	kvm_pvops(HVC_GUEST_SHMEM_REGISTER, base_phys);

	//printk(KERN_INFO "[SeKVM_Guest] Writing %d to the first byte of the shared memory\n", 12345);
    //*(int*) base_virt = 12345;

	shmem_info.size = size;
	shmem_info.base_phys = base_phys;

	return base_virt;
}

//EXPORT_SYMBOL(get_shmem_size);
EXPORT_SYMBOL(get_registered_size);
EXPORT_SYMBOL(get_shmem_base);
//EXPORT_SYMBOL(alloc_shmem_guest);
//EXPORT_SYMBOL(__kvm_call_hyp);
EXPORT_SYMBOL(shmem_info);