#pragma once

#include <QMainWindow>
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QProcess>
#include <QMenu>
#include <QJsonObject>

#include "NVML.hpp"
#include "settings_manager.hpp"
#include "settingswindow.hpp"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    QSystemTrayIcon& get_tray_icon();

private slots:
    void on_actionShow_hide_app_window_triggered();
    void on_actionSettings_triggered();
    void on_pushButton_apply_power_settings_clicked();
    void toggle_tray();
    void update_dynamic_info();
    void apply_settings(const QJsonObject& settings);

private:
    Ui::MainWindow* ui;
    QTimer dynamic_info_update_timer_;
    QSystemTrayIcon tray_icon_;
    QMenu tray_menu_;
    NVMLDevice nvml_device_;

    SettingsManager settings_manager_;
    SettingsWindow settings_window_;

    bool minimize_to_tray_on_close_;

    void set_static_info();
    void closeEvent(QCloseEvent* event_);
};
