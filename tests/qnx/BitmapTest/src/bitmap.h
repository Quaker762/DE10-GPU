/**
 * 32-bit MSBITMAP/DIB loader
 */
#pragma once

#include "common/assert.h"

#include <cstdint>
#include <string>
#include <vector>

struct bmp_file_header
{
    char signature[2];
    uint32_t filesize;
    uint16_t reserved[2];
    uint32_t pixdat_offset;
} __attribute__((packed));

struct bmp_info_header
{
    uint32_t header_size;
    int32_t bmp_width;
    int32_t bmp_height;
    uint16_t color_planes;
    uint16_t bpp;
    uint32_t compression_method;
    int32_t h_res;
    int32_t v_res;
    uint32_t num_colors_in_palette;
    uint32_t num_important_colors_used;
} __attribute__((packed));

// This probably won't be needed because we're using uncompressed
// 24-bit BMPs, bu
enum class CompressionMethod : uint8_t
{
    BI_RGB = 0,
    BI_RLE8,
    BI_RLE4,
    BI_BITFIELDS,
    BI_JPEG,
    BI_PNG,
    BI_ALPHABITFIELDS,
    BI_CMYK,
    BI_CMYKRLE8,
    BI_CMYKREL4
};

class CMSBitmap
{
public:
    CMSBitmap() {}
    CMSBitmap(const std::string&);

    void load(const std::string&);

    int32_t width() const
    {
        ASSERT(m_fheader.signature[0] == 'B');
        return m_iheader.bmp_width;
    };
    int32_t height() const
    {
        ASSERT(m_fheader.signature[0] == 'B');
        return m_iheader.bmp_height;
    }
    uint16_t bpp() const
    {
        ASSERT(m_fheader.signature[0] == 'B');
        return m_iheader.bpp;
    }
    uint32_t filesize() const
    {
        ASSERT(m_fheader.signature[0] == 'B');
        return m_fheader.filesize;
    }

    const uint8_t* pixel_data() const { return m_data.data(); }

private:
    bmp_file_header m_fheader{};
    bmp_info_header m_iheader{};

    std::vector<uint8_t> m_data{};
};
