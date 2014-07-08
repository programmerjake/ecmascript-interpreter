#ifndef UNICODE_CATEGORY_H_INCLUDED
#define UNICODE_CATEGORY_H_INCLUDED

#include <cwchar>

inline bool isCharacterCategoryLuLlLtLmLoNl(wint_t chIn)
{
    unsigned ch = (unsigned)chIn;
    if(chIn == WEOF)
        return false;
    if(ch >= 0x41 && ch <= 0x5A)
        return true;
    if(ch >= 0x61 && ch <= 0x7A)
        return true;
    if(ch == 0xAA)
        return true;
    if(ch == 0xB5)
        return true;
    if(ch == 0xBA)
        return true;
    if(ch >= 0xC0 && ch <= 0xD6)
        return true;
    if(ch >= 0xD8 && ch <= 0xF6)
        return true;
    if(ch >= 0xF8 && ch <= 0x2C1)
        return true;
    if(ch >= 0x2C6 && ch <= 0x2D1)
        return true;
    if(ch >= 0x2E0 && ch <= 0x2E4)
        return true;
    if(ch == 0x2EC)
        return true;
    if(ch == 0x2EE)
        return true;
    if(ch >= 0x370 && ch <= 0x374)
        return true;
    if(ch >= 0x376 && ch <= 0x377)
        return true;
    if(ch >= 0x37A && ch <= 0x37D)
        return true;
    if(ch == 0x37F)
        return true;
    if(ch == 0x386)
        return true;
    if(ch >= 0x388 && ch <= 0x38A)
        return true;
    if(ch == 0x38C)
        return true;
    if(ch >= 0x38E && ch <= 0x3A1)
        return true;
    if(ch >= 0x3A3 && ch <= 0x3F5)
        return true;
    if(ch >= 0x3F7 && ch <= 0x481)
        return true;
    if(ch >= 0x48A && ch <= 0x52F)
        return true;
    if(ch >= 0x531 && ch <= 0x556)
        return true;
    if(ch == 0x559)
        return true;
    if(ch >= 0x561 && ch <= 0x587)
        return true;
    if(ch >= 0x5D0 && ch <= 0x5EA)
        return true;
    if(ch >= 0x5F0 && ch <= 0x5F2)
        return true;
    if(ch >= 0x620 && ch <= 0x64A)
        return true;
    if(ch >= 0x66E && ch <= 0x66F)
        return true;
    if(ch >= 0x671 && ch <= 0x6D3)
        return true;
    if(ch == 0x6D5)
        return true;
    if(ch >= 0x6E5 && ch <= 0x6E6)
        return true;
    if(ch >= 0x6EE && ch <= 0x6EF)
        return true;
    if(ch >= 0x6FA && ch <= 0x6FC)
        return true;
    if(ch == 0x6FF)
        return true;
    if(ch == 0x710)
        return true;
    if(ch >= 0x712 && ch <= 0x72F)
        return true;
    if(ch >= 0x74D && ch <= 0x7A5)
        return true;
    if(ch == 0x7B1)
        return true;
    if(ch >= 0x7CA && ch <= 0x7EA)
        return true;
    if(ch >= 0x7F4 && ch <= 0x7F5)
        return true;
    if(ch == 0x7FA)
        return true;
    if(ch >= 0x800 && ch <= 0x815)
        return true;
    if(ch == 0x81A)
        return true;
    if(ch == 0x824)
        return true;
    if(ch == 0x828)
        return true;
    if(ch >= 0x840 && ch <= 0x858)
        return true;
    if(ch >= 0x8A0 && ch <= 0x8B2)
        return true;
    if(ch >= 0x904 && ch <= 0x939)
        return true;
    if(ch == 0x93D)
        return true;
    if(ch == 0x950)
        return true;
    if(ch >= 0x958 && ch <= 0x961)
        return true;
    if(ch >= 0x971 && ch <= 0x980)
        return true;
    if(ch >= 0x985 && ch <= 0x98C)
        return true;
    if(ch >= 0x98F && ch <= 0x990)
        return true;
    if(ch >= 0x993 && ch <= 0x9A8)
        return true;
    if(ch >= 0x9AA && ch <= 0x9B0)
        return true;
    if(ch == 0x9B2)
        return true;
    if(ch >= 0x9B6 && ch <= 0x9B9)
        return true;
    if(ch == 0x9BD)
        return true;
    if(ch == 0x9CE)
        return true;
    if(ch >= 0x9DC && ch <= 0x9DD)
        return true;
    if(ch >= 0x9DF && ch <= 0x9E1)
        return true;
    if(ch >= 0x9F0 && ch <= 0x9F1)
        return true;
    if(ch >= 0xA05 && ch <= 0xA0A)
        return true;
    if(ch >= 0xA0F && ch <= 0xA10)
        return true;
    if(ch >= 0xA13 && ch <= 0xA28)
        return true;
    if(ch >= 0xA2A && ch <= 0xA30)
        return true;
    if(ch >= 0xA32 && ch <= 0xA33)
        return true;
    if(ch >= 0xA35 && ch <= 0xA36)
        return true;
    if(ch >= 0xA38 && ch <= 0xA39)
        return true;
    if(ch >= 0xA59 && ch <= 0xA5C)
        return true;
    if(ch == 0xA5E)
        return true;
    if(ch >= 0xA72 && ch <= 0xA74)
        return true;
    if(ch >= 0xA85 && ch <= 0xA8D)
        return true;
    if(ch >= 0xA8F && ch <= 0xA91)
        return true;
    if(ch >= 0xA93 && ch <= 0xAA8)
        return true;
    if(ch >= 0xAAA && ch <= 0xAB0)
        return true;
    if(ch >= 0xAB2 && ch <= 0xAB3)
        return true;
    if(ch >= 0xAB5 && ch <= 0xAB9)
        return true;
    if(ch == 0xABD)
        return true;
    if(ch == 0xAD0)
        return true;
    if(ch >= 0xAE0 && ch <= 0xAE1)
        return true;
    if(ch >= 0xB05 && ch <= 0xB0C)
        return true;
    if(ch >= 0xB0F && ch <= 0xB10)
        return true;
    if(ch >= 0xB13 && ch <= 0xB28)
        return true;
    if(ch >= 0xB2A && ch <= 0xB30)
        return true;
    if(ch >= 0xB32 && ch <= 0xB33)
        return true;
    if(ch >= 0xB35 && ch <= 0xB39)
        return true;
    if(ch == 0xB3D)
        return true;
    if(ch >= 0xB5C && ch <= 0xB5D)
        return true;
    if(ch >= 0xB5F && ch <= 0xB61)
        return true;
    if(ch == 0xB71)
        return true;
    if(ch == 0xB83)
        return true;
    if(ch >= 0xB85 && ch <= 0xB8A)
        return true;
    if(ch >= 0xB8E && ch <= 0xB90)
        return true;
    if(ch >= 0xB92 && ch <= 0xB95)
        return true;
    if(ch >= 0xB99 && ch <= 0xB9A)
        return true;
    if(ch == 0xB9C)
        return true;
    if(ch >= 0xB9E && ch <= 0xB9F)
        return true;
    if(ch >= 0xBA3 && ch <= 0xBA4)
        return true;
    if(ch >= 0xBA8 && ch <= 0xBAA)
        return true;
    if(ch >= 0xBAE && ch <= 0xBB9)
        return true;
    if(ch == 0xBD0)
        return true;
    if(ch >= 0xC05 && ch <= 0xC0C)
        return true;
    if(ch >= 0xC0E && ch <= 0xC10)
        return true;
    if(ch >= 0xC12 && ch <= 0xC28)
        return true;
    if(ch >= 0xC2A && ch <= 0xC39)
        return true;
    if(ch == 0xC3D)
        return true;
    if(ch >= 0xC58 && ch <= 0xC59)
        return true;
    if(ch >= 0xC60 && ch <= 0xC61)
        return true;
    if(ch >= 0xC85 && ch <= 0xC8C)
        return true;
    if(ch >= 0xC8E && ch <= 0xC90)
        return true;
    if(ch >= 0xC92 && ch <= 0xCA8)
        return true;
    if(ch >= 0xCAA && ch <= 0xCB3)
        return true;
    if(ch >= 0xCB5 && ch <= 0xCB9)
        return true;
    if(ch == 0xCBD)
        return true;
    if(ch == 0xCDE)
        return true;
    if(ch >= 0xCE0 && ch <= 0xCE1)
        return true;
    if(ch >= 0xCF1 && ch <= 0xCF2)
        return true;
    if(ch >= 0xD05 && ch <= 0xD0C)
        return true;
    if(ch >= 0xD0E && ch <= 0xD10)
        return true;
    if(ch >= 0xD12 && ch <= 0xD3A)
        return true;
    if(ch == 0xD3D)
        return true;
    if(ch == 0xD4E)
        return true;
    if(ch >= 0xD60 && ch <= 0xD61)
        return true;
    if(ch >= 0xD7A && ch <= 0xD7F)
        return true;
    if(ch >= 0xD85 && ch <= 0xD96)
        return true;
    if(ch >= 0xD9A && ch <= 0xDB1)
        return true;
    if(ch >= 0xDB3 && ch <= 0xDBB)
        return true;
    if(ch == 0xDBD)
        return true;
    if(ch >= 0xDC0 && ch <= 0xDC6)
        return true;
    if(ch >= 0xE01 && ch <= 0xE30)
        return true;
    if(ch >= 0xE32 && ch <= 0xE33)
        return true;
    if(ch >= 0xE40 && ch <= 0xE46)
        return true;
    if(ch >= 0xE81 && ch <= 0xE82)
        return true;
    if(ch == 0xE84)
        return true;
    if(ch >= 0xE87 && ch <= 0xE88)
        return true;
    if(ch == 0xE8A)
        return true;
    if(ch == 0xE8D)
        return true;
    if(ch >= 0xE94 && ch <= 0xE97)
        return true;
    if(ch >= 0xE99 && ch <= 0xE9F)
        return true;
    if(ch >= 0xEA1 && ch <= 0xEA3)
        return true;
    if(ch == 0xEA5)
        return true;
    if(ch == 0xEA7)
        return true;
    if(ch >= 0xEAA && ch <= 0xEAB)
        return true;
    if(ch >= 0xEAD && ch <= 0xEB0)
        return true;
    if(ch >= 0xEB2 && ch <= 0xEB3)
        return true;
    if(ch == 0xEBD)
        return true;
    if(ch >= 0xEC0 && ch <= 0xEC4)
        return true;
    if(ch == 0xEC6)
        return true;
    if(ch >= 0xEDC && ch <= 0xEDF)
        return true;
    if(ch == 0xF00)
        return true;
    if(ch >= 0xF40 && ch <= 0xF47)
        return true;
    if(ch >= 0xF49 && ch <= 0xF6C)
        return true;
    if(ch >= 0xF88 && ch <= 0xF8C)
        return true;
    if(ch >= 0x1000 && ch <= 0x102A)
        return true;
    if(ch == 0x103F)
        return true;
    if(ch >= 0x1050 && ch <= 0x1055)
        return true;
    if(ch >= 0x105A && ch <= 0x105D)
        return true;
    if(ch == 0x1061)
        return true;
    if(ch >= 0x1065 && ch <= 0x1066)
        return true;
    if(ch >= 0x106E && ch <= 0x1070)
        return true;
    if(ch >= 0x1075 && ch <= 0x1081)
        return true;
    if(ch == 0x108E)
        return true;
    if(ch >= 0x10A0 && ch <= 0x10C5)
        return true;
    if(ch == 0x10C7)
        return true;
    if(ch == 0x10CD)
        return true;
    if(ch >= 0x10D0 && ch <= 0x10FA)
        return true;
    if(ch >= 0x10FC && ch <= 0x1248)
        return true;
    if(ch >= 0x124A && ch <= 0x124D)
        return true;
    if(ch >= 0x1250 && ch <= 0x1256)
        return true;
    if(ch == 0x1258)
        return true;
    if(ch >= 0x125A && ch <= 0x125D)
        return true;
    if(ch >= 0x1260 && ch <= 0x1288)
        return true;
    if(ch >= 0x128A && ch <= 0x128D)
        return true;
    if(ch >= 0x1290 && ch <= 0x12B0)
        return true;
    if(ch >= 0x12B2 && ch <= 0x12B5)
        return true;
    if(ch >= 0x12B8 && ch <= 0x12BE)
        return true;
    if(ch == 0x12C0)
        return true;
    if(ch >= 0x12C2 && ch <= 0x12C5)
        return true;
    if(ch >= 0x12C8 && ch <= 0x12D6)
        return true;
    if(ch >= 0x12D8 && ch <= 0x1310)
        return true;
    if(ch >= 0x1312 && ch <= 0x1315)
        return true;
    if(ch >= 0x1318 && ch <= 0x135A)
        return true;
    if(ch >= 0x1380 && ch <= 0x138F)
        return true;
    if(ch >= 0x13A0 && ch <= 0x13F4)
        return true;
    if(ch >= 0x1401 && ch <= 0x166C)
        return true;
    if(ch >= 0x166F && ch <= 0x167F)
        return true;
    if(ch >= 0x1681 && ch <= 0x169A)
        return true;
    if(ch >= 0x16A0 && ch <= 0x16EA)
        return true;
    if(ch >= 0x16EE && ch <= 0x16F8)
        return true;
    if(ch >= 0x1700 && ch <= 0x170C)
        return true;
    if(ch >= 0x170E && ch <= 0x1711)
        return true;
    if(ch >= 0x1720 && ch <= 0x1731)
        return true;
    if(ch >= 0x1740 && ch <= 0x1751)
        return true;
    if(ch >= 0x1760 && ch <= 0x176C)
        return true;
    if(ch >= 0x176E && ch <= 0x1770)
        return true;
    if(ch >= 0x1780 && ch <= 0x17B3)
        return true;
    if(ch == 0x17D7)
        return true;
    if(ch == 0x17DC)
        return true;
    if(ch >= 0x1820 && ch <= 0x1877)
        return true;
    if(ch >= 0x1880 && ch <= 0x18A8)
        return true;
    if(ch == 0x18AA)
        return true;
    if(ch >= 0x18B0 && ch <= 0x18F5)
        return true;
    if(ch >= 0x1900 && ch <= 0x191E)
        return true;
    if(ch >= 0x1950 && ch <= 0x196D)
        return true;
    if(ch >= 0x1970 && ch <= 0x1974)
        return true;
    if(ch >= 0x1980 && ch <= 0x19AB)
        return true;
    if(ch >= 0x19C1 && ch <= 0x19C7)
        return true;
    if(ch >= 0x1A00 && ch <= 0x1A16)
        return true;
    if(ch >= 0x1A20 && ch <= 0x1A54)
        return true;
    if(ch == 0x1AA7)
        return true;
    if(ch >= 0x1B05 && ch <= 0x1B33)
        return true;
    if(ch >= 0x1B45 && ch <= 0x1B4B)
        return true;
    if(ch >= 0x1B83 && ch <= 0x1BA0)
        return true;
    if(ch >= 0x1BAE && ch <= 0x1BAF)
        return true;
    if(ch >= 0x1BBA && ch <= 0x1BE5)
        return true;
    if(ch >= 0x1C00 && ch <= 0x1C23)
        return true;
    if(ch >= 0x1C4D && ch <= 0x1C4F)
        return true;
    if(ch >= 0x1C5A && ch <= 0x1C7D)
        return true;
    if(ch >= 0x1CE9 && ch <= 0x1CEC)
        return true;
    if(ch >= 0x1CEE && ch <= 0x1CF1)
        return true;
    if(ch >= 0x1CF5 && ch <= 0x1CF6)
        return true;
    if(ch >= 0x1D00 && ch <= 0x1DBF)
        return true;
    if(ch >= 0x1E00 && ch <= 0x1F15)
        return true;
    if(ch >= 0x1F18 && ch <= 0x1F1D)
        return true;
    if(ch >= 0x1F20 && ch <= 0x1F45)
        return true;
    if(ch >= 0x1F48 && ch <= 0x1F4D)
        return true;
    if(ch >= 0x1F50 && ch <= 0x1F57)
        return true;
    if(ch == 0x1F59)
        return true;
    if(ch == 0x1F5B)
        return true;
    if(ch == 0x1F5D)
        return true;
    if(ch >= 0x1F5F && ch <= 0x1F7D)
        return true;
    if(ch >= 0x1F80 && ch <= 0x1FB4)
        return true;
    if(ch >= 0x1FB6 && ch <= 0x1FBC)
        return true;
    if(ch == 0x1FBE)
        return true;
    if(ch >= 0x1FC2 && ch <= 0x1FC4)
        return true;
    if(ch >= 0x1FC6 && ch <= 0x1FCC)
        return true;
    if(ch >= 0x1FD0 && ch <= 0x1FD3)
        return true;
    if(ch >= 0x1FD6 && ch <= 0x1FDB)
        return true;
    if(ch >= 0x1FE0 && ch <= 0x1FEC)
        return true;
    if(ch >= 0x1FF2 && ch <= 0x1FF4)
        return true;
    if(ch >= 0x1FF6 && ch <= 0x1FFC)
        return true;
    if(ch == 0x2071)
        return true;
    if(ch == 0x207F)
        return true;
    if(ch >= 0x2090 && ch <= 0x209C)
        return true;
    if(ch == 0x2102)
        return true;
    if(ch == 0x2107)
        return true;
    if(ch >= 0x210A && ch <= 0x2113)
        return true;
    if(ch == 0x2115)
        return true;
    if(ch >= 0x2119 && ch <= 0x211D)
        return true;
    if(ch == 0x2124)
        return true;
    if(ch == 0x2126)
        return true;
    if(ch == 0x2128)
        return true;
    if(ch >= 0x212A && ch <= 0x212D)
        return true;
    if(ch >= 0x212F && ch <= 0x2139)
        return true;
    if(ch >= 0x213C && ch <= 0x213F)
        return true;
    if(ch >= 0x2145 && ch <= 0x2149)
        return true;
    if(ch == 0x214E)
        return true;
    if(ch >= 0x2160 && ch <= 0x2188)
        return true;
    if(ch >= 0x2C00 && ch <= 0x2C2E)
        return true;
    if(ch >= 0x2C30 && ch <= 0x2C5E)
        return true;
    if(ch >= 0x2C60 && ch <= 0x2CE4)
        return true;
    if(ch >= 0x2CEB && ch <= 0x2CEE)
        return true;
    if(ch >= 0x2CF2 && ch <= 0x2CF3)
        return true;
    if(ch >= 0x2D00 && ch <= 0x2D25)
        return true;
    if(ch == 0x2D27)
        return true;
    if(ch == 0x2D2D)
        return true;
    if(ch >= 0x2D30 && ch <= 0x2D67)
        return true;
    if(ch == 0x2D6F)
        return true;
    if(ch >= 0x2D80 && ch <= 0x2D96)
        return true;
    if(ch >= 0x2DA0 && ch <= 0x2DA6)
        return true;
    if(ch >= 0x2DA8 && ch <= 0x2DAE)
        return true;
    if(ch >= 0x2DB0 && ch <= 0x2DB6)
        return true;
    if(ch >= 0x2DB8 && ch <= 0x2DBE)
        return true;
    if(ch >= 0x2DC0 && ch <= 0x2DC6)
        return true;
    if(ch >= 0x2DC8 && ch <= 0x2DCE)
        return true;
    if(ch >= 0x2DD0 && ch <= 0x2DD6)
        return true;
    if(ch >= 0x2DD8 && ch <= 0x2DDE)
        return true;
    if(ch == 0x2E2F)
        return true;
    if(ch >= 0x3005 && ch <= 0x3007)
        return true;
    if(ch >= 0x3021 && ch <= 0x3029)
        return true;
    if(ch >= 0x3031 && ch <= 0x3035)
        return true;
    if(ch >= 0x3038 && ch <= 0x303C)
        return true;
    if(ch >= 0x3041 && ch <= 0x3096)
        return true;
    if(ch >= 0x309D && ch <= 0x309F)
        return true;
    if(ch >= 0x30A1 && ch <= 0x30FA)
        return true;
    if(ch >= 0x30FC && ch <= 0x30FF)
        return true;
    if(ch >= 0x3105 && ch <= 0x312D)
        return true;
    if(ch >= 0x3131 && ch <= 0x318E)
        return true;
    if(ch >= 0x31A0 && ch <= 0x31BA)
        return true;
    if(ch >= 0x31F0 && ch <= 0x31FF)
        return true;
    if(ch == 0x3400)
        return true;
    if(ch == 0x4DB5)
        return true;
    if(ch == 0x4E00)
        return true;
    if(ch == 0x9FCC)
        return true;
    if(ch >= 0xA000 && ch <= 0xA48C)
        return true;
    if(ch >= 0xA4D0 && ch <= 0xA4FD)
        return true;
    if(ch >= 0xA500 && ch <= 0xA60C)
        return true;
    if(ch >= 0xA610 && ch <= 0xA61F)
        return true;
    if(ch >= 0xA62A && ch <= 0xA62B)
        return true;
    if(ch >= 0xA640 && ch <= 0xA66E)
        return true;
    if(ch >= 0xA67F && ch <= 0xA69D)
        return true;
    if(ch >= 0xA6A0 && ch <= 0xA6EF)
        return true;
    if(ch >= 0xA717 && ch <= 0xA71F)
        return true;
    if(ch >= 0xA722 && ch <= 0xA788)
        return true;
    if(ch >= 0xA78B && ch <= 0xA78E)
        return true;
    if(ch >= 0xA790 && ch <= 0xA7AD)
        return true;
    if(ch >= 0xA7B0 && ch <= 0xA7B1)
        return true;
    if(ch >= 0xA7F7 && ch <= 0xA801)
        return true;
    if(ch >= 0xA803 && ch <= 0xA805)
        return true;
    if(ch >= 0xA807 && ch <= 0xA80A)
        return true;
    if(ch >= 0xA80C && ch <= 0xA822)
        return true;
    if(ch >= 0xA840 && ch <= 0xA873)
        return true;
    if(ch >= 0xA882 && ch <= 0xA8B3)
        return true;
    if(ch >= 0xA8F2 && ch <= 0xA8F7)
        return true;
    if(ch == 0xA8FB)
        return true;
    if(ch >= 0xA90A && ch <= 0xA925)
        return true;
    if(ch >= 0xA930 && ch <= 0xA946)
        return true;
    if(ch >= 0xA960 && ch <= 0xA97C)
        return true;
    if(ch >= 0xA984 && ch <= 0xA9B2)
        return true;
    if(ch == 0xA9CF)
        return true;
    if(ch >= 0xA9E0 && ch <= 0xA9E4)
        return true;
    if(ch >= 0xA9E6 && ch <= 0xA9EF)
        return true;
    if(ch >= 0xA9FA && ch <= 0xA9FE)
        return true;
    if(ch >= 0xAA00 && ch <= 0xAA28)
        return true;
    if(ch >= 0xAA40 && ch <= 0xAA42)
        return true;
    if(ch >= 0xAA44 && ch <= 0xAA4B)
        return true;
    if(ch >= 0xAA60 && ch <= 0xAA76)
        return true;
    if(ch == 0xAA7A)
        return true;
    if(ch >= 0xAA7E && ch <= 0xAAAF)
        return true;
    if(ch == 0xAAB1)
        return true;
    if(ch >= 0xAAB5 && ch <= 0xAAB6)
        return true;
    if(ch >= 0xAAB9 && ch <= 0xAABD)
        return true;
    if(ch == 0xAAC0)
        return true;
    if(ch == 0xAAC2)
        return true;
    if(ch >= 0xAADB && ch <= 0xAADD)
        return true;
    if(ch >= 0xAAE0 && ch <= 0xAAEA)
        return true;
    if(ch >= 0xAAF2 && ch <= 0xAAF4)
        return true;
    if(ch >= 0xAB01 && ch <= 0xAB06)
        return true;
    if(ch >= 0xAB09 && ch <= 0xAB0E)
        return true;
    if(ch >= 0xAB11 && ch <= 0xAB16)
        return true;
    if(ch >= 0xAB20 && ch <= 0xAB26)
        return true;
    if(ch >= 0xAB28 && ch <= 0xAB2E)
        return true;
    if(ch >= 0xAB30 && ch <= 0xAB5A)
        return true;
    if(ch >= 0xAB5C && ch <= 0xAB5F)
        return true;
    if(ch >= 0xAB64 && ch <= 0xAB65)
        return true;
    if(ch >= 0xABC0 && ch <= 0xABE2)
        return true;
    if(ch == 0xAC00)
        return true;
    if(ch == 0xD7A3)
        return true;
    if(ch >= 0xD7B0 && ch <= 0xD7C6)
        return true;
    if(ch >= 0xD7CB && ch <= 0xD7FB)
        return true;
    if(ch >= 0xF900 && ch <= 0xFA6D)
        return true;
    if(ch >= 0xFA70 && ch <= 0xFAD9)
        return true;
    if(ch >= 0xFB00 && ch <= 0xFB06)
        return true;
    if(ch >= 0xFB13 && ch <= 0xFB17)
        return true;
    if(ch == 0xFB1D)
        return true;
    if(ch >= 0xFB1F && ch <= 0xFB28)
        return true;
    if(ch >= 0xFB2A && ch <= 0xFB36)
        return true;
    if(ch >= 0xFB38 && ch <= 0xFB3C)
        return true;
    if(ch == 0xFB3E)
        return true;
    if(ch >= 0xFB40 && ch <= 0xFB41)
        return true;
    if(ch >= 0xFB43 && ch <= 0xFB44)
        return true;
    if(ch >= 0xFB46 && ch <= 0xFBB1)
        return true;
    if(ch >= 0xFBD3 && ch <= 0xFD3D)
        return true;
    if(ch >= 0xFD50 && ch <= 0xFD8F)
        return true;
    if(ch >= 0xFD92 && ch <= 0xFDC7)
        return true;
    if(ch >= 0xFDF0 && ch <= 0xFDFB)
        return true;
    if(ch >= 0xFE70 && ch <= 0xFE74)
        return true;
    if(ch >= 0xFE76 && ch <= 0xFEFC)
        return true;
    if(ch >= 0xFF21 && ch <= 0xFF3A)
        return true;
    if(ch >= 0xFF41 && ch <= 0xFF5A)
        return true;
    if(ch >= 0xFF66 && ch <= 0xFFBE)
        return true;
    if(ch >= 0xFFC2 && ch <= 0xFFC7)
        return true;
    if(ch >= 0xFFCA && ch <= 0xFFCF)
        return true;
    if(ch >= 0xFFD2 && ch <= 0xFFD7)
        return true;
    if(ch >= 0xFFDA && ch <= 0xFFDC)
        return true;
    if(ch >= 0x10000 && ch <= 0x1000B)
        return true;
    if(ch >= 0x1000D && ch <= 0x10026)
        return true;
    if(ch >= 0x10028 && ch <= 0x1003A)
        return true;
    if(ch >= 0x1003C && ch <= 0x1003D)
        return true;
    if(ch >= 0x1003F && ch <= 0x1004D)
        return true;
    if(ch >= 0x10050 && ch <= 0x1005D)
        return true;
    if(ch >= 0x10080 && ch <= 0x100FA)
        return true;
    if(ch >= 0x10140 && ch <= 0x10174)
        return true;
    if(ch >= 0x10280 && ch <= 0x1029C)
        return true;
    if(ch >= 0x102A0 && ch <= 0x102D0)
        return true;
    if(ch >= 0x10300 && ch <= 0x1031F)
        return true;
    if(ch >= 0x10330 && ch <= 0x1034A)
        return true;
    if(ch >= 0x10350 && ch <= 0x10375)
        return true;
    if(ch >= 0x10380 && ch <= 0x1039D)
        return true;
    if(ch >= 0x103A0 && ch <= 0x103C3)
        return true;
    if(ch >= 0x103C8 && ch <= 0x103CF)
        return true;
    if(ch >= 0x103D1 && ch <= 0x103D5)
        return true;
    if(ch >= 0x10400 && ch <= 0x1049D)
        return true;
    if(ch >= 0x10500 && ch <= 0x10527)
        return true;
    if(ch >= 0x10530 && ch <= 0x10563)
        return true;
    if(ch >= 0x10600 && ch <= 0x10736)
        return true;
    if(ch >= 0x10740 && ch <= 0x10755)
        return true;
    if(ch >= 0x10760 && ch <= 0x10767)
        return true;
    if(ch >= 0x10800 && ch <= 0x10805)
        return true;
    if(ch == 0x10808)
        return true;
    if(ch >= 0x1080A && ch <= 0x10835)
        return true;
    if(ch >= 0x10837 && ch <= 0x10838)
        return true;
    if(ch == 0x1083C)
        return true;
    if(ch >= 0x1083F && ch <= 0x10855)
        return true;
    if(ch >= 0x10860 && ch <= 0x10876)
        return true;
    if(ch >= 0x10880 && ch <= 0x1089E)
        return true;
    if(ch >= 0x10900 && ch <= 0x10915)
        return true;
    if(ch >= 0x10920 && ch <= 0x10939)
        return true;
    if(ch >= 0x10980 && ch <= 0x109B7)
        return true;
    if(ch >= 0x109BE && ch <= 0x109BF)
        return true;
    if(ch == 0x10A00)
        return true;
    if(ch >= 0x10A10 && ch <= 0x10A13)
        return true;
    if(ch >= 0x10A15 && ch <= 0x10A17)
        return true;
    if(ch >= 0x10A19 && ch <= 0x10A33)
        return true;
    if(ch >= 0x10A60 && ch <= 0x10A7C)
        return true;
    if(ch >= 0x10A80 && ch <= 0x10A9C)
        return true;
    if(ch >= 0x10AC0 && ch <= 0x10AC7)
        return true;
    if(ch >= 0x10AC9 && ch <= 0x10AE4)
        return true;
    if(ch >= 0x10B00 && ch <= 0x10B35)
        return true;
    if(ch >= 0x10B40 && ch <= 0x10B55)
        return true;
    if(ch >= 0x10B60 && ch <= 0x10B72)
        return true;
    if(ch >= 0x10B80 && ch <= 0x10B91)
        return true;
    if(ch >= 0x10C00 && ch <= 0x10C48)
        return true;
    if(ch >= 0x11003 && ch <= 0x11037)
        return true;
    if(ch >= 0x11083 && ch <= 0x110AF)
        return true;
    if(ch >= 0x110D0 && ch <= 0x110E8)
        return true;
    if(ch >= 0x11103 && ch <= 0x11126)
        return true;
    if(ch >= 0x11150 && ch <= 0x11172)
        return true;
    if(ch == 0x11176)
        return true;
    if(ch >= 0x11183 && ch <= 0x111B2)
        return true;
    if(ch >= 0x111C1 && ch <= 0x111C4)
        return true;
    if(ch == 0x111DA)
        return true;
    if(ch >= 0x11200 && ch <= 0x11211)
        return true;
    if(ch >= 0x11213 && ch <= 0x1122B)
        return true;
    if(ch >= 0x112B0 && ch <= 0x112DE)
        return true;
    if(ch >= 0x11305 && ch <= 0x1130C)
        return true;
    if(ch >= 0x1130F && ch <= 0x11310)
        return true;
    if(ch >= 0x11313 && ch <= 0x11328)
        return true;
    if(ch >= 0x1132A && ch <= 0x11330)
        return true;
    if(ch >= 0x11332 && ch <= 0x11333)
        return true;
    if(ch >= 0x11335 && ch <= 0x11339)
        return true;
    if(ch == 0x1133D)
        return true;
    if(ch >= 0x1135D && ch <= 0x11361)
        return true;
    if(ch >= 0x11480 && ch <= 0x114AF)
        return true;
    if(ch >= 0x114C4 && ch <= 0x114C5)
        return true;
    if(ch == 0x114C7)
        return true;
    if(ch >= 0x11580 && ch <= 0x115AE)
        return true;
    if(ch >= 0x11600 && ch <= 0x1162F)
        return true;
    if(ch == 0x11644)
        return true;
    if(ch >= 0x11680 && ch <= 0x116AA)
        return true;
    if(ch >= 0x118A0 && ch <= 0x118DF)
        return true;
    if(ch == 0x118FF)
        return true;
    if(ch >= 0x11AC0 && ch <= 0x11AF8)
        return true;
    if(ch >= 0x12000 && ch <= 0x12398)
        return true;
    if(ch >= 0x12400 && ch <= 0x1246E)
        return true;
    if(ch >= 0x13000 && ch <= 0x1342E)
        return true;
    if(ch >= 0x16800 && ch <= 0x16A38)
        return true;
    if(ch >= 0x16A40 && ch <= 0x16A5E)
        return true;
    if(ch >= 0x16AD0 && ch <= 0x16AED)
        return true;
    if(ch >= 0x16B00 && ch <= 0x16B2F)
        return true;
    if(ch >= 0x16B40 && ch <= 0x16B43)
        return true;
    if(ch >= 0x16B63 && ch <= 0x16B77)
        return true;
    if(ch >= 0x16B7D && ch <= 0x16B8F)
        return true;
    if(ch >= 0x16F00 && ch <= 0x16F44)
        return true;
    if(ch == 0x16F50)
        return true;
    if(ch >= 0x16F93 && ch <= 0x16F9F)
        return true;
    if(ch >= 0x1B000 && ch <= 0x1B001)
        return true;
    if(ch >= 0x1BC00 && ch <= 0x1BC6A)
        return true;
    if(ch >= 0x1BC70 && ch <= 0x1BC7C)
        return true;
    if(ch >= 0x1BC80 && ch <= 0x1BC88)
        return true;
    if(ch >= 0x1BC90 && ch <= 0x1BC99)
        return true;
    if(ch >= 0x1D400 && ch <= 0x1D454)
        return true;
    if(ch >= 0x1D456 && ch <= 0x1D49C)
        return true;
    if(ch >= 0x1D49E && ch <= 0x1D49F)
        return true;
    if(ch == 0x1D4A2)
        return true;
    if(ch >= 0x1D4A5 && ch <= 0x1D4A6)
        return true;
    if(ch >= 0x1D4A9 && ch <= 0x1D4AC)
        return true;
    if(ch >= 0x1D4AE && ch <= 0x1D4B9)
        return true;
    if(ch == 0x1D4BB)
        return true;
    if(ch >= 0x1D4BD && ch <= 0x1D4C3)
        return true;
    if(ch >= 0x1D4C5 && ch <= 0x1D505)
        return true;
    if(ch >= 0x1D507 && ch <= 0x1D50A)
        return true;
    if(ch >= 0x1D50D && ch <= 0x1D514)
        return true;
    if(ch >= 0x1D516 && ch <= 0x1D51C)
        return true;
    if(ch >= 0x1D51E && ch <= 0x1D539)
        return true;
    if(ch >= 0x1D53B && ch <= 0x1D53E)
        return true;
    if(ch >= 0x1D540 && ch <= 0x1D544)
        return true;
    if(ch == 0x1D546)
        return true;
    if(ch >= 0x1D54A && ch <= 0x1D550)
        return true;
    if(ch >= 0x1D552 && ch <= 0x1D6A5)
        return true;
    if(ch >= 0x1D6A8 && ch <= 0x1D6C0)
        return true;
    if(ch >= 0x1D6C2 && ch <= 0x1D6DA)
        return true;
    if(ch >= 0x1D6DC && ch <= 0x1D6FA)
        return true;
    if(ch >= 0x1D6FC && ch <= 0x1D714)
        return true;
    if(ch >= 0x1D716 && ch <= 0x1D734)
        return true;
    if(ch >= 0x1D736 && ch <= 0x1D74E)
        return true;
    if(ch >= 0x1D750 && ch <= 0x1D76E)
        return true;
    if(ch >= 0x1D770 && ch <= 0x1D788)
        return true;
    if(ch >= 0x1D78A && ch <= 0x1D7A8)
        return true;
    if(ch >= 0x1D7AA && ch <= 0x1D7C2)
        return true;
    if(ch >= 0x1D7C4 && ch <= 0x1D7CB)
        return true;
    if(ch >= 0x1E800 && ch <= 0x1E8C4)
        return true;
    if(ch >= 0x1EE00 && ch <= 0x1EE03)
        return true;
    if(ch >= 0x1EE05 && ch <= 0x1EE1F)
        return true;
    if(ch >= 0x1EE21 && ch <= 0x1EE22)
        return true;
    if(ch == 0x1EE24)
        return true;
    if(ch == 0x1EE27)
        return true;
    if(ch >= 0x1EE29 && ch <= 0x1EE32)
        return true;
    if(ch >= 0x1EE34 && ch <= 0x1EE37)
        return true;
    if(ch == 0x1EE39)
        return true;
    if(ch == 0x1EE3B)
        return true;
    if(ch == 0x1EE42)
        return true;
    if(ch == 0x1EE47)
        return true;
    if(ch == 0x1EE49)
        return true;
    if(ch == 0x1EE4B)
        return true;
    if(ch >= 0x1EE4D && ch <= 0x1EE4F)
        return true;
    if(ch >= 0x1EE51 && ch <= 0x1EE52)
        return true;
    if(ch == 0x1EE54)
        return true;
    if(ch == 0x1EE57)
        return true;
    if(ch == 0x1EE59)
        return true;
    if(ch == 0x1EE5B)
        return true;
    if(ch == 0x1EE5D)
        return true;
    if(ch == 0x1EE5F)
        return true;
    if(ch >= 0x1EE61 && ch <= 0x1EE62)
        return true;
    if(ch == 0x1EE64)
        return true;
    if(ch >= 0x1EE67 && ch <= 0x1EE6A)
        return true;
    if(ch >= 0x1EE6C && ch <= 0x1EE72)
        return true;
    if(ch >= 0x1EE74 && ch <= 0x1EE77)
        return true;
    if(ch >= 0x1EE79 && ch <= 0x1EE7C)
        return true;
    if(ch == 0x1EE7E)
        return true;
    if(ch >= 0x1EE80 && ch <= 0x1EE89)
        return true;
    if(ch >= 0x1EE8B && ch <= 0x1EE9B)
        return true;
    if(ch >= 0x1EEA1 && ch <= 0x1EEA3)
        return true;
    if(ch >= 0x1EEA5 && ch <= 0x1EEA9)
        return true;
    if(ch >= 0x1EEAB && ch <= 0x1EEBB)
        return true;
    if(ch == 0x20000)
        return true;
    if(ch == 0x2A6D6)
        return true;
    if(ch == 0x2A700)
        return true;
    if(ch == 0x2B734)
        return true;
    if(ch == 0x2B740)
        return true;
    if(ch == 0x2B81D)
        return true;
    if(ch >= 0x2F800 && ch <= 0x2FA1D)
        return true;
    return false;
}

