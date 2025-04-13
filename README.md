# tiny-dos
Tiny-DOS is a minimalistic, modular 16-bit DOS-like operating system for educational purposes.

## Progress

- ✅ **Bootloader**: Successfully displays "HELLO, WORLD!" on boot.
- ✅ **Kernel**: Successfully transitions into the kernel, overcoming the 512-byte bootloader limit.
- ✅ **Mini OS**: The initial working version of the micro-system with the following features:
    - User login and authentication system.
    - Dynamic command prompt that changes based on user type (`root` or regular user).
    - Fully functional command line with support for input, backspace, and Enter to trigger the next prompt.

## TODO

- ⬜ **Refactor and modularize**: As the project grows and more features are added, it becomes increasingly important to refactor the kernel.asm file. Future work will focus on:
  - Splitting kernel code into separate files to better organize the growing codebase.
  - Defining macros and global constants for easier maintainability and scalability.
  - Implementing *'pseudo-modularization'* for improved code structure and clarity.

## Milestone

| Version (Stage) | Content                                   | Difficulty Level | Implementation                                 |
|-----------------|-------------------------------------------|------------------|------------------------------------------------|
| v1              | Bootloader + Kernel + Shell + Input/Print | ⭐⭐               | Basic functionality with simple implementation |
