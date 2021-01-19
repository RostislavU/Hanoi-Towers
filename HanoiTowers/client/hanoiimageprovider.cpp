/*
 * Copyright (C) 2018-2020 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
*/

#include "hanoiclient.h"
#include "hanoiimageprovider.h"

#include <QThread>
#include <QThreadPool>

HanoiImageProvider::HanoiImageProvider(const HanoiClient *client) {
    _pool = new QThreadPool();
    _client = client;
}

void HanoiImageProvider::stop() {
    _client = nullptr;
}

HanoiImageProvider::~HanoiImageProvider() {
    _pool->deleteLater();
}

QQuickImageResponse *HanoiImageProvider::requestImageResponse(const QString &id,
                                                              const QSize &requestedSize) {

    AsyncImageResponse *response = new AsyncImageResponse(id, requestedSize, _client);
    _pool->start(response);
    return response;

}

AsyncImageResponse::AsyncImageResponse(const QString &id, const QSize &requestedSize,
                                       const HanoiClient *client)
    : m_id(id), m_requestedSize(requestedSize), m_texture(0), _client(client) {
    setAutoDelete(false);
}

QQuickTextureFactory *AsyncImageResponse::textureFactory() const {
    return m_texture;
}

void AsyncImageResponse::run() {
    if (!_client) {
        emit finished();
        return;
    }

    QImage image = _client->userAvatar(m_id.toLocal8Bit());;

    if (m_requestedSize.isValid())
        image = image.scaled(m_requestedSize);

    m_texture = QQuickTextureFactory::textureFactoryForImage(image);
    emit finished();
}
