#include <regex>
#include "fstream"

#include "FazanGUI.h"
#include <QtWidgets/QApplication>

std::list<std::wregex> loadIgnoreList()
{
    std::wifstream fin("ignoreWordList.txt");
    if (!fin.good()) return {};

    std::list<std::wregex> regexList;
    std::wstring word;

	while(fin >> word)
        regexList.emplace_back(word);

    fin.close();
    return regexList;
}

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    SplashScreen splashscreenWindow;
    splashscreenWindow.show();
    application.processEvents(QEventLoop::AllEvents);

    FazanDataStructure* fazanDS;
    auto threadWordLoading = std::thread([&]() {
        auto minTimeExit = std::chrono::system_clock::now() + std::chrono::seconds(2);

        std::wifstream fin("flex.txt");
        fazanDS = new FazanDataStructure(fin, loadIgnoreList());

        std::this_thread::sleep_until(minTimeExit);
        }
    );

    threadWordLoading.join();
    splashscreenWindow.hide();

    FazanGUI mainAppWindow;
    mainAppWindow.show();
    mainAppWindow.loadWords(fazanDS);

	return application.exec();
}
