/**
 *
 */
#include "bitmap.h"

#include "common/log.hpp"

#include <cstdio>

CMSBitmap::CMSBitmap(const std::string& fname)
{
    load(fname);
}

void CMSBitmap::load(const std::string& fname)
{
    FILE* bmp;

    log(LogLevel::INFO, "CMSBitmap: attempting to load bitmap %s...\n", fname.c_str());
    bmp = fopen(fname.c_str(), "rb");
    if(!bmp)
    {
        log(LogLevel::ERROR, "CMSBitmap: failed to open a handle to %s!\n", fname.c_str());
        return;
    }

    // Read in the file and info header
    fread(&m_fheader, sizeof(bmp_file_header), 1, bmp);
    fread(&m_iheader, sizeof(bmp_info_header), 1, bmp);
    ASSERT(m_fheader.signature[0] == 'B' && m_fheader.signature[1] == 'M');
    ASSERT(m_fheader.filesize > 0);

    // Now let's load the actual pixel data
    fseek(bmp, m_fheader.pixdat_offset, SEEK_SET);
    m_data.resize(static_cast<size_t>(width() * height() * bpp()));
    fread(&m_data.data()[0], sizeof(uint8_t), static_cast<size_t>(width() * height() * bpp()), bmp);
    log(LogLevel::INFO, "CMSBitmap: done!\n");
}
