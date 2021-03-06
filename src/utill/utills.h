//
// Created by Islam, Abdullah Al Raqibul on 1/30/20.
//

#ifndef UTILLS_H
#define UTILLS_H

#include <algorithm>
#include <iostream>
#include <cstring>
#include <sstream>
#include <map>
using namespace std;

namespace utils {
    inline int _abs(int a) {
        return a < 0 ? -a : a;
    }

    inline int _min(int a, int b) {
        return a < b ? a : b;
    }

    inline int _max(int a, int b) {
        return a > b ? a : b;
    }

    inline bool to_bool(std::string str) {
        bool ret;
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        std::istringstream is(str);
        is >> std::boolalpha >> ret;
        return ret;
    }

    class Properties {
    public:
        std::string GetProperty(const std::string &key,
                                const std::string &default_value = std::string()) const;

        const std::string &operator[](const std::string &key) const;

        const std::map <std::string, std::string> &properties() const;

        void SetProperty(const std::string &key, const std::string &value);

    private:
        std::map <std::string, std::string> properties_;
    };

    inline std::string Properties::GetProperty(const std::string &key,
                                               const std::string &default_value) const {
        std::map<std::string, std::string>::const_iterator it = properties_.find(key);
        if (properties_.end() == it) {
            return default_value;
        } else return it->second;
    }

    inline const std::string &Properties::operator[](const std::string &key) const {
        return properties_.at(key);
    }

    inline const std::map <std::string, std::string> &Properties::properties() const {
        return properties_;
    }

    inline void Properties::SetProperty(const std::string &key,
                                        const std::string &value) {
        properties_[key] = value;
    }

    // get time difference in nano seconds
    static inline long time_diff(struct timespec start, struct timespec end) {
        return (end.tv_sec - start.tv_sec) * (long) 1e9 + (end.tv_nsec - start.tv_nsec);
    }

    // count number of 1 bits
    static inline int count_set_bit(int num) {
        int cnt = 0;
        while(num) {
            cnt += (num & 1);
            num = num >> 1;
        }
        return cnt;
    }

    // random generator function
    static inline int my_random(int i) {
        srand(time(0));
        return rand() % i;
    }

} // utils

#endif //UTILLS_H
