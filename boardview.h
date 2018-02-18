// Made by Louis Hendrikx

#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <spaceview.h>
#include <pieceview.h>
#include <player.h>
#include "auctiondialog.h"
#include <QGraphicsView>
#include <QMouseEvent>


#include "board.h"

class BoardView: public QGraphicsView
{
    Q_OBJECT

public:
    BoardView(Board* p_board, Game* p_game,QWidget* parent);
    ~BoardView();
    /**
     * @brief resizeEvent: scales the Board when the window resizes
     */
    void resizeEvent(QResizeEvent*);

    /**
     * @brief InitPiece: initializes the Piece of a player
     * @param p_player: the player who's piece need to bee initialized
     */
    void InitPiece(Player* p_player);
    //void mousePressEvent(QMouseEvent* e);
    void mouseDoubleClickEvent(QMouseEvent*e);

    void mouseReleaseEvent(QMouseEvent* e);

    void ConnectProperties();

public slots:
    /**
     * @brief MovePiece: moves the piece on the board
     * @param p_playerID: the player number which needed to be moved
     * @param p_location: location where to move
     */
    void MovePiece(int p_playerID, int p_location);
    /**
     * @brief PlayerHasThrownTriple: sets the bool that the player has thrown a triple
     */
    void PlayerHasThrownTriple();
    void PlayerHasBuildHouses(int p_numberOfHouses,int p_space);
private:
    /**
     * @brief LoadSpaces: loads all the space coordinates in to the game
     */
    void LoadSpaces();
    void InitHouses();
    void DeleteHouse(int p_space);
    void ConnectPlayers(Game* p_game);

    QList<SpaceView*> m_spaces;
    QList<QGraphicsPixmapItem*> m_houses;
    QLabel* m_imageLabel;

    QList<PieceView*> m_pieces;
    QGraphicsPixmapItem* m_boardPixmapItem;
    QGraphicsScene* m_scene;
    Board * m_board;
    Game* m_game;
    bool m_playerHasThrownTriple=false;
    int m_height=0;
    int m_width=0;
};

#endif // BOARDVIEW_H
