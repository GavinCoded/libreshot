#pragma once

#include <QObject>
#include <QVariantMap>
#include <QEventLoop>
#include <QList>
#include <QPair>

namespace libreshot {

class portal_handler : public QObject {
    Q_OBJECT

public:
    using stream_info = QPair<uint, QVariantMap>;

    explicit portal_handler(QObject *parent = nullptr);
    void wait(QString &error);

    QString token() const { return token_; }
    QString session_path() const { return session_path_; }
    QString restore_token() const { return restore_token_; }
    QList<stream_info> streams() const { return streams_; }

public slots:
    void on_response(uint code, QVariantMap results);

private:
    QEventLoop loop_;
    QString token_;
    QString handle_path_;
    QString error_;
    QString session_path_;
    QString restore_token_;
    QList<stream_info> streams_;
    bool responded_ = false;
};

}
