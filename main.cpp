#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "gamedatamodel.h"
#include "gamedatabase.h"

int main(int argc, char *argv[])
{
    if (qEnvironmentVariableIsEmpty("QTGLESSTREAM_DISPLAY")) {
        qputenv("QT_QPA_EGLFS_PHYSICAL_WIDTH", QByteArray("213"));
        qputenv("QT_QPA_EGLFS_PHYSICAL_HEIGHT", QByteArray("120"));

        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    }

    QGuiApplication app(argc, argv);
    qmlRegisterType<GameDataModel>("GameDataModel", 1, 0, "GameDataModel");
    qmlRegisterSingletonType<GameDataBase>("GameDataBase", 1, 0, "GameDataBase", GameDataBase::gamedatabaseProvider);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
