#include "pieceview.h"

PieceView::PieceView(int p_id, QGraphicsItem* parent) : QGraphicsPixmapItem(parent)
{
    QString fileName=":/Images/piece"+QString::number(p_id+1)+ ".png";
    setPixmap(QPixmap(fileName));
}
