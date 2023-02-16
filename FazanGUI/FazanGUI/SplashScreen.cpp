#include "SplashScreen.h"

#include <fstream>
#include <random>

SplashScreen::SplashScreen(QWidget* parent):
	QWidget(parent, Qt::FramelessWindowHint)
{
	setFixedSize(400, 550);
	setStyleSheet("font-family: 'Comic Neue'; font-style: bold; font-size: 25px; color: white;");
	QPixmap pixBanner("res\\img\\Splash.png");
	pixBanner = pixBanner.scaled(400, 600, Qt::KeepAspectRatio, Qt::SmoothTransformation);

	lblBanner.setParent(this);
	lblBanner.setPixmap(pixBanner);
	lblBanner.setGeometry(0, -25, 400, 600);

	lblInfo.setParent(this);
	lblInfo.setText("LOADING WORDS...");
	lblInfo.setAlignment(Qt::AlignCenter);
	lblInfo.setGeometry(0, 425, 400, 30);

	QPixmap pixBtnTitleApp("res\\img\\SimpleLogo.png");
	setWindowIcon(QIcon(pixBtnTitleApp));

	srand(time(NULL));
	QString tipChosen = QString::fromStdString(loadRandomFunFact());
	lblTip.setParent(this);
	lblTip.setText(tipChosen);
	lblTip.setAlignment(Qt::AlignHCenter);
	lblTip.setGeometry(50, 460, 300, 100);
	lblTip.setStyleSheet("font-size: 12px; font-style: normal");
	lblTip.setWordWrap(true);
}

std::string SplashScreen::loadRandomFunFact()
{
	std::ifstream funFactFile("funfacts.txt");
	if (!funFactFile.good())
		return "FAZAN";

	std::vector<std::string> facts;
	std::string fact;

	while (funFactFile) {
		std::getline(funFactFile, fact);
		facts.emplace_back(fact);
	}

	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, facts.size());
	return(facts[dist(rd)]);
}
