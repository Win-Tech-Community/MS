#ifndef __DESCRYPT_H__
#define __DESCRYPT_H__

#ifdef __cplusplus
extern "C" {
#endif

#define ENCRYPT   0
#define DECRYPT   1

#ifndef DECR_KEY
#define DECR_KEY  0
#define ENCR_KEY  1
#define ENCR_STD  2
#define ENCR_SES  4
#endif

#define CRYPT_ERR 1
#define CRYPT_OK  0

unsigned FAR __cdecl
DES_CBC(    unsigned            Option,
            const char FAR *    Key,
            unsigned char FAR * IV,
            unsigned char FAR * Source,
            unsigned char FAR * Dest,
            unsigned            Size);


unsigned FAR __cdecl
DES_CBC_LM( unsigned            Option,
            const char FAR *    Key,
            unsigned char FAR * IV,
            unsigned char FAR * Source,
            unsigned char FAR * Dest,
            unsigned            Size);

unsigned FAR __cdecl
DES_ECB(    unsigned            Option,
            const char FAR *    Key,
            unsigned char FAR * Src,
            unsigned char FAR * Dst);

unsigned FAR __cdecl
DES_ECB_LM( unsigned            Option,
            const char FAR *    Key,
            unsigned char FAR * Src,
            unsigned char FAR * Dst);

#ifdef __cplusplus
}
#endif

#endif // __DESCRYPT_H__

