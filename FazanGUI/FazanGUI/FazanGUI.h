#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FazanGUI.h"

#include "QLabel"
#include "QLineEdit"
#include "QPushButton"
#include "QCheckBox"

#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QMessageBox"
#include "QDesktopServices"
#include "QMouseEvent"
#include "SplashScreen.h"

#include "FazanDS.h"
#include "FazanCheatGame.h"
#include "Extra.h"
#include <thread>
#include <future>


class FazanGUI : public QMainWindow
{
    Q_OBJECT

public:
    FazanGUI(QWidget *parent = nullptr);
    ~FazanGUI() override = default;

public slots:
    void loadWords(FazanDataStructure* fds);

private:
    Ui::FazanGUIClass ui;

    //Constants
    const unsigned kWindowW = 400;
    const unsigned kWindowH = 550;
    const unsigned kLogoSize = 220;
    const unsigned kInputMargin = 20;
    const unsigned kEnterWordBtnWidth = 70;

    QLabel lblLogo;

	QLineEdit inpWord;
    QLineEdit inpRec;

    QPushButton btnEnterWord;
    QLabel lblRec;

    QWidget containerChk;
    QVBoxLayout layOptions;
    QCheckBox chkDeleteTyped;
    QCheckBox chkDeleteRec;
    QCheckBox chkDoRec;
    QCheckBox chkDoCheck;

    QWidget containerBtn;
    QHBoxLayout layBtn;
    QPushButton btnReload;
    QPushButton btnGenLockWord;
    QPushButton btnGenLongChain;

    QWidget barStatus;
    QPushButton btnCloseApp;
    QPushButton btnMinimizeApp;
    QPushButton btnTitleApp;

    QPoint curPos;

    FazanDataStructure* x;

private:
    void initOptions(const unsigned optionsContainerVerticalOffset);
    void initBtns(const unsigned btnContainerVerticalOffset);
    void initStatusBar();

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private slots:
    void onExitApplicationBtnRelease();
    void onMinimizeApplicationBtnRelease();
    void onLogoRelease();
};