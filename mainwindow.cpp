#include "mainwindow.h"
//#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    //ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    this->setMinimumSize(800, 500);
    this->resize(1400, 900);

    QWidget * wdg = new QWidget(this);

    m_game=new Game();
    m_gameView=new GameView(m_game, wdg);
    setCentralWidget(wdg);

    //setLayout(m_gameView);
    //setCentralWidget(m_gameView);
}

MainWindow::~MainWindow()
{
    //delete ui;
    delete m_game;
    delete m_gameView;
}
