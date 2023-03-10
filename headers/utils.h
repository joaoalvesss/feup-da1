#ifndef PROJETO_1_UTILS_H
#define PROJETO_1_UTILS_H

#include <string>
#include <list>

using namespace std;

namespace utils::file {
        std::list<std::string> readCsv(const std::string &fileName);
}
#endif //PROJETO_1_UTILS_H
