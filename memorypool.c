// 内存管理 虚拟内存管理 堆
// 难点
// 不确定块的大小
// 不确定分配和释放的时机
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MEM_PAGE_SIZE 0x1000  // 4096
typedef struct memoryblock_s
{
    int block_size; //每块32     
    int free_count; //可用块128     4k/128

    void *mem; // 指向分出的内存块4k
    void *ptr; // 指向内存块

}memblock_t;
// page,block,
int memp_init(memblock_t *mp,size_t block_size)
{
    if(!mp) return -1;
    memset(mp,0,sizeof(memblock_t));
    
    mp->block_size = block_size;
    mp->free_count = MEM_PAGE_SIZE / block_size;
    mp->mem = malloc(MEM_PAGE_SIZE);
    if(!mp->mem) return -1;

    mp->ptr = mp->mem;

    int i = 0;
    // 将内存块链表串联起来
    char *ptr = mp->ptr;
    for(i = 0; i < mp->free_count; i++)
    {
        // 每个内存块的起始位置存放指向下一个内存块的指针
        *(char**)ptr = ptr + block_size; 
        ptr += block_size;
    }
    *(char**)ptr = NULL;
    return 0;

}
void* _malloc(memblock_t *mp,size_t size)
{
    // 页内分配
    if(!mp || mp->free_count == 0) return NULL; 
    if(mp->block_size < size) return NULL;
    void *ptr = mp->ptr;
    mp->ptr = *(char**)ptr; // 指向下一块
    mp->free_count--;


    return ptr;
}
void _free(memblock_t *mp,void *ptr)
{
    if(!mp) return;
    // 头插法
    *(char**)ptr = mp->ptr;
    mp->ptr = ptr; 
    mp->free_count++;

}

int main(int argc, char const *argv[])
{
    memblock_t mp;
    memp_init(&mp,32);

    void *p1 = _malloc(&mp,5);
    printf("p1--> %p\n",p1);

    void *p2 = _malloc(&mp,10);
    printf("p2--> %p\n",p2);

    void *p3 = _malloc(&mp,15);
    printf("p3--> %p\n",p3);

    void *p4 = _malloc(&mp,20);
    printf("p4--> %p\n",p4);

    _free(&mp,p1);
    printf("mp.ptr--> %p\n",mp.ptr);

    _free(&mp,p3);
    printf("mp.ptr--> %p\n",mp.ptr);

    void* p5 = _malloc(&mp,25);
    printf("p5--> %p\n",p5);

    void* p6 = _malloc(&mp,30);
    printf("p6--> %p\n",p6);


    return 0;
}
