// syntaxhighlighter.cpp
#include "highlighter.hpp"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument* parent)
    : QSyntaxHighlighter(parent) {
    // Настройка цветов и стилей
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);

    parameterFormat.setForeground(QColor(42, 130, 218));

    qualityFormat.setForeground(Qt::darkGreen);
    qualityFormat.setFontItalic(true);

    numberFormat.setForeground(QColor(255, 165, 0));

    commentFormat.setForeground(Qt::gray);
    commentFormat.setFontItalic(true);

    setupRules();
}

void SyntaxHighlighter::setupRules() {
    // Комментарии
    HighlightingRule commentRule;
    commentRule.pattern = QRegularExpression("//[^\n]*");
    commentRule.format = commentFormat;
    highlightingRules.append(commentRule);

    // Ключевые слова
    QStringList keywordPatterns = {
        "\\bSPHERE\\b", "\\bBOX\\b",   "\\bTRIANGLE\\b", "\\bQUADRANGLE\\b",
        "\\bGAMMA\\b",  "\\bDEPTH\\b", "\\bQUALITY\\b",  "\\bZN\\b",
        "\\bZF\\b",     "\\bSW\\b",    "\\bSH\\b",       "\\bRADIUS\\b",
        "\\bPower\\b"};

    for (const QString& pattern : keywordPatterns) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // Параметры с суффиксами
    HighlightingRule paramRule;
    paramRule.pattern = QRegularExpression(
        "\\b(Br|Bg|Bb|EYE[xyz]|VIEW[xyz]|UP[xyz]|"
        "CENTER[xyz]|MIN[xyz]|MAX[xyz]|POINT[1-4][xyz]|"
        "KDr|KDg|KDb|KSr|KSg|KSb)\\b");
    paramRule.format = parameterFormat;
    highlightingRules.append(paramRule);

    // Значения качества
    HighlightingRule qualityRule;
    qualityRule.pattern = QRegularExpression("\\b(rough|normal|fine)\\b");
    qualityRule.format = qualityFormat;
    highlightingRules.append(qualityRule);

    // Числа (включая отрицательные и десятичные)
    HighlightingRule numberRule;
    numberRule.pattern =
        QRegularExpression("[-+]?\\d+(\\.\\d+)?([eE][-+]?\\d+)?");
    numberRule.format = numberFormat;
    highlightingRules.append(numberRule);
}

void SyntaxHighlighter::highlightBlock(const QString& text) {
    for (const auto& rule : highlightingRules) {
        QRegularExpressionMatchIterator it = rule.pattern.globalMatch(text);
        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            setFormat(match.capturedStart(), match.capturedLength(),
                      rule.format);
        }
    }
}
