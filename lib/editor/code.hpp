#pragma once

#include <QPainter>
#include <QPlainTextEdit>
#include <QSyntaxHighlighter>
#include <QTextBlock>
#include <QTextEdit>
#include <QWidget>

class LineNumberArea;

class CodeEditor : public QPlainTextEdit {
    Q_OBJECT
   public:
    explicit CodeEditor(QWidget* parent = nullptr);
    void lineNumberAreaPaintEvent(QPaintEvent* event);
    int lineNumberAreaWidth();

   private:
    std::unique_ptr<QWidget> m_line_number_area;

   protected:
    void resizeEvent(QResizeEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

   private slots:
    void updateLineNumberAreaWidth();
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect& rect, int dy);
};

class LineNumberArea : public QWidget {
   public:
    explicit LineNumberArea(CodeEditor* editor)
        : QWidget(editor), m_code_editor(editor) {}

    QSize sizeHint() const override {
        return QSize(m_code_editor->lineNumberAreaWidth(), 0);
    }

   protected:
    void paintEvent(QPaintEvent* event) override {
        m_code_editor->lineNumberAreaPaintEvent(event);
    }

   private:
    CodeEditor* m_code_editor;
};
