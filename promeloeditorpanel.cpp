#include "promeloeditorpanel.h"

#include <QTabBar>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QDebug>
#include <QMouseEvent>

PromeloEditorPanel::PromeloEditorPanel(QWidget *parent) {
    newEmptyEditor();
    initConfig();

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

    QTabBar *tab = findChild<QTabBar *>();
    tab->setExpanding(false);
   // tab->setStyleSheet("QMdiArea>QTabBar::tab{text-align:left;min-width:80px;max-width:200px}");
    tab->setUsesScrollButtons(true);

}

void PromeloEditorPanel::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug()<<"clicke mdi...."<<event->pos();
    QTabBar *tabBar = findChild<QTabBar *>();

    if(tabBar && tabBar->isVisible())
    {
        //trans point
        QPoint tabBarPos = tabBar->mapFromParent(event->pos());
        if(tabBar->tabAt(tabBarPos)==-1){
            qDebug()<<"clicke...."<<event->pos();
            newEmptyEditor();
            event->accept();
        }
    }

    QMdiArea::mouseDoubleClickEvent(event);
}
