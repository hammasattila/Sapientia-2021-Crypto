#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class OpenTextAttacker {
  protected:
    std::string openText;
    std::vector<char> table;
    std::istringstream iss;

  public:
    OpenTextAttacker(std::string plainText) : openText(plainText), table(26), iss(openText) {}

    bool attack(std::string word) {
        std::string openWord;

        iss >> openWord;
        if (openWord.length() == word.length()) {
            for (size_t i = 0; i < openWord.length(); ++i) {
                if (table[word[i] - 'A'] && table[word[i] - 'A'] != openWord[i]) {
                    break;
                }

                table[word[i] - 'A'] = openWord[i];
            }

            for (auto &&it : table) {
                if (!it) {
                    return false;
                }
            }

            return true;
        }

        reset();

        return false;
    }

    void reset() {
        iss.str(openText);
        for (auto &&it : table) {
            it = 0;
        }
    }

    void print(std::ostream &os = std::cout) {
        auto border = [](std::ostream &os) {
            for (size_t i = 0; i < 26 * 2 + 1; ++i) {
                os << "-";
            }
            os << std::endl;
        };

        border(os);
        for (char c = 'A'; c <= 'Z'; ++c) {
            os << "|" << c;
        }
        os << "|" << std::endl;
        border(os);
        for (auto &&it : table) {
            os << "|" << (it ? it : '0');
        }
        os << "|" << std::endl;
        border(os);
    }

    std::string &decrypt(std::string &s) {
        for (auto &&it : s) {
            it = ('A' <= it && it <= 'Z') ? table[it - 'A'] : it;
        }

        return s;
    }

    static std::string &toUpper(std::string &s) {
        for (auto &&it : s) {
            if ('a' <= it && it <= 'z') {
                it += 'A' - 'a';
            }
        }

        return s;
    }
};

int main(int argc, char const *argv[]) {

    std::ifstream fin{"lab01-ex06-in.txt"};
    size_t numberOfTest = 0;

    fin >> numberOfTest;
    fin.getline(nullptr, 0);

    for (size_t i = 0; i < numberOfTest; ++i) {
        bool solved = false;
        std::cout << i << std::endl;
        std::string text;
        std::string line;
        do {
            line.clear();
            getline(fin, line);
            std::cout << line << std::endl;
            text.append(line);
            text.append("\n");
        } while (line.length());

        OpenTextAttacker::toUpper(text);

        std::istringstream iss(text);
        std::string word;
        while (!solved && !iss.eof()) {
            getline(iss, line);
            OpenTextAttacker opa{"THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG"};
            std::istringstream liss(line);
            while (!solved && !liss.eof()) {
                liss >> word;
                if (opa.attack(word)) {
                    solved = true;
                    opa.print(std::cout);
                    std::cout << opa.decrypt(text) << std::endl;
                }
            }
        }

        if (!solved) {
            std::cout << "NO SOLUTION" << std::endl;
        }
    }

    fin.close();

    return 0;
}
