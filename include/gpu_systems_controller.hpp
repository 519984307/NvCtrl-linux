#pragma once

#include <QObject>

#include "gpu_fan_controller.hpp"
#include "gpu_clock_controller.hpp"
#include "gpu_power_controller.hpp"
#include "gpu_utilizations_controller.hpp"

#include "nlohmann/json.hpp"

class GpuSystemsController final : public QObject
{
    Q_OBJECT

public:
    GpuSystemsController(QObject* parent = nullptr);

    void set_current_gpu(NVMLpp::NVML_device* current_gpu);
    void update_info();

    void set_fan_speed(unsigned value);
    void set_power_limit(unsigned value);
    void set_current_clock_profile(const nlohmann::json& clock_profile);

signals:
    void fan_info_ready(const GpuFanController::fan_rates& fan_rates);
    void fan_controller_error();

    void clock_info_ready(const GpuClockController::clock_values& clock_values);
    void clock_controller_error();

    void power_info_ready(const GpuPowerController::power_rates& power_rates);
    void power_controller_error();

    void utilization_info_ready(const GpuUtilizationsController::utilization_rates& utilization_rates);
    void utilization_controller_encoder_unsupported();

private slots:
    void on_GpuFanController_info_ready(const GpuFanController::fan_rates& fan_rates);
    void on_GpuFanController_error_occured();

    void on_GpuClockController_info_ready(const GpuClockController::clock_values& clock_values);
    void on_GpuClockController_error_occured();

    void on_GpuPowerController_info_ready(const GpuPowerController::power_rates& power_rates);
    void on_GpuPowerController_error_occured();

    void on_GpuUtilizationsController_info_ready(const GpuUtilizationsController::utilization_rates& utilization_rates);
    void on_GpuUtilizationsController_encoder_decoder_unsupported();

private:
    GpuFanController fan_controller_;
    GpuClockController clock_controller_;
    GpuPowerController power_controller_;
    GpuUtilizationsController utilizations_controller_;
};
