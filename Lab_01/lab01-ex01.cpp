#include <fstream>
#include <iostream>

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
};

void toUppaerCase(char &c) {
    if ('a' <= c && c <= 'z') {
        c += 'A' - 'a';
    }
}

int main(int argc, char const *argv[]) {
    int key = 13;
    char c;

    Cesar crypt{key};

    std::ifstream fin{"lab01-ex01-in.txt"};
    std::ofstream fout{"lab01-ex01-cryped.txt"};
    while (!fin.eof()) {
        fin >> std::noskipws >> c;
        toUppaerCase(c);
        fout << crypt.encrypt(c);
    }
    fin.close();
    fout.close();

    fin.open("lab01-ex01-cryped.txt");
    fout.open("lab01-ex01-out.txt");
    while (!fin.eof()) {
        fin >> std::noskipws >> c;
        toUppaerCase(c);
        fout << crypt.decrypt(c);
    }
    fin.close();
    fout.close();

    return 0;
}
