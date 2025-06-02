#pragma once

#include <qboxlayout.h>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qpushbutton.h>
#include <QActionGroup>
#include <QPlainTextEdit>
#include <QWidget>
#include "../parser/parser.hpp"
#include "code.hpp"
#include "highlighter.hpp"

class Editor : public QWidget {
    Q_OBJECT
   private slots:
    void apply();

   public:
    explicit Editor(QWidget* parent = nullptr);

   private:
    std::shared_ptr<CodeEditor> m_text_edit;
    std::shared_ptr<SyntaxHighlighter> m_highlighter;
    Parser m_parser;
    std::shared_ptr<QVBoxLayout> m_layout;

   public slots:
    void set_text(const QString& code);
};
