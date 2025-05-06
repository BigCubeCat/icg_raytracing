#include "editor.hpp"
#include <qboxlayout.h>

Editor::Editor(QWidget* parent)
    : QWidget(parent),
      m_text_edit(this),
      m_highlighter(m_text_edit.document()) {
    m_layout.addWidget(&m_text_edit);
    setLayout(&m_layout);

    m_text_edit.setStyleSheet(
        "QPlainTextEdit { font-family: Consolas; font-size: 12pt; }");
}
