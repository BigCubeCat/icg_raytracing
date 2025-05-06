#pragma once

#include <qboxlayout.h>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <QActionGroup>
#include <QPlainTextEdit>
#include <QWidget>

#include "highlighter.hpp"

class Editor : public QWidget {
    Q_OBJECT
   private:
    QPlainTextEdit m_text_edit;
    SyntaxHighlighter m_highlighter;

    QHBoxLayout m_layout;

   public:
    explicit Editor(QWidget* parent = nullptr);

    void line_number_area_paint_event(QPaintEvent* event);
    int line_number_area_width();
};

class LineNumberArea : public QWidget {
   public:
    explicit LineNumberArea(Editor* editor)
        : QWidget(editor), m_editor(editor) {}

    QSize sizeHint() const override {
        return QSize(m_editor->line_number_area_width(), 0);
    }

   protected:
    void paintEvent(QPaintEvent* event) override {
        m_editor->line_number_area_paint_event(event);
    }

   private:
    Editor* m_editor;
};
