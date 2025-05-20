#pragma once

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
    CodeEditor* textEdit;
    SyntaxHighlighter* highlighter;
};
