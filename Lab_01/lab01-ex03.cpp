#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class KeywordCesar {
  private:
    char _encrypt(char &c) { return c = (begin <= c && c <= end) ? table[(c - begin + key) % set_size] : c; }
    char _decrypt(char &c) {
        if (begin <= c && c <= end) {
            c = std::find(table.begin(), table.end(), c) - table.begin();
            c -= key;
            while (c < 0) {
                c += set_size;
            }
            c += begin;
        }

        return c;
    }

    void _toUppaerCase(char &c) {
        if ('a' <= c && c <= 'z') {
            c += 'A' - 'a';
        }
    }

  protected:
    int key;
    std::string pswd;
    std::vector<char> table;

    const size_t begin = 'A';
    const size_t end = 'Z';
    const size_t set_size = end - begin + 1;

  public:
    KeywordCesar(int key, std::string pswd) : key(key), pswd(pswd) {
        for (const char c : pswd) {
            if (std::find(table.begin(), table.end(), c) == table.end()) {
                table.push_back(c);
            }
        }
        for (char c = begin; c <= end; ++c) {
            if (std::find(table.begin(), table.end(), c) == table.end()) {
                table.push_back(c);
            }
        }
    }

    char encrypt(char &c) {
        _toUppaerCase(c);
        return _encrypt(c);
    }
    char decrypt(char &c) {
        _toUppaerCase(c);
        return _decrypt(c);
    }
};

int main(int argc, char const *argv[]) {
    int key = 7;
    char c;

    const char inputPath[] = "lab01-ex03-in.txt", cryptedPath[] = "lab01-ex03-crypted.txt", outputPath[] = "lab01-ex03-out.txt";

    KeywordCesar crypt{key, "PASWD"};

    std::ifstream fin{inputPath};
    if (!fin.is_open()) {
        exit(1);
    }
    std::ofstream fout{cryptedPath};
    if (!fout.is_open()) {
        exit(1);
    }
    while (true) {
        fin >> std::noskipws >> c;
        if (fin.eof()) {
            break;
        }
        fout << crypt.encrypt(c);
    }
    std::cout << "Hello" << std::endl;
    fin.close();
    fout.close();

    fin.open(cryptedPath);
    if (!fin.is_open()) {
        exit(1);
    }
    fout.open(outputPath);
    if (!fout.is_open()) {
        exit(1);
    }
    while (true) {
        fin >> std::noskipws >> c;
        if (fin.eof()) {
            break;
        }
        std::cout << c << " ";
        crypt.decrypt(c);
        std::cout << c << std::endl;
        fout << c;
    }
    fin.close();
    fout.close();

    return 0;
}
