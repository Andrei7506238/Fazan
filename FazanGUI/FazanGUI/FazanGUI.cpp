#include "FazanGUI.h"
#include "FazanGUI.h"
#include "FazanGUI.h"


FazanGUI::FazanGUI(QWidget* parent)
	: QMainWindow(parent, Qt::FramelessWindowHint)
{
	setFixedSize(kWindowW, kWindowH);
	setStyleSheet("background: #4B164B; font-family: 'Comic Neue'; font-style: normal; font-size: 20px;");

	//Status bar
	initStatusBar();

	//Logo
	const unsigned kLogoMargin = (kWindowW - kLogoSize) / 2;
	QPixmap pixLogo("res\\img\\FazanLogo.png");
	pixLogo = pixLogo.scaled(kLogoSize, kLogoSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	lblLogo.setParent(this);
	lblLogo.setPixmap(pixLogo);
	lblLogo.setGeometry(kLogoMargin, 30, kLogoSize, kLogoSize);

	//Enter word
	const unsigned kWordEnterVerticalOffset = kLogoSize + kInputMargin;
	inpWord.setParent(this);
	inpWord.setStyleSheet("background: #330F33; color: white; border: none;");
	inpWord.setGeometry(kInputMargin, kWordEnterVerticalOffset, kWindowW - 2 * kInputMargin - kEnterWordBtnWidth - 30, 30);
	inpWord.setPlaceholderText("Enter word");

	btnEnterWord.setParent(this);
	btnEnterWord.setGeometry(kWindowW - 2 * kInputMargin - kEnterWordBtnWidth, kWordEnterVerticalOffset, kEnterWordBtnWidth, 30);
	btnEnterWord.setStyleSheet("color: white; font-style: bold; background-color: #571957;");
	btnEnterWord.setText("Enter");


	//Recomended word
	const unsigned kWordRecomVerticalOffset = kLogoSize + kInputMargin + 50;

	inpRec.setParent(this);
	inpRec.setStyleSheet("background: #330F33; color: white; border: none");
	inpRec.setGeometry(kInputMargin, kWordRecomVerticalOffset, kWindowW - 2 * kInputMargin, 30);
	inpRec.setPlaceholderText("Recommended word");
	inpRec.setReadOnly(true);


	//Options
	initOptions(kWordRecomVerticalOffset + 50);

	//Buttons
	initBtns(kWindowH - 50);

	////Warning
	//QMessageBox dgWarn;
	//dgWarn.setText("The entered word can't be found in the word list or has been eliminated");
	//dgWarn.exec();
}

void FazanGUI::initOptions(const unsigned optionsContainerVerticalOffset)
{
	containerChk.setParent(this);
	containerChk.setGeometry(50, optionsContainerVerticalOffset, kWindowW - 100, 125);
	containerChk.setLayout(&layOptions);
	containerChk.setStyleSheet("QWidget{color: white; font-size: 16px;}");

	chkDeleteTyped.setText("Removed typed words");
	chkDeleteRec.setText("Removed recommended words");
	chkDoRec.setText("Recommend words");
	chkDoCheck.setText("Check typed words");

	layOptions.addWidget(&chkDeleteTyped);
	layOptions.addWidget(&chkDeleteRec);
	layOptions.addWidget(&chkDoRec);
	layOptions.addWidget(&chkDoCheck);
}

void FazanGUI::initBtns(const unsigned btnContainerVerticalOffset)
{
	containerBtn.setParent(this);
	containerBtn.setGeometry(0, btnContainerVerticalOffset, kWindowW, 50);
	containerBtn.setLayout(&layBtn);
	containerBtn.setObjectName("containerBtn");
	containerBtn.setStyleSheet("QWidget{color: white; font-size: 18px; background-color: #571957;} QWidget#containerBtn{background-color: #330F33;}");

	btnReload.setText("Reload List");
	btnGenLockWord.setText("Block List");
	btnGenLongChain.setText("Long Game");

	layBtn.addWidget(&btnReload);
	layBtn.addWidget(&btnGenLockWord);
	layBtn.addWidget(&btnGenLongChain);
}

void FazanGUI::initStatusBar()
{
	barStatus.setParent(this);
	barStatus.setGeometry(0, 0, kWindowH, 30);
	barStatus.setStyleSheet("background-color: #1A0F1B;");
	QSize iconSize(20, 20);

	QPixmap pixBtnCloseApp("res\\img\\icons\\IconClose.png");
	btnCloseApp.setParent(&barStatus);
	btnCloseApp.setFlat(true);
	btnCloseApp.setIcon(QIcon(pixBtnCloseApp));
	btnCloseApp.setIconSize(iconSize);
	btnCloseApp.setGeometry(kWindowW - 30, 2, 25, 25);
	connect(&btnCloseApp, &QPushButton::released, this, &FazanGUI::onExitApplicationBtnRelease);

	QPixmap pixBtnMinimizeApp("res\\img\\icons\\IconMinimize.png");
	btnMinimizeApp.setParent(&barStatus);
	btnMinimizeApp.setFlat(true);
	btnMinimizeApp.setIcon(QIcon(pixBtnMinimizeApp));
	btnMinimizeApp.setIconSize(iconSize);
	btnMinimizeApp.setGeometry(kWindowW - 70, 2, 25, 25);
	connect(&btnMinimizeApp, &QPushButton::released, this, &FazanGUI::onMinimizeApplicationBtnRelease);

	QPixmap pixBtnTitleApp("res\\img\\SimpleLogo.png");
	btnTitleApp.setParent(&barStatus);
	btnTitleApp.setFlat(true);
	btnTitleApp.setIcon(QIcon(pixBtnTitleApp));
	btnTitleApp.setIconSize(iconSize);
	btnTitleApp.setGeometry(5, 2, 25, 25);
	connect(&btnTitleApp, &QPushButton::released, this, &FazanGUI::onLogoRelease);

	setWindowIcon(QIcon(pixBtnTitleApp));
}

void FazanGUI::mousePressEvent(QMouseEvent* event)
{
	QMainWindow::mousePressEvent(event);
	curPos = event->globalPos();
}

void FazanGUI::mouseMoveEvent(QMouseEvent* event)
{
	QMainWindow::mouseMoveEvent(event);
	auto newPos = event->globalPos() - curPos;
	move(pos() + newPos);
	curPos = event->globalPos();
}

void FazanGUI::loadWords(FazanDataStructure *fds)
{
	x = fds;
}

void FazanGUI::onExitApplicationBtnRelease()
{
	QCoreApplication::exit();
}

void FazanGUI::onMinimizeApplicationBtnRelease()
{
	setWindowState(Qt::WindowMinimized);
}

void FazanGUI::onLogoRelease()
{
	QDesktopServices::openUrl(QUrl("https://github.com/Andrei7506238/Fazan"));
}
