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

void TextDocumentHelper::copy(){
    auto cursor = textCursor();
    int startSelection = cursor.selectionStart();
    int endSelection = cursor.selectionEnd();
    QString text = toRawText(startSelection,endSelection);
    if(text.isEmpty()){
        return;
    }
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(text);
}

QString TextDocumentHelper::rawText(){
    auto doc = textDocument();
    return toRawText(0,doc->characterCount()-1);
}

QString TextDocumentHelper::toRawText(int start,int end){
    auto doc = textDocument();
    QString text;
    int index = 0;
    for(QTextBlock it = doc->begin();it != doc->end();it =it.next()){
        QTextBlock::iterator iterator;
        for (iterator = it.begin(); !(iterator.atEnd()); ++iterator) {
            QTextFragment fragment = iterator.fragment();
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
    }
    return text;
}

void TextDocumentHelper::cut(){
    copy();
    textCursor().removeSelectedText();
}

void TextDocumentHelper::paste(){
    const QClipboard *clipboard = QGuiApplication::clipboard();
    const QMimeData *mimeData = clipboard->mimeData();
    if (mimeData->hasImage()) {
        qDebug()<<"Cannot display image data";
    } else if (mimeData->hasHtml()) {
        Q_EMIT insertTextChanged(mimeData->text());
    } else if (mimeData->hasText()) {
        Q_EMIT insertTextChanged(mimeData->text());
    } else {
        qDebug()<<"Cannot display ohter data";
    }
}
