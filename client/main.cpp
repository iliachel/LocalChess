#include <QCoreApplication>
#include <QTcpSocket>
#include <QSocketNotifier>
#include <QTextStream>
#include <QDebug>

class ChessClient : public QObject {
    Q_OBJECT
public:
    ChessClient(QString host, quint16 port) {
        connect(&socket, &QTcpSocket::connected, this, [&](){
            qDebug() << "Connected to server";
        });

        connect(&socket, &QTcpSocket::readyRead, this, [&](){
            QByteArray data = socket.readAll();
            qDebug() << "Server:" << data;
        });

        // stdin notifier
        notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
        connect(notifier, &QSocketNotifier::activated, this, &ChessClient::readUserInput);

        socket.connectToHost(host, port);
    }

private slots:
    void readUserInput() {
        QTextStream in(stdin);
        QString line = in.readLine();

        if(line.isEmpty())
            return;

        socket.write(line.toUtf8() + "\n");
        socket.flush();
    }

private:
    QTcpSocket socket;
    QSocketNotifier *notifier;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ChessClient client("127.0.0.1", 5555);
    return a.exec();
}

#include "main.moc"
