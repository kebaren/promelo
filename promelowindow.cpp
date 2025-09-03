#include "promelowindow.h"
#include "ui_promelowindow.h"
#include <QTabBar>

PromeloWindow::PromeloWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PromeloWindow)
{
    ui->setupUi(this);
    eidtPanel = new PromeloEditorPanel(this);
    //manger tab hide
    ui->ManagerPanel->tabBar()->hide();
    ui->EditSplitter->insertWidget(0,eidtPanel);

}

PromeloWindow::~PromeloWindow()
{
    delete ui;
}



void PromeloWindow::on_btnFileManager_clicked()
{
    ui->ManagerPanel->setCurrentIndex(0);
    if(ui->Manager2Editor->sizes().first() > 0){

    }else{
        ui->ManagerPanel->setVisible(true);
        ui->ManagerPanel->setFixedWidth(200);
    }

}


void PromeloWindow::on_btnSearchManager_clicked()
{
    ui->ManagerPanel->setCurrentIndex(2);
    if(ui->Manager2Editor->sizes().first() > 0){

    }else{
        ui->ManagerPanel->setVisible(true);
        ui->ManagerPanel->setFixedWidth(200);
    }
}

