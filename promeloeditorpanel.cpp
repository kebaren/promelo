#include "promeloeditorpanel.h"

#include <QTabBar>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QDebug>
#include <QMouseEvent>
#include <QMessageBox>

PromeloEditorPanel::PromeloEditorPanel(QWidget *parent) {
    newEmptyEditor();
    initConfig();
    initSlots();

}

bool PromeloEditorPanel::newEmptyEditor()
{
    editor = new PromeloEditor();
    editor->setWindowTitle(tr("Untitled"));
    addSubWindow(editor);
    editor->show();
    return true;
}

void PromeloEditorPanel::saveFile(const QString &filePath)
{

}


void PromeloEditorPanel::initConfig()
{
    //tab show
    setViewMode(QMdiArea::TabbedView);
    setTabsClosable(true);
    setTabsMovable(true);
    setDocumentMode(true);

    tabBar = findChild<QTabBar *>();
    tabBar->setExpanding(false);
    tabBar->setStyleSheet("QMdiArea>QTabBar::tab{text-align:left;min-width:80px;max-width:200px}");
    tabBar->setUsesScrollButtons(true);

}

void PromeloEditorPanel::initSlots()
{
    connect(tabBar,&QTabBar::tabCloseRequested,this,&PromeloEditorPanel::closeTab);
}

void PromeloEditorPanel::closeTab()
{
    int index  = tabBar->currentIndex();
    PromeloEditor *editor = static_cast<PromeloEditor*>(currentSubWindow()->widget());

    if(!editor->isFileSaed()){

        // save file
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Comfirm Close"), tr("This file is not saved, did you want to save this file?"),
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            editor->saveFile();

        }
        if(editor->isFileFirstSaved()){

        }
    }


}

void PromeloEditorPanel::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug()<<"clicke mdi...."<<event->pos();
//     QTabBar *tabBar = findChild<QTabBar *>();

//     if(tabBar && tabBar->isVisible())
//     {
//         //trans point
//         QPoint tabBarPos = tabBar->mapFromParent(event->pos());
//         if(tabBar->tabAt(tabBarPos)==-1){
//             qDebug()<<"clicke...."<<event->pos();
//             newEmptyEditor();
//             event->accept();
//         }
//     }

//     QMdiArea::mouseDoubleClickEvent(event);
}
