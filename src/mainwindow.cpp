#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent}
    , ui{new Ui::MainWindow}
    , dynamic_info_update_timer_{this}
    , tray_icon_{QIcon{"/home/alexcr4ckpentest/Pictures/Screenshots/ico.png"}}
    , tray_menu_{this}
    , nvml_device_{}
    , settings_window_{this}
{
    ui->setupUi(this);
    setMinimumSize(size());
    setMaximumSize(size() * 1.35);

    tray_menu_.addAction("Show/hide app window", this, &MainWindow::toggle_tray);
    tray_icon_.setContextMenu(&tray_menu_);

    connect(&dynamic_info_update_timer_, &QTimer::timeout, this, &MainWindow::update_dynamic_info);
    connect(ui->horizontalSlider_power_limit, &QAbstractSlider::valueChanged, this, [this](int value) {
        ui->label_current_power_limit_slider->setText(QString::number(value));
    });

    set_static_info();
    update_dynamic_info();
    dynamic_info_update_timer_.setInterval(1250);
    dynamic_info_update_timer_.start();
}

void MainWindow::on_pushButton_apply_power_settings_clicked()
{
    const auto ret_code{QProcess::execute("/usr/bin/pkexec", {"/usr/bin/nvidia-smi", "-pl", QString::number(ui->horizontalSlider_power_limit->value())})};
    if (ret_code == 0)
    {
        ui->statusbar->showMessage(QString{"Set new power limit: %1"}.arg(ui->horizontalSlider_power_limit->value()));
    }
    else
    {
        ui->statusbar->showMessage("Failed to set power limit");
    }
}

void MainWindow::on_action_Exit_triggered()
{
}

void MainWindow::update_dynamic_info()
{
    nvml_device_.update_dynamic_info();
    const auto& dynamic_info{nvml_device_.get_dynamic_info()};

    ui->progressBar_GPU_usage_percentage->setValue(dynamic_info.gpu_usage_percentage);
    ui->progressBar_memory_usage_percentage->setValue(dynamic_info.memory_usage_percentage);
    ui->progressBar_encoder_usage_percentage->setValue(dynamic_info.encoder_usage_percentage);
    ui->progressBar_decoder_usage_percentage->setValue(dynamic_info.decoder_usage_percentage);

    ui->lineEdit_current_power_limit->setText(QString::number(dynamic_info.current_power_limit / 1000) + " W");
    ui->lineEdit_current_power_usage->setText(QString::number(dynamic_info.current_power_usage / 1000.f) + " W");
    ui->lineEdit_current_temperature->setText(QString::number(dynamic_info.current_gpu_temperature) + " °C");
}

void MainWindow::toggle_tray()
{
    if (isHidden())
    {
        showNormal();
    }
    else
    {
        hide();
        tray_icon_.show();
    }
}

void MainWindow::closeEvent(QCloseEvent* event_)
{
}

void MainWindow::set_static_info()
{
    ui->lineEdit_GPU_name->setText(QString::fromStdString(nvml_device_.get_name()));
    ui->lineEdit_GPU_driver_version->setText(QString::fromStdString(nvml_device_.get_system_driver_version()));
    ui->lineEdit_GPU_VBIOS_version->setText(QString::fromStdString(nvml_device_.get_vbios_version()));
    ui->lineEdit_GPU_UUID->setText(QString::fromStdString(nvml_device_.get_uuid()));

    ui->lineEdit_max_power_usage->setText(QString::number(nvml_device_.get_max_power_usage() / 1000) + " W");
    ui->lineEdit_min_power_usage->setText(QString::number(nvml_device_.get_min_power_usage() / 1000) + " W");
    ui->lineEdit_default_power_usage->setText(QString::number(nvml_device_.get_default_power_usage() / 1000.f) + " W");

    ui->horizontalSlider_power_limit->setMaximum(nvml_device_.get_max_power_usage() / 1000);
    ui->horizontalSlider_power_limit->setMinimum(nvml_device_.get_min_power_usage() / 1000);
    ui->horizontalSlider_power_limit->setValue(nvml_device_.get_dynamic_info().current_power_limit / 1000);

    ui->label_current_power_limit_slider->setText(QString::number(nvml_device_.get_dynamic_info().current_power_limit / 1000));
    ui->label_max_power_limit_slider->setText(QString::number(nvml_device_.get_max_power_usage() / 1000));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionShow_hide_app_window_triggered()
{
    hide();
    tray_icon_.show();
}


void MainWindow::on_actionSettings_triggered()
{
    settings_window_.show();
}

