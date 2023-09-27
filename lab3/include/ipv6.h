#pragma once
#include <stdint.h>

// Псевдо-заголовок IPv6:
// ╔═══════════════════════════════════════════════════════════════════════╗
// ║  0x00 ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ 0x0f  ║
// ╠═══════════════════════════════════════════════════════════════════════╣
// ║76543210╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍76543210║
// ╠═══════════════════════════════════════════════════════════════════════╣
// ║                             Source address                            ║
// ╚═══════════════════════════════════════════════════════════════════════╝
// ╔═══════════════════════════════════════════════════════════════════════╗
// ║  0x10 ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ 0x1f  ║
// ╠═══════════════════════════════════════════════════════════════════════╣
// ║76543210╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍ ╍76543210║
// ╠═══════════════════════════════════════════════════════════════════════╣
// ║                          Destination address                          ║
// ╚═══════════════════════════════════════════════════════════════════════╝
// ╔════════╦════════╦════════╦════════╦════════╦════════╦════════╦════════╗
// ║  0x20  ║  0x21  ║  0x22  ║  0x23  ║  0x24  ║  0x25  ║  0x26  ║  0x27  ║
// ╠════════╬════════╬════════╬════════╬════════╬════════╬════════╬════════╣
// ║76543210║76543210║76543210║76543210║76543210║76543210║76543210║76543210║
// ╠════════╬════════╬════════╬════════╬════════╬════════╬════════╬════════╣
// ║           ICMPv6 length           ║      Zeros (0x000000)    ║NextHdr ║
// ╚════════╩════════╩════════╩════════╩════════╩════════╩════════╩════════╝
// NextHdr - Next header - поле пакета IPv6.

typedef struct 
{
    uint8_t  src_addr[16];
    uint8_t  dest_addr[16];
    uint32_t icmp_len;
    uint8_t  zeros[3];
    uint8_t  next_hdr;
} __attribute__((packed)) ipv6;