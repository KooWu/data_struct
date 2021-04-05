target := main

lib_array := ./array/libarray_struct.so
lib_list := ./list/liblist_struct.so
lib_tree := ./tree/libtree_struct.so

array_dir := ./array/
list_dir := ./list/
tree_dir := ./tree/

all: $(target)
array: $(lib_array)
list: $(lib_list)
tree: $(lib_tree)

$(target):$(lib_array) $(lib_list) $(lib_tree)
	@echo "\033[32m make all done \033[0m"
$(lib_array):#改成伪目标好一点
	make -C $(array_dir)
$(lib_list):
	make -C $(list_dir)
$(lib_tree):
	make -C $(tree_dir)

.PHONY:clean cleanobj cleantarget#说明clean/cleanobj cleantarget是一个伪目标
clean: cleanobj cleantarget#说明-rm -rf -执行错误也无所谓
cleanobj:
	make cleanobj -C $(tree_dir)
	make cleanobj -C $(array_dir)
	make cleanobj -C $(list_dir)
cleantarget:
	make cleantarget -C $(tree_dir)
	make cleantarget -C $(array_dir)
	make cleantarget -C $(list_dir)