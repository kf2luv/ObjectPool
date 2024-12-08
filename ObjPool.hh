#include <iostream>

template <class T>
class ObjectPool {
    const size_t MEM_SIZE = 36;
    const size_t OBJ_SIZE = sizeof(T);

   public:
    ObjectPool() : _memory(nullptr), _free_list(nullptr), _rest_mem(0) {}

    template <typename... Args>
    T *New(Args &&...args) {
        T *t;
        try {
            if (_free_list != nullptr) {  // free链表有闲置内存块 (pop_front)
                void *next = *(void **)_free_list;
                t = (T *)_free_list;
                _free_list = next;
            } else {
                if (_rest_mem < OBJ_SIZE) {  // 剩余空间不足
                    _memory = (char *)malloc(MEM_SIZE);
                    if (_memory == nullptr) {
                        throw std::bad_alloc();
                    }
                    _rest_mem = MEM_SIZE;
                }
                // 取出大小为OBJ_SIZE的空间返回
                t = (T *)_memory;
                // 取出的大小
                size_t take_size = OBJ_SIZE >= sizeof(void *) ? OBJ_SIZE : sizeof(void *);
                //_memory覆盖掉取出的空间
                _memory += take_size;
                // 更新剩余空间
                _rest_mem -= OBJ_SIZE;
            }
        } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
        }

        // placement new
        T *obj_ptr = new (t) T(std::forward<Args>(args)...);
        return obj_ptr;
    }

    T *New() {
        T *t;
        try {
            if (_free_list != nullptr) { 
                void *next = *(void **)_free_list;
                t = (T *)_free_list;
                _free_list = next;
            } else {
                if (_rest_mem < OBJ_SIZE) { 
                    _memory = (char *)malloc(MEM_SIZE);
                    if (_memory == nullptr) {
                        throw std::bad_alloc();
                    }
                    _rest_mem = MEM_SIZE;
                }
                t = (T *)_memory;
                size_t take_size = OBJ_SIZE >= sizeof(void *) ? OBJ_SIZE : sizeof(void *);
                _memory += take_size;
                _rest_mem -= OBJ_SIZE;
            }
        } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
        }

        new (t) T;
        return t;
    }

    void Delete(T *obj) {
        obj->~T();
        // 用归还块的前4/8个字节存储next指针
        *(void **)obj = _free_list;
        _free_list = (void *)obj;
    }

   private:
    // 一大块用于“分配”的空间，将被切分为多个内存块，每块大小sizeof(T)
    char *_memory;
    // _memory中剩余的空间
    size_t _rest_mem = 0;
    // 自由链表，管理用户“归还”的内存块
    void *_free_list = nullptr;
};