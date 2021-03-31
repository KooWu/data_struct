#ifndef COMM_H
#define COMM_H

#if 1
#define dbg(fmt, args... ) printf("file[%s], line[%d]: "fmt"\n", __FILE__, __LINE__, ##args);
#else
#define dbg(fmt, msg... )
#endif

#endif