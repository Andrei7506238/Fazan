#include "FazanGUI.h"
#include <QtWidgets/QApplication>

#include <fstream>
#include <regex>

std::list<std::regex> loadIgnoreList()
{
    std::ifstream fin("ignoreWordList.txt");
    if (!fin.good()) return {};

    std::list<std::regex> regexList;
    std::string word;

    while (fin >> word)
        regexList.emplace_back(word);

    fin.close();
    return regexList;
}

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    SplashScreen splashScreen;
    splashScreen.show();

    application.processEvents(QEventLoop::AllEvents);

    FazanDataStructure* fazanDS;
    auto th = std::thread([&]() {
        auto minTimeExit = std::chrono::system_clock::now() + std::chrono::seconds(2);

        std::ifstream fin("wordList.txt");
        fazanDS = new FazanDataStructure(fin, loadIgnoreList());

        std::this_thread::sleep_until(minTimeExit);
        }
    );

    th.join();
    splashScreen.hide();

    FazanGUI fazanMainWindow;
    fazanMainWindow.show();
    fazanMainWindow.loadWords(fazanDS);
    return application.exec();
}
