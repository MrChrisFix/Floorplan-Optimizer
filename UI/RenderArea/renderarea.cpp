#include "renderarea.h"
#include "ralineedit.h"
#include <string>
#include <QPainter>


RenderArea::RenderArea(QWidget *parent)
    : QWidget{parent}
{
    this->widthBox = nullptr;
    this->heightBox = nullptr;
    this->currentVariant = nullptr;

    this->length = 1;
    this->height = 1;
}

void RenderArea::setLength(QString newLength)
{
    if(!newLength.isEmpty())
    {
        this->length = newLength.toUInt();
        if(currentVariant != nullptr)
            this->currentVariant->SetWidth(newLength.toUInt());
        this->reshapeAndDraw();
    }
}

void RenderArea::setHeight(QString newHeight)
{
    if(!newHeight.isEmpty())
    {
        this->height = newHeight.toUInt();
        if(currentVariant != nullptr)
            this->currentVariant->SetHeight(newHeight.toUInt());
        this->reshapeAndDraw();
    }
}

void RenderArea::onVariantChange(FPA::Variant* variant)
{
    this->currentVariant = variant;

    if(variant == nullptr)
    {
        this->height = 1;
        this->length = 1;
    }
    else
    {
        this->height = variant->GetHeight();
        this->length = variant->GetWidth();
    }
    this->heightBox->setText(QString::number(this->height));
    this->widthBox->setText(QString::number(this->length));


    this->reshapeAndDraw();
}

void RenderArea::reshapeAndDraw()
{
    if(this->length < 1 || this->height < 1)
        return;

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
    //painter.drawText(rect, Qt::AlignCenter, "Center");
    //painter.drawText(rect, Qt::AlignHCenter, "Top center");
    //painter.drawText(rect, Qt::AlignHCenter | Qt::AlignBottom,  "Bottom center");
    //painter.drawText(rect, Qt::AlignVCenter, "Left center");
    //painter.drawText(rect, Qt::AlignVCenter | Qt::AlignRight, "Right center");
}

void RenderArea::resizeEvent(QResizeEvent * event)
{
    this->MAXDRAWSIZE = std::min(this->geometry().height(), this->geometry().width())/2;

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
