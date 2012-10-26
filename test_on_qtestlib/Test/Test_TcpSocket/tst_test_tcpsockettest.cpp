#include <QString>
#include <QtTest>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtConcurrentRun>
#include "tcpsocket.h"

class Test_TcpSocketTest : public QObject
{
    Q_OBJECT
    
public:
    Test_TcpSocketTest();
    
private Q_SLOTS:
    void test_send();
};

Test_TcpSocketTest::Test_TcpSocketTest()
{
}

QByteArray connectAndReceive(QTcpServer *server, bool *timedOut)
{
    QTcpSocket *receiver = 0;
    server->waitForNewConnection(100, timedOut);
    receiver = server->nextPendingConnection();
    receiver->waitForReadyRead(100);
    return receiver->readAll();
}

void Test_TcpSocketTest::test_send()
{
    bool timedOut = false;
    QTcpServer server;
    server.listen(QHostAddress::Any, 3001);
    QFuture<QByteArray> future = QtConcurrent::run(connectAndReceive, &server, &timedOut);
    TcpSocket client;
    QVERIFY(client.connect("localhost", 3001));
    QVERIFY(client.send("test"));

    future.waitForFinished();
    QVERIFY(!timedOut);
    QCOMPARE(future.result(), QByteArray("test", 5));
}

QTEST_APPLESS_MAIN(Test_TcpSocketTest)

#include "tst_test_tcpsockettest.moc"
