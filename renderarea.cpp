#include "renderarea.h"
#include "ralineedit.h"
#include <string>
#include <QPainter>


RenderArea::RenderArea(QWidget *parent)
    : QWidget{parent}
{
    this->widthBox = nullptr;
    this->heightBox = nullptr;

    this->length = 1;
    this->height = 1;

//    QHBoxLayout* para = (QHBoxLayout*)this->parent();
//    auto size = std::min(para->sizeHint().height(), para->sizeHint().width());
//    this->setMaximumSize(size, size);
}

void RenderArea::setLength(QString newLength)
{
    if(!newLength.isEmpty())
    {
        this->length = newLength.toDouble();
        this->reshapeAndDraw();
    }
}

void RenderArea::setHeight(QString newHeight)
{
    if(!newHeight.isEmpty())
    {
        this->height = newHeight.toDouble();
        this->reshapeAndDraw();
    }
}

void RenderArea::reshapeAndDraw()
{
    if(this->length > this->height)
    {
        this->drawLenght = MAXDRAWSIZE;
        this->drawHeight = this->height * MAXDRAWSIZE / this->length;
    }
    else
    {
        this->drawLenght = this->length * MAXDRAWSIZE / this->height;
        this->drawHeight = MAXDRAWSIZE;
    }
    this->repaint();
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    auto emptySpaceTop = (this->size().height() - this->drawHeight) / 2;
    auto emptySpaceLeft = (this->size().width() - this->drawLenght) / 2;
    QRect rect(emptySpaceLeft, emptySpaceTop, this->drawLenght, this->drawHeight); //left, top, width, height
    QPainter painter(this);
    painter.drawRect(rect);
}

void RenderArea::resizeEvent(QResizeEvent * event)
{
    this->MAXDRAWSIZE = std::min(this->geometry().height(), this->geometry().width())/2;
    //auto relation = this->MAXDRAWSIZE / std::max(this->length, this->height);

    if(this->length > this->height)
    {
        this->drawLenght = MAXDRAWSIZE;
        this->drawHeight = this->height * MAXDRAWSIZE / this->length;
    }
    else
    {
        this->drawLenght = this->length * MAXDRAWSIZE / this->height;
        this->drawHeight = MAXDRAWSIZE;
    }

    if(this->widthBox == nullptr || this->heightBox == nullptr)
    {
        auto boxes = this->children();
        if(!boxes.isEmpty())
        {
            if(boxes[0]->objectName() == "widthTextEdit")
            {
                this->widthBox = (RALineEdit*)boxes[0];
                this->heightBox = (RALineEdit*)boxes[1];
            }
            else
            {
                this->widthBox = (RALineEdit*)boxes[1];
                this->heightBox = (RALineEdit*)boxes[0];
            }
        }
    }


    if(this->widthBox != nullptr && this->heightBox != nullptr)
    {
        int x, y, wid, hei;

        //Width box (Top)
        x = this->geometry().width()/2 - this->widthBox->width()/2;
        auto emptySpaceTop = (this->size().height() - this->MAXDRAWSIZE) / 2;
        y = emptySpaceTop - 70;
        wid = this->widthBox->width();
        hei = this->widthBox->height();
        this->widthBox->setGeometry(x, y ,wid, hei);

        //Height box (Left)
        auto emptySpaceLeft = (this->size().width() - this->MAXDRAWSIZE) / 2;
        x = emptySpaceLeft - 70;
        y = this->geometry().height()/2 - this->heightBox->height()/2;
        wid = this->heightBox->width();
        hei = this->heightBox->height();
        this->heightBox->setGeometry(x, y, wid, hei);
    }

}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(200, 200);
}

QSize RenderArea::sizeHint() const
{
    return QSize(200, 200);
}
