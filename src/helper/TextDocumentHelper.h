#ifndef TEXTDOCUMENTHELPER_H
#define TEXTDOCUMENTHELPER_H

#include <QObject>
#include <QQuickTextDocument>
#include <stdafx.h>
#include <QRegularExpression>

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
    QTextDocument *textDocument() const;
    QTextCursor textCursor() const;
    Q_INVOKABLE void insertImage(const QString& url);
    Q_SLOT void handleEmojiText();
    Q_INVOKABLE void copy();
    Q_INVOKABLE void cut();
    Q_INVOKABLE QString rawText();
    QString toRawText(int start,int end);
private:
    QRegularExpression  _tagRegular;
    QString _prefix = "qrc:/res/image/emoji/";
};

#endif // TEXTDOCUMENTHELPER_H
