#include "code.hpp"

CodeEditor::CodeEditor(QWidget* parent) : QPlainTextEdit(parent) {
    m_line_number_area = std::unique_ptr<QWidget>(new LineNumberArea(this));

    connect(this, &CodeEditor::blockCountChanged, this,
            &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this,
            &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this,
            &CodeEditor::highlightCurrentLine);

    updateLineNumberAreaWidth();
    highlightCurrentLine();
}

int CodeEditor::lineNumberAreaWidth() {
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }
    return 3 + (fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits);
}

void CodeEditor::updateLineNumberAreaWidth() {
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect& rect, int dy) {
    if (dy) {
        m_line_number_area->scroll(0, dy);
    } else {
        m_line_number_area->update(0, rect.y(), m_line_number_area->width(),
                                   rect.height());
    }

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth();
}

void CodeEditor::resizeEvent(QResizeEvent* event) {
    QPlainTextEdit::resizeEvent(event);
    QRect cr = contentsRect();
    m_line_number_area->setGeometry(
        QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent* event) {
    QPainter painter(m_line_number_area.get());
    painter.fillRect(event->rect(), QColor(240, 240, 240));

    QTextBlock block = firstVisibleBlock();
    int block_number = block.blockNumber();
    int top = static_cast<int>(
        blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + static_cast<int>(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(block_number + 1);
            painter.setPen(QColor(100, 100, 100));
            painter.drawText(0, top, m_line_number_area->width() - 3,
                             fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + static_cast<int>(blockBoundingRect(block).height());
        ++block_number;
    }
}

void CodeEditor::highlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extra_selections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        QColor line_color = QColor(Qt::yellow).lighter(160);
        selection.format.setBackground(line_color);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extra_selections.append(selection);
    }

    setExtraSelections(extra_selections);
}

void CodeEditor::keyPressEvent(QKeyEvent* event) {
    QPlainTextEdit::keyPressEvent(event);
}
