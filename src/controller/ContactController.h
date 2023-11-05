#ifndef CONTACTCONTROLLER_H
#define CONTACTCONTROLLER_H

#include <QObject>

class ContactController : public QObject
{
    Q_OBJECT
public:
    explicit ContactController(QObject *parent = nullptr);
    ~ContactController() override;
    Q_INVOKABLE void hadnleClickItemContact(const QString& uid);

};

#endif // CONTACTCONTROLLER_H
