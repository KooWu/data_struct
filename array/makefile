target:=libarray_struct.so
allc:=$(wildcard ./*.c)
objs:=array_stack.o array_queue.o

all:$(target)
obj:$(objs)
lib32:
$(target):$(objs)
	gcc -shared $^ -o $@
$(objs):%.o:%.c
	gcc -c -I ./../common/ -fPIC $< -o $@
lib32:
	gcc -m32 -I ./../common/ -shared -fPIC $(allc) -o $(target)
.PHONY:clean cleanobj cleantarget lib32
clean:cleanobj cleantarget
cleanobj:
	-rm -rf *.o
cleantarget:
	-rm -rf $(target)
	