inline bool isCharacterCategoryMnMc(wint_t chIn)
{
    unsigned ch = (unsigned)chIn;
    if(chIn == WEOF)
        return false;
    if(ch >= 0x300 && ch <= 0x36F)
        return true;
    if(ch >= 0x483 && ch <= 0x487)
        return true;
    if(ch >= 0x591 && ch <= 0x5BD)
        return true;
    if(ch == 0x5BF)
        return true;
    if(ch >= 0x5C1 && ch <= 0x5C2)
        return true;
    if(ch >= 0x5C4 && ch <= 0x5C5)
        return true;
    if(ch == 0x5C7)
        return true;
    if(ch >= 0x610 && ch <= 0x61A)
        return true;
    if(ch >= 0x64B && ch <= 0x65F)
        return true;
    if(ch == 0x670)
        return true;
    if(ch >= 0x6D6 && ch <= 0x6DC)
        return true;
    if(ch >= 0x6DF && ch <= 0x6E4)
        return true;
    if(ch >= 0x6E7 && ch <= 0x6E8)
        return true;
    if(ch >= 0x6EA && ch <= 0x6ED)
        return true;
    if(ch == 0x711)
        return true;
    if(ch >= 0x730 && ch <= 0x74A)
        return true;
    if(ch >= 0x7A6 && ch <= 0x7B0)
        return true;
    if(ch >= 0x7EB && ch <= 0x7F3)
        return true;
    if(ch >= 0x816 && ch <= 0x819)
        return true;
    if(ch >= 0x81B && ch <= 0x823)
        return true;
    if(ch >= 0x825 && ch <= 0x827)
        return true;
    if(ch >= 0x829 && ch <= 0x82D)
        return true;
    if(ch >= 0x859 && ch <= 0x85B)
        return true;
    if(ch >= 0x8E4 && ch <= 0x903)
        return true;
    if(ch >= 0x93A && ch <= 0x93C)
        return true;
    if(ch >= 0x93E && ch <= 0x94F)
        return true;
    if(ch >= 0x951 && ch <= 0x957)
        return true;
    if(ch >= 0x962 && ch <= 0x963)
        return true;
    if(ch >= 0x981 && ch <= 0x983)
        return true;
    if(ch == 0x9BC)
        return true;
    if(ch >= 0x9BE && ch <= 0x9C4)
        return true;
    if(ch >= 0x9C7 && ch <= 0x9C8)
        return true;
    if(ch >= 0x9CB && ch <= 0x9CD)
        return true;
    if(ch == 0x9D7)
        return true;
    if(ch >= 0x9E2 && ch <= 0x9E3)
        return true;
    if(ch >= 0xA01 && ch <= 0xA03)
        return true;
    if(ch == 0xA3C)
        return true;
    if(ch >= 0xA3E && ch <= 0xA42)
        return true;
    if(ch >= 0xA47 && ch <= 0xA48)
        return true;
    if(ch >= 0xA4B && ch <= 0xA4D)
        return true;
    if(ch == 0xA51)
        return true;
    if(ch >= 0xA70 && ch <= 0xA71)
        return true;
    if(ch == 0xA75)
        return true;
    if(ch >= 0xA81 && ch <= 0xA83)
        return true;
    if(ch == 0xABC)
        return true;
    if(ch >= 0xABE && ch <= 0xAC5)
        return true;
    if(ch >= 0xAC7 && ch <= 0xAC9)
        return true;
    if(ch >= 0xACB && ch <= 0xACD)
        return true;
    if(ch >= 0xAE2 && ch <= 0xAE3)
        return true;
    if(ch >= 0xB01 && ch <= 0xB03)
        return true;
    if(ch == 0xB3C)
        return true;
    if(ch >= 0xB3E && ch <= 0xB44)
        return true;
    if(ch >= 0xB47 && ch <= 0xB48)
        return true;
    if(ch >= 0xB4B && ch <= 0xB4D)
        return true;
    if(ch >= 0xB56 && ch <= 0xB57)
        return true;
    if(ch >= 0xB62 && ch <= 0xB63)
        return true;
    if(ch == 0xB82)
        return true;
    if(ch >= 0xBBE && ch <= 0xBC2)
        return true;
    if(ch >= 0xBC6 && ch <= 0xBC8)
        return true;
    if(ch >= 0xBCA && ch <= 0xBCD)
        return true;
    if(ch == 0xBD7)
        return true;
    if(ch >= 0xC00 && ch <= 0xC03)
        return true;
    if(ch >= 0xC3E && ch <= 0xC44)
        return true;
    if(ch >= 0xC46 && ch <= 0xC48)
        return true;
    if(ch >= 0xC4A && ch <= 0xC4D)
        return true;
    if(ch >= 0xC55 && ch <= 0xC56)
        return true;
    if(ch >= 0xC62 && ch <= 0xC63)
        return true;
    if(ch >= 0xC81 && ch <= 0xC83)
        return true;
    if(ch == 0xCBC)
        return true;
    if(ch >= 0xCBE && ch <= 0xCC4)
        return true;
    if(ch >= 0xCC6 && ch <= 0xCC8)
        return true;
    if(ch >= 0xCCA && ch <= 0xCCD)
        return true;
    if(ch >= 0xCD5 && ch <= 0xCD6)
        return true;
    if(ch >= 0xCE2 && ch <= 0xCE3)
        return true;
    if(ch >= 0xD01 && ch <= 0xD03)
        return true;
    if(ch >= 0xD3E && ch <= 0xD44)
        return true;
    if(ch >= 0xD46 && ch <= 0xD48)
        return true;
    if(ch >= 0xD4A && ch <= 0xD4D)
        return true;
    if(ch == 0xD57)
        return true;
    if(ch >= 0xD62 && ch <= 0xD63)
        return true;
    if(ch >= 0xD82 && ch <= 0xD83)
        return true;
    if(ch == 0xDCA)
        return true;
    if(ch >= 0xDCF && ch <= 0xDD4)
        return true;
    if(ch == 0xDD6)
        return true;
    if(ch >= 0xDD8 && ch <= 0xDDF)
        return true;
    if(ch >= 0xDF2 && ch <= 0xDF3)
        return true;
    if(ch == 0xE31)
        return true;
    if(ch >= 0xE34 && ch <= 0xE3A)
        return true;
    if(ch >= 0xE47 && ch <= 0xE4E)
        return true;
    if(ch == 0xEB1)
        return true;
    if(ch >= 0xEB4 && ch <= 0xEB9)
        return true;
    if(ch >= 0xEBB && ch <= 0xEBC)
        return true;
    if(ch >= 0xEC8 && ch <= 0xECD)
        return true;
    if(ch >= 0xF18 && ch <= 0xF19)
        return true;
    if(ch == 0xF35)
        return true;
    if(ch == 0xF37)
        return true;
    if(ch == 0xF39)
        return true;
    if(ch >= 0xF3E && ch <= 0xF3F)
        return true;
    if(ch >= 0xF71 && ch <= 0xF84)
        return true;
    if(ch >= 0xF86 && ch <= 0xF87)
        return true;
    if(ch >= 0xF8D && ch <= 0xF97)
        return true;
    if(ch >= 0xF99 && ch <= 0xFBC)
        return true;
    if(ch == 0xFC6)
        return true;
    if(ch >= 0x102B && ch <= 0x103E)
        return true;
    if(ch >= 0x1056 && ch <= 0x1059)
        return true;
    if(ch >= 0x105E && ch <= 0x1060)
        return true;
    if(ch >= 0x1062 && ch <= 0x1064)
        return true;
    if(ch >= 0x1067 && ch <= 0x106D)
        return true;
    if(ch >= 0x1071 && ch <= 0x1074)
        return true;
    if(ch >= 0x1082 && ch <= 0x108D)
        return true;
    if(ch == 0x108F)
        return true;
    if(ch >= 0x109A && ch <= 0x109D)
        return true;
    if(ch >= 0x135D && ch <= 0x135F)
        return true;
    if(ch >= 0x1712 && ch <= 0x1714)
        return true;
    if(ch >= 0x1732 && ch <= 0x1734)
        return true;
    if(ch >= 0x1752 && ch <= 0x1753)
        return true;
    if(ch >= 0x1772 && ch <= 0x1773)
        return true;
    if(ch >= 0x17B4 && ch <= 0x17D3)
        return true;
    if(ch == 0x17DD)
        return true;
    if(ch >= 0x180B && ch <= 0x180D)
        return true;
    if(ch == 0x18A9)
        return true;
    if(ch >= 0x1920 && ch <= 0x192B)
        return true;
    if(ch >= 0x1930 && ch <= 0x193B)
        return true;
    if(ch >= 0x19B0 && ch <= 0x19C0)
        return true;
    if(ch >= 0x19C8 && ch <= 0x19C9)
        return true;
    if(ch >= 0x1A17 && ch <= 0x1A1B)
        return true;
    if(ch >= 0x1A55 && ch <= 0x1A5E)
        return true;
    if(ch >= 0x1A60 && ch <= 0x1A7C)
        return true;
    if(ch == 0x1A7F)
        return true;
    if(ch >= 0x1AB0 && ch <= 0x1ABD)
        return true;
    if(ch >= 0x1B00 && ch <= 0x1B04)
        return true;
    if(ch >= 0x1B34 && ch <= 0x1B44)
        return true;
    if(ch >= 0x1B6B && ch <= 0x1B73)
        return true;
    if(ch >= 0x1B80 && ch <= 0x1B82)
        return true;
    if(ch >= 0x1BA1 && ch <= 0x1BAD)
        return true;
    if(ch >= 0x1BE6 && ch <= 0x1BF3)
        return true;
    if(ch >= 0x1C24 && ch <= 0x1C37)
        return true;
    if(ch >= 0x1CD0 && ch <= 0x1CD2)
        return true;
    if(ch >= 0x1CD4 && ch <= 0x1CE8)
        return true;
    if(ch == 0x1CED)
        return true;
    if(ch >= 0x1CF2 && ch <= 0x1CF4)
        return true;
    if(ch >= 0x1CF8 && ch <= 0x1CF9)
        return true;
    if(ch >= 0x1DC0 && ch <= 0x1DF5)
        return true;
    if(ch >= 0x1DFC && ch <= 0x1DFF)
        return true;
    if(ch >= 0x20D0 && ch <= 0x20DC)
        return true;
    if(ch == 0x20E1)
        return true;
    if(ch >= 0x20E5 && ch <= 0x20F0)
        return true;
    if(ch >= 0x2CEF && ch <= 0x2CF1)
        return true;
    if(ch == 0x2D7F)
        return true;
    if(ch >= 0x2DE0 && ch <= 0x2DFF)
        return true;
    if(ch >= 0x302A && ch <= 0x302F)
        return true;
    if(ch >= 0x3099 && ch <= 0x309A)
        return true;
    if(ch == 0xA66F)
        return true;
    if(ch >= 0xA674 && ch <= 0xA67D)
        return true;
    if(ch == 0xA69F)
        return true;
    if(ch >= 0xA6F0 && ch <= 0xA6F1)
        return true;
    if(ch == 0xA802)
        return true;
    if(ch == 0xA806)
        return true;
    if(ch == 0xA80B)
        return true;
    if(ch >= 0xA823 && ch <= 0xA827)
        return true;
    if(ch >= 0xA880 && ch <= 0xA881)
        return true;
    if(ch >= 0xA8B4 && ch <= 0xA8C4)
        return true;
    if(ch >= 0xA8E0 && ch <= 0xA8F1)
        return true;
    if(ch >= 0xA926 && ch <= 0xA92D)
        return true;
    if(ch >= 0xA947 && ch <= 0xA953)
        return true;
    if(ch >= 0xA980 && ch <= 0xA983)
        return true;
    if(ch >= 0xA9B3 && ch <= 0xA9C0)
        return true;
    if(ch == 0xA9E5)
        return true;
    if(ch >= 0xAA29 && ch <= 0xAA36)
        return true;
    if(ch == 0xAA43)
        return true;
    if(ch >= 0xAA4C && ch <= 0xAA4D)
        return true;
    if(ch >= 0xAA7B && ch <= 0xAA7D)
        return true;
    if(ch == 0xAAB0)
        return true;
    if(ch >= 0xAAB2 && ch <= 0xAAB4)
        return true;
    if(ch >= 0xAAB7 && ch <= 0xAAB8)
        return true;
    if(ch >= 0xAABE && ch <= 0xAABF)
        return true;
    if(ch == 0xAAC1)
        return true;
    if(ch >= 0xAAEB && ch <= 0xAAEF)
        return true;
    if(ch >= 0xAAF5 && ch <= 0xAAF6)
        return true;
    if(ch >= 0xABE3 && ch <= 0xABEA)
        return true;
    if(ch >= 0xABEC && ch <= 0xABED)
        return true;
    if(ch == 0xFB1E)
        return true;
    if(ch >= 0xFE00 && ch <= 0xFE0F)
        return true;
    if(ch >= 0xFE20 && ch <= 0xFE2D)
        return true;
    if(ch == 0x101FD)
        return true;
    if(ch == 0x102E0)
        return true;
    if(ch >= 0x10376 && ch <= 0x1037A)
        return true;
    if(ch >= 0x10A01 && ch <= 0x10A03)
        return true;
    if(ch >= 0x10A05 && ch <= 0x10A06)
        return true;
    if(ch >= 0x10A0C && ch <= 0x10A0F)
        return true;
    if(ch >= 0x10A38 && ch <= 0x10A3A)
        return true;
    if(ch == 0x10A3F)
        return true;
    if(ch >= 0x10AE5 && ch <= 0x10AE6)
        return true;
    if(ch >= 0x11000 && ch <= 0x11002)
        return true;
    if(ch >= 0x11038 && ch <= 0x11046)
        return true;
    if(ch >= 0x1107F && ch <= 0x11082)
        return true;
    if(ch >= 0x110B0 && ch <= 0x110BA)
        return true;
    if(ch >= 0x11100 && ch <= 0x11102)
        return true;
    if(ch >= 0x11127 && ch <= 0x11134)
        return true;
    if(ch == 0x11173)
        return true;
    if(ch >= 0x11180 && ch <= 0x11182)
        return true;
    if(ch >= 0x111B3 && ch <= 0x111C0)
        return true;
    if(ch >= 0x1122C && ch <= 0x11237)
        return true;
    if(ch >= 0x112DF && ch <= 0x112EA)
        return true;
    if(ch >= 0x11301 && ch <= 0x11303)
        return true;
    if(ch == 0x1133C)
        return true;
    if(ch >= 0x1133E && ch <= 0x11344)
        return true;
    if(ch >= 0x11347 && ch <= 0x11348)
        return true;
    if(ch >= 0x1134B && ch <= 0x1134D)
        return true;
    if(ch == 0x11357)
        return true;
    if(ch >= 0x11362 && ch <= 0x11363)
        return true;
    if(ch >= 0x11366 && ch <= 0x1136C)
        return true;
    if(ch >= 0x11370 && ch <= 0x11374)
        return true;
    if(ch >= 0x114B0 && ch <= 0x114C3)
        return true;
    if(ch >= 0x115AF && ch <= 0x115B5)
        return true;
    if(ch >= 0x115B8 && ch <= 0x115C0)
        return true;
    if(ch >= 0x11630 && ch <= 0x11640)
        return true;
    if(ch >= 0x116AB && ch <= 0x116B7)
        return true;
    if(ch >= 0x16AF0 && ch <= 0x16AF4)
        return true;
    if(ch >= 0x16B30 && ch <= 0x16B36)
        return true;
    if(ch >= 0x16F51 && ch <= 0x16F7E)
        return true;
    if(ch >= 0x16F8F && ch <= 0x16F92)
        return true;
    if(ch >= 0x1BC9D && ch <= 0x1BC9E)
        return true;
    if(ch >= 0x1D165 && ch <= 0x1D169)
        return true;
    if(ch >= 0x1D16D && ch <= 0x1D172)
        return true;
    if(ch >= 0x1D17B && ch <= 0x1D182)
        return true;
    if(ch >= 0x1D185 && ch <= 0x1D18B)
        return true;
    if(ch >= 0x1D1AA && ch <= 0x1D1AD)
        return true;
    if(ch >= 0x1D242 && ch <= 0x1D244)
        return true;
    if(ch >= 0x1E8D0 && ch <= 0x1E8D6)
        return true;
    if(ch >= 0xE0100 && ch <= 0xE01EF)
        return true;
    return false;
}

