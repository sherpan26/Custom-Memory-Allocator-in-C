#ifndef _MYMALLOC_H
#define _MYMALLOC_H
//defines a macro malloc(), passes size to allocate with the file name 
#define malloc(s)   mymalloc(s, __FILE__, __LINE__)
//passes a pointer
#define free(p)     myfree(p, __FILE__, __LINE__)
//allocation 
void *mymalloc(size_t size, char *file, int line);
//deallocation
void myfree(void *ptr, char *file, int line);

#endif
