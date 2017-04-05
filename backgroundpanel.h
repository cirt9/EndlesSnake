#ifndef BACKGROUNDPANEL_H
#define BACKGROUNDPANEL_H

#include <QGraphicsRectItem>
#include <QBrush>

class BackgroundPanel : public QGraphicsRectItem
{
public:
    BackgroundPanel(int x, int y, int width, int height, QColor color, double opacity = 1.0, QGraphicsItem * parent = nullptr);
    ~BackgroundPanel() {}
};

#endif // BACKGROUNDPANEL_H
