target:=liblist_struct.so
objs:=list.o list_stack.o list_queue.o

all:$(target)
obj:$(objs)
$(target):$(objs)
	gcc -shared $^ -o $@
$(objs):%.o:%.c
	gcc -c -I ./../common/ -fPIC $< -o $@
.PHONY:clean cleanobj cleantarget
clean:cleanobj cleantarget
cleanobj:
	-rm -rf *.o
cleantarget:
	-rm -rf $(target)
	