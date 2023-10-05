#include <linux/types.h>
#include <kvm/pvops.h>
#include <linux/export.h>


unsigned long long get_shmem_size_op(void){
    return kvm_pvops(HVC_GET_SHMEM_SIZE);
} 
EXPORT_SYMBOL(get_shmem_size_op);

void* register_shmem_guest_op(unsigned long long base_addr) {
    kvm_pvops(HVC_GUEST_SHMEM_REGISTER, base_addr);
}
EXPORT_SYMBOL(register_shmem_guest_op);


