#include "TextDocumentHelper.h"

#include <QTextCursor>
#include <QDebug>
#include <QGuiApplication>
#include <QClipboard>
#include <QPainter>
#include <QTextBlock>
#include <QMimeData>
#include <helper/EmoticonHelper.h>

TextDocumentHelper::TextDocumentHelper(QObject *parent)
    : QObject{parent}
{
    _document = nullptr;
}

TextDocumentHelper::~TextDocumentHelper(){

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

QString TextDocumentHelper::rawText(){
    auto doc = textDocument();
    return toRawText(0,doc->characterCount()-1);
}

QString TextDocumentHelper::toRawText(int start,int end){
    auto doc = textDocument();
    QString text;
    QTextBlock block = doc->begin();
    int index = 0;
    while (block.isValid()) {
        for (QTextBlock::iterator it = block.begin(); !it.atEnd(); ++it) {
            QTextFragment fragment = it.fragment();
            QTextCharFormat format = fragment.charFormat();
            if(format.isImageFormat()){
                QTextImageFormat imageFormat = format.toImageFormat();
                for (int var = 0; var < fragment.length(); var++) {
                    if(index>=start && index < end){
                        text.append(EmoticonHelper::getInstance()->getTagByUrl(imageFormat.name()));
                    }
                    index++;
                }
            }else{
                auto s = fragment.text();
                for (int var = 0; var < fragment.length(); var++) {
                    if(index>=start && index < end){
                        text.append(s.at(var));
                    }
                    index++;
                }
            }
        }
        if(doc->lastBlock() != block){
            text.append("\n");
        }
        block = block.next();
    }
    return text;
}
