#ifndef UTILS_ARGUMENT_PARSER_HPP
#define UTILS_ARGUMENT_PARSER_HPP
#pragma once

#include <string>
#include <vector>

namespace utils {

    class ArgumentParser{
        public:
            ArgumentParser (int &argc, char **argv){
                for (int i=1; i < argc; i++) {
                    this->_tokens.push_back(std::string(argv[i]));
                }
            }
            template<class T> T Get(const std::string &option, T defaultValue) const {
                std::vector<std::string>::const_iterator itr;
                
                itr = std::find(this->_tokens.begin(), this->_tokens.end(), option);

                if (itr != this->_tokens.end() && ++itr != this->_tokens.end()){
                    std::stringstream convert(*itr);
                    T value;
                    convert >> value;
                    return value;
                }

                return defaultValue;
            }
            bool Exists(const std::string &option) const {
                return std::find(this->_tokens.begin(), this->_tokens.end(), option)
                    != this->_tokens.end();
            }
        private:
            std::vector <std::string> _tokens;
    };

}

#endif
