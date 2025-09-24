#include "promeloeditor.h"
#include "Scintilla.h"

#include <QRGB>
#include <cmath>
#include <QDebug>
#include <QTimer>
#include <algorithm>
#include <QFileDialog>
#include <QtConcurrent/QtConcurrent>


PromeloEditor::PromeloEditor(QWidget *parent) {


    initConfig();


}

PromeloEditor::~PromeloEditor()
{

}

void PromeloEditor::initConfig()
{
    //utf8 setting
    setCodePage(SC_CP_UTF8);

    //setting line number initialial
    setMarginWidthN(0,20);
    //line number auto adjust
    connect(this, &PromeloEditor::notify, this, &PromeloEditor::updateLineNumberMargin);

}


void PromeloEditor:: updateLineNumberMargin()
{
    int lineCounts = lineCount();
    int linePixelWidth = (std::max<int>(std::log10(lineCounts),3)+1) *textWidth(STYLE_LINENUMBER,"8")+8;
    setMarginWidthN(0,linePixelWidth);
}

bool PromeloEditor::isFileSaed()
{
    return m_isFileSaved;
}

bool PromeloEditor::saveFile()
{
    QString dir = QCoreApplication::applicationDirPath();
    QString FilePath = QFileDialog::getSaveFileName(this,tr("Save File"),dir,tr("c++ File(*.cpp *.h *.cxx *.hpp)"));

    if(FilePath.isEmpty()){
        return false;
    }
    return true;
}

bool PromeloEditor::isFileFirstSaved()
{
    return m_isFileFirstSvaed;
}


