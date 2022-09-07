#include <iostream>

#include <QApplication>
#include <QMessageBox>

#include "spdlog/spdlog.h"

#include "mainwindow.hpp"
#include "settings_manager.hpp"

static void qt_msg_handler(QtMsgType msg_type, const QMessageLogContext& context,
                           const QString& message)
{
    switch (msg_type)
    {
    case QtMsgType::QtCriticalMsg:  spdlog::critical(message.toStdString()); break;
    case QtMsgType::QtDebugMsg:     spdlog::debug("{}:{} in {}: {}", context.file, context.line, context.function, message.toStdString()); break;
    case QtMsgType::QtFatalMsg:     spdlog::critical(message.toStdString()); break;
    case QtMsgType::QtInfoMsg:      spdlog::info(message.toStdString()); break;
    case QtMsgType::QtWarningMsg:   spdlog::warn(message.toStdString()); break;
    }
}

int main(int argc, char** argv)
{
#ifndef NDEBUG
    spdlog::set_level(spdlog::level::debug);
#else
    spdlog::set_level(spdlog::level::info);
#endif

    qInstallMessageHandler(qt_msg_handler);

    QApplication app {argc, argv};
    SettingsManager& settings_manager {SettingsManager::instance()};

    QObject::connect(&settings_manager, &SettingsManager::error,
                     [](const QString& err_msg)
    {
        qCritical().nospace().noquote() << err_msg;
        QMessageBox::critical(nullptr, "Error", err_msg);
        std::exit(1);
    });

    settings_manager.open_file(QIODevice::ReadOnly);
    const auto app_settings{settings_manager.load_settings()};
    settings_manager.close_file();

    const bool minimize_to_tray_on_startup {app_settings["minimize_to_tray_on_startup"].toBool()};
    MainWindow main_window {app_settings};

    if (minimize_to_tray_on_startup)
    {
        main_window.get_tray_icon().show();
        qInfo().nospace().noquote() << "Start minimized to tray";
    }
    else
    {
        main_window.show();
        qInfo().nospace().noquote() << "Start normal window";
    }

    return app.exec();
}
