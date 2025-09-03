#include "promeloeditor.h"

PromeloEditor::PromeloEditor(QWidget *parent) {
    layout = new QVBoxLayout();
    editor = new CoreEditor();
    layout->addWidget(editor);
    setLayout(layout);
}

CoreEditor::CoreEditor(QWidget *parent)
{
    send(SCI_SETMARGINTYPEN,1,SC_MARGIN_NUMBER);
    send(SCI_SETMARGINWIDTHN,1,60);
}
