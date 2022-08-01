#include <QMessageBox>
#include <QProcess>

#include "mainwindow.hpp"
#include "nvmlpp/util/nvmlpp_errors.hpp"
#include "ui_mainwindow.h"

#include "nvmlpp/nvmlpp_session.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow {parent}
    , ui {new Ui::MainWindow}
    , tray_icon_ {this}
    , settings_manager_ {SettingsManager::instance()}
    , gpu_utilizations_controller_ {}
    , gpu_power_controller_ {}
    , gpu_clock_controller_ {}
    , dynamic_info_update_timer_ {}
    , minimize_to_tray_on_close_ {false}
    , update_freq_ms_ {}
    , nvml_devices_list_ {}
{
    ui->setupUi(this);
    setMinimumSize(size());

    connect_slots_and_signals();
    setup_tray_menu();
    load_app_settings();
    load_GPUs();

    set_static_info();
    gpu_utilizations_controller_.update_info();
    gpu_power_controller_.update_info();
    gpu_clock_controller_.update_info();

    dynamic_info_update_timer_.start();
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::apply_settings(const QJsonObject& settings)
{
    minimize_to_tray_on_close_ = settings["minimize_to_tray_on_close"].toBool();
    update_freq_ms_ = settings["update_freq_ms"].toInt();

    qDebug().noquote().nospace() << "New settings applied: " << settings;
}

void MainWindow::on_GpuUtilizationsController_gpu_utilization(unsigned gpu_utilization)
{
    ui->progressBar_GPU_usage->setValue(gpu_utilization);
}

void MainWindow::on_GpuUtilizationsController_memory_utilization(unsigned memory_utilization, unsigned used_memory)
{
    ui->progressBar_GPU_mem_usage->setValue(memory_utilization);
    ui->lineEdit_GPU_mem_usage->setText(QString::number(used_memory) + " of " + ui->lineEdit_GPU_total_mem->text());
}

void MainWindow::on_GpuUtilizationsController_encoder_decoder_utilization(unsigned encoder_utilization, unsigned decoder_utilization)
{
    ui->progressBar_GPU_encoder_usage->setValue(encoder_utilization);
    ui->progressBar_GPU_decoder_usage->setValue(decoder_utilization);
}

void MainWindow::on_GpuUtilizationsController_pstate_level(unsigned pstate_level)
{
    ui->lineEdit_current_pstate->setText("Pstate: " + QString::number(pstate_level));
}

void MainWindow::on_GpuPowerController_power_usage(unsigned power_usage)
{
    ui->lineEdit_current_power_usage->setText(QString::number(power_usage) + " W");
}

void MainWindow::on_GpuPowerController_power_limit(unsigned power_limit)
{
    ui->lineEdit_current_power_limit->setText(QString::number(power_limit) + " W");
}

void MainWindow::on_GpuClockController_graphics_clock(unsigned graphics_clock)
{
    ui->lineEdit_graphics_clock_current->setText(QString::number(graphics_clock) + " MHz");
}

void MainWindow::on_GpuClockController_video_clock(unsigned video_clock)
{
    ui->lineEdit_video_clock_current->setText(QString::number(video_clock) + " MHz");
}

void MainWindow::on_GpuClockController_sm_clock(unsigned sm_clock)
{
    ui->lineEdit_sm_clock_current->setText(QString::number(sm_clock) + " MHz");
}

void MainWindow::on_GpuClockController_memory_clock(unsigned memory_clock)
{
    ui->lineEdit_memory_clock_current->setText(QString::number(memory_clock) + " MHz");
}

void MainWindow::on_GpuClockController_error()
{
    ui->groupBox_clock_info->setDisabled(false);
}

void MainWindow::connect_slots_and_signals()
{
    connect(&tray_icon_, &QSystemTrayIcon::activated, this, &MainWindow::toggle_tray);

    connect(&gpu_utilizations_controller_, &GpuUtilizationsController::gpu_utilization, this,&MainWindow::on_GpuUtilizationsController_gpu_utilization);
    connect(&gpu_utilizations_controller_, &GpuUtilizationsController::memory_utilization, this, &MainWindow::on_GpuUtilizationsController_memory_utilization);
    connect(&gpu_utilizations_controller_, &GpuUtilizationsController::encoder_decoder_utilization, this, &MainWindow::on_GpuUtilizationsController_encoder_decoder_utilization);
    connect(&gpu_utilizations_controller_, &GpuUtilizationsController::pstate_level, this, &MainWindow::on_GpuUtilizationsController_pstate_level);

    connect(&gpu_power_controller_, &GpuPowerController::power_usage, this, &MainWindow::on_GpuPowerController_power_usage);
    connect(&gpu_power_controller_, &GpuPowerController::power_limit, this, &MainWindow::on_GpuPowerController_power_limit);

    connect(&gpu_clock_controller_, &GpuClockController::graphics_clock, this, &MainWindow::on_GpuClockController_graphics_clock);
    connect(&gpu_clock_controller_, &GpuClockController::video_clock, this, &MainWindow::on_GpuClockController_video_clock);
    connect(&gpu_clock_controller_, &GpuClockController::sm_clock, this, &MainWindow::on_GpuClockController_sm_clock);
    connect(&gpu_clock_controller_, &GpuClockController::memory_clock, this, &MainWindow::on_GpuClockController_memory_clock);
    connect(&gpu_clock_controller_, &GpuClockController::error, this, &MainWindow::on_GpuClockController_error);

    connect(&dynamic_info_update_timer_, &QTimer::timeout, &gpu_utilizations_controller_, &GpuUtilizationsController::update_info);
    connect(&dynamic_info_update_timer_, &QTimer::timeout, &gpu_power_controller_, &GpuPowerController::update_info);
    connect(&dynamic_info_update_timer_, &QTimer::timeout, &gpu_clock_controller_, &GpuClockController::update_info);

    connect(&settings_manager_, &SettingsManager::error, this, [this](const QString& err_msg)
    {
        qCritical().nospace().noquote() << err_msg;
        QMessageBox::critical(this, "Error", err_msg);
        on_actionExit_triggered();
    });

    connect(ui->horizontalSlider_change_power_limit, &QSlider::valueChanged, this, [this](int value)
    {
        ui->label_power_limit_slider_indicator->setText(QString::number(value));
    });
}

void MainWindow::setup_tray_menu()
{
    QMenu* tray_menu {new QMenu {this}};
    tray_menu->addAction("Show/Hide app window", this, &MainWindow::toggle_tray);
    tray_menu->addAction("Exit", this, &MainWindow::on_actionExit_triggered);
    tray_icon_.setContextMenu(tray_menu);
}

void MainWindow::load_app_settings()
{
    auto& settings_manager {SettingsManager::instance()};
    settings_manager.open_file(QIODevice::ReadOnly);

    const auto app_settings{settings_manager.load_settings()};
    settings_manager.close_file();

    minimize_to_tray_on_close_ = app_settings["minimize_to_tray_on_close"].toBool();
    update_freq_ms_ = app_settings["update_freq_ms"].toInt();
    dynamic_info_update_timer_.setInterval(update_freq_ms_);

    qDebug().noquote().nospace() << "Settings has been loaded: " << app_settings;
}

void MainWindow::set_static_info()
{
    const auto& current_gpu {get_current_gpu()};
    ui->lineEdit_GPU_name->setText(QString::fromStdString(current_gpu->get_name()));
    ui->lineEdit_GPU_arch->setText(QString::fromStdString(current_gpu->get_arch()));
    ui->lineEdit_GPU_uuid->setText(QString::fromStdString(current_gpu->get_uuid()));
    ui->lineEdit_GPU_VBIOS_ver->setText(QString::fromStdString(current_gpu->get_vbios_version()));
    ui->lineEdit_GPU_driver_ver->setText(QString::fromStdString(NVMLpp::Session::instance().get_system_driver_version()));
    ui->lineEdit_GPU_bus_type->setText(QString::fromStdString(current_gpu->get_bus_type()) + " " + QString::fromStdString(current_gpu->get_pci_bus_id()));
    ui->lineEdit_GPU_total_mem->setText(QString::number(current_gpu->get_total_memory()) + " MiB");

    try
    {
        const unsigned min_power_limit {current_gpu->get_min_power_limit()};
        const unsigned max_power_limit {current_gpu->get_max_power_limit()};
        const unsigned current_power_limit {current_gpu->get_current_power_limit()};

        ui->lineEdit_default_power_limit->setText(QString::number(current_gpu->get_default_power_limit()) + " W");
        ui->lineEdit_enforced_power_limit->setText(QString::number(current_gpu->get_enforced_power_limit()) + " W");
        ui->label_power_limit_slider_indicator->setText(QString::number(current_power_limit));
        ui->lineEdit_min_power_limit->setText(QString::number(min_power_limit) + " W");
        ui->lineEdit_max_power_limit->setText(QString::number(max_power_limit) + " W");
        ui->horizontalSlider_change_power_limit->setMinimum(min_power_limit);
        ui->horizontalSlider_change_power_limit->setMaximum(max_power_limit);
        ui->horizontalSlider_change_power_limit->setValue(current_power_limit);
    }
    catch (const NVMLpp::errors::error_not_supported&)
    {
        ui->groupBox_power_control->setEnabled(false);
        qWarning().noquote().nospace() << "Power control not supported, widget disabled";
    }

    try
    {
        ui->lineEdit_graphics_clock_max->setText(QString::number(current_gpu->get_max_clock_graphics()) + " MHz");
        ui->lineEdit_video_clock_max->setText(QString::number(current_gpu->get_max_clock_video()) + " MHz");
        ui->lineEdit_sm_clock_max->setText(QString::number(current_gpu->get_max_clock_sm()) + " MHz");
        ui->lineEdit_memory_clock_max->setText(QString::number(current_gpu->get_max_clock_memory()) + " MHz");
    }
    catch (const NVMLpp::errors::error&)
    {
        ui->groupBox_clock_info->setEnabled(false);
        qWarning().noquote().nospace() << "Clock control no supported, widget disabled";
    }

    qDebug().noquote().nospace() << "Static info has been set";
}

void MainWindow::load_GPUs()
{
    nvml_devices_list_ = NVMLpp::Session::instance().get_devices();
    for (const auto& gpu : nvml_devices_list_)
    {
        ui->comboBox_select_GPU->addItem(QString::fromStdString(gpu.get_name()));
    }

    set_current_gpu_for_controllers();

    qInfo().noquote().nospace() << "Total GPUs found: " << nvml_devices_list_.size();
}

NVMLpp::NVML_device* MainWindow::get_current_gpu()
{
    const int current_device_index {ui->comboBox_select_GPU->currentIndex()};
    return &nvml_devices_list_[current_device_index];
}

void MainWindow::set_current_gpu_for_controllers() noexcept
{
    const auto& current_gpu {get_current_gpu()};
    gpu_utilizations_controller_.set_device(current_gpu);
    gpu_power_controller_.set_device(current_gpu);
    gpu_clock_controller_.set_device(current_gpu);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    qDebug().noquote().nospace() << "minimize_to_tray_on_close_=" << minimize_to_tray_on_close_;

    if (minimize_to_tray_on_close_)
    {
        event->ignore();
        hide();
        tray_icon_.show();
        qDebug().noquote().nospace() << "Event ignored, minimized to tray";
    }
    else
    {
        tray_icon_.hide();
        event->accept();
        qDebug().noquote().nospace() << "Event accepted, MainWindow closed";
    }
}

void MainWindow::on_comboBox_select_GPU_activated(int index)
{
    set_current_gpu_for_controllers();
    set_static_info();
    qDebug().noquote().nospace() << "GPU selected: " << ui->comboBox_select_GPU->currentText();
}

void MainWindow::on_pushButton_apply_power_limit_clicked()
{
    gpu_power_controller_.set_power_limit(ui->horizontalSlider_change_power_limit->value());
}

void MainWindow::on_actionUpdate_GPUs_list_triggered()
{
    qDebug() << "Updating list of GPUs...";
    nvml_devices_list_.clear();
    ui->comboBox_select_GPU->clear();
    load_GPUs();
}

void MainWindow::on_actionExit_triggered()
{
    minimize_to_tray_on_close_ = false;
    close();
}
