#pragma once

#include <QObject>

#include "nvmlpp/nvmlpp_device.hpp"
#include "nlohmann/json.hpp"

class GpuClockController final : public QObject
{
    Q_OBJECT

    enum { PSTATE_COUNT = 8 };

public:
    struct clock_values
    {
        unsigned graphics;
        unsigned video;
        unsigned sm;
        unsigned memory;
    };

    GpuClockController(QObject* parrent = nullptr);
    void set_device(const NVMLpp::NVML_device *nvml_device) noexcept;

    void apply_clock_profile(const nlohmann::json& clock_offset_profile);
    void reset_clocks();

public slots:
    void update_info();

signals:
    void info_ready(const GpuClockController::clock_values&);
    void error_occured();

private:
    const NVMLpp::NVML_device* current_gpu_;

    void run_nvidia_settings(QStringList&& args);
};
