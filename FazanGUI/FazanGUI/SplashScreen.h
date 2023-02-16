#pragma once

#include <QLabel>
#include "QWidget"

class SplashScreen: public QWidget
{
	Q_OBJECT

public:
	SplashScreen(QWidget* parent = nullptr);
	~SplashScreen() override = default;

private:
	QLabel lblBanner;
	QLabel lblInfo;
	QLabel lblTip;

private:
	std::string loadRandomFunFact();
};

