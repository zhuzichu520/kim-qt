#include "TextDocumentHelper.h"

#include <QTextCursor>
#include <QDebug>

TextDocumentHelper::TextDocumentHelper(QObject *parent)
    : QObject{parent}
{
    _document = nullptr;
    connect(this,&TextDocumentHelper::documentChanged,this,[this]{
        if(_document){
            connect(_document->textDocument(),&QTextDocument::contentsChanged,this,&TextDocumentHelper::handleEmojiText);
        }
    });
}

void TextDocumentHelper::handleEmojiText(){
    disconnect(_document->textDocument(),&QTextDocument::contentsChanged,this,&TextDocumentHelper::handleEmojiText);
    insertImage("qrc:/res/image/emoji/emoji_01.png");
    connect(_document->textDocument(),&QTextDocument::contentsChanged,this,&TextDocumentHelper::handleEmojiText);
}

QTextDocument* TextDocumentHelper::textDocument() const
{
    if (_document)
        return _document->textDocument();
    else return nullptr;
}

QTextCursor TextDocumentHelper::textCursor() const
{
    QTextDocument *doc = textDocument();
    if (!doc)
        return QTextCursor();
    QTextCursor cursor = QTextCursor(doc);
    if (_selectionStart != _selectionEnd)
    {
        cursor.setPosition(_selectionStart);
        cursor.setPosition(_selectionEnd, QTextCursor::KeepAnchor);
    }
    else
    {
        cursor.setPosition(_cursorPosition);
    }

    return cursor;
}

void TextDocumentHelper::insertImage(const QString& url){
    QTextImageFormat format;
    format.setName(url);
    format.setWidth(20);
    format.setHeight(20);
    textCursor().insertImage(format, QTextFrameFormat::InFlow);
}
