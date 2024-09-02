// 编译命令: gcc -o deadlock deadlock.c -lpthread -ldl

#define _GNU_SOURCE
#include <dlfcn.h>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>

#if 1

typedef unsigned long int uint64;

#define MAX 100 // 定义图中最大顶点数量

// 枚举类型定义线程和资源
enum Type {PROCESS, RESOURCE};

// 资源类型结构体
struct source_type {
    uint64 id;               // 线程或资源的ID
    enum Type type;          // 类型: 线程或资源
    uint64 lock_id;          // 线程持有的锁ID
    int degress;             // 递归锁计数
};

// 图的顶点结构体
struct vertex {
    struct source_type s;    // 资源或线程的信息
    struct vertex *next;     // 指向下一个顶点的指针
};

// 图结构体
struct task_graph {
    struct vertex list[MAX]; // 顶点列表
    int num;                 // 顶点数量
    struct source_type locklist[MAX]; // 锁列表
    int lockidx;             // 锁列表索引
    pthread_mutex_t mutex;   // 互斥锁，用于同步图的访问
};

struct task_graph *tg = NULL; // 全局图指针
int path[MAX+1];              // 路径数组，用于存储检测到的环
int visited[MAX];             // 访问标记数组，用于DFS
int k = 0;                    // 环路径计数器
int deadlock = 0;             // 死锁标志

// 创建顶点函数，分配内存并初始化
struct vertex *create_vertex(struct source_type type) {
    struct vertex *tex = (struct vertex *)malloc(sizeof(struct vertex));
    tex->s = type;
    tex->next = NULL;
    return tex;
}

// 搜索图中是否存在给定的顶点
int search_vertex(struct source_type type) {
    int i = 0;
    for (i = 0; i < tg->num; i++) {
        if (tg->list[i].s.type == type.type && tg->list[i].s.id == type.id) {
            return i; // 找到返回索引
        }
    }
    return -1; // 未找到返回 -1
}

// 添加顶点到图中
void add_vertex(struct source_type type) {
    if (search_vertex(type) == -1) { // 如果图中不存在该顶点
        tg->list[tg->num].s = type;  // 添加顶点
        tg->list[tg->num].next = NULL;
        tg->num++; // 增加顶点数量
    }
}

// 添加边，表示线程对资源的请求或持有
int add_edge(struct source_type from, struct source_type to) {
    add_vertex(from); // 确保顶点存在
    add_vertex(to);

    struct vertex *v = &(tg->list[search_vertex(from)]);

    while (v->next != NULL) {
        v = v->next; // 遍历到最后一个节点
    }

    v->next = create_vertex(to); // 添加边
}

// 验证两个顶点之间是否存在边
int verify_edge(struct source_type i, struct source_type j) {
    if (tg->num == 0) return 0; // 如果图为空，返回0

    int idx = search_vertex(i);
    if (idx == -1) {
        return 0; // 顶点不存在，返回0
    }

    struct vertex *v = &(tg->list[idx]);

    while (v != NULL) {
        if (v->s.id == j.id) return 1; // 如果找到，返回1
        v = v->next;
    }

    return 0; // 否则返回0
}

// 删除两个顶点之间的边
int remove_edge(struct source_type from, struct source_type to) {
    int idxi = search_vertex(from);
    int idxj = search_vertex(to);

    if (idxi != -1 && idxj != -1) { // 顶点都存在
        struct vertex *v = &tg->list[idxi];
        struct vertex *remove;

        while (v->next != NULL) {
            if (v->next->s.id == to.id) {
                remove = v->next; // 找到要删除的边
                v->next = v->next->next;
                free(remove); // 释放内存
                break;
            }
            v = v->next;
        }
    }
}

// 打印死锁环路
void print_deadlock(void) {
    int i = 0;
    printf("cycle : ");
    for (i = 0; i < k-1; i++) {
        printf("%ld --> ", tg->list[path[i]].s.id);
    }
    printf("%ld\n", tg->list[path[i]].s.id);
}

// 深度优先搜索（DFS）检测环路
int DFS(int idx) {
    struct vertex *ver = &tg->list[idx];
    if (visited[idx] == 1) { // 如果已访问，检测到环路
        path[k++] = idx;
        print_deadlock();    // 打印环路
        deadlock = 1;
        return 0;
    }

    visited[idx] = 1; // 标记为已访问
    path[k++] = idx;

    while (ver->next != NULL) {
        DFS(search_vertex(ver->next->s)); // 递归调用DFS
        k--;
        ver = ver->next;
    }
    return 1;
}

