/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#ifndef HANOICLIENT_H
#define HANOICLIENT_H

#ifdef RELEASE_BUILD
#define REMOTE_HOST "quasarapp.ddns.net"
#else
#define REMOTE_HOST "127.0.0.1"
#endif
#define REMOTE_PORT 7770
#include <databasenode.h>
#include <profiledata.h>

class LocalUser;
class UserData;

enum class Status {
    OfflineUser,
    Dissconnected,
    Connected
};

class HanoiClient: public QH::DataBaseNode
{
    Q_OBJECT
public:
    HanoiClient();

    QH::ParserResult parsePackage(const QH::Package &pkg,
                                  const QH::AbstractNodeInfo *sender) override;

    QStringList SQLSources() const override;

    QString currentUserName() const;
    void setCurrentUserName(const QString &currentUserName);
    ProfileData currentProfile();
    void connectToServer(const QH::HostAddress& host);

signals:
    void requestError(const QString & err);
    void statusChanged(int state);

private slots:
    void handleError(const QString& error);

private:

    const LocalUser *getUser(const QString &userId) const;
    const UserData *getUserData(const QString &userId) const;
    defaultProfile();

    Status _status;
    QString _currentUserName;
    QH::HostAddress _serverAddress;


};

#endif // HANOICLIENT_H
