# tiny-dos

> "This project doesn't reinvent the wheel — it just lets you touch the axle for the first time."

## Background

**Tiny-DOS** is a minimalistic, modular 16-bit operating system that emulates a DOS-like (or Unix-like) environment. 
It is designed primarily for educational purposes, allowing users to explore and learn the fundamental 
concepts of system programming, low-level operations, and assembly language. The operating system is 
built using a combination of assembly language and simple kernel design, offering a hands-on experience 
of OS development.

## Progress

- ✅ **Bootloader**: Successfully displays "HELLO, WORLD!" on boot.
- ✅ **Kernel**: Successfully transitions into the kernel, overcoming the 512-byte bootloader limit.
- ✅ **Mini OS**: The initial working version of the micro-system with the following features:
    - User login and authentication system.
    - Dynamic command prompt that changes based on user type (`root` or regular user).
    - Fully functional command line with support for input, backspace, and Enter to trigger the next prompt.
    - Added a dynamic greeting based on the system time.
    - Added `10+` built-in commands for enhanced functionality.
- ✅ **Refactor Code**: Transition from a single, soon-to-be-bloated kernel file to a better-organized *"pseudo-modular"* structure.

## TODO

- ⬜ **Optimize command dispatch**: Replace the current linear matching logic with a jump table for more efficient command handling.

## Milestone

| Version (Stage) | Content                                   | Difficulty Level | Implementation                                      |
|-----------------|-------------------------------------------|------------------|-----------------------------------------------------|
| v1              | Bootloader + Kernel + Shell + Input/Print | ⭐⭐               | Basic functionality with simple implementation      |
| v2              | Modularization + Macro + Libs + Commands  | ⭐⭐⭐              | Enhanced structure and added more built-in commands |