inline bool isCharacterCategoryNd(wint_t chIn)
{
    unsigned ch = (unsigned)chIn;
    if(chIn == WEOF)
        return false;
    if(ch >= 0x30 && ch <= 0x39)
        return true;
    if(ch >= 0x660 && ch <= 0x669)
        return true;
    if(ch >= 0x6F0 && ch <= 0x6F9)
        return true;
    if(ch >= 0x7C0 && ch <= 0x7C9)
        return true;
    if(ch >= 0x966 && ch <= 0x96F)
        return true;
    if(ch >= 0x9E6 && ch <= 0x9EF)
        return true;
    if(ch >= 0xA66 && ch <= 0xA6F)
        return true;
    if(ch >= 0xAE6 && ch <= 0xAEF)
        return true;
    if(ch >= 0xB66 && ch <= 0xB6F)
        return true;
    if(ch >= 0xBE6 && ch <= 0xBEF)
        return true;
    if(ch >= 0xC66 && ch <= 0xC6F)
        return true;
    if(ch >= 0xCE6 && ch <= 0xCEF)
        return true;
    if(ch >= 0xD66 && ch <= 0xD6F)
        return true;
    if(ch >= 0xDE6 && ch <= 0xDEF)
        return true;
    if(ch >= 0xE50 && ch <= 0xE59)
        return true;
    if(ch >= 0xED0 && ch <= 0xED9)
        return true;
    if(ch >= 0xF20 && ch <= 0xF29)
        return true;
    if(ch >= 0x1040 && ch <= 0x1049)
        return true;
    if(ch >= 0x1090 && ch <= 0x1099)
        return true;
    if(ch >= 0x17E0 && ch <= 0x17E9)
        return true;
    if(ch >= 0x1810 && ch <= 0x1819)
        return true;
    if(ch >= 0x1946 && ch <= 0x194F)
        return true;
    if(ch >= 0x19D0 && ch <= 0x19D9)
        return true;
    if(ch >= 0x1A80 && ch <= 0x1A89)
        return true;
    if(ch >= 0x1A90 && ch <= 0x1A99)
        return true;
    if(ch >= 0x1B50 && ch <= 0x1B59)
        return true;
    if(ch >= 0x1BB0 && ch <= 0x1BB9)
        return true;
    if(ch >= 0x1C40 && ch <= 0x1C49)
        return true;
    if(ch >= 0x1C50 && ch <= 0x1C59)
        return true;
    if(ch >= 0xA620 && ch <= 0xA629)
        return true;
    if(ch >= 0xA8D0 && ch <= 0xA8D9)
        return true;
    if(ch >= 0xA900 && ch <= 0xA909)
        return true;
    if(ch >= 0xA9D0 && ch <= 0xA9D9)
        return true;
    if(ch >= 0xA9F0 && ch <= 0xA9F9)
        return true;
    if(ch >= 0xAA50 && ch <= 0xAA59)
        return true;
    if(ch >= 0xABF0 && ch <= 0xABF9)
        return true;
    if(ch >= 0xFF10 && ch <= 0xFF19)
        return true;
    if(ch >= 0x104A0 && ch <= 0x104A9)
        return true;
    if(ch >= 0x11066 && ch <= 0x1106F)
        return true;
    if(ch >= 0x110F0 && ch <= 0x110F9)
        return true;
    if(ch >= 0x11136 && ch <= 0x1113F)
        return true;
    if(ch >= 0x111D0 && ch <= 0x111D9)
        return true;
    if(ch >= 0x112F0 && ch <= 0x112F9)
        return true;
    if(ch >= 0x114D0 && ch <= 0x114D9)
        return true;
    if(ch >= 0x11650 && ch <= 0x11659)
        return true;
    if(ch >= 0x116C0 && ch <= 0x116C9)
        return true;
    if(ch >= 0x118E0 && ch <= 0x118E9)
        return true;
    if(ch >= 0x16A60 && ch <= 0x16A69)
        return true;
    if(ch >= 0x16B50 && ch <= 0x16B59)
        return true;
    if(ch >= 0x1D7CE && ch <= 0x1D7FF)
        return true;
    return false;
}

