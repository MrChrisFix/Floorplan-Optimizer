#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Algorithm/Variant.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

private slots:
    void ChangeTypeComboBox(Alg::Variant* var);
    void onRequirementAdd();
    void onRequirementRemove(QString);

    void importXML();
    void exportXML();

private:
    Ui::MainWindow *ui;
    void setupTheWindow();
    void makeConnections();
};
#endif // MAINWINDOW_H
