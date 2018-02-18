 #include "boardview.h"

#include <QFile>
#include <QTextStream>

BoardView::BoardView(Board*p_board, Game* p_game, QWidget* parent):QGraphicsView(parent)
{
    m_board=p_board;
    m_game = p_game;
    m_imageLabel=new QLabel;

    connect(m_game,SIGNAL(PlayerHasThrownTriple()),this,SLOT(PlayerHasThrownTriple()));
    ConnectPlayers(p_game);

    m_scene=new QGraphicsScene(this);
    setScene(m_scene);
    m_boardPixmapItem = m_scene->addPixmap(QPixmap(":/Images/US_Board_klein.png"));

    LoadSpaces();
    InitHouses();
}

BoardView::~BoardView()
{
    for(int i =0;i<m_houses.length();i++)
    {
        if(m_houses[i]!=NULL)
            delete m_houses[i];
    }
    m_houses.clear();
    delete m_imageLabel;
    delete m_scene;
}

void BoardView::resizeEvent(QResizeEvent *)
{
    fitInView(m_boardPixmapItem, Qt::KeepAspectRatio);
}


void BoardView::InitPiece(Player *p_player)
{
    PieceView* piece = new PieceView(p_player->GetNumber(),m_spaces[p_player->GetPosition()]);
    m_pieces << piece;
}

void BoardView::mouseDoubleClickEvent(QMouseEvent *e)
{
    QGraphicsView::mouseDoubleClickEvent(e);

    if(!m_scene->selectedItems().isEmpty())
    {
        QGraphicsItem *s = m_scene->selectedItems().first();
        SpaceView* selectedSpace=(SpaceView*) s;
        int spaceNumber=selectedSpace->GetPosition();

        QString imageName=":/Images/properties/"+QString::number(spaceNumber)+ ".png";
        QImage image;
        image.load(imageName);
        //TODO: showing the image
        if(!image.isNull()){
            m_imageLabel->setPixmap(QPixmap::fromImage(image));
            m_imageLabel->setFixedSize(image.size());
            m_imageLabel->show();
        }

        s->setSelected(false);
        m_scene->clearSelection();
    }
}

void BoardView::mouseReleaseEvent(QMouseEvent *e)
{
    QGraphicsView::mouseReleaseEvent(e);

    if(!m_scene->selectedItems().isEmpty())
    {
        QGraphicsItem *s = m_scene->selectedItems().last();
        SpaceView* selectedSpace=(SpaceView*) s;
        if(m_playerHasThrownTriple)
        {
            m_playerHasThrownTriple=false;
            m_game->MakeTripleMove(selectedSpace->GetPosition());
        }
        else if(m_game->GetPlayerUsingBusTicket())
        {
            m_game->MakeBusTicketMove(selectedSpace->GetPosition());
        }
        else if(m_board->GetPlayerHasLandedOnAuctionSpace()){
            int spacePosition=selectedSpace->GetPosition();
            m_board->SetPlayerHasLandedOnAuctionSpace(false);
            AuctionDialog auction(m_game->GetPlayers());
            auction.exec();
            m_game->BuyPropertyToPlayer(m_board->GetProperty(spacePosition),auction.GetHighestBid(),auction.GetHighestBidPlayer());
        }
    }
}

void BoardView::ConnectProperties()
{
    for (int i = 0; i < m_board->GetNumProperties(); i++)
    {
        Property*placeProperty=m_board->GetProperty(i);
        if(placeProperty!=NULL)
        {
          connect(placeProperty,SIGNAL(BuildTierChanged(int,int)),this,SLOT(PlayerHasBuildHouses(int,int)));
        }
    }
}

void BoardView::MovePiece(int p_playerNumber, int p_location)
{
    m_pieces[p_playerNumber]->setParentItem(m_spaces[p_location]);
}

void BoardView::PlayerHasThrownTriple()
{
    m_playerHasThrownTriple=true;
}

void BoardView::PlayerHasBuildHouses(int p_numberOfHouses, int p_space)
{
    QGraphicsPixmapItem* houseImage;
    if(p_numberOfHouses>0)
    {
        if(m_houses[p_space]!=NULL)
            DeleteHouse(p_space);

        QString fileName=":/Images/house"+QString::number(p_numberOfHouses)+ ".png";
        houseImage=new QGraphicsPixmapItem(fileName,m_spaces[p_space]);
        houseImage->setScale(0.06);
    }
    else
    {
        if(!m_houses[p_space]==NULL)
            DeleteHouse(p_space);
        houseImage=NULL;
    }
    m_houses[p_space]=houseImage;
}

void BoardView::DeleteHouse(int p_space)
{
    delete m_houses[p_space];
    m_houses[p_space]=NULL;
}

void BoardView::LoadSpaces()
{
    // Load space rectangles from file
    QFile file(":/Data/spacesRects.txt");

    file.open(QFile::ReadOnly);

    QTextStream textStream(&file);

    int count = 0;

    while(!textStream.atEnd())
    {
        QString line = textStream.readLine();
        QStringList list = line.split(' ');

        SpaceView* s = new SpaceView(m_board->GetSpace(count), m_game,count, m_boardPixmapItem);
        s->setRect(0, 0, list[2].toInt(), list[3].toInt());
        s->setPos(list[0].toInt(), list[1].toInt());
        //s->setPen(QPen(Qt::red)); // Draw red border around rect
        s->setFlag(QGraphicsItem::ItemIsSelectable);
        m_spaces.append(s);
        count++;
    }

    file.close();
}

void BoardView::InitHouses()
{
    for(int i=0;i<m_spaces.length();i++)
        m_houses.append(NULL);
}

void BoardView::ConnectPlayers(Game *p_game)
{
    QList<Player*> players = p_game->GetPlayers();

    for (int i = 0; i < players.length(); i++)
    {
        connect(players[i], SIGNAL(PlayerMoved(int, int)), this, SLOT(MovePiece(int,int)));
    }

}
