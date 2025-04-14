# tiny-dos
Tiny-DOS is a minimalistic, modular 16-bit DOS-like operating system for educational purposes.

## Progress

- ✅ **Bootloader**: Successfully displays "HELLO, WORLD!" on boot.
- ✅ **Kernel**: Successfully transitions into the kernel, overcoming the 512-byte bootloader limit.
- ✅ **Mini OS**: The initial working version of the micro-system with the following features:
    - User login and authentication system.
    - Dynamic command prompt that changes based on user type (`root` or regular user).
    - Fully functional command line with support for input, backspace, and Enter to trigger the next prompt.
- ✅ **Refactor Code**: Transition from a single, soon-to-be-bloated kernel file to a better-organized *"pseudo-modular"* structure.

## TODO

- ⬜ **Add Datetime Module**: Implement a module for getting and formatting the current date and time.
- ⬜ **Optimize Welcome Screen**: Enhance the user experience by adding a dynamic greeting based on the system time.
- ⬜ **Add Basic Commands**: Implement essential commands such as `help`, `cls`, `date`, etc.

## Milestone

| Version (Stage) | Content                                   | Difficulty Level | Implementation                                 |
|-----------------|-------------------------------------------|------------------|------------------------------------------------|
| v1              | Bootloader + Kernel + Shell + Input/Print | ⭐⭐               | Basic functionality with simple implementation |
