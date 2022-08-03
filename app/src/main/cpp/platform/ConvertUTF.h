//
// Created by windy on 2022/8/3.
//

#ifndef ANDROIDNATIVEOPENGLES_CONVERTUTF_H
#define ANDROIDNATIVEOPENGLES_CONVERTUTF_H


#include <stddef.h>   /* ptrdiff_t */

/* ---------------------------------------------------------------------
    The following 4 definitions are compiler-specific.
    The C standard does not guarantee that wchar_t has at least
    16 bits, so wchar_t is no less portable than unsigned short!
    All should be unsigned values to avoid sign extension during
    bit mask & shift operations.
------------------------------------------------------------------------ */

typedef unsigned int UTF32;  /* at least 32 bits */
typedef unsigned short UTF16;  /* at least 16 bits */
typedef unsigned char UTF8;   /* typically 8 bits */
typedef unsigned char Boolean; /* 0 or 1 */

/* Some fundamental constants */
#define UNI_REPLACEMENT_CHAR (UTF32)0x0000FFFD
#define UNI_MAX_BMP (UTF32)0x0000FFFF
#define UNI_MAX_UTF16 (UTF32)0x0010FFFF
#define UNI_MAX_UTF32 (UTF32)0x7FFFFFFF
#define UNI_MAX_LEGAL_UTF32 (UTF32)0x0010FFFF

#define UNI_MAX_UTF8_BYTES_PER_CODE_POINT 4

#define UNI_UTF16_BYTE_ORDER_MARK_NATIVE  0xFEFF
#define UNI_UTF16_BYTE_ORDER_MARK_SWAPPED 0xFFFE

typedef enum {
    conversionOK,           /* conversion successful */
    sourceExhausted,        /* partial character in source, but hit end */
    targetExhausted,        /* insuff. room in target for conversion */
    sourceIllegal           /* source sequence is illegal/malformed */
} ConversionResult;

typedef enum {
    strictConversion = 0,
    lenientConversion
} ConversionFlags;

/* This is for C++ and does no harm in C */
#ifdef __cplusplus
extern "C" {
#endif

ConversionResult ConvertUTF8toUTF16(
        const UTF8 **sourceStart, const UTF8 *sourceEnd,
        UTF16 **targetStart, UTF16 *targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF8toUTF32(
        const UTF8 **sourceStart, const UTF8 *sourceEnd,
        UTF32 **targetStart, UTF32 *targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF16toUTF8(
        const UTF16 **sourceStart, const UTF16 *sourceEnd,
        UTF8 **targetStart, UTF8 *targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF32toUTF8(
        const UTF32 **sourceStart, const UTF32 *sourceEnd,
        UTF8 **targetStart, UTF8 *targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF16toUTF32(
        const UTF16 **sourceStart, const UTF16 *sourceEnd,
        UTF32 **targetStart, UTF32 *targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF32toUTF16(
        const UTF32 **sourceStart, const UTF32 *sourceEnd,
        UTF16 **targetStart, UTF16 *targetEnd, ConversionFlags flags);

Boolean isLegalUTF8Sequence(const UTF8 *source, const UTF8 *sourceEnd);

Boolean isLegalUTF8String(const UTF8 **source, const UTF8 *sourceEnd);

unsigned getNumBytesForUTF8(UTF8 firstByte);

int getUTF8StringLength(const UTF8 *utf8);

#ifdef __cplusplus
}

/*************************************************************************/
/* Below are LLVM-specific wrappers of the functions above. */

//#include "llvm/ADT/ArrayRef.h"
//#include "llvm/ADT/StringRef.h"

#include <vector>
#include <string>

namespace llvm {

/**
 * Convert an UTF8 StringRef to UTF8, UTF16, or UTF32 depending on
 * WideCharWidth. The converted data is written to ResultPtr, which needs to
 * point to at least WideCharWidth * (Source.Size() + 1) bytes. On success,
 * ResultPtr will point one after the end of the copied string. On failure,
 * ResultPtr will not be changed, and ErrorPtr will be set to the location of
 * the first character which could not be converted.
 * \return true on success.
 */
bool ConvertUTF8toWide(unsigned WideCharWidth, const std::string& Source,
                       char *&ResultPtr, const UTF8 *&ErrorPtr);

/**
 * Convert an Unicode code point to UTF8 sequence.
 *
 * \param Source a Unicode code point.
 * \param [in,out] ResultPtr pointer to the output buffer, needs to be at least
 * \c UNI_MAX_UTF8_BYTES_PER_CODE_POINT bytes.  On success \c ResultPtr is
 * updated one past end of the converted sequence.
 *
 * \returns true on success.
 */
bool ConvertCodePointToUTF8(unsigned Source, char *&ResultPtr);

/**
 * Convert the first UTF8 sequence in the given source buffer to a UTF32
 * code point.
 *
 * \param [in,out] source A pointer to the source buffer. If the conversion
 * succeeds, this pointer will be updated to point to the byte just past the
 * end of the converted sequence.
 * \param sourceEnd A pointer just past the end of the source buffer.
 * \param [out] target The converted code
 * \param flags Whether the conversion is strict or lenient.
 *
 * \returns conversionOK on success
 *
 * \sa ConvertUTF8toUTF32
 */
static inline ConversionResult convertUTF8Sequence(const UTF8 **source,
                                                   const UTF8 *sourceEnd,
                                                   UTF32 *target,
                                                   ConversionFlags flags) {
  if (*source == sourceEnd)
    return sourceExhausted;
  unsigned size = getNumBytesForUTF8(**source);
  if ((ptrdiff_t)size > sourceEnd - *source)
    return sourceExhausted;
  return ConvertUTF8toUTF32(source, *source + size, &target, target + 1, flags);
}

/**
 * Returns true if a blob of text starts with a UTF-16 big or little endian byte
 * order mark.
 */
bool hasUTF16ByteOrderMark(const char* SrcBytes, size_t len);

/**
 * Converts a stream of raw bytes assumed to be UTF16 into a UTF8 std::string.
 *
 * \param [in] SrcBytes A buffer of what is assumed to be UTF-16 encoded text.
 * \param [out] Out Converted UTF-8 is stored here on success.
 * \returns true on success
 */
bool convertUTF16ToUTF8String(const std::u16string& utf16, std::string &Out);

} /* end namespace llvm */

#endif

#endif //ANDROIDNATIVEOPENGLES_CONVERTUTF_H
