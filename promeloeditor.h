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

    //file saved status
    bool isFileSaed();
    bool saveFile();
    bool isFileFirstSaved();

private:
    void initConfig();
    void updateLineNumberMargin();


private slots:


private:
    bool m_isFileSaved = false;
    bool m_isFileFirstSvaed = false;



};

#endif // PROMELOEDITOR_H
