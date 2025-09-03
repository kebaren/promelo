#include "promeloeditorpanel.h"

#include <QTabBar>

PromeloEditorPanel::PromeloEditorPanel(QWidget *parent) {

    for(int i=0; i< 4; i++)
    {
         newEmptyEditor();
    }


    config();
}

bool PromeloEditorPanel::newEmptyEditor()
{
    editor = new PromeloEditor(this);
    editor->setWindowTitle(tr("New File"));
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
    //tab->setExpanding(false);
    tab->setStyleSheet("QTabBar::tab{min-width:80px;max-width:200px}");
    tab->setUsesScrollButtons(true);

}
