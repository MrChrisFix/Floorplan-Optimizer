#ifndef CONFIGURATIONPLANE_H
#define CONFIGURATIONPLANE_H

#include "Algorithm/resultStruct.h"
#include <QWidget>

class ConfigurationPlane : public QWidget
{
    Q_OBJECT
private:
    FPA::ResultStruct _results;

public:
    explicit ConfigurationPlane(QWidget *parent = nullptr);
    ~ConfigurationPlane();

    void setResults(FPA::ResultStruct results);

protected:
    void paintEvent(QPaintEvent *event) override;

signals:

};

#endif // CONFIGURATIONPLANE_H
