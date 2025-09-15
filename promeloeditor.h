#ifndef PROMELOEDITOR_H
#define PROMELOEDITOR_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QTimer>
#include <QThread>

#include "Scintilla.h"
#include "ScintillaEditBase.h"

class PromeloEditor : public ScintillaEditBase
{
    Q_OBJECT
public:
    PromeloEditor(QWidget *parent=0);
    ~PromeloEditor();
    //hide or show line number
    void showLineNumber(bool shown);
    //set font
    void setFontFamily(QFont *font);
private:
    void initConfig();
    void updateLineNumberMargin();


private slots:
    void anjustLineMargin(Scintilla::ModificationFlags type, Scintilla::Position position, Scintilla::Position length, Scintilla::Position linesAdded,const QByteArray &text, Scintilla::Position line, Scintilla::FoldLevel foldNow, Scintilla::FoldLevel foldPrev);

private slots:

private:
    QTimer *timer;
    QThread *workerThread;
    qint64 lastLineCount= 0;


};

#endif // PROMELOEDITOR_H
