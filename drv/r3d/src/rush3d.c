/**
 *  Implementation of rush3d.c
 *
 */
#include "rush3d.h"
#include "bridge.h"
#include "register.h"

#include <stdio.h>

int main()
{
    bridge_init();

    printf("Kek");
    for(int i = 0; i < 10; i++)
    {
    	write_port(i, i);
    }
   // write_port(CONTROL_STATUS_H, (uint32_t)0xDEADBEEF);
    //write_port(CONTROL_STATUS_L, (uint32_t)0xCAFEBABE);
   //sleep(1);
    printf("\n0x%x ", (uint32_t)read_port(CONTROL_STATUS_L));
    printf("\n0x%x ", (uint32_t)read_port(CONTROL_STATUS_H));
    /*
    for(int i = 0; i < 0x3f; i++)
    {
    	printf("\n0x%x ", (uint32_t)read_port(i));
    }
	*/

   // dump_ram();
}
