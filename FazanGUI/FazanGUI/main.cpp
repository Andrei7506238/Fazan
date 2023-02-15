#include "FazanGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SplashScreen ss;
    ss.show();

    a.processEvents(QEventLoop::AllEvents);

    FazanDataStructure* fazanDS;
    auto th = std::thread([&]() {
        auto minTimeExit = std::chrono::system_clock::now() + std::chrono::seconds(2);

        std::ifstream fin("flex.txt");
        fazanDS = new FazanDataStructure(fin);

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
