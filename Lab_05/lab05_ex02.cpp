#define CRYPTOPP_DEFAULT_NO_DLL

#include "crypto++/blowfish.h"
#include "crypto++/dll.h"

void Blowfish_Encrypt(CryptoPP::SecByteBlock hexKey, CryptoPP::SecByteBlock hexIV, const char *infile, const char *outfile);
void Blowfish_Decrypt(CryptoPP::SecByteBlock hexKey, CryptoPP::SecByteBlock hexIV, const char *infile, const char *outfile);

int main() {
    // Generate a random key
    CryptoPP::AutoSeededRandomPool rnd;
    CryptoPP::SecByteBlock key(0x00, CryptoPP::Blowfish::DEFAULT_KEYLENGTH);
    rnd.GenerateBlock(key, key.size());
    // Generate a random IV
    CryptoPP::SecByteBlock iv(0x00, CryptoPP::Blowfish::BLOCKSIZE);
    rnd.GenerateBlock(iv, CryptoPP::Blowfish::BLOCKSIZE);

    Blowfish_Encrypt(key, iv, "lab05-ex02-in.txt", "lab05-ex02-crypted.txt");

    Blowfish_Decrypt(key, iv, "lab05-ex02-crypted.txt", "lab05-ex02-out.txt");

    return 0;
}

void Blowfish_Encrypt(CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv, const char *infile, const char *outfile) {
    CryptoPP::CBC_Mode<CryptoPP::Blowfish>::Encryption bf(key, key.size(), iv);
    CryptoPP::FileSource(infile, true, new CryptoPP::StreamTransformationFilter(bf, new CryptoPP::FileSink(outfile)));
}

void Blowfish_Decrypt(CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv, const char *infile, const char *outfile) {
    CryptoPP::CBC_Mode<CryptoPP::Blowfish>::Decryption bf(key, key.size(), iv);
    CryptoPP::FileSource(infile, true, new CryptoPP::StreamTransformationFilter(bf, new CryptoPP::FileSink(outfile)));
}