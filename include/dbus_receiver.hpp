#pragma once

#include <QObject>

class DBusReceiver final : public QObject
{
    Q_OBJECT

public:
    DBusReceiver(std::string_view service_name, QObject* parent = nullptr);

public slots:
    Q_SCRIPTABLE int handle_message();

signals:
    void message_received();
};
