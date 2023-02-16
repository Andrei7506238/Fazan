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
    QApplication a(argc, argv);

    SplashScreen ss;
    ss.show();

    a.processEvents(QEventLoop::AllEvents);

    FazanDataStructure* fazanDS;
    auto th = std::thread([&]() {
        auto minTimeExit = std::chrono::system_clock::now() + std::chrono::seconds(2);

        std::ifstream fin("redus.txt");
        fazanDS = new FazanDataStructure(fin, loadIgnoreList());

        std::this_thread::sleep_until(minTimeExit);
        }
    );

    th.join();
    ss.hide();

    FazanGUI w;
    w.show();
    w.loadWords(fazanDS);
    return a.exec();
}
