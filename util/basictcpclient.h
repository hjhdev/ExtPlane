#ifndef BASICTCPCLIENT_H
#define BASICTCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QTimer>

/**
 * @brief The BasicTcpClient class is a very basic text-based
 * TCP client that can read and write lines to a TCP socket.
 */
class BasicTcpClient : public QTcpSocket
{
    Q_OBJECT
    Q_PROPERTY(QString lineEnding READ lineEnding WRITE setLineEnding NOTIFY lineEndingChanged)
    Q_PROPERTY(QString hostName READ hostName WRITE setHostName NOTIFY connectionChanged)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY connectionChanged)
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)

public:
    explicit BasicTcpClient(QObject *parent = nullptr);
    virtual ~BasicTcpClient() {}
    Q_INVOKABLE virtual void startConnection();
    void writeLine(QString line);
    QString lineEnding() const;
    QString hostName() const;
    int port() const;
    bool connected() const;

public slots:
    void setLineEnding(QString lineEnding);
    void setHostName(QString hostName);
    void setPort(int port);

signals:
    void receivedLine(QString & line);
    void connectionMessage(QString text);
    void networkError(QString errorString);
    void lineEndingChanged(QString lineEnding);
    void connectionChanged();
    void connectedChanged(bool connected);

private slots:
    void socketConnected();
    void socketError(QAbstractSocket::SocketError err);
    void readClient();
    void tryReconnect();

private:
    QTimer reconnectTimer;
    QString m_lineEnding;
    QString m_host;
    int m_port;
};

#endif // BASICTCPCLIENT_H
