#ifndef RENDERAREA_H
#define RENDERAREA_H

#include "qlineedit.h"
#include <QWidget>

class RenderArea : public QWidget
{
    Q_OBJECT
private:
    float length, height;
    float drawLenght, drawHeight;
    float MAXDRAWSIZE;                  /// The maximal side size of the drawn rectangle
    QLineEdit *widthBox, *heightBox;

public:
    explicit RenderArea(QWidget *parent = nullptr);
    void setLength(float newLength);
    void setHeight(float newHeight);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent * event) override;
private:
    void reshapeAndDraw();

signals:

};

#endif // RENDERAREA_H
