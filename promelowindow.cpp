#include "promelowindow.h"
#include "ui_promelowindow.h"
#include <QTabBar>
#include <QFileDialog>

PromeloWindow::PromeloWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PromeloWindow)
{
    ui->setupUi(this);
    //seetings window flags


    eidtPanel = new PromeloEditorPanel(this);
    //manger tab hide
    ui->ManagerPanel->tabBar()->hide();
    ui->ManagerPanel->hide();
    ui->rightPanel->hide();
    ui->TerminalPanel->hide();
    ui->containerLayout->addWidget(eidtPanel);


}

PromeloWindow::~PromeloWindow()
{
    delete ui;
}



void PromeloWindow::on_btnFileManager_clicked()
{
    // ui->ManagerPanel_2->setCurrentIndex(0);
    // if(ui->splManger2Container->sizes().first() > 0){

    // }else{
    //     ui->ManagerPanel->setVisible(true);
    //     ui->ManagerPanel->setFixedWidth(200);
    // }

}


void PromeloWindow::on_btnSearchManager_clicked()
{
    // ui->ManagerPanel->setCurrentIndex(2);
    // if(ui->splManger2Container->sizes().first() > 0){

    // }else{
    //     ui->ManagerPanel->setVisible(true);
    //     ui->ManagerPanel->setFixedWidth(200);
    // }
}


void PromeloWindow::on_actionSave_triggered()
{
    QString path = QFileDialog::getSaveFileName(this,tr("save file"),tr("untiled"),tr("C++ File(*.cpp *.h *.cxx *.hpp);C File(*.c *.h)"));
    eidtPanel->saveFile(path);

}


void PromeloWindow::on_actionNew_File_triggered()
{
    eidtPanel->newEmptyEditor();
}


void PromeloWindow::on_actionExit_triggered()
{
    close();
}

