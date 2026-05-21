#ifndef CCACHE_HPP
#define CCACHE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

namespace CMakeCacheParse
{
    // Forward declaration so the proxy knows it exists
    class parse;

    // A proxy class to handle the intermediate ->fetch() and ->type() syntax
    class ElementProxy {
    private:
        const parse& _parserRef;
        std::string _key;

    public:
        ElementProxy(const parse& parser, std::string key) 
            : _parserRef(parser), _key(std::move(key)) {}

        // This allows the -> syntax from your README to work perfectly
        ElementProxy* operator->() { return this; }

        std::string fetch() const;
        std::string type() const;
    };

    class parse {
    private:
        std::string _contents;

    public: 
        parse() = default;
        
        parse(std::string cont) {
            _contents = removeNewlinesAndComments(std::move(cont));
        }

        std::string removeNewlinesAndComments(std::string str) {
            std::istringstream iss(str);
            std::string line;
            std::string result;

            while (std::getline(iss, line)) {
                // Remove comments (anything after '#' or "//")
                size_t commentPos = line.find('#');
                size_t commentPos2 = line.find("//");
                if (commentPos != std::string::npos || commentPos2 != std::string::npos) {
                    line = line.substr(0, commentPos);
                }
                
                // Trim leading whitespace
                line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char ch) {
                    return !std::isspace(ch);
                }));
                
                // Trim trailing whitespace
                line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch) {
                    return !std::isspace(ch);
                }).base(), line.end());

                if (!line.empty()) {
                    result += line + "\n";
                }
            }
            return result;
        }

        std::string getAnswerFromKey(const std::string& key) const {
            std::istringstream iss(_contents);
            std::string line;

            while (std::getline(iss, line)) {
                if (line.find(key + ":") == 0) {
                    size_t equalPos = line.find('=');
                    if (equalPos != std::string::npos) {
                        return line.substr(equalPos + 1);
                    }
                }
            }
            return ""; 
        }

        std::string getTypeFromKey(const std::string& key) const {
            std::istringstream iss(_contents);
            std::string line;

            while (std::getline(iss, line)) {
                if (line.find(key + ":") == 0) {
                    size_t colonPos = line.find(':');
                    size_t equalPos = line.find('=');
                    if (colonPos != std::string::npos && equalPos != std::string::npos) {
                        return line.substr(colonPos + 1, equalPos - colonPos - 1);
                    }
                }
            }
            return "";
        }

        // Returns the proxy object 
        ElementProxy operator[] (std::string key) const {
            return ElementProxy(*this, std::move(key));
        }
    };

    // Out-of-line implementations for the proxy to avoid compilation ordering issues
    inline std::string ElementProxy::fetch() const {
        return _parserRef.getAnswerFromKey(_key);
    }

    inline std::string ElementProxy::type() const {
        return _parserRef.getTypeFromKey(_key);
    }

} // namespace CMakeCacheParse

#endif // CCACHE_HPP