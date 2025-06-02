#include "editor.hpp"
#include <qboxlayout.h>
#include "code.hpp"

Editor::Editor(QWidget* parent) : QWidget(parent) {
    m_text_edit = std::make_shared<CodeEditor>(this);
    m_highlighter =
        std::make_shared<SyntaxHighlighter>(m_text_edit->document());
    m_layout.addWidget(m_text_edit.get());
    setLayout(&m_layout);
    m_text_edit->setStyleSheet(R"(
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
