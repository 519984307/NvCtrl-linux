#include "nvmlpp/util/nvmlpp_errors.hpp"

#include "gpu_utilizations_controller.hpp"

GpuUtilizationsController::GpuUtilizationsController(const NVMLpp::NVML_device* nvml_device, QObject* parrent)
    : QObject {parrent}
    , current_gpu_ {nvml_device}
{ }

void GpuUtilizationsController::update_info()
{
    if (current_gpu_)
    {
        emit gpu_utilization(current_gpu_->get_gpu_utilization());
        emit memory_utilization(current_gpu_->get_memory_utilization(), current_gpu_->get_used_memory());
        try
        {
            emit encoder_decoder_utilization(current_gpu_->get_encoder_utilization(),
                                             current_gpu_->get_decoder_utilization());
            emit pstate_level(static_cast<unsigned>(current_gpu_->get_performance_state()));
        }
        catch (const NVMLpp::errors::error_not_supported&) {}
    }
}
