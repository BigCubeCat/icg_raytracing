#pragma once

#include <QRegularExpression>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class SyntaxHighlighter : public QSyntaxHighlighter {
    Q_OBJECT

   public:
    explicit SyntaxHighlighter(QTextDocument* parent = nullptr);

   protected:
    void highlightBlock(const QString& text) override;

   private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    void setupRules();

    QTextCharFormat keywordFormat;
    QTextCharFormat parameterFormat;
    QTextCharFormat qualityFormat;
    QTextCharFormat numberFormat;
    QTextCharFormat commentFormat;
};
