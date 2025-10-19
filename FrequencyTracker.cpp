#include "FrequencyTracker.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

namespace {
// Convert to lowercase for case-insensitive counting/search.
std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return s;
}
} // namespace

FrequencyTracker::FrequencyTracker(const std::string& t_inputPath,
                                   const std::string& t_backupPath)
    : m_inputPath(t_inputPath), m_backupPath(t_backupPath) {}

bool FrequencyTracker::load() {
    std::ifstream in(m_inputPath);
    if (!in.is_open()) {
        std::cerr << "Error: could not open input file: " << m_inputPath << "\n";
        return false;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back(); // handle CRLF
        if (line.empty()) continue;

        // Per spec, each line is one word. Normalize to lowercase.
        ++m_freq[toLower(line)];
    }
    in.close();
    return true;
}

bool FrequencyTracker::writeBackup() const {
    std::ofstream out(m_backupPath);
    if (!out.is_open()) {
        std::cerr << "Error: could not write backup file: " << m_backupPath << "\n";
        return false;
    }
    for (const auto& kv : m_freq) {
        out << kv.first << ' ' << kv.second << '\n';
    }
    out.close();
    return true;
}

int FrequencyTracker::countOf(const std::string& t_item) const {
    const auto it = m_freq.find(toLower(t_item));
    return (it == m_freq.end()) ? 0 : it->second;
}

void FrequencyTracker::printAll(std::ostream& os) const {
    for (const auto& kv : m_freq) {
        os << kv.first << ' ' << kv.second << '\n';
    }
}

void FrequencyTracker::printHistogram(std::ostream& os, char symbol) const {
    // Simple ANSI colors for a bit of visual flair. Safe to remove if needed.
    static const std::string colors[] = {
        "\033[31m", "\033[32m", "\033[33m",
        "\033[34m", "\033[35m", "\033[36m"
    };
    static const std::string reset = "\033[0m";

    int idx = 0;
    for (const auto& kv : m_freq) {
        os << kv.first << ' ';
        const std::string& color = colors[idx % 6];
        for (int i = 0; i < kv.second; ++i) {
            os << color << symbol << reset;
        }
        os << '\n';
        ++idx;
    }
}