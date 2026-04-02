#pragma once

#include <QObject>
#include <QPoint>
#include <QString>
#include <QTimer>

namespace libreshot {

class text_input : public QObject {
    Q_OBJECT

public:
    explicit text_input(QObject *parent = nullptr);
    void start(QPoint pos);
    void commit();
    void cancel();
    bool active() const { return active_; }
    void on_key(int key, const QString &ch);
    void set_pos(QPoint pos);
    QPoint pos() const { return pos_; }
    QString text() const { return text_; }
    bool cursor_on() const { return cursor_on_; }

signals:
    void changed();
    void committed(QPoint pos, const QString &text);

private:
    bool active_ = false;
    QPoint pos_;
    QString text_;
    bool cursor_on_ = true;
    QTimer blink_;
};

}
