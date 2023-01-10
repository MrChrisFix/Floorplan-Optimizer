#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Algorithm/Variant.h"
#include "Algorithm/AlgorithmManager.h"
#include "resultDialog.h"
#include "optOptionsDialog.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    ResultDialog* resultDialog;
    OptOptionsDialog* optionsDialog;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

private slots:
    void ChangeTypeComboBox(FPA::Variant* var);
    void onRequirementAdd();
    void onRequirementRemove(QString);
    void onStartOptimization();
    void FindOptimal();

    void importXML();
    void exportXML();
    void onNewAction();
    void onTypeDelete();

private:
    Ui::MainWindow *ui;
    void setupTheWindow();
    void makeConnections();
};
#endif // MAINWINDOW_H
