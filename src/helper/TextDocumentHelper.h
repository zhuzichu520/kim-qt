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
    Q_PROPERTY_AUTO(int,emoticonSize)
public:
    explicit TextDocumentHelper(QObject *parent = nullptr);
    ~TextDocumentHelper();
    QTextDocument *textDocument() const;
    QTextCursor textCursor() const;
    Q_INVOKABLE void insertImage(const QString& url);
    Q_INVOKABLE QString rawText();
    Q_SIGNAL void insertTextChanged(QString text);
    QString toRawText(int start,int end);
};

#endif // TEXTDOCUMENTHELPER_H
