#include "promeloeditor.h"
#include "Scintilla.h"

#include <QRGB>
#include <cmath>
#include <QDebug>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>

class PromeloEditor;

void PromeloEditor:: updateLineNumberMargin()
{

    //do not update
    qint64 totalLines = send(SCI_GETLINECOUNT);
    Scintilla::Position lineCount = std::log10(totalLines);
    if (lineCount == lastLineCount) {
        return;
    }
    lastLineCount = lineCount;
    int digits = 1;
    if (lineCount > 0) {
        digits = lineCount + 1;
    }
    char fontName[64];
    this->send(SCI_STYLEGETFONT, STYLE_LINENUMBER, reinterpret_cast<sptr_t>(fontName));
    int fontSize = static_cast<int>(send(SCI_STYLEGETSIZE, STYLE_LINENUMBER));
    bool bold = send(SCI_STYLEGETBOLD, STYLE_LINENUMBER);
    QFont font(QString::fromUtf8(fontName), fontSize);
    font.setBold(bold);
    QFontMetrics metrics(font);
    QString maxDigitStr = QString::number(totalLines);
    int textWidth = metrics.horizontalAdvance(maxDigitStr);
    int width = textWidth + 8;

    if (width < 20) {
        width = 20;
    }

    send(SCI_SETMARGINWIDTHN, 0, width);

}

void PromeloEditor::anjustLineMargin(Scintilla::ModificationFlags type, Scintilla::Position position, Scintilla::Position length, Scintilla::Position linesAdded, const QByteArray &text, Scintilla::Position line, Scintilla::FoldLevel foldNow, Scintilla::FoldLevel foldPrev)
{
    Q_UNUSED(position);
    Q_UNUSED(length);
    Q_UNUSED(text);
    Q_UNUSED(line);
    Q_UNUSED(foldNow);
    Q_UNUSED(foldPrev);

    // if(type == Scintilla::ModificationFlags::InsertText || type == Scintilla::ModificationFlags::DeleteText){
    //     timer->start();
    // }
    if(linesAdded != 0)    timer->start();

}

PromeloEditor::PromeloEditor(QWidget *parent) {


    initConfig();


}

PromeloEditor::~PromeloEditor()
{

}

void PromeloEditor::initConfig()
{
    //get total line count
    lastLineCount = std::log10(send(SCI_GETLINECOUNT));
    //setting line number
    send(SCI_SETMARGINTYPEN,0,SC_MARGIN_NUMBER);
    send(SCI_SETMARGINWIDTHN,0,20);

    //line number area style
    send(SCI_STYLESETBACK,STYLE_LINENUMBER,qRgb(255,255,255));

    timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(100);
    connect(this,&PromeloEditor::modified,this,&PromeloEditor::anjustLineMargin);
    connect(timer, &QTimer::timeout, this, &PromeloEditor::updateLineNumberMargin);

}

void PromeloEditor::showLineNumber(bool shown)
{
    if(shown){
        send(SCI_SETMARGINTYPEN,1,SC_MARGIN_NUMBER);
        send(SCI_SETMARGINWIDTHN,1,40);
    }else{
        send(SCI_SETMARGINTYPEN,0,SC_MARGIN_NUMBER);
        send(SCI_SETMARGINWIDTHN,0,0);

    }
}

void PromeloEditor::setFontFamily(QFont *font)
{
    send(SCI_STYLESETFONT,STYLE_DEFAULT,(sptr_t)font->family().toUtf8().data());
    send(SCI_STYLESETSIZE,STYLE_DEFAULT,font->pointSize());
}
