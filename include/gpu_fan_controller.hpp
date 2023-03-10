#pragma once

#include <QObject>
#include "nvmlpp/nvmlpp_device.hpp"

class GpuFanController final : public QObject
{
    Q_OBJECT

public:
    struct fan_rates
    {
        unsigned fan_speed_level;
    };

    GpuFanController(QObject* parent = nullptr);
    void set_device(NVMLpp::NVML_device* nvml_device) noexcept;

public slots:
    void update_info();
    void set_fan_speed(unsigned fan_speed_level);
    void set_fan_control_state(bool value);

signals:
    void info_ready(const GpuFanController::fan_rates&);
    void error_occured();

private:
    NVMLpp::NVML_device* current_gpu_;

    void run_nvidia_settings(const QString& arg);
};
