#ifndef MEMORY_DEBUG_HPP
#define MEMORY_DEBUG_HPP

#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__

// Returns the available memory on the device in bytes
int getMemory();

#endif