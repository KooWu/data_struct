target:=libtree_struct.so
objs:=tree.o
test:=test

all:$(target)
obj:$(objs)

$(target):$(objs)
	gcc -shared $^ -o $@
$(objs):%.o:%.c
	gcc -c -I ./../common/ -I ./../array/ -fPIC $< -o $@
test:
	gcc -I ./../common/ -I ./../array/ test.c tree.c -o $@ -L ./../array/ -larray_struct
test32:
	gcc -Wl,-rpath=./../array/ -m32 -I ./../common/ -I ./../array/ test.c tree.c -o $@ -L ./../array/ -larray_struct
#-Wl,-rpath=./../array/指定运行时库
.PHONY:clean cleanobj cleantarget test test32
clean:cleanobj cleantarget
cleanobj:
	-rm -rf *.o
cleantarget:
	-rm -rf $(target) $(test)
	
