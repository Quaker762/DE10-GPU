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

int main()
{
    CMSBitmap bitmap("/fs/test.bmp");

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
    uint32_t* fb = reinterpret_cast<uint32_t*>(mmap(NULL, FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT * 4, PROT_READ | PROT_WRITE, MAP_SHARED, memfile, FRAMEBUFFER_ADDRESS));

    if(fb == MAP_FAILED)
    {
        std::printf("Failed to map framebuffer!\n");
        return -1;
    }

    memcpy(fb, bitmap.pixel_data(), bitmap.width() * bitmap.height() * 3);
    std::printf("You should now have a nice bitmap on the screen!\nIf you don't, you fucking suck! Thanks!");
    return 0;
}