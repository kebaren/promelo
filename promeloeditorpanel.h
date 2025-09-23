#ifndef PROMELOEDITORPANEL_H
#define PROMELOEDITORPANEL_H

#include <QObject>
#include <QMdiArea>
#include "promeloeditor.h"

class PromeloEditorPanel : public QMdiArea
{
    Q_OBJECT
public:
    PromeloEditorPanel(QWidget *parent = nullptr);
    bool newEmptyEditor();
    void saveFile(const QString &filePath);
private:
    void initConfig();


protected:
    //rewrite mouse double click
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    PromeloEditor *editor;
};

#endif // PROMELOEDITORPANEL_H
