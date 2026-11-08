#include "TextProcessor.h"
#include <fstream>
#include <sstream>
#include <vector>

static int countWords(const std::string& sentence) {
    std::istringstream iss(sentence);
    std::string word;
    int count = 0;
    while (iss >> word) {
        ++count;
    }
    return count;
}

int TextProcessor::printSentencesWithWordCount(const std::string& filename, int wordsCount) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл '" << filename << "'\n";
        return -1;
    }

    std::string fullText((std::istreambuf_iterator<char>(file)),
                          std::istreambuf_iterator<char>());
    file.close();

    if (fullText.empty()) {
        std::cout << "Файл пуст.\n";
        return 0;
    }

    std::vector<std::string> sentences;
    std::string current;

    for (size_t i = 0; i < fullText.size(); ++i) {
        char c = fullText[i];
        current += c;
        
        if (c == '.' || c == '!' || c == '?') {
            while (i + 1 < fullText.size() && 
                  (fullText[i+1] == '.' || fullText[i+1] == '!' || fullText[i+1] == '?')) {
                ++i;
                current += fullText[i];
            }
           
            size_t first = current.find_first_not_of(" \t\n\r");
            if (first != std::string::npos) {
                size_t last = current.find_last_not_of(" \t\n\r");
                sentences.push_back(current.substr(first, last - first + 1));
            }
            current.clear();
        }
    }

    size_t first = current.find_first_not_of(" \t\n\r");
    if (first != std::string::npos) {
        sentences.push_back(current.substr(first));
    }

    int found = 0;
    for (size_t i = 0; i < sentences.size(); ++i) {
        if (countWords(sentences[i]) == wordsCount) {
            std::cout << "[" << (i + 1) << "] " << sentences[i] << "\n";
            ++found;
        }
    }

    return found;
}