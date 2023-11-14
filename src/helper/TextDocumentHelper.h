#ifndef TEXTDOCUMENTHELPER_H
#define TEXTDOCUMENTHELPER_H

#include <QObject>
#include <QQuickTextDocument>
#include <stdafx.h>

class TextDocumentHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY_AUTO(QQuickTextDocument*,document)
    Q_PROPERTY_AUTO(int,cursorPosition)
    Q_PROPERTY_AUTO(int,selectionStart)
    Q_PROPERTY_AUTO(int,selectionEnd)
public:
    explicit TextDocumentHelper(QObject *parent = nullptr);
    QTextDocument *textDocument() const;
    QTextCursor textCursor() const;
    Q_INVOKABLE void insertImage(const QString& url);
    Q_SLOT void handleEmojiText();
};

#endif // TEXTDOCUMENTHELPER_H
