/*
 * Copyright (C) 2018-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#ifndef USERPREVIEW_H
#define USERPREVIEW_H

#include <QByteArray>
#include <QString>

struct UserPreview {
    UserPreview();
    UserPreview(const QString& id);

    QString id;
    QString userName;
    int record;

    friend bool operator==(const UserPreview& left, const UserPreview& right);
};
#endif // USERPREVIEW_H