#include <fstream>
#include <iostream>

class CesarBin {
  protected:
    int key;

  public:
    CesarBin(int key) : key(key) {}

    char encrypt(char &c) { return c = (*((unsigned char *)&c)) + key; }
    char decrypt(char &c) { return c = (*((unsigned char *)&c)) - key; }
};

void toUppaerCase(char &c) {
    if ('a' <= c && c <= 'z') {
        c += 'A' - 'a';
    }
}

int main(int argc, char const *argv[]) {
    int key = 98;
    char c;

    CesarBin crypt{key};

    std::ifstream fin{"lab01-ex02-in.flv"};
    if (!fin.is_open()) {
        exit(1);
    }
    std::ofstream fout{"lab01-ex02-crypted.flv"};
    if (!fout.is_open()) {
        exit(1);
    }
    while (!fin.eof()) {
        fin.read(&c, 1);
        if (fin.gcount() == 0) {
            break;
        }
        crypt.encrypt(c);
        fout.write(&c, 1);
        crypt.decrypt(c);
    }
    fin.close();
    fout.close();

    fin.open("lab01-ex02-crypted.flv");
    if (!fin.is_open()) {
        exit(1);
    }
    fout.open("lab01-ex02-out.flv");
    if (!fout.is_open()) {
        exit(1);
    }
    while (!fin.eof()) {
        fin.read(&c, 1);
        if (fin.gcount() == 0) {
            break;
        }
        crypt.decrypt(c);
        fout.write(&c, 1);
    }
    fin.close();
    fout.close();

    return 0;
}