inline bool isCharacterCategoryPc(wint_t chIn)
{
    unsigned ch = (unsigned)chIn;
    if(chIn == WEOF)
        return false;
    if(ch == 0x5F)
        return true;
    if(ch >= 0x203F && ch <= 0x2040)
        return true;
    if(ch == 0x2054)
        return true;
    if(ch >= 0xFE33 && ch <= 0xFE34)
        return true;
    if(ch >= 0xFE4D && ch <= 0xFE4F)
        return true;
    if(ch == 0xFF3F)
        return true;
    return false;
}

inline bool isWhiteSpace(wint_t ch)
{
    switch(ch)
    {
    case ' ':
    case '\v':
    case '\f':
    case '\t':
    case L'\u00A0':
    case L'\u1680':
    case L'\u2000':
    case L'\u2001':
    case L'\u2002':
    case L'\u2003':
    case L'\u2004':
    case L'\u2005':
    case L'\u2006':
    case L'\u2007':
    case L'\u2008':
    case L'\u2009':
    case L'\u200A':
    case L'\u202F':
    case L'\u205F':
    case L'\u3000':
    case L'\uFEFF':
        return true;
    default:
        return false;
    }
}

inline bool isLineTerminator(wint_t ch)
{
    switch(ch)
    {
    case '\n':
    case '\r':
    case L'\u2028':
    case L'\u2029':
        return true;
    default:
        return false;
    }
}

