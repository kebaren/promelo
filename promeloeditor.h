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

    //get line count
    qint64 getLineCount();
    //get current line
    qint64 getCurrentLineIndex();
    QString getTextFromPosition(qint64 startlen, qint64 endlen);
    qint64 getTextLength();
    //save file
    bool saveFile(const QString &filePath);
private:
    void initConfig();
    void updateLineNumberMargin();
    void resizeEvent(QResizeEvent *event)override;


private slots:
    void adjustLineMargin(Scintilla::ModificationFlags type, Scintilla::Position position, Scintilla::Position length, Scintilla::Position linesAdded,const QByteArray &text, Scintilla::Position line, Scintilla::FoldLevel foldNow, Scintilla::FoldLevel foldPrev);
    void updateUiMargin(Scintilla::Update updated);
private slots:

private:
    QTimer *timer;

    //last line margin width
    qint64 lastLineCount= 0;
    int count=0;


};

#endif // PROMELOEDITOR_H
