Running gdb with valgrind
```bash
valgrind --leak-check=full --vgdb=yes --vgdb-error=0 ./push_swap

```gdb
gdb --args ./push_swap 42
target remote | vgdb --pid=64082
set args 42

```
```

```
which command is used to set args in gdb?
```
```gdb
