#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MEM_PAGE_SIZE 0x1000  // 4096

typedef struct memorypage_s {
    void *mem;              // 指向分配的内存页
    void *ptr;              // 指向当前内存块
    struct memorypage_s *next; // 指向下一个内存页（用于扩展）
} memorypage_t;

typedef struct memoryblock_s {
    int block_size;         // 每块大小
    int free_count;         // 当前可用块的数量
    memorypage_t *pages;    // 指向内存页链表
} memblock_t;

int memp_init(memblock_t *mp, size_t block_size) {
    if (!mp) return -1;
    memset(mp, 0, sizeof(memblock_t));
    
    mp->block_size = block_size;

    // 分配第一个页面并初始化
    memorypage_t *first_page = malloc(sizeof(memorypage_t));
    if (!first_page) return -1;

    first_page->mem = malloc(MEM_PAGE_SIZE);
    if (!first_page->mem) {
        free(first_page);
        return -1;
    }

    first_page->ptr = first_page->mem;
    first_page->next = NULL;

    mp->pages = first_page;
    mp->free_count = MEM_PAGE_SIZE / block_size;

    // 初始化内存块链表
    char *ptr = first_page->ptr;
    for (int i = 0; i < mp->free_count; i++) {
        *(char**)ptr = ptr + block_size;
        ptr += block_size;
    }
    *(char**)ptr = NULL;

    return 0;
}

void* _malloc(memblock_t *mp, size_t size) {
    if (!mp || size > mp->block_size) return NULL;

    memorypage_t *page = mp->pages;
    
    while (page) {
        if (mp->free_count > 0) {
            void *ptr = page->ptr;
            page->ptr = *(char**)ptr;
            mp->free_count--;
            return ptr;
        }
        page = page->next;
    }

    // 当前页面已用尽，动态分配新页面
    memorypage_t *new_page = malloc(sizeof(memorypage_t));
    if (!new_page) return NULL;

    new_page->mem = malloc(MEM_PAGE_SIZE);
    if (!new_page->mem) {
        free(new_page);
        return NULL;
    }

    new_page->ptr = new_page->mem;
    new_page->next = mp->pages;
    mp->pages = new_page;

    mp->free_count = MEM_PAGE_SIZE / mp->block_size;

    // 初始化新页面的内存块链表
    char *ptr = new_page->ptr;
    for (int i = 0; i < mp->free_count; i++) {
        *(char**)ptr = ptr + mp->block_size;
        ptr += mp->block_size;
    }
    *(char**)ptr = NULL;

    // 递归调用再尝试分配
    return _malloc(mp, size);
}

void _free(memblock_t *mp, void *ptr) {
    if (!mp || !ptr) return;

    memorypage_t *page = mp->pages;

    // 找到对应的页面（假设指针是有效的）
    while (page) {
        if (ptr >= page->mem && ptr < (page->mem + MEM_PAGE_SIZE)) {
            *(char**)ptr = page->ptr;
            page->ptr = ptr;
            mp->free_count++;
            return;
        }
        page = page->next;
    }
}

void memp_destroy(memblock_t *mp) {
    if (!mp) return;

    memorypage_t *page = mp->pages;
    while (page) {
        memorypage_t *next = page->next;
        free(page->mem);
        free(page);
        page = next;
    }

    memset(mp, 0, sizeof(memblock_t));
}

int main() {
    memblock_t pool;
    memp_init(&pool, 32);
    void* p[500];
    // 示例分配和释放
    for(int i = 0; i < 500;++i)
    {
        p[i] = _malloc(&pool,32);
        printf("%p \n",p[i]);
    }
    // 销毁内存池
    memp_destroy(&pool);

    return 0;
}
