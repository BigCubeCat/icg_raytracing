#pragma once

#include <qboxlayout.h>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <QActionGroup>
#include <QPlainTextEdit>
#include <QWidget>
#include "code.hpp"
#include "highlighter.hpp"

class Editor : public QWidget {
    Q_OBJECT

   public:
    explicit Editor(QWidget* parent = nullptr);

   private:
    std::shared_ptr<CodeEditor> m_text_edit;
    std::shared_ptr<SyntaxHighlighter> m_highlighter;
    QVBoxLayout m_layout;
};