// 从指定索引开始搜索环路
int search_for_cycle(int idx) {
    struct vertex *ver = &tg->list[idx];
    visited[idx] = 1;
    k = 0;
    path[k++] = idx;

    while (ver->next != NULL) {
        int i = 0;
        for (i = 0; i < tg->num; i++) {
            if (i == idx) continue;
            visited[i] = 0; // 重置访问标记
        }

        for (i = 1; i <= MAX; i++) {
            path[i] = -1; // 重置路径数组
        }
        k = 1;

        DFS(search_vertex(ver->next->s)); // 执行DFS
        ver = ver->next;
    }
}

#endif

#if 1

// 搜索锁列表中是否存在指定的锁
int search_lock(uint64 lock) {
    int i = 0;
    for (i = 0; i < tg->lockidx; i++) {
        if (tg->locklist[i].lock_id == lock) {
            return i; // 返回锁索引
        }
    }
    return -1; // 未找到返回 -1
}

// 搜索锁列表中的空位置
int search_empty_lock(uint64 lock) {
    int i = 0;
    for (i = 0; i < tg->lockidx; i++) {
        if (tg->locklist[i].lock_id == 0) {
            return i; // 返回空位置索引
        }
    }
    return tg->lockidx; // 未找到则返回当前锁索引
}

// 在获取锁之前更新图信息
void lock_before(uint64_t tid, uint64_t lockaddr) {
    /*
    如果lockaddr已经存在，tid指向lockaddr的当前拥有者。
    */

    int idx = 0;

    for (idx = 0; idx < tg->lockidx; idx++) {
        if (tg->locklist[idx].lock_id == lockaddr) { // 锁已存在
            struct source_type from;
            from.id = tid;
            from.type = PROCESS;
            add_vertex(from);

            struct source_type to;
            to.id = tg->locklist[idx].id; // 当前锁拥有者
            to.type = PROCESS;
            add_vertex(to);

            tg->locklist[idx].degress++;

            if (!verify_edge(from, to)) // 如果不存在边
                add_edge(from, to); // 添加边
        }
    }
}

// 在获取锁之后更新图信息
void lock_after(uint64_t tid, uint64_t lockaddr) {
    /*
    如果锁不存在，则初始化锁信息；如果存在，更新锁的持有者。
    */
    int idx = 0;
    if (-1 == (idx = search_lock(lockaddr))) { // 如果锁不存在
        int eidx = search_empty_lock(lockaddr);
        tg->locklist[eidx].id = tid; // 更新锁信息
        tg->locklist[eidx].lock_id = lockaddr;
        tg->lockidx++;
    } else { // 锁已存在
        struct source_type from;
        from.id = tid;
        from.type = PROCESS;
        add_vertex(from);

        struct source_type to;
        to.id = tg->locklist[idx].id; // 当前锁拥有者
        to.type = PROCESS;
        add_vertex(to);

        tg->locklist[idx].degress--;

        if (verify_edge(from, to))
            remove_edge(from, to); // 移除边

        tg->locklist[idx].id = tid; // 更新锁持有者
    }
}

// 解锁后更新图信息
void unlock_after(uint64_t tid, uint64_t lockaddr) {
    int idx = 0;
    if (-1 == (idx = search_lock(lockaddr))) {
        // 锁不存在，返回
        return;
    } else {
        struct source_type from;
        from.id = tid;
        from.type = PROCESS;
        add_vertex(from);

        struct source_type to;
        to.id = tg->locklist[idx].id; // 当前锁持有者
        to.type = PROCESS;
        add_vertex(to);

        if (verify_edge(from, to))
            remove_edge(from, to); // 移除边

        tg->locklist[idx].lock_id = 0; // 重置锁信息
        tg->locklist[idx].degress = 0;
        tg->locklist[idx].id = 0;
    }
}

#endif

#if 1

void (*pthread_mutex_lockp)(pthread_mutex_t *mutex);
void (*pthread_mutex_unlockp)(pthread_mutex_t *mutex);

