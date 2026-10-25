#include <QtTest>
#include <QSettings>
#include <QTemporaryDir>

#include "../idlescan.hpp"

class TestIdleScan : public QObject
{
    Q_OBJECT

private slots:
    void defaultsToOff();
    void offWhenSetFalse();
    void onWhenSetTrue();
};

static QString settingsPath(const QTemporaryDir &dir)
{
    return dir.filePath("AirPodsTrayApp.conf");
}

void TestIdleScan::defaultsToOff()
{
    QTemporaryDir dir;
    QSettings settings(settingsPath(dir), QSettings::IniFormat);

    QVERIFY(!idleScanEnabled(settings));
}

void TestIdleScan::offWhenSetFalse()
{
    QTemporaryDir dir;
    {
        QSettings written(settingsPath(dir), QSettings::IniFormat);
        written.setValue("bluetooth/idleScan", false);
    }
    QSettings settings(settingsPath(dir), QSettings::IniFormat);

    QVERIFY(!idleScanEnabled(settings));
}

void TestIdleScan::onWhenSetTrue()
{
    QTemporaryDir dir;
    {
        QSettings written(settingsPath(dir), QSettings::IniFormat);
        written.setValue("bluetooth/idleScan", true);
    }
    QSettings settings(settingsPath(dir), QSettings::IniFormat);

    QVERIFY(idleScanEnabled(settings));
}

QTEST_GUILESS_MAIN(TestIdleScan)
#include "tst_idlescan.moc"
