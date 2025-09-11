#include "promeloeditor.h"

#include <QRGB>

PromeloEditor::PromeloEditor(QWidget *parent) {

    initConfig();
}

PromeloEditor::~PromeloEditor()
{

}

void PromeloEditor::initConfig()
{
    //setting line number
    send(SCI_SETMARGINTYPEN,1,SC_MARGIN_NUMBER);
    send(SCI_SETMARGINWIDTHN,1,40);
    send(SCI_SETMARGINMASKN,0,SC_MASK_FOLDERS);
    send(SCI_SETMARGINSENSITIVEN,0,1);

    //line number area style
    send(SCI_STYLESETBACK,STYLE_LINENUMBER,qRgb(255,255,255));
}

void PromeloEditor::showLineNumber(bool shown)
{
}
