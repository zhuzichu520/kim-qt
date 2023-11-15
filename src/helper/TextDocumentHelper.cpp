#include "TextDocumentHelper.h"

#include <QTextCursor>
#include <QDebug>
#include <QGuiApplication>
#include <QClipboard>
#include <QTextBlock>
#include <helper/EmoticonHelper.h>

TextDocumentHelper::TextDocumentHelper(QObject *parent)
    : QObject{parent}
{
    emoticonSize(18);
    _document = nullptr;
    connect(this,&TextDocumentHelper::documentChanged,this,[this]{
        if(_document){
            connect(_document->textDocument(),&QTextDocument::contentsChanged,this,&TextDocumentHelper::handleEmojiText);
        }
    });
}

void TextDocumentHelper::handleEmojiText(){
    disconnect(textDocument(),&QTextDocument::contentsChanged,this,&TextDocumentHelper::handleEmojiText);
    QString text = textDocument()->toRawText();
    auto cursor = textCursor();
    QRegularExpressionMatchIterator it = EmoticonHelper::getInstance()->_tagRegular.globalMatch(text);
    int offset = 0;
    while (it.hasNext ()) {
        QRegularExpressionMatch match = it.next();
        int length = match.capturedLength ();
        int begin = match.capturedStart () + offset;
        cursor.setPosition(begin,QTextCursor::MoveAnchor);
        cursor.setPosition(begin+length,QTextCursor::KeepAnchor);
        QTextImageFormat format;
        auto tag = match.captured(1);
        format.setName(QString::fromStdString("%1%2").arg(EmoticonHelper::getInstance()->_prefix,EmoticonHelper::getInstance()->getFileByTag(tag)));
        format.setWidth(emoticonSize());
        format.setHeight(emoticonSize());
        format.setVerticalAlignment(QTextImageFormat::AlignBottom);
        cursor.insertImage(format,QTextFrameFormat::InFlow);
        offset += 1 - length;
    }
    connect(textDocument(),&QTextDocument::contentsChanged,this,&TextDocumentHelper::handleEmojiText);
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
                        text.append(EmoticonHelper::getInstance()->getTagByFile(imageFormat.name().replace(EmoticonHelper::getInstance()->_prefix,"")));
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
