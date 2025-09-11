#ifndef PROMELOEDITOR_H
#define PROMELOEDITOR_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>

#include "Scintilla.h"
#include "ScintillaEditBase.h"

class CoreEditor;

class PromeloEditor : public ScintillaEditBase
{
    Q_OBJECT
public:
    PromeloEditor(QWidget *parent=0);
    ~PromeloEditor();
    //hide or show line number
    void showLineNumber(bool shown);
private:
    void initConfig();
private:


    void RGB(int, int, int);
};

#endif // PROMELOEDITOR_H
