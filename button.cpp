#include "button.h"

Button::Button(QString textOnButton, int width, int height, int fontSize, QGraphicsItem * parent) : QGraphicsRectItem(parent)
{
    setRect(0,0,width,height);
    setZValue(1);

    buttonColor.setStyle(Qt::SolidPattern);
    buttonColor.setColor("dark blue");
    hoverButtonColor.setStyle(Qt::SolidPattern);
    hoverButtonColor.setColor("blue");

    setBrush(buttonColor);

    text = new QGraphicsTextItem(textOnButton, this);
    QFont textFont("times new roman", fontSize);
    text->setFont(textFont);

    int textPositionX = rect().width()/2 - text->boundingRect().width()/2;
    int textPositionY = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(textPositionX,textPositionY);

    setAcceptHoverEvents(true);
}

void Button::setButtonColor(const QColor & color)
{
    buttonColor.setStyle(Qt::SolidPattern);
    buttonColor.setColor(color);
    setBrush(buttonColor);
}

void Button::setHoverButtonColor(const QColor &color)
{
    hoverButtonColor.setStyle(Qt::SolidPattern);
    hoverButtonColor.setColor(color);
}

void Button::setFontColor(const QColor & color)
{
    text->setDefaultTextColor(color);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    setBrush(hoverButtonColor);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    setBrush(buttonColor);
}
