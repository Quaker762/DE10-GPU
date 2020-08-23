/**
 * Bitmap Test for DE10 GPU
 *
 * Jesse Buhagiar 02/08/2020
 */

#include "bitmap.h"

#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>

static constexpr int FRAMEBUFFER_WIDTH = 640;
static constexpr int FRAMEBUFFER_HEIGHT = 480;
static constexpr uint32_t FRAMEBUFFER_ADDRESS = 0x38000000;
static constexpr uint32_t FRAMEBUFFER_ADDRESS2 = 0x3812c000;

int main()
{
    /*
    CMSBitmap bitmap("/fs/yikes.bmp");

    // for(int i = 0; i < (bitmap.width() * bitmap.height()); i++)
    //{
    //	std::printf("0x%x\n", *reinterpret_cast<const uint32_t*>(bitmap.pixel_data() + i));
    //}

    int memfile = open("/dev/mem", O_RDWR);
    if(memfile < 0)
    {
        std::printf("Failed to open a handle to /dev/mem!\n");
        return -1;
    }

    // Now let's map the framebuffer to a pointer that we can write to
    uint32_t* fb = reinterpret_cast<uint32_t*>(mmap(NULL, FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT * 4, PROT_READ | PROT_WRITE, MAP_SHARED, memfile, FRAMEBUFFER_ADDRESS2));

    if(fb == MAP_FAILED)
    {
        std::printf("Failed to map framebuffer!\n");
        return -1;
    }
    //memcpy(fb, bitmap.pixel_data(), bitmap.width() * bitmap.height() * 3);

    int idx = 0;
    for(int i = 0; i < bitmap.width() * bitmap.height(); i++)
    {
      *reinterpret_cast<uint32_t*>(fb + i) = *reinterpret_cast<const uint32_t*>(bitmap.pixel_data() + idx);
      idx += 4;
    }


    for(int y = 0; y < 480; y++)
    {
        for(int x = 0; x < 640; x++)
        {
            reinterpret_cast<uint32_t*>(fb)[y * 640 + x + 4] = (static_cast<uint32_t>(x ^ y));
        }
    }
*/
/*
   for(int i = 0; i < 480000000; ++i){
    	if(i%4 < 2)
    		*(fb + i) = 0x00FF0000;
    	else
    		*(fb + i) = 0x0000FF00;
	   // *(fb + i) = i;
    }
*/

    int memfile = open("/dev/mem", O_RDWR);
    if(memfile < 0)
    {
        std::printf("Failed to open a handle to /dev/mem!\n");
        return -1;
    }

	uint32_t* fb = reinterpret_cast<uint32_t*>(mmap(NULL, 64, PROT_READ | PROT_WRITE, MAP_SHARED, memfile, 0xFFD0501C));
    //uint32_t* ptr = (uint32_t*)0xc0000000;
    *fb = 0xCAFEBABE;

    std::printf("You should now have a nice bitmap on the screen!\nIf you don't, you fucking suck! Thanks!");
    return 0;
}
