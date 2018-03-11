if [ $1 = 1 ]
then
	export DYLD_LIBRARY_PATH=/Users/agouby/work/malloc/
	export DYLD_INSERT_LIBRARIES=libft_malloc.so
	export DYLD_FORCE_FLAT_NAMESPACE=1
else
	export DYLD_INSERT_LIBRARIES=
	export DYLD_FORCE_FLAT_NAMESPACE=
	export DYLD_LIBRARY_PATH=
fi
