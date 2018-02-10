#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

int main() {
    std::fstream os;
    os.open("out.txt", std::fstream::out);
    DIR *d;
    struct dirent *dir;
    struct stat ss{};
    std::vector<std::pair<std::string, short>> mapVector;
    auto *map = new std::map<std::string, short>();
    d = opendir(".");
    dir = readdir(d);                     //возвращает очередную запись из каталога
    for (; dir != NULL; dir = readdir(d)) //считываем записи из каталога
    {
        stat(dir->d_name, &ss); //системный вызов для получения инфы
        map->insert(map->begin(), std::pair<std::string, short>(dir->d_name, ss.st_nlink));
    };
//

    for (auto iterator = map->begin(); iterator != map->end(); ++iterator) {
        mapVector.push_back(*iterator);
    };
    auto cmp = [](std::pair<std::string, short> elem1, std::pair<std::string, short> elem2) {
        return elem1.second > elem2.second;
    };
    sort(mapVector.begin(), mapVector.end(), cmp);
//
//
//
//    std::sort(map->begin(), map->end(), cmp);
    auto currentLinkNumber = mapVector.begin()->second;
    os << currentLinkNumber << " ============================" << std::endl;
    std::cout << currentLinkNumber << std::endl;
    for (auto i = mapVector.begin(); i != mapVector.end(); i++) {
        if (currentLinkNumber != i->second) {
            os << i->second << " ============================" << std::endl;
            std::cout << i->second << std::endl;
            currentLinkNumber = i->second;
        }
        os << i->first << std::endl;
        std::cout << i->first << std::endl;
    }
    os.close();
    return 0;
}
