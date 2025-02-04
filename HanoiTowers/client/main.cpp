/*
 * Copyright (C) 2018-2021 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include <QGuiApplication>
#include <QFont>
#include <QFontDatabase>
#include <iostream>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include "backEnd.h"
#include <QTranslator>
#include <qmlnotifyservice.h>
#include <credits.h>

void setFont(const QGuiApplication& app){

    QString fontPath = "://ubuntu";
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    if (fontId != -1)
    {
        QFont font(QFontDatabase::applicationFontFamilies(fontId).at(0));
        app.setFont(font);
    }
}

bool initLocale(const QString &locale, QGuiApplication& app, QTranslator &translator){

    QString defaultLocale = QLocale::system().name();
    defaultLocale.truncate(defaultLocale.lastIndexOf('_'));

    if(!locale.isEmpty() && translator.load(QString(":/languages/%0").arg(locale))){
        return app.installTranslator(&translator);
    }

    if(!translator.load(QString(":/languages/%0").arg(defaultLocale))){
        return false;
    }

    return app.installTranslator(&translator);
}

int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("HanoiTowers"); // <--
    QGuiApplication::setOrganizationName("QuasarApp"); // <--
    QGuiApplication::setOrganizationDomain("https://github.com/QuasarApp"); // <--

    QGuiApplication app(argc, argv);
    setFont(app);

    QTranslator translator;

    QString locale = "";

    if(argc > 1) {
        locale = QString::fromLatin1(argv[1]);
    }

    if(!initLocale(locale, app, translator)){
        std::cout << "error load language : " << locale.toStdString() <<std::endl;
    }

    QQmlApplicationEngine engine;
    BackEnd back(&engine);
    auto root = engine.rootContext();

    if (!QmlNotificationService::init(&engine)) {
        return 1;
    }

    if (!QuasarAppCredits::init(&engine)) {
        return 2;
    }

    root->setContextProperty("backEnd", &back);
    root->setContextProperty("OnlineStatusQml", QVariant::fromValue(OnlineStatusQml{}));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
