#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

struct flags {
    bool b0;
    bool b1;
};

map<string, flags> methodFlagMap;

void parse(string configFile) {
    string line, method, flag0, flag1;

    ifstream fileStream(configFile.c_str());

#if 0
    while (!fileStream.eof()) {
        fileStream.getline(line, 256);
#else
    while (getline(fileStream, line)) {
#endif

        cout  << line << endl;
        std::istringstream iss(line);
        getline(iss, method, ' ');
        getline(iss, flag0, ' ');
        getline(iss, flag1, ' ');

        methodFlagMap[method].b0 = (flag0 != "0");
        methodFlagMap[method].b1 = (flag1 != "0");
    } 
}

void dumpMap() {
    map<string, flags>::iterator i;
    for (i=methodFlagMap.begin(); i!=methodFlagMap.end(); i++) {
        cout << "method:" << (*i).first << endl;;
        cout << "flag0:" << (*i).second.b0 << endl;
        cout << "flag1:" << (*i).second.b1 << endl;
    }

    unsigned int k = methodFlagMap.erase("not exist");
    struct flags f;
    methodFlagMap["a"] = f;
    cout << "erase not exist return " << k << endl;
    cout << "erase not exist return " << methodFlagMap.erase("a") << endl;
}

int main(int argc, char *argv[]) {
    string file;
    if (argc > 1) {
        file = string(argv[1]);
    }

    parse(file);
    dumpMap();
    return 0;
}
