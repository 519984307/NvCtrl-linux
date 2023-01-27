#include <QProcess>
#include <QDebug>

#include "nvmlpp/util/nvmlpp_errors.hpp"
#include "gpu_clock_controller.hpp"

constexpr const char* NVIDIA_SETTINGS_BIN {"/usr/bin/nvidia-settings"};
constexpr const char* NVIDIA_SETTINGS_GPU_CLOCK_OFFSET {"[gpu:%1]/GPUGraphicsClockOffset[%2]=%3"};
constexpr const char* NVIDIA_SETTINGS_MEM_CLOCK_OFFSET {"[gpu:%1]/GPUMemoryTransferRateOffset[%2]=%3"};



GpuClockController::GpuClockController(QObject* parrent)
    : QObject {parrent}
    , current_gpu_ {nullptr}
{ }



void GpuClockController::set_device(const NVMLpp::NVML_device* nvml_device) noexcept
{
    current_gpu_ = nvml_device;
}



void GpuClockController::apply_clock_profile(const nlohmann::json& clock_offset_profile)
{
    const auto& gpu_offsets = clock_offset_profile["offset_values"]["gpu_offsets"];
    const auto& mem_offsets = clock_offset_profile["offset_values"]["memory_offsets"];

    QStringList args {};
    const auto construct_arg_list {
        [&args, this](const char* attribute, const nlohmann::json& value) {
            const auto [index, gpu_clock_offset] {value.get<std::pair<int, int>>()};
            args.append(QStringLiteral("-a"));
            args.append(QString{attribute}
                        .arg(current_gpu_->get_index())
                        .arg(index)
                        .arg(gpu_clock_offset));
        }
    };

    for (const auto& offset : gpu_offsets)
    {
        construct_arg_list(NVIDIA_SETTINGS_GPU_CLOCK_OFFSET, offset);
    }

    for (const auto& offset : mem_offsets)
    {
        construct_arg_list(NVIDIA_SETTINGS_MEM_CLOCK_OFFSET, offset);
    }

    run_nvidia_settings(std::move(args));
}



void GpuClockController::reset_clocks()
{
    QStringList args {};
    for (unsigned i {0}; i < PSTATE_COUNT; i++)
    {
        args.append(QStringLiteral("-a"));
        args.append(QString{NVIDIA_SETTINGS_GPU_CLOCK_OFFSET}
                    .arg(current_gpu_->get_index())
                    .arg(i)
                    .arg(0));

        args.append(QStringLiteral("-a"));
        args.append(QString{NVIDIA_SETTINGS_MEM_CLOCK_OFFSET}
                    .arg(current_gpu_->get_index())
                    .arg(i)
                    .arg(0));
    }
    run_nvidia_settings(std::move(args));
}



void GpuClockController::update_info()
{
    try
    {
        clock_values clock_values_ {
            .graphics = current_gpu_->get_clock_graphics(),
            .video = current_gpu_->get_clock_video(),
            .sm = current_gpu_->get_clock_sm(),
            .memory = current_gpu_->get_clock_memory()
        };
        emit info_ready(clock_values_);
    }
    catch (const NVMLpp::errors::error_not_supported&)
    {
        emit error_occured();
    }
}



void GpuClockController::run_nvidia_settings(QStringList&& args)
{
    auto err_code {QProcess::execute(NVIDIA_SETTINGS_BIN, args)};
    if (err_code == 0)
    {
        qInfo().noquote().nospace() << "Options applied: " << args << " " << " for current gpu";
    }
    else
    {
        qCritical().nospace().noquote() << "Failed to apply " << args << " for current gpu";
    }
}
