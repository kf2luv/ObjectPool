# 定长内存池

## Logic

![image-20241207184208853](https://ckfs.oss-cn-beijing.aliyuncs.com/img/202412071842950.png)

## Reality

![image-20241207184227999](https://ckfs.oss-cn-beijing.aliyuncs.com/img/202412071842046.png)



## API

`T* New()`

1.free链表有，先从链表里取

2.否则，再去memory里取。

因为从memory中取，可能会出现空间不足扩容的情况，效率低，此时若free链表中有闲置的空间，直接拿掉就快一点。



`void Delete(T* obj)`

 1.obj指向的空间为“归还块”, 将“归还块”头插到free链表中

 2.用归还块的前4/8个字节存储next指针 (实现free链表结构) 



## Hints

- 内存块大小（OBJ_SIZE）不够存储一个指针怎么办？

  扩成一个指针变量的大小，再取走。反正用户拿到的都是T*指针，即使指针指向的空间大于sizeof(T)，解引用后看到的还是T的大小

- 不同类型的指针，指向同一块空间，所看到的内容是不同的！

  ![image-20241207184532117](https://ckfs.oss-cn-beijing.aliyuncs.com/img/202412071845146.png)

- 值得再思考一下的：`*(void**)ptr = nxt;`



## TODO

1. 定位new，和构造函数更加相似
2. 直接用系统调用开辟空间，绕开malloc