#include "EmoticonHelper.h"

#include <QImage>

Emoticon::Emoticon(QObject *parent)
    : QObject{parent}
{
    this->_file = "file";
    this->_name = "name";
    this->_tag = "tag";
}

Emoticon::Emoticon(QString file,QString name,QString tag,QObject *parent)
    : QObject{parent}
{
    this->_file = file;
    this->_name = name;
    this->_tag = tag;
}

QString EmoticonHelper::getFileByTag(const QString& tag){
    foreach (auto item, _datas) {
        if(item->tag()==tag){
            return item->file();
        }
    }
    return "";
}

QString EmoticonHelper::getTagByFile(const QString& file){
    foreach (auto item, _datas) {
        if(item->file()==file){
            return item->tag();
        }
    }
    return "";
}

QString EmoticonHelper::getTagByUrl(QString url){
    return getTagByFile(url.replace(_prefix,""));
}

EmoticonHelper::EmoticonHelper(QObject *parent)
    : QObject{parent}
{
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_00.png","emoticon_emoji_0","[大笑]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_01.png","emoticon_emoji_01","[开心]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_02.png","emoticon_emoji_02","[色]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_03.png","emoticon_emoji_03","[酷]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_04.png","emoticon_emoji_04","[奸笑]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_05.png","emoticon_emoji_05","[亲]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_06.png","emoticon_emoji_06","[伸舌头]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_07.png","emoticon_emoji_07","[眯眼]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_08.png","emoticon_emoji_08","[可爱]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_09.png","emoticon_emoji_09","[鬼脸]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_10.png","emoticon_emoji_10","[偷笑]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_11.png","emoticon_emoji_11","[喜悦]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_12.png","emoticon_emoji_12","[狂喜]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_13.png","emoticon_emoji_13","[惊讶]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_14.png","emoticon_emoji_14","[流泪]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_15.png","emoticon_emoji_15","[流汗]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_16.png","emoticon_emoji_16","[天使]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_17.png","emoticon_emoji_17","[笑哭]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_18.png","emoticon_emoji_18","[尴尬]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_19.png","emoticon_emoji_19","[惊恐]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_20.png","emoticon_emoji_20","[大哭]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_21.png","emoticon_emoji_21","[烦躁]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_22.png","emoticon_emoji_22","[恐怖]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_23.png","emoticon_emoji_23","[两眼冒星]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_24.png","emoticon_emoji_24","[害羞]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_25.png","emoticon_emoji_25","[睡着]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_26.png","emoticon_emoji_26","[冒星]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_27.png","emoticon_emoji_27","[口罩]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_28.png","emoticon_emoji_28","[OK]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_29.png","emoticon_emoji_29","[好吧]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_30.png","emoticon_emoji_30","[鄙视]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_31.png","emoticon_emoji_31","[难受]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_32.png","emoticon_emoji_32","[不屑]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_33.png","emoticon_emoji_33","[不舒服]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_34.png","emoticon_emoji_34","[愤怒]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_35.png","emoticon_emoji_35","[鬼怪]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_36.png","emoticon_emoji_36","[发怒]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_37.png","emoticon_emoji_37","[生气]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_38.png","emoticon_emoji_38","[不高兴]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_39.png","emoticon_emoji_39","[皱眉]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_40.png","emoticon_emoji_40","[心碎]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_41.png","emoticon_emoji_41","[心动]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_42.png","emoticon_emoji_42","[好的]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_43.png","emoticon_emoji_43","[低级]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_44.png","emoticon_emoji_44","[赞]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_45.png","emoticon_emoji_45","[鼓掌]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_46.png","emoticon_emoji_46","[给力]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_47.png","emoticon_emoji_47","[打你]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_48.png","emoticon_emoji_48","[阿弥陀佛]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_49.png","emoticon_emoji_49","[拜拜]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_50.png","emoticon_emoji_50","[第一]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_51.png","emoticon_emoji_51","[拳头]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_52.png","emoticon_emoji_52","[手掌]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_53.png","emoticon_emoji_53","[剪刀]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_54.png","emoticon_emoji_54","[招手]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_55.png","emoticon_emoji_55","[不要]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_56.png","emoticon_emoji_56","[举着]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_57.png","emoticon_emoji_57","[思考]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_58.png","emoticon_emoji_58","[猪头]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_59.png","emoticon_emoji_59","[不听]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_60.png","emoticon_emoji_60","[不看]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_61.png","emoticon_emoji_61","[不说]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_62.png","emoticon_emoji_62","[猴子]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_63.png","emoticon_emoji_63","[炸弹]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_64.png","emoticon_emoji_64","[睡觉]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_65.png","emoticon_emoji_65","[筋斗云]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_66.png","emoticon_emoji_66","[火箭]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_67.png","emoticon_emoji_67","[救护车]")));
    _datas.append(QSharedPointer<Emoticon>(new Emoticon("emoji_68.png","emoticon_emoji_68","[便便]")));
    QList<QString> tags;
    foreach (auto item, _datas) {
        tags.append(item.get()->tag());
    }
    QString tagPattern = "("+ tags.join("|") + ")";
    _tagRegular.setPattern(tagPattern.replace("[","\\[").replace("]","\\]"));
}

QString EmoticonHelper::toEmoticonString(QString text,int size){
    QRegularExpressionMatchIterator it = EmoticonHelper::getInstance()->_tagRegular.globalMatch(text);
    int offset = 0;
    while (it.hasNext ()) {
        QRegularExpressionMatch match = it.next();
        int length = match.capturedLength ();
        int begin = match.capturedStart () + offset;
        QString tag = match.captured(1);
        QString replaceString = QString::fromStdString("<img src=\"%1\" width=\"%2\" height=\"%2\" alt=\"%3\"/>").arg((_prefix + getFileByTag(tag)),QString::number(size),tag);
        text.replace(begin,length,replaceString);
        offset += replaceString.length() - length;
    }
    return QString::fromStdString("<p style=\"vertical-align:middle;white-space:pre-wrap;\">%1</p>").arg(text);
}

