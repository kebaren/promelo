#ifndef PROMELOEDITOR_H
#define PROMELOEDITOR_H

#include <QObject>
#include <QWidget>

#include "Scintilla.h"
#include "ScintillaEdit.h"

class PromeloEditor : public ScintillaEdit
{
    Q_OBJECT
public:
    PromeloEditor(QWidget *parent=0);
    ~PromeloEditor();

private:
    void initConfig();
    void updateLineNumberMargin();

private slots:


private:




};

#endif // PROMELOEDITOR_H
