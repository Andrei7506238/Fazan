#include "FazanGUI.h"
#include "FazanGUI.h"
#include "FazanGUI.h"


FazanGUI::FazanGUI(QWidget* parent)
	: QMainWindow(parent, Qt::FramelessWindowHint)
{
	setFixedSize(kWindowW, kWindowH);
	setStyleSheet("background: #4B164B; font-family: 'Comic Neue'; font-style: normal; font-size: 20px;");

	//Initialize widgets
	initStatusBar();
	initLogo();
	initInputLines();
	initOptions(inpRec.pos().y() + 50);
	initBtns(kWindowH - 50);
}

FazanGUI::~FazanGUI()
{
	delete x;
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

	chkDeleteTyped.setCheckState(Qt::Checked);
	chkDeleteRec.setCheckState(Qt::Checked);
	chkDoRec.setCheckState(Qt::Checked);
	chkDoCheck.setCheckState(Qt::Checked);
}

void FazanGUI::initBtns(const unsigned btnContainerVerticalOffset)
{
	containerBtn.setParent(this);
	containerBtn.setGeometry(0, btnContainerVerticalOffset, kWindowW, 50);
	containerBtn.setLayout(&layBtn);
	containerBtn.setObjectName("containerBtn");
	containerBtn.setStyleSheet("QWidget{color: white; font-size: 18px; background-color: #571957;} QWidget#containerBtn{background-color: #330F33;}");

	btnGenLockWord.setText("Block List");
	btnGenLongChain.setText("Long Game");

	layBtn.addWidget(&btnGenLockWord);
	layBtn.addWidget(&btnGenLongChain);

	connect(&btnGenLockWord, &QPushButton::released, this, &FazanGUI::onGenerateBlockingWordsBtnRelease);
	connect(&btnGenLongChain, &QPushButton::released, this, &FazanGUI::onGenerateLongPathBtnRelease);
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

void FazanGUI::initLogo()
{
	const unsigned kLogoMargin = (kWindowW - kLogoSize) / 2;
	QPixmap pixLogo("res\\img\\FazanLogo.png");
	pixLogo = pixLogo.scaled(kLogoSize, kLogoSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	lblLogo.setParent(this);
	lblLogo.setPixmap(pixLogo);
	lblLogo.setGeometry(kLogoMargin, 30, kLogoSize, kLogoSize);
}

void FazanGUI::initInputLines()
{
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

	connect(&btnEnterWord, &QPushButton::released, this, &FazanGUI::onGenerateRelease);
	connect(&inpWord, &QLineEdit::returnPressed, this, &FazanGUI::onGenerateRelease);


	//Recomended word
	const unsigned kWordRecomVerticalOffset = kLogoSize + kInputMargin + 50;

	inpRec.setParent(this);
	inpRec.setStyleSheet("background: #330F33; color: white; border: none");
	inpRec.setGeometry(kInputMargin, kWordRecomVerticalOffset, kWindowW - 2 * kInputMargin, 30);
	inpRec.setPlaceholderText("Recommended word");
	inpRec.setReadOnly(true);
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

void FazanGUI::onGenerateRelease()
{
	//Get word
	std::string nw = inpWord.text().toStdString();

	//Check if the word is valid
	bool wordIsValid = true;
	if (!x->checkWordExists(nw)) {
		wordIsValid = false;

		//If process anyway skip over the message and continue round
		if (chkDoCheck.checkState()) {

			//Warning
			auto dgWarn = std::make_shared<QMessageBox>();
			dgWarn->setText("The entered word can't be found in the word list or has been eliminated");
			dgWarn->exec();

			return;
		}
	}

	//Delete adversary word if word is valid
	if (wordIsValid && chkDeleteTyped.checkState())
		x->deleteWord(nw);

	//If not marked only for deletion get suggestion
	if (chkDoRec.checkState()) {
		auto res = x->suggestWord(nw);

		//If words are avaliable
		if (res.first.length()) {
			inpRec.setText(QString::fromStdString(res.first));

			//Delete reccomended word if checkbox set
			if(chkDeleteRec.checkState())
				x->deleteWord(res.first);
		}
		//Otherwise round over for advantage player
		else {
			inpRec.setText("FAILED");
		}
	}

}

void FazanGUI::onGenerateBlockingWordsBtnRelease() const
{
	size_t countBlockingWords = 0;
	std::ofstream out("blockingWords.txt");
	if (!out.good()) {
		auto dgWarn = std::make_shared<QMessageBox>();
		dgWarn->setText("The file Blockingwords.txt couldn't be opened for writing.");
		dgWarn->exec();
	}

	for (size_t line = 0; line < FazanDataStructure::MLCGS; line++) {
		out << "\n " << MorphoAnalyzer::groupInvConverter(line) << "\t";
		auto lst = x->getBlockingWords(line);
		countBlockingWords += lst.size();

		for (auto& blockingWord : lst)
			out << blockingWord << " ";
	}

	auto dgSuccess = std::make_shared<QMessageBox>();
	dgSuccess->setText("The file Blockingwords.txt generated. Number of blocking words: " + countBlockingWords);
	dgSuccess->exec();
	out.close();
}

void FazanGUI::onGenerateLongPathBtnRelease() const
{
	std::ofstream out("longPath.txt");
	if (!out.good()) {
		auto dgWarn = std::make_shared<QMessageBox>();
		dgWarn->setText("The file longestChain.txt couldn't be opened for writing.");
		dgWarn->exec();
	}

	size_t countChainWords = 0;

	std::string bestWord = x->getMaxWordWithPrefix();
	while (bestWord.length() > 0) {
		out << bestWord << std::endl;
		++countChainWords;
		x->deleteWord(bestWord);
		bestWord = x->getMaxWordWithPrefix(MorphoAnalyzer::sufixId(bestWord));
	}

	auto dgSuccess = std::make_shared<QMessageBox>();
	dgSuccess->setText("The file longestChain.txt generated. Number of blocking words: " + countChainWords);
	dgSuccess->exec();
	out.close();
}
