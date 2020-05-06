#pragma once

#include <QPlainTextEdit>

class Editor final : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth();
    void updateLineNumberArea(QRect rect, int dy);

private:
    QWidget *m_lineNumberArea;
};

class LineNumberArea : public QWidget
{
    Q_OBJECT

public:
    LineNumberArea(Editor *editor)
        : QWidget(editor)
        , m_codeEditor{editor}
    {}

    QSize sizeHint() const override { return QSize(m_codeEditor->lineNumberAreaWidth(), 0); }

protected:
    void paintEvent(QPaintEvent *event) override { m_codeEditor->lineNumberAreaPaintEvent(event); }

private:
    Editor *m_codeEditor;
};
