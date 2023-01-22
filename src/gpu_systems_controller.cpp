#include "gpu_systems_controller.hpp"

GpuSystemsController::GpuSystemsController(QObject* parent)
    : QObject {parent}
    , fan_controller_ {}
    , clock_controller_ {}
    , power_controller_ {}
    , utilizations_controller_ {}
{
    connect(&fan_controller_, &GpuFanController::info_ready, this, &GpuSystemsController::on_GpuFanController_info_ready);
    connect(&fan_controller_, &GpuFanController::error_occured, this, &GpuSystemsController::on_GpuFanController_error_occured);

    connect(&clock_controller_, &GpuClockController::info_ready, this, &GpuSystemsController::on_GpuClockController_info_ready);
    connect(&clock_controller_, &GpuClockController::error_occured, this, &GpuSystemsController::on_GpuClockController_error_occured);

    connect(&power_controller_, &GpuPowerController::info_ready, this, &GpuSystemsController::on_GpuPowerController_info_ready);
    connect(&power_controller_, &GpuPowerController::error_occured, this, &GpuSystemsController::on_GpuPowerController_error_occured);

    connect(&utilizations_controller_, &GpuUtilizationsController::info_ready,
            this, &GpuSystemsController::on_GpuUtilizationsController_info_ready);
    connect(&utilizations_controller_, &GpuUtilizationsController::encoder_decoder_unsupported,
            this, &GpuSystemsController::on_GpuUtilizationsController_encoder_decoder_unsupported);
}



void GpuSystemsController::set_current_gpu(NVMLpp::NVML_device* current_gpu)
{
    fan_controller_.set_device(current_gpu);
    clock_controller_.set_device(current_gpu);
    power_controller_.set_device(current_gpu);
    utilizations_controller_.set_device(current_gpu);
}



void GpuSystemsController::update_info()
{
    fan_controller_.update_info();
    clock_controller_.update_info();
    power_controller_.update_info();
    utilizations_controller_.update_info();
}



void GpuSystemsController::set_fan_speed(unsigned value)
{
    fan_controller_.set_fan_speed(value);
}



void GpuSystemsController::set_fan_control_state(bool enabled)
{
    fan_controller_.set_fan_control_state(enabled);
}



void GpuSystemsController::set_power_limit(unsigned value)
{
    power_controller_.set_power_limit(value);
}



void GpuSystemsController::set_current_clock_profile(const nlohmann::json& clock_profile)
{
    clock_controller_.apply_clock_profile(clock_profile);
}



void GpuSystemsController::reset_clocks()
{
    clock_controller_.reset_clocks();
}



void GpuSystemsController::on_GpuFanController_info_ready(const GpuFanController::fan_rates& fan_rates)
{
    emit fan_info_ready(fan_rates);
}



void GpuSystemsController::on_GpuFanController_error_occured()
{
    emit fan_controller_error();
}



void GpuSystemsController::on_GpuClockController_info_ready(const GpuClockController::clock_values& clock_values)
{
    emit clock_info_ready(clock_values);
}



void GpuSystemsController::on_GpuClockController_error_occured()
{
    emit clock_controller_error();
}



void GpuSystemsController::on_GpuPowerController_info_ready(const GpuPowerController::power_rates& power_rates)
{
    emit power_info_ready(power_rates);
}



void GpuSystemsController::on_GpuPowerController_error_occured()
{
    emit power_controller_error();
}



void GpuSystemsController::on_GpuUtilizationsController_info_ready(const GpuUtilizationsController::utilization_rates& utilization_rates)
{
    emit utilization_info_ready(utilization_rates);
}



void GpuSystemsController::on_GpuUtilizationsController_encoder_decoder_unsupported()
{
    emit utilization_controller_encoder_unsupported();
}
