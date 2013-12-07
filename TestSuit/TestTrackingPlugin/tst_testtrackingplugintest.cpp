#include <QString>
#include <QtTest>
#include <QCoreApplication>

class TestTrackingPluginTest : public QObject
{
    Q_OBJECT

public:
    TestTrackingPluginTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
    void testCase1_data();

    //void test
};

TestTrackingPluginTest::TestTrackingPluginTest()
{
}

void TestTrackingPluginTest::initTestCase()
{
}

void TestTrackingPluginTest::cleanupTestCase()
{
}

void TestTrackingPluginTest::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

void TestTrackingPluginTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

QTEST_MAIN(TestTrackingPluginTest)

#include "tst_testtrackingplugintest.moc"
