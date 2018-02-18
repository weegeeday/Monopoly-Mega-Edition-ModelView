#include "gameview.h"

GameView::GameView(Game * p_game, QWidget* parent): QHBoxLayout(parent)
{
    m_game=p_game;



    AskNumberOfPlayers();

    m_boardView=new BoardView(m_game->GetBoard(), m_game, NULL);

    m_playerViewLayout = new QVBoxLayout();
    addLayout(m_playerViewLayout);

    const QList<Player*> players=m_game->GetPlayers();    
    foreach(Player* player, players)
    {
        m_playerViews.append(new PlayerView(player));
        m_playerViewLayout->addWidget(m_playerViews.last());
        m_boardView->InitPiece(player);
    }

    addWidget(m_boardView);

    m_turnView=new TurnView(m_game);
    addWidget(m_turnView);
    connect(m_game,SIGNAL(EndOfGame(Player*)),this,SLOT(EndOfGame(Player*)));
    m_boardView->ConnectProperties();

}

void GameView::EndOfGame(Player *p_player)
{
    QString message="Player "+ QString::number(p_player->GetNumber()+1);
    message+=" won the game!\n!!! Congratulations !!!";
    QMessageBox::information(NULL,"End Of Game",message,"OK");
    QApplication::quit();
}


void GameView::AskNumberOfPlayers()
{
    StartDialog startDialog;
    startDialog.exec();

    if (startDialog.LoadFileSelected())
    {

        QString fileName = startDialog.GetLoadFile();
        m_game->ReadFromFile(fileName);

    }
    else
        m_game->InitializePlayers(startDialog.GetSelectedValue());
}
