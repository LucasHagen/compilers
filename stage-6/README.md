# Compiler

This is the Stage-6 of the Compilers project from the discipline of the Federal University of Rio Grande do Sul.

## Stack Frame Structure

The stack frame's structure is as follows.

```c
----- TOP  -----
                 <- rsp
Return Address   (4 bytes)
Return Value     (4 bytes)
Static Link      (4 bytes)
Dynamic Link     (4 bytes)
Local Variables  (4 bytes x |variables|)
Parameters       (4 bytes x |parameters|)  <- rfp
----- BASE -----
```

## Authors
- Lucas Hagen
- Gabriel Pakulski
