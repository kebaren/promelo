#ifndef PROMELOEDITOR_H
#define PROMELOEDITOR_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>

#include "Scintilla.h"
#include "ScintillaEditBase.h"

class CoreEditor;

class PromeloEditor:public QWidget
{
    Q_OBJECT
public:
    PromeloEditor(QWidget *parent=0);
private:
    CoreEditor *editor;
    QVBoxLayout *layout;
};

class CoreEditor : public ScintillaEditBase{

    Q_OBJECT
public:
    CoreEditor(QWidget *parent = 0);
};

#endif // PROMELOEDITOR_H
