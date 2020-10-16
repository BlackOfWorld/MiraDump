#include "SignatureInfo.h"

std::string Trim(const char* signatureString) {
    char *newString = new char[strlen(signatureString) + 2];
    int numBlank = 0;
    int j = 0;
    for (int i = 0; i < strlen(signatureString); i++) {
        if (*(signatureString + i) != ' ') {
            newString[j] = *(signatureString + i);
            ++j;
        } else {
            ++numBlank;
        }
    }
    newString[strlen(signatureString) - numBlank] = '\0';
    return static_cast<std::string>(newString);
}

SignatureInfo::SignatureInfo(std::string& name, const std::string& signatureString, std::string& module, const int& offset, const int& extra)
        : name(name), module(module), offset(offset), extra(extra)
{
    this->signatureString = Trim(signatureString.c_str());
    if (signatureString.find("xx") != std::string::npos) {
        this->signature = this->SigParserXX();
    } else if (signatureString.find('?') != std::string::npos) {
        this->signature = this->SigParserQuestion();
    }
}

std::vector<int> SignatureInfo::SigParserXX() const
{
    int i = 0;
    int sigSize = this->signatureString.size();
    std::vector<int> result{};
    result.reserve(45);
    while (sigSize > i) {
        std::string byte = this->signatureString.substr(i, 2);
        if (byte == "xx") {
            result.push_back(-1);
        } else if ( byte.size() == 2) {
            result.push_back(std::stoi(byte, 0, 16));
        } else {
            return std::vector<int>{};
        }
        i += 2;
    }
    return result;
}

std::vector<int> SignatureInfo::SigParserQuestion() const
{
    int i = 0;
    int sigSize = this->signatureString.size();
    std::vector<int> result{};
    while (sigSize > i) {
        std::string byte = this->signatureString.substr(i, 1);
        if (byte == "?") {
            result.push_back(-1);
            i += 1;
        } else {
            result.push_back(std::stoi(this->signatureString.substr(i, 2), 0, 16));
            i += 2;
        }
    }
    return result;
}