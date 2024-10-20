#ifndef IO_H
#define IO_H

#include <stdint.h>


static __inline unsigned char inb (unsigned short int port)
{
  unsigned char _v;
  __asm__ __volatile__ (
    "inb %1, %0"
    :"=a" (_v)
    :"Nd" (port)
    );
  return _v;
}

static __inline void outb(uint16_t port, uint8_t data)
{
    __asm__ volatile (
        "outb %0, %1"
        :
        : "a"(data), "Nd"(port));
}

#endif