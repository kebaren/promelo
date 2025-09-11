#include "promeloeditorpanel.h"

#include <QTabBar>

PromeloEditorPanel::PromeloEditorPanel(QWidget *parent) {
    newEmptyEditor();
    config();
}

bool PromeloEditorPanel::newEmptyEditor()
{
    editor = new PromeloEditor(this);
    editor->setWindowTitle(tr("New File if you want to use but i can tel you"));
    addSubWindow(editor);
    return true;
}


void PromeloEditorPanel::config()
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
