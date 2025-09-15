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
    //update line margin width
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
    int width = textWidth + 4;

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
    //utf8 setting
    send(SCI_SETCODEPAGE, SC_CP_UTF8);

    //setting line number initialial
    send(SCI_SETMARGINTYPEN,0,SC_MARGIN_NUMBER);
    send(SCI_SETMARGINWIDTHN,0,20);
    //line number area style
    send(SCI_STYLESETBACK,STYLE_LINENUMBER,qRgb(255,255,255));

    //auto caculate the margin width
    //get total line count
    lastLineCount = std::log10(send(SCI_GETLINECOUNT));
    //delay to apply change margin width
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

qint64 PromeloEditor::getLineCount()
{
    return send(SCI_GETLINECOUNT);
}

qint64 PromeloEditor::getCurrentLineIndex()
{
    return send(SCI_GETCURLINE);
}

QString PromeloEditor::getTextFromPosition(qint64 startlen, qint64 endlen)
{
    QString result {"0"};
    qint64 charCount = getTextLength();

    if(startlen<0) startlen=0;
    if(startlen>charCount) return result;
    if(endlen <0) return result;

    char *buffer = new char[endlen-startlen+1];
    if(endlen>charCount) endlen = charCount;
    Sci_TextRange srange;
    srange.chrg.cpMin = startlen;
    srange.chrg.cpMax = endlen;
    srange.lpstrText = buffer;
    send(SCI_GETTEXTRANGE,0,(sptr_t)&srange);
    result = QString::fromUtf8(buffer,endlen-startlen+1);
    qDebug()<<"buffer:"<<buffer;
    delete []buffer;
    return result;
}

qint64 PromeloEditor::getTextLength()
{
    return send(SCI_GETTEXTLENGTH);
}


bool PromeloEditor::saveFile(const QString &filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly| QIODevice::Text)){
        return false;
    }
    QTextStream inFile(&file);
    inFile.setCodec("UTF-8");
    int totalLen = getTextLength();
    int bufferLen = 4096;
    QString str;
    qint64 index = 0;
    // while(totalLen>0){
    //     str = getTextFromPosition(index,index+bufferLen);
    //     inFile<<str;
    //     index += bufferLen;
    //     totalLen -= index;
    //     inFile.flush();
    // }
    const char *utf8Data = reinterpret_cast<const char*>(send(SCI_GETCHARACTERPOINTER));
    str = QString::fromUtf8(utf8Data);
    qDebug()<<"file:"<<str;
    inFile<<str;
    file.close();
    return true;
}

