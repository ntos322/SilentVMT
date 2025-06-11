# SilentVMT
SilentVMT is a lightweight library that provides efficient and silent shadow VMT (Virtual Method Table) hooking for x86 and x64 architectures.



## What is Shadow VMT Hooking?
Virtual Method Table (VMT) hooking is a technique used to modify or intercept the virtual function calls of a class. It's commonly used in game hacking, reverse engineering, and other applications that require intercepting and modifying function calls.

Traditional VMT hooking involves directly modifying the original VMT, which can be detected by anti-cheat software or cause crashes due to other parts of the application or other hook libraries modifying the same table.

Shadow VMT hooking, on the other hand, creates a copy of the original VMT, and then redirects the instance's VMT pointer to the new copy. This way, the original VMT remains untouched, making the hooking process more stealthy and less prone to conflicts or crashes.


## Features
- Efficient and simple hooking process
- Supports both x86 and x64


## Example usage
Check out [example.cpp](https://github.com/ntos322/SilentVMT/blob/main/example.cpp)


<hr />

