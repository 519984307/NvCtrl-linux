#pragma once

#include <QObject>

#include "nvmlpp/nvmlpp_device.hpp"

class GpuUtilizationsController final : public QObject
{
    Q_OBJECT

public:
    struct utilization_rates
    {
        unsigned gpu;
        unsigned mem;
        unsigned mem_used;
        unsigned encoder;
        unsigned decoder;
        unsigned pstate;
        unsigned gpu_core_temp;
    };

    GpuUtilizationsController(QObject* parrent = nullptr);
    void set_device(const NVMLpp::NVML_device* nvml_device) noexcept;

public slots:
    void update_info();

signals:
    void info_ready(const GpuUtilizationsController::utilization_rates&);
    void encoder_decoder_unsupported();

private:
    const NVMLpp::NVML_device* current_gpu_;
};
