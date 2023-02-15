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

	std::array<std::string, 14> funFacts = {
		"There are many variations of the game, and players can make up their own rules.",
		"The game can be a great way to practice and improve your language skills.",
		"The game can be played in groups of two or more players.",
		"Fazan can be played in any language, not just Romanian.",
		"Fazan is a great way to pass the time while waiting for something.",
		"Fazan is a popular and beloved game in Romania, and it is sure to provide fun for anyone who plays it.",
		"Also try hangman.",
		"There are versions of the game that only accept specific categories.",
		"The word FAZAN is the most popular blocking word.",
		"Pheasants are known for their beautiful, colorful feathers, which are often used in clothing and decorations.",
		"Male pheasants are known for their elaborate courtship displays, which involve puffing up their feathers, strutting around, and making loud calls to attract females.",
		"Pheasants are ground-dwelling birds and prefer to live in areas with dense vegetation and low-lying shrubs.",
		"In some cultures, pheasants are considered symbols of good luck and prosperity.",
		"Pheasants are birds that are native to Asia, but they have been introduced to other parts of the world, including Europe and North America, where they are often hunted for sport."
	};
};

