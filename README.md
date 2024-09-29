## The Net Test Patcher

### What is this?

This is a small C program which patches hl.exe from the [Half-Life Net Test 2 beta](https://archive.org/details/nettest-2) to remove the CD check and timebomb. Writes the patched file to hlpatch.exe.

### How do I compile this myself?

I used TCC (Tiny C) to compile this program, i.e. `tcc nettest-patcher.c`. By modifying the filenames, file size, and patches (location, old byte, new byte), you can use this code to create a patcher for any file you'd like.
