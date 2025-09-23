#ifndef PROMELOWINDOW_H
#define PROMELOWINDOW_H

#include "promeloeditorpanel.h"

#include <QMainWindow>

namespace Ui {
class PromeloWindow;
}

class PromeloWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PromeloWindow(QWidget *parent = nullptr);
    ~PromeloWindow();

private slots:


    void on_btnFileManager_clicked();

    void on_btnSearchManager_clicked();

    void on_actionSave_triggered();

    void on_actionNew_File_triggered();

private:
    Ui::PromeloWindow *ui;
    PromeloEditorPanel *eidtPanel;
};

#endif // PROMELOWINDOW_H