// 死锁检测函数，遍历所有顶点寻找环路
int check_dead_lock(void) {
    int i = 0;

    if (tg->num == 0) return 0; // 图为空

    deadlock = 0;

    for (i = 0; i < tg->num; i++) {
        search_for_cycle(i); // 检测环路
        if (deadlock == 1) {
            printf("complete\n");
            return 1;
        }
    }

    printf("no deadlock\n");
    return 0;
}

// 死锁检测线程
void *check_deadlock_thread(void *arg) {
    for (;;) {
        sleep(5); // 每5秒检测一次
        pthread_mutex_lock(&(tg->mutex)); // 锁定图
        check_dead_lock();
        pthread_mutex_unlock(&(tg->mutex)); // 解锁图
    }
}

// 自定义的pthread_mutex_lock函数，用于死锁检测
int pthread_mutex_lock(pthread_mutex_t *mutex) {
    int ret;
    uint64_t tid = (uint64_t)pthread_self(); // 获取当前线程ID
    uint64_t lockaddr = (uint64_t)mutex;     // 获取锁地址

    pthread_mutex_lock(&(tg->mutex)); // 锁定图的互斥锁
    lock_before(tid, lockaddr);       // 获取锁前的更新
    pthread_mutex_unlock(&(tg->mutex));

    ret = pthread_mutex_lockp(mutex); // 调用真实的pthread_mutex_lock

    pthread_mutex_lock(&(tg->mutex));
    lock_after(tid, lockaddr);        // 获取锁后的更新
    pthread_mutex_unlock(&(tg->mutex));
    return ret;
}

// 自定义的pthread_mutex_unlock函数，用于死锁检测
int pthread_mutex_unlock(pthread_mutex_t *mutex) {
    int ret;
    uint64_t tid = (uint64_t)pthread_self(); // 获取当前线程ID
    uint64_t lockaddr = (uint64_t)mutex;     // 获取锁地址

    ret = pthread_mutex_unlockp(mutex);      // 调用真实的pthread_mutex_unlock

    pthread_mutex_lock(&(tg->mutex));        // 锁定图的互斥锁
    unlock_after(tid, lockaddr);             // 解锁后的更新
    pthread_mutex_unlock(&(tg->mutex));
    return ret;
}

// 初始化钩子函数
void init_hook(void) {
    pthread_mutex_lockp = dlsym(RTLD_NEXT, "pthread_mutex_lock");   // 获取真实pthread_mutex_lock地址
    pthread_mutex_unlockp = dlsym(RTLD_NEXT, "pthread_mutex_unlock"); // 获取真实pthread_mutex_unlock地址
}

// 启动死锁检测线程
void start_check(void) {
    pthread_t p;
    pthread_create(&p, NULL, check_deadlock_thread, NULL); // 创建死锁检测线程
}

// 初始化图结构
void init_graph(void) {
    tg = malloc(sizeof(struct task_graph)); // 分配图的内存
    tg->num = 0;
    tg->lockidx = 0;
    pthread_mutex_init(&(tg->mutex), NULL); // 初始化互斥锁
}

// 线程函数，模拟线程执行过程
void *task_thread(void *arg) {
    pthread_mutex_t *lock = (pthread_mutex_t *)arg; // 获取锁
    pthread_mutex_lock(lock); // 锁定
    pthread_mutex_unlock(lock); // 解锁
    return NULL;
}

#endif

int main(void) {
    int i;
    pthread_t p[5]; // 线程数组
    pthread_mutex_t lock[5]; // 互斥锁数组

    init_graph(); // 初始化图
    init_hook(); // 初始化钩子
    start_check(); // 启动死锁检测线程

    for (i = 0; i < 5; i++) {
        pthread_mutex_init(&lock[i], NULL); // 初始化互斥锁
    }

    // 创建并启动5个线程，分别锁定并等待不同的锁，模拟死锁
    pthread_create(&p[0], NULL, task_thread, (void *)&lock[1]);
    pthread_create(&p[1], NULL, task_thread, (void *)&lock[2]);
    pthread_create(&p[2], NULL, task_thread, (void *)&lock[3]);
    pthread_create(&p[3], NULL, task_thread, (void *)&lock[4]);
    pthread_create(&p[4], NULL, task_thread, (void *)&lock[0]);

    for (i = 0; i < 5; i++) {
        pthread_join(p[i], NULL); // 等待线程完成
    }

    return 0;
}
