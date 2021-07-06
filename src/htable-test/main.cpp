/*!
    \file       main.cpp
    \brief      Client source file

    \note       The Cherno YouTube channel:
                "I did a C++ University Assignment" video

    \author     Gem Aludino
    \date       6 Jul 2021
 */

#include <iostream>
#include <sstream>
#include <array>
#include <iterator>

class HashTable {
public:
    struct Entry {
        std::string data = "";
        std::string status = "never used";

        std::ostream &print_debug(std::ostream &os = std::cout) const {
            os << "'" << data << "' : [" << status << "]";
            return os;
        }

        friend std::ostream &operator<<(std::ostream &os, const Entry &e) {
            os << e.data; 
            return os;
        }
    };

    static const int size = 26;

    HashTable() = default;

    void insert(const std::string &key) {
        auto index = -1;
        if (!find(key, &index)) { return; }
    
        m_entries[index].data = key;
        m_entries[index].status = "occupied";
    }

    void erase(const std::string &key) {
        auto index = -1;
        if (!find(key, &index)) { return; }
        
        m_entries[index].data.clear();
        m_entries[index].status = "tombstone";
    }

    friend std::ostream &operator<<(std::ostream &os, const HashTable &h) {
        // Only output Entry e in m_entries such that e.status == "occupied"
        std::copy_if(h.m_entries.begin(), 
                     h.m_entries.end(),
                     std::ostream_iterator<Entry>(os, " "),
                     [](const Entry &e) -> bool {
                        return e.status == "occupied";
                     });
        return os;
    }

    std::ostream &print_debug(std::ostream &os = std::cout) const {
        std::for_each(m_entries.begin(), 
                      m_entries.end(),
                     [](const auto &entry) { 
                        entry.print_debug() << '\n'; 
                     });
        return os;
    }
private:
    int hash(const std::string &key) {
        // precondition: key.back() is [a, z]
        return key.back() - 'a';
    }

    bool find(const std::string &key, int *out_index = nullptr) {
        for (auto index = hash(key);
             index < size;
             index = (index + 1) % size) {
            // return true if a free space is available
            if (m_entries[index].status == "never used" ||
                m_entries[index].status == "tombstone") {
                if (out_index) { *out_index = index; } 
                return true;
            }
    
            // return true if the desired key is found
            if (m_entries[index].data == key) {
                if (out_index) { *out_index = index; }
                return true;
            }
        }
    
        if (out_index) { *out_index = -1; }
        return false;
    }

    std::array<Entry, size> m_entries;
};

/*!
    \brief      Program execution begins here.
    
    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    // Aapple Aorange Dapple Astrawberry
    // orange strawberry
    auto input = std::string();
    std::cout << "Enter input ==> ";

    std::getline(std::cin, input);
    auto ss = std::stringstream(input); 

    auto hashTable = HashTable();

    while (ss.good()) {
        auto token = std::string();
        ss >> token;
  
        auto entry_name = token.substr(1);

        switch (token[0]) {
        case 'A':
            hashTable.insert(entry_name);
            break;
        case 'D':
            hashTable.erase(entry_name);
            break;
        default:
            std::cout << "[" << token[0] << " is not a valid command.]" << std::endl;
            break;
        }
    }
        
    std::cout << '\n' << hashTable << std::endl;
    return EXIT_SUCCESS;
}

