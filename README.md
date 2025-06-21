# SimpleGC
SimpleGC is a simple and educational garbage collector designed to help understand the fundamentals of automatic memory management. It handles allocation and cleanup in C projects, making it easier to experiment with basic GC concepts


```sql
.
├── bin
│   └── libgc.a
├── debug
│   └── gc_debug.c
├── folder_structure.txt
├── includes
│   ├── gc.h
│   ├── gc_macros.h
│   └── gc_structs.h
├── lib
├── LICENSE
├── main.c
├── Makefile
├── obj
│   ├── debug
│   │   └── gc_debug.o
│   └── src
│       ├── gc_block_handler.o
│       ├── gc.o
│       └── gc_utils.o
├── README.md
├── src
│   ├── gc_block_handler.c
│   ├── gc.c
│   └── gc_utils.c
└── test
    ├── all_test
    ├── basic_gc_test.c
    ├── init_gc_test.c
    └── struct_gc_test.c
```
