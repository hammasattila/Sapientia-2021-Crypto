#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Cesar {
  protected:
    int key;
    const size_t begin = 'A';
    const size_t end = 'Z';
    const size_t set_size = end - begin + 1;

  public:
    Cesar(int key) : key(key) {}

    char encrypt(char &c) { return c = (begin <= c && c <= end) ? ((c - begin + key + set_size) % set_size) + begin : c; }
    char decrypt(char &c) { return c = (begin <= c && c <= end) ? ((c - begin - key + set_size) % set_size) + begin : c; }
    void setKey(int key) { this->key = key; }
};

void toUppaerCase(char &c) {
    if ('a' <= c && c <= 'z') {
        c += 'A' - 'a';
    }
}

int main(int argc, char const *argv[]) {
    int key = 7;
    char c;

    const char inputPath[] = "lab01-ex04-crypted.txt", outputPath[] = "lab01-ex04-out.txt";

    for (size_t key = 0; key < 25; ++key) {
        Cesar crypt{key};
        std::ifstream fin{inputPath};
        if (!fin.is_open()) {
            exit(1);
        }
        std::ofstream fout{outputPath, std::ofstream::out | std::ofstream::app};
        if (!fout.is_open()) {
            exit(1);
        }
        while (true) {
            fin >> std::noskipws >> c;
            if (fin.eof()) {
                break;
            }
            toUppaerCase(c);
            fout << crypt.decrypt(c);
        }
        fin.close();
        fout.close();
    }

    return 0;
}
