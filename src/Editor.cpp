#include "Editor.hpp"

#include <QPainter>
#include <QTextBlock>

Editor::Editor(QWidget *parent)
    : QPlainTextEdit(parent)
    , m_lineNumberArea{new LineNumberArea(this)}
{
    connect(this, &Editor::updateRequest, this, &Editor::updateLineNumberArea);

    updateLineNumberAreaWidth();
}

void Editor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(m_lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0,
                             top,
                             m_lineNumberArea->width(),
                             fontMetrics().height(),
                             Qt::AlignRight,
                             number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

constexpr static auto ten = 10;
constexpr static auto marginForRedability = 5;

int Editor::lineNumberAreaWidth()
{
    const auto s = QString::number(blockCount());
    return marginForRedability + fontMetrics().horizontalAdvance(QLatin1Char('9')) * s.size();
}

void Editor::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    QRect cr = contentsRect();
    m_lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void Editor::updateLineNumberAreaWidth()
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void Editor::updateLineNumberArea(QRect rect, int dy)
{
    dy ? m_lineNumberArea->scroll(0, dy)
       : m_lineNumberArea->update(0, rect.y(), m_lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect())) {
        updateLineNumberAreaWidth();
    }
}
