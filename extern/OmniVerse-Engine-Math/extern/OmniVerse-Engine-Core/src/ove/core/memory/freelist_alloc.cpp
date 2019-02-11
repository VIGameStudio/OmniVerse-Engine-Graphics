#include "linear_alloc.hpp"

namespace core {

/// FreeListalloc_t
/*FreeListalloc_t::FreeListalloc_t(u64 size, void* start)
    : alloc_t(size, start), free_blocks((FreeBlock*)start)
{
    ASSERT(size > sizeof(FreeBlock));

    free_blocks->size  = size;
    free_blocks->next = nullptr;
}

FreeListalloc_t::~FreeListalloc_t()
{
    free_blocks        = nullptr;
}

void* FreeListalloc_t::allocate(u64 size, u8 alignment)
{
    ASSERT(size != 0 && alignment != 0);

    FreeBlock* prev_free_block = nullptr;
    FreeBlock* free_block     = free_blocks;

    while(free_block != nullptr)
    {
        //Calculate adjustment needed to keep object correctly aligned
        u8 adjustment = ptrmath::alignForwardAdjustmentWithHeader(free_block,
alignment, sizeof(AllocationHeader));

        u64 total_size = size + adjustment;

        //If allocation doesn't fit in this FreeBlock, try the next
        if(free_block->size < total_size)
        {
            prev_free_block = free_block;
            free_block = free_block->next;
            continue;
        }

        static_assert(sizeof(AllocationHeader) >= sizeof(FreeBlock),
"sizeof(AllocationHeader) < sizeof(FreeBlock)");

        //If allocations in the remaining memory will be impossible
        if(free_block->size - total_size <= sizeof(AllocationHeader))
        {
            //Increase allocation size instead of creating a new FreeBlock
            total_size = free_block->size;

            if(prev_free_block != nullptr)
                prev_free_block->next = free_block->next;
            else
                free_blocks = free_block->next;
        }
        else
        {
            //Else create a new FreeBlock containing remaining memory
            FreeBlock* next_block = (FreeBlock*)( ptrmath::add(free_block,
total_size) );
            next_block->size = free_block->size - total_size;
            next_block->next = free_block->next;

            if(prev_free_block != nullptr)
                prev_free_block->next = next_block;
            else
                free_blocks = next_block;
        }

        uptr aligned_address = (uptr)free_block + adjustment;

        AllocationHeader* header = (AllocationHeader*)(aligned_address -
sizeof(AllocationHeader));
        header->size             = total_size;
        header->adjustment       = adjustment;

        usedMem += total_size;
        numAllocs++;

        ASSERT(ptrmath::alignForwardAdjustment((void*)aligned_address,
alignment) == 0);

        return (void*)aligned_address;
    }

    //ASSERT(false && "Couldn't find free block large enough!");

    return nullptr;
}

void FreeListalloc_t::deallocate(void* p)
{
    ASSERT(p != nullptr);

    AllocationHeader* header = (AllocationHeader*)ptrmath::subtract(p,
sizeof(AllocationHeader));

    uptr   block_start = reinterpret_cast<uptr>(p) - header->adjustment;
    u64 block_size  = header->size;
    uptr   block_end   = block_start + block_size;

    FreeBlock* prev_free_block = nullptr;
    FreeBlock* free_block = free_blocks;

    while(free_block != nullptr)
    {
        if( (uptr) free_block >= block_end )
            break;

        prev_free_block = free_block;
        free_block = free_block->next;
    }

    if(prev_free_block == nullptr)
    {
        prev_free_block = (FreeBlock*) block_start;
        prev_free_block->size = block_size;
        prev_free_block->next = free_blocks;

        free_blocks = prev_free_block;
    } else if((uptr) prev_free_block + prev_free_block->size == block_start)
    {
        prev_free_block->size += block_size;
    } else
    {
        FreeBlock* temp = (FreeBlock*) block_start;
        temp->size = block_size;
        temp->next = prev_free_block->next;
        prev_free_block->next = temp;

        prev_free_block = temp;
    }

    if( free_block != nullptr && (uptr) free_block == block_end)
    {
        prev_free_block->size += free_block->size;
        prev_free_block->next = free_block->next;
    }

    numAllocs--;
    usedMem -= block_size;
}*/

}
