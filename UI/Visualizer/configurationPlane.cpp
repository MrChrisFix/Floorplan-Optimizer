#include "configurationPlane.h"
#include "Algorithm/Type.h"
#include "qpainter.h"

ConfigurationPlane::ConfigurationPlane(QWidget *parent)
    : QWidget{parent}
{

}

ConfigurationPlane::~ConfigurationPlane()
{

}

int ConfigurationPlane::findMostLeft()
{
    int min = 0;
    for(auto& el : _results.bestPlacement)
    {
        if(el.second->TopLeft().X < min)
            min = el.second->TopLeft().X;
    }
    return min;
}


void ConfigurationPlane::paintEvent(QPaintEvent *event)
{
    int MAXDRAWSIZE = std::min(this->geometry().height(), this->geometry().width());
    const qreal FREESPACE = MAXDRAWSIZE*0.05;
    qreal resolution = std::max(this->geometry().height(), this->geometry().width()) *1.0/ MAXDRAWSIZE;
    MAXDRAWSIZE -= 2 * FREESPACE;

    qreal drawLenght, drawHeight;
    if(this->_results.bestWidth > this->_results.bestHeight)
    {
        if(this->_results.bestWidth * 1.0 > this->_results.bestHeight * 1.0 * resolution)
        {
            int newMax = std::max(this->geometry().height(), this->geometry().width()) - 2* FREESPACE;
            drawLenght = newMax * 1.0;
            drawHeight = this->_results.bestHeight * newMax * 1.0 / this->_results.bestWidth;
        }
        else
        {
            drawLenght = MAXDRAWSIZE * 1.0;
            drawHeight = this->_results.bestHeight * MAXDRAWSIZE * 1.0 / this->_results.bestWidth;
        }
    }
    else
    {
        drawLenght = this->_results.bestWidth * MAXDRAWSIZE * 1.0 / this->_results.bestHeight;
        drawHeight = MAXDRAWSIZE * 1.0;
    }

    const qreal WIDTH_SCALE = drawLenght/this->_results.bestWidth;
    const qreal HEIGHT_SCALE = drawHeight/this->_results.bestHeight;

    QPainter painter(this);
    painter.translate(FREESPACE - findMostLeft()*WIDTH_SCALE, FREESPACE); //TODO: Test_2.xml is not showing up correctly
    for(auto& rect : this->_results.bestPlacement)
    {
        auto tl = rect.second->TopLeft();
        auto var = rect.second->GetVariant();
        auto TLX = tl.X*WIDTH_SCALE;
        auto TLY = tl.Y*HEIGHT_SCALE;
        QRect qrect(TLX, TLY, var->GetWidth() * WIDTH_SCALE, var->GetHeight() * HEIGHT_SCALE);

        painter.drawRect(qrect);


        painter.drawText(qrect, Qt::AlignCenter, QString::fromStdString(rect.first->GetName()));
        QString horizontal(" " + QString::number(var->GetWidth()));
        QString vertical(" " + QString::number(var->GetHeight()));
        painter.drawText(qrect, Qt::AlignHCenter | Qt::AlignBottom, horizontal);
        painter.drawText(qrect, Qt::AlignVCenter, vertical);
    }
}

void ConfigurationPlane::setResults(FPA::ResultStruct results)
{
    this->_results = results;
}
