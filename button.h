#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QFont>

class Button : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    QGraphicsTextItem * text;
    QBrush buttonColor;
    QBrush hoverButtonColor;

    void mousePressEvent(QGraphicsSceneMouseEvent * = nullptr);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * = nullptr);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * = nullptr);

public:
    Button(QString textOnButton, int width, int height, int fontSize, QGraphicsItem * parent = nullptr);
    ~Button() {}

    void setButtonColor(const QColor & color);
    void setHoverButtonColor(const QColor & color);
    void setFontColor(const QColor & color);

signals:
    void clicked();
};


#endif // BUTTON_H
