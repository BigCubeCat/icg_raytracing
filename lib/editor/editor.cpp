#include "editor.hpp"
#include <qboxlayout.h>
#include "code.hpp"

Editor::Editor(QWidget* parent) : QWidget(parent) {
    textEdit = new CodeEditor(this);
    highlighter = new SyntaxHighlighter(textEdit->document());

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(textEdit);
    setLayout(layout);

    textEdit->setStyleSheet(R"(
        CodeEditor {
            font-family: Consolas;
            font-size: 12pt;
            background-color: #fffff8;
        }
        QScrollBar:vertical {
            width: 12px;
        }
    )");
}
