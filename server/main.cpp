#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class ChessServer : public QTcpServer {
    Q_OBJECT
public:
    explicit ChessServer(QObject *parent = nullptr) : QTcpServer(parent) {}

    void start() {
        if(!listen(QHostAddress::Any, 5555)) {
            qDebug() << "Server error";
            return;
        }
        qDebug() << "Server started on port 5555";
    }

protected:
    void incomingConnection(qintptr socketDescriptor) override {
        QTcpSocket *client = new QTcpSocket(this);
        client->setSocketDescriptor(socketDescriptor);
        clients.append(client);

        qDebug() << "Client connected" << client;

        connect(client, &QTcpSocket::readyRead, this, [=](){
            auto data = client->readAll();
            qDebug() << "Received:" << data;

            handleMove(client, QString::fromUtf8(data).trimmed());
        });

        if(clients.size() == 2) {
            white = clients[0];
            black = clients[1];
            currentTurn = white;

            white->write("YOU_WHITE\nYOUR_TURN\n");
            black->write("YOU_BLACK\nWAIT\n");
        }
    }

private:
    QList<QTcpSocket*> clients;
    QTcpSocket* white = nullptr;
    QTcpSocket* black = nullptr;
    QTcpSocket* currentTurn = nullptr;

    void handleMove(QTcpSocket* sender, const QString &move) {
        if(clients.size() < 2)
            return;

        if(sender != currentTurn) {
            sender->write("NOT_YOUR_TURN\n");
            return;
        }

        QTcpSocket* opponent = (sender == white) ? black : white;

        opponent->write(("MOVE:" + move + "\n").toUtf8());

        // Меняем очередь
        currentTurn = opponent;
        currentTurn->write("YOUR_TURN\n");
        sender->write("WAIT\n");
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ChessServer server;
    server.start();
    return a.exec();
}

#include "main.moc"