inline bool isUnicodeLetter(wint_t ch)
{
    return isCharacterCategoryLuLlLtLmLoNl(ch);
}

inline bool isUnicodeCombiningMark(wint_t ch)
{
    return isCharacterCategoryMnMc(ch);
}

inline bool isUnicodeDigit(wint_t ch)
{
    return isCharacterCategoryNd(ch);
}

inline bool isUnicodeConnectorPunctuation(wint_t ch)
{
    return isCharacterCategoryPc(ch);
}

inline bool isHexDigit(wint_t ch)
{
    if(ch >= '0' && ch <= '9')
        return true;
    if(ch >= 'A' && ch <= 'F')
        return true;
    if(ch >= 'a' && ch <= 'f')
        return true;
    return false;
}

inline unsigned getDigitValue(wint_t ch)
{
    if(ch >= '0' && ch <= '9')
        return (unsigned)ch - (unsigned)'0';
    if(ch >= 'A' && ch <= 'Z')
        return (unsigned)ch - (unsigned)'A' + 0xA;
    else
        return (unsigned)ch - (unsigned)'a' + 0xA;
}

inline wchar_t getDigitCharacter(unsigned v)
{
    if(v < 10)
        return L'0' + v;
    v -= 10;
    return L'A' + v;
}

inline bool isNonEscapeIdentifierStart(wint_t ch)
{
    return ch == '$' || ch == '_' || isUnicodeLetter(ch);
}

inline bool isNonEscapeIdentifierPart(wint_t ch)
{
    return ch == L'\u200C' || ch == L'\u200D' || isNonEscapeIdentifierStart(ch) || isUnicodeDigit(ch) || isUnicodeCombiningMark(ch) || isUnicodeConnectorPunctuation(ch);
}

inline bool isDecimalDigit(wint_t ch)
{
    return (ch >= '0' && ch <= '9');
}

inline bool isNonZeroDigit(wint_t ch)
{
    return (ch > '0' && ch <= '9');
}

inline bool isEscapeCharacter(wint_t ch)
{
    if(isDecimalDigit(ch))
        return true;
    switch(ch)
    {
    case '\'':
    case '\"':
    case '\\':
    case 'b':
    case 'f':
    case 'n':
    case 'r':
    case 't':
    case 'v':
    case 'u':
    case 'x':
        return true;
    default:
        return false;
    }
}

inline bool isNonEscapeCharacter(wint_t ch)
{
    if(ch == WEOF || isEscapeCharacter(ch))
        return false;
    return true;
}

inline bool isStrWhiteSpace(wint_t ch)
{
    return isWhiteSpace(ch) || isLineTerminator(ch);
}

#endif // UNICODE_CATEGORY_H_INCLUDED
