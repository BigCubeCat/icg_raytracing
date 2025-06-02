#include "editor.hpp"
#include <qboxlayout.h>
#include <QDebug>
#include <memory>
#include "code.hpp"
#include "model.hpp"

Editor::Editor(DataModel* data, QWidget* parent)
    : QWidget(parent), m_data(data) {
    m_text_edit = std::make_shared<CodeEditor>(this);
    m_highlighter =
        std::make_shared<SyntaxHighlighter>(m_text_edit->document());
    m_layout = std::make_shared<QVBoxLayout>();
    m_layout->addWidget(m_text_edit.get());
    setLayout(m_layout.get());
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
    connect(m_text_edit.get(), &QPlainTextEdit::textChanged, this,
            &Editor::apply);
}

void Editor::set_text(const QString& code) {
    m_text_edit->setPlainText(code);
}

void Editor::apply() {
    std::string text = m_text_edit->toPlainText().toStdString();
    m_parser.set_text(text);
    if (m_parser.is_valid()) {
        auto objects = m_parser();
        qDebug() << "count objects = " << objects.size();
        m_data->set_objects(std::move(objects));
        emit new_objects();
    }
}
