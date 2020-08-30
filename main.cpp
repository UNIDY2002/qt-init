#include <iostream>
#include <fstream>
#include <direct.h>
#include <cstring>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cout << "Usage: qt-init <ProjectName> <QtSDKPath> <MinGWBinPath>" << endl;
        return 0;
    }

    cout << "[INFO] Checking CMake..." << endl;
    if (system("cmake --version > version.txt")) {
        remove("version.txt");
        cerr << "Tried to execute `cmake --version` but failed." << endl
             << "Please make sure that you have CMake installed and added to path." << endl;
        return -1;
    }

    ifstream versionFile("version.txt", ios::in);
    string minVersion;
    versionFile >> minVersion >> minVersion >> minVersion;
    cout << "[INFO] CMake version: " << minVersion << endl;
    versionFile.close();
    remove("version.txt");

    auto project = argv[1];
    auto sdk = argv[2];
    auto mingw = argv[3];
    if (mingw[strlen(mingw) - 1] == '/' || mingw[strlen(mingw) - 1] == '\\') {
        mingw[strlen(mingw) - 1] = 0;
    }

    if (!access(project, 0)) {
        cerr << "[Error] Directory " << project << " already exists. STOP." << endl;
        return -1;
    }

    cout << "[INFO] Making Qt project " << project << "..." << endl;
    mkdir(project);
    chdir(project);

    cout << "[INFO] Generating source files..." << endl;
    ofstream cmake("CMakeLists.txt", ios::out);
    cmake << "# Generated with qt-init" << endl
          << "# See: https://github.com/UNIDY2002/qt-init" << endl
          << endl
          << "cmake_minimum_required(VERSION " << minVersion << ")" << endl
          << "project(" << project << ")" << endl
          << endl
          << "set(CMAKE_CXX_STANDARD 14)" << endl
          << "set(CMAKE_C_COMPILER " << mingw << "/gcc)" << endl
          << "set(CMAKE_CXX_COMPILER " << mingw << "/g++)" << endl
          << endl
          << "set(CMAKE_AUTOMOC ON)" << endl
          << "set(CMAKE_AUTOUIC ON)" << endl
          << "set(CMAKE_AUTORCC ON)" << endl
          << endl
          << "set(CMAKE_PREFIX_PATH " << sdk << ")" << endl
          << endl
          << "# For new modules, simply add them here." << endl
          << "find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)" << endl
          << endl
          << "aux_source_directory(. DIRS_SRCS)" << endl
          << endl
          << "include_directories(.)" << endl
          << endl
          << "# Resource files are supposed to be added below." << endl
          << "qt5_add_resources(QRC_FILES)" << endl
          << endl
          << "add_executable(" << project << " main.cpp ${QRC_FILES})" << endl
          << endl
          << "# And do not forget to link new modules here." << endl
          << "target_link_libraries(" << project << " Qt5::Core Qt5::Gui Qt5::Widgets)" << endl;
    cmake.close();
    ofstream main("main.cpp", ios::out);
    main << "#include <QApplication>" << endl
         << "#include <QWidget>" << endl
         << endl
         << "int main(int argc, char *argv[]) {" << endl
         << "    QApplication app(argc, argv);" << endl
         << "    QWidget w;" << endl
         << "    w.show();" << endl
         << "    return QApplication::exec();" << endl
         << "}" << endl;
    main.close();

    cout << "[INFO] Initializing CMake project..." << endl;
    mkdir("cmake-build-debug");
    chdir("cmake-build-debug");
    system(R"(cmake -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - MinGW Makefiles" ..)");
    chdir("..");
    cout << "[INFO] CMake building..." << endl;
    system((string("cmake --build cmake-build-debug --target ") + project).c_str());
    chdir("cmake-build-debug");
    cout << "[INFO] Running..." << endl;
    system(project);
    return 0;
}
