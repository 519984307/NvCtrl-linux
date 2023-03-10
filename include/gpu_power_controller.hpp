#pragma once

#include <QObject>
#include "nvmlpp/nvmlpp_device.hpp"

class GpuPowerController final : public QObject
{
    Q_OBJECT
public:
    struct power_rates
    {
        unsigned usage;
        unsigned limit;
    };

    GpuPowerController(QObject* parrent = nullptr);
    void set_device(const NVMLpp::NVML_device* nvml_device) noexcept;

public slots:
    void set_power_limit(unsigned limit);
    void update_info();

signals:
    void info_ready(const GpuPowerController::power_rates&);
    void power_usage(unsigned);
    void power_limit(unsigned);
    void error_occured();

private:
    const NVMLpp::NVML_device* current_gpu_;
};
