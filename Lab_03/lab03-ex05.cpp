#include <fstream>
#include <iostream>
#include <random>
#include <string>
/// NTL
#include <NTL/mat_ZZ.h>
#include <NTL/matrix.h>

template <int mod = 256>
uint8_t generateRandomNumber();

class Hill {
  private:
    const int mod = 256;

  protected:
    NTL::Mat<NTL::ZZ> mKey, mInvKey;
    size_t mN;

    NTL::Mat<NTL::ZZ> toMat(const char *const buf) {
        NTL::Mat<NTL::ZZ> res;
        res.SetDims(mN, 1);
        for (size_t i = 0; i < mN; ++i) {
            res[i][0] = NTL::to_ZZ(static_cast<uint8_t>(buf[i]));
        }

        return res;
    }

    const char *const toBuf(const NTL::Mat<NTL::ZZ> mat, char *const buf) {
        for (size_t i = 0; i < mN; ++i) {
            buf[i] = static_cast<char>(NTL::to_int(mat[i][0]));
        }

        return buf;
    }

  public:
    Hill(size_t blockSize) {
        setBlockSize(blockSize);
    }

    void setBlockSize(size_t blockSize) {
        mN = blockSize;
        mKey.SetDims(mN, mN);
        mInvKey.SetDims(mN, mN);
        generateKey();
    }

    void generateKey() {
        NTL::Mat<NTL::ZZ> adjKey;
        NTL::ZZ d;
        size_t i, j, n = mKey.NumRows();
        adjKey.SetDims(n, n);

        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                mKey[i][j] = NTL::to_ZZ(generateRandomNumber() % mod);
            }
        }

        while (true) {
            NTL::inv(d, adjKey, mKey, 0);
            d = d % mod;
            if (d < 0) {
                d += mod;
            }

            if (GCD(d, NTL::to_ZZ(mod)) != NTL::to_ZZ(1)) {
                i = generateRandomNumber() % n;
                j = generateRandomNumber() % n;
                mKey[i][j] = NTL::to_ZZ(generateRandomNumber() % mod);
            } else
                break;
        }

        NTL::ZZ idet = NTL::InvMod(d, NTL::to_ZZ(mod));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                mInvKey[i][j] = (adjKey[i][j] * idet) % mod;
    }

    NTL::Mat<NTL::ZZ> getKey() { return mKey; }
    NTL::Mat<NTL::ZZ> getInvKey() { return mInvKey; }

    void encrypt(std::string inputFileName, std::string outputFileName) {

        std::ifstream fin{inputFileName, std::ios::binary};
        std::ofstream fout{outputFileName, std::ios::binary};

        if (!fin.is_open() || !fout.is_open()) {
            exit(1);
        }

        char *buf = new char[mN];
        bool finished = false;
        while (!fin.eof()) {
            fin.read(buf, mN);
            if (fin.gcount() < mN) {
                int temp = mN - fin.gcount();
                for (size_t i = fin.gcount(); i < mN; ++i) {
                    buf[i] = temp;
                }

                finished = true;
            }

            NTL::Mat<NTL::ZZ> temp;
            NTL::mul(temp, mKey, toMat(buf));
            for (size_t i = 0; i < mN; ++i) {
                temp[i][0] = temp[i][0] % mod;
            }
            toBuf(temp, buf);

            fout.write(buf, mN);

            if (finished) {
                break;
            }
        }
        delete[] buf;
        fin.close();
        fout.close();
    }

    void decrypt(std::string inputFileName, std::string outputFileName) {

        std::ifstream fin{inputFileName, std::ios::binary};
        std::ofstream fout{outputFileName, std::ios::binary};

        if (!fin.is_open() || !fout.is_open()) {
            exit(1);
        }

        char *buf = new char[mN];
        size_t n = mN;
        while (!fin.eof()) {
            fin.read(buf, mN);
            if (fin.gcount() < mN) {
                break;
            }

            NTL::Mat<NTL::ZZ> temp;
            NTL::mul(temp, mInvKey, toMat(buf));
            for (size_t i = 0; i < mN; ++i) {
                temp[i][0] = temp[i][0] % mod;
            }
            toBuf(temp, buf);

            fin.peek();
            if (fin.eof()) {
                uint8_t temp = buf[mN - 1];
                if (temp <= mN) {
                    n = mN - temp;
                }
            }

            fout.write(buf, n);
        }
        delete[] buf;
        fin.close();
        fout.close();
    }

    void printKey(std::ostream &os = std::cout) {
        for (int i = 0; i < mKey.NumRows(); ++i) {
            for (int j = 0; j < mKey.NumCols(); ++j) {
                std::cout << " " << mKey[i][j];
            }
            std::cout << std::endl;
        }
    }

    void printInvKey(std::ostream &os = std::cout) {
        for (int i = 0; i < mInvKey.NumRows(); ++i) {
            for (int j = 0; j < mInvKey.NumCols(); ++j) {
                std::cout << " " << mInvKey[i][j];
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    Hill hill{5};

    hill.setBlockSize(56);

    hill.encrypt("lab03-ex05-in.txt", "lab03-ex05-crypted.txt");
    hill.decrypt("lab03-ex05-crypted.txt", "lab03-ex05-out.txt");

    return 0;
}

template <int mod = 256>
uint8_t generateRandomNumber() {
    // First create an instance of an engine.
    static std::random_device rnd_device;
    // Specify the engine and distribution.
    static std::mt19937 mersenne_engine{rnd_device()}; // Generates random integers
    static std::uniform_int_distribution<int> dist{0, mod};

    return dist(mersenne_engine);
}