#include "promeloeditorpanel.h"

#include <QTabBar>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QDebug>

PromeloEditorPanel::PromeloEditorPanel(QWidget *parent) {
    newEmptyEditor();
    initConfig();
}

bool PromeloEditorPanel::newEmptyEditor()
{
    editor = new PromeloEditor();
    editor->setWindowTitle(tr("New File"));
    addSubWindow(editor);
    return true;
}

void PromeloEditorPanel::saveFile(const QString &filePath)
{
    editor->saveFile(filePath);
}


void PromeloEditorPanel::initConfig()
{
    //tab show
    setViewMode(QMdiArea::TabbedView);
    setTabsClosable(true);
    setTabsMovable(true);
    //setDocumentMode(true);

    QTabBar *tab = findChild<QTabBar *>();
    tab->setExpanding(false);
    tab->setStyleSheet("QMdiArea>QTabBar::tab{text-align:left;min-width:80px;max-width:200px}");
    tab->setUsesScrollButtons(true);
}
