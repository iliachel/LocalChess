#include <QCoreApplication>
#include <QTcpSocket>
#include <QTextStream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTcpSocket socket;

    socket.connectToHost("127.0.0.1", 5555);
    if(!socket.waitForConnected(3000)) {
        qDebug() << "Connection failed";
        return 0;
    }

    qDebug() << "Connected to server";

    QObject::connect(&socket, &QTcpSocket::readyRead, [&](){
        QByteArray data = socket.readAll();
        qDebug() << "Server:" << data;
    });

    QTextStream input(stdin);
    QObject::connect(&a, &QCoreApplication::aboutToQuit, [&](){
        socket.close();
    });

    // простой ввод ходов
    QObject::connect(&socket, &QTcpSocket::connected, [&](){
        qDebug() << "Enter moves like e2e4";

        while(true){
            QString move = input.readLine();
            socket.write(move.toUtf8() + "\n");
            socket.flush();
        }
    });

    return a.exec();
}